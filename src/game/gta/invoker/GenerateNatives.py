import json

crossmap = {}
natives = {}
current_idx = 0
crossmap_hash_list = []

class Arg:
    def __init__(self, name: str, type: str):
        self.name = name
        self.type = type.replace("BOOL", "bool").replace("Any*", "void*")

    def __str__(self) -> str:
        return str(self.type) + " " + str(self.name)

class NativeFunc:
    def __init__(self, namespace: str, name: str, hash: int, args: list[dict], return_type: str):
        self.namespace = namespace
        self.name = name
        self.hash = hash
        self.args: list[Arg] = []
        self.return_type = return_type.replace("BOOL", "bool").replace("Any*", "void*")
        self.native_index = -1

        for arg in args:
            self.args.append(Arg(arg["name"], arg["type"]))
    
    def get_native_def_str(self) -> str:
        assert self.native_index != -1

        param_decl = ""
        param_pass = ""
        if len(self.args) > 0:
            for arg in self.args:
                param_decl += str(arg) + ", "
                param_pass += arg.name + ", "
            param_decl = param_decl[:-2]
            param_pass = param_pass[:-2]
        
        return f"FORCEINLINE constexpr {self.return_type} {self.name}({param_decl}) {{ return YimMenu::NativeInvoker::Invoke<{self.native_index}, {self.return_type}>({param_pass}); }}"

class CrossmapEntry:
    def __init__(self, translated_hash: int):
        self.hash = translated_hash
        self.native_index = -1

def load_crossmap_data():
    global crossmap

    data = open("crossmap.txt").readlines()
    for item in data:
        translation = item.split(",")
        crossmap[int(translation[0], 16)] = CrossmapEntry(int(translation[1], 16))

def load_natives_data():
    global natives

    data = json.load(open("natives.json"))
    for ns, natives_list in data.items():
        natives[ns] = []
        for hash_str, native_data in natives_list.items():
            natives[ns].append(NativeFunc(ns, native_data["name"], int(hash_str, 16), native_data["params"], native_data["return_type"]))

def allocate_indices():
    global current_idx, crossmap_hash_list

    for _, n in natives.items():
        for native in n:
            hash = native.hash
            if hash in crossmap:
                crossmap[hash].native_index = current_idx
                native.native_index = current_idx
                crossmap_hash_list.append(crossmap[hash].hash)
                current_idx += 1


def write_crossmap_header():
        open("Crossmap.hpp", "w+").write(f"""#pragma once
#include <script/scrNativeHandler.hpp>

namespace YimMenu
{{
	constexpr std::array<rage::scrNativeHash, {len(crossmap_hash_list)}> g_Crossmap = {{{",".join([f"0x{x:X}" for x in crossmap_hash_list])}}};
}}
""")

def write_natives_header():
    natives_buf = ""

    for ns, nvs in natives.items():
        natives_buf += f"namespace {ns}\n{{\n"
        for nat_data in nvs:
            if nat_data.native_index == -1:
                continue

            natives_buf += f"\t{nat_data.get_native_def_str()}\n"
        natives_buf += "}\n\n"
    
    natives_buf = natives_buf[:-2]
    open("../Natives.hpp", "w+").write(f"""#pragma once
#include "invoker/Invoker.hpp"

// clang-format off
{natives_buf}
// clang-format on
""")
    
if __name__ == "__main__":
    load_crossmap_data()
    load_natives_data()
    allocate_indices()
    write_crossmap_header()
    write_natives_header()