// tools/string-patcher.cpp
// Post-build tool: scans compiled DLL for known strings, XOR-obfuscates them.
// Win32-only, runs in CI after build.
//
// Usage: string-patcher.exe input.dll output.dll

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

struct PatchTarget {
    const char* search;
    size_t      len;
    uint8_t     key;    // 0 = generate random key per build
};

static PatchTarget g_targets[] = {
    {"yimmenu",   8, 0},
    {"YimMenu",   7, 0},
};

static const size_t g_numTargets = sizeof(g_targets) / sizeof(g_targets[0]);

static size_t buf_find(const std::vector<uint8_t>& buf, const uint8_t* needle,
                       size_t needleLen, size_t start) {
    if (needleLen == 0 || start + needleLen > buf.size())
        return std::string::npos;
    for (size_t i = start; i <= buf.size() - needleLen; i++) {
        if (memcmp(buf.data() + i, needle, needleLen) == 0)
            return i;
    }
    return std::string::npos;
}

static std::vector<uint8_t> readFile(const char* path) {
    HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: Cannot open %s (error %lu)\n", path, GetLastError());
        exit(1);
    }
    DWORD size = GetFileSize(h, nullptr);
    std::vector<uint8_t> buf(size);
    DWORD read = 0;
    if (!ReadFile(h, buf.data(), size, &read, nullptr) || read != size) {
        fprintf(stderr, "Error: Cannot read %s\n", path);
        CloseHandle(h);
        exit(1);
    }
    CloseHandle(h);
    return buf;
}

static void writeFile(const char* path, const std::vector<uint8_t>& buf) {
    HANDLE h = CreateFileA(path, GENERIC_WRITE, 0, nullptr,
                           CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: Cannot write %s (error %lu)\n", path, GetLastError());
        exit(1);
    }
    DWORD written = 0;
    if (!WriteFile(h, buf.data(), (DWORD)buf.size(), &written, nullptr)) {
        fprintf(stderr, "Error: Cannot write %s\n", path);
        CloseHandle(h);
        exit(1);
    }
    CloseHandle(h);
}

// Get list of byte ranges to scan (only PE data sections, skip .text)
static std::vector<std::pair<size_t, size_t>> getScanRanges(const std::vector<uint8_t>& buf)
{
    std::vector<std::pair<size_t, size_t>> ranges;

    if (buf.size() < 0x100)
        return ranges;

    // Parse DOS header
    const auto dos = (const IMAGE_DOS_HEADER*)buf.data();
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return ranges; // not a PE file, scan entire file

    // Parse NT headers
    const auto nt  = (const IMAGE_NT_HEADERS*)(buf.data() + dos->e_lfanew);
    const auto opt = &nt->OptionalHeader;

    // Determine section header offset (PE32 vs PE32+)
    DWORD sectionOffset;
    WORD  sectionSize;
    if (opt->Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        sectionOffset = dos->e_lfanew + FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) + sizeof(IMAGE_OPTIONAL_HEADER64);
        sectionSize   = sizeof(IMAGE_SECTION_HEADER);
    } else if (opt->Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        sectionOffset = dos->e_lfanew + FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) + sizeof(IMAGE_OPTIONAL_HEADER32);
        sectionSize   = sizeof(IMAGE_SECTION_HEADER);
    } else {
        return ranges;
    }

    WORD numSections = nt->FileHeader.NumberOfSections;
    for (WORD i = 0; i < numSections; i++) {
        const auto section = (const IMAGE_SECTION_HEADER*)(buf.data() + sectionOffset + i * sectionSize);

        // Skip executable sections — patching code corrupts the DLL
        if (section->Characteristics & IMAGE_SCN_MEM_EXECUTE)
            continue;

        // Skip directories that don't contain string data
        if (!(section->Characteristics & IMAGE_SCN_MEM_READ))
            continue;

        DWORD offset = section->PointerToRawData;
        DWORD size   = section->SizeOfRawData;

        if (offset > 0 && size > 0 && offset + size <= buf.size()) {
            ranges.emplace_back(offset, size);
        }
    }

    // Fallback: if no data sections found, scan whole file
    if (ranges.empty())
        ranges.emplace_back(0, buf.size());

    return ranges;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.dll output.dll\n", argv[0]);
        return 1;
    }

    srand((unsigned int)time(nullptr));
    auto buf = readFile(argv[1]);
    auto ranges = getScanRanges(buf);
    size_t totalPatched = 0;

    printf("Scanning %zu section(s)\n", ranges.size());

    for (size_t t = 0; t < g_numTargets; t++) {
        auto& target = g_targets[t];

        // PDB path: null it out instead of XOR
        if (target.len == 13 && memcmp(target.search, "YimMenuV2.pdb", 13) == 0) {
            size_t patched = 0;
            for (auto& [start, len] : ranges) {
                size_t end = start + len;
                size_t pos = start;
                while ((pos = buf_find(buf, (const uint8_t*)target.search, target.len, pos)) != std::string::npos
                       && pos < end) {
                    std::memset(buf.data() + pos, 0, target.len);
                    patched++;
                    pos += target.len;
                }
            }
            if (patched)
                printf("  PDB path: %zu occurrence(s) nulled\n", patched);
            totalPatched += patched;
            continue;
        }

        uint8_t key = (uint8_t)((rand() % 255) + 1);
        size_t patched = 0;

        for (auto& [start, len] : ranges) {
            size_t end = start + len;
            size_t pos = start;
            while ((pos = buf_find(buf, (const uint8_t*)target.search, target.len, pos)) != std::string::npos
                   && pos < end) {
                for (size_t i = 0; i < target.len; i++) {
                    buf[pos + i] ^= key;
                }
                patched++;
                pos += target.len;
            }
        }

        if (patched)
            printf("  \"%s\": %zu occurrence(s) patched (key 0x%02X)\n", target.search, patched, key);
        totalPatched += patched;
    }

    writeFile(argv[2], buf);
    printf("Total: %zu occurrence(s) patched across %zu section(s)\n", totalPatched, ranges.size());
    return 0;
}
