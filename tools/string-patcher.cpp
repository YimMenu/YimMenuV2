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
    {"YimMenuV2", 9, 0},
    {"yimmenu",   8, 0},
    {"YimMenu",   7, 0},
    {"Yim",       3, 0},
    {"yim",       3, 0},
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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.dll output.dll\n", argv[0]);
        return 1;
    }

    srand((unsigned int)time(nullptr));
    auto buf = readFile(argv[1]);
    size_t patched = 0;

    for (size_t t = 0; t < g_numTargets; t++) {
        auto& target = g_targets[t];
        uint8_t key = target.key ? target.key : (uint8_t)((rand() % 255) + 1);

        size_t pos = 0;
        while ((pos = buf_find(buf, (const uint8_t*)target.search, target.len, pos)) != std::string::npos) {
            for (size_t i = 0; i < target.len; i++) {
                buf[pos + i] ^= key;
            }
            patched++;
            pos += target.len;
        }
    }

    // Null out PDB path references
    const char* pdbStr = "YimMenuV2.pdb";
    size_t pdbLen = strlen(pdbStr);
    size_t pos = 0;
    while ((pos = buf_find(buf, (const uint8_t*)pdbStr, pdbLen, pos)) != std::string::npos) {
        std::memset(buf.data() + pos, 0, pdbLen);
        patched++;
        pos += pdbLen;
    }

    writeFile(argv[2], buf);
    printf("Patched %zu occurrences. Output: %s\n", patched, argv[2]);
    return 0;
}
