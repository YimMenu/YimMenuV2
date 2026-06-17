from enum import global_enum_repr
import json

natives = {}
current_idx = 0
hash_list = []

class Arg:
    def __init__(self, name: str, type: str):
        self.name = name.replace("...", "varargs")
        self.type = type.replace("Any*", "void*")

        if (self.type == ""):
            self.type = "Args&&..."

    def __str__(self) -> str:
        return str(self.type) + " " + str(self.name)

class NativeFunc:
    def __init__(self, namespace: str, name: str, hash: int, args: list[dict], return_type: str):
        global current_idx, hash_list

        self.namespace = namespace
        self.name = name
        self.hash = hash
        self.args: list[Arg] = []
        self.return_type = return_type.replace("Any*", "void*")
        self.native_index = current_idx
        self.variadic = False
        current_idx += 1
        hash_list.append(hash)

        self.fix_vectors = "false"

        for arg in args:
            if (arg["name"] == "..."):
                self.variadic = True
            if arg["type"] == "Vector3*":
                self.fix_vectors = "true"
            self.args.append(Arg(arg["name"], arg["type"]))
    
    def get_native_def_str(self) -> str:
        assert self.native_index != -1

        param_decl = ""
        param_pass = ""
        if len(self.args) > 0:
            for arg in self.args:
                param_decl += str(arg) + ", "
                if arg.name == "varargs":
                    param_pass += arg.name + "..., "
                else:
                    param_pass += arg.name + ", "
            param_decl = param_decl[:-2]
            param_pass = param_pass[:-2]
        
        var_template = ""
        if self.variadic:
            var_template = "template <typename... Args> "

        return f"{var_template}FORCEINLINE constexpr {self.return_type} {self.name}({param_decl}) {{ return YimMenu::NativeInvoker::Invoke<{self.native_index}, {self.return_type}, {self.fix_vectors}>({param_pass}); }}"
    
def load_natives_data():
    global natives

    data = json.load(open("natives_gen9.json"))
    for ns, natives_list in data.items():
        natives[ns] = []
        for hash_str, native_data in natives_list.items():
            natives[ns].append(NativeFunc(ns, native_data["name"], int(hash_str, 16), native_data["params"], native_data["return_type"]))

def write_crossmap_header():
        open("Crossmap.hpp", "w+").write(f"""#pragma once
#include "types/script/scrNativeHandler.hpp"

namespace YimMenu
{{
	constexpr std::array<rage::scrNativeHash, {len(hash_list)}> g_Crossmap = {{{",".join([f"0x{x:X}" for x in hash_list])}}};
}}
""")

def load_crossmap_data():
    data = open("crossmap.txt").readlines()
    for item in data:
        translation = item.split(",")
        old = int(translation[0], 16)
        new = int(translation[1], 16)
        try:
            hash_list[hash_list.index(old)] = new
        except Exception as e:
            pass

def write_natives_header():
    natives_buf = ""
    natives_index_buf = ""

    for ns, nvs in natives.items():
        natives_buf += f"namespace {ns}\n{{\n"
        for nat_data in nvs:
            if nat_data.native_index == -1:
                continue

            natives_buf += f"\t{nat_data.get_native_def_str()}\n"
            natives_index_buf += f"\t{nat_data.name} = {nat_data.native_index},\n"
        natives_buf += "}\n\n"
    
    natives_buf = natives_buf[:-2]

    open("../Natives.hpp", "w+").write(f"""#pragma once
#include "invoker/Invoker.hpp"
#include "types/script/types.hpp"

// clang-format off
enum class NativeIndex
{{
{natives_index_buf}}};

{natives_buf}
// clang-format on
""")

# make sure we block obvious footguns
lua_blacklist = {
    "WAIT": "Use script.yield instead",
    "REGISTER_SCRIPT_VARIABLE": "Not allowed",
    "UNREGISTER_SCRIPT_VARIABLE": "Not allowed",
    "FORCE_CHECK_SCRIPT_VARIABLES": "Not allowed",
    "NETWORK_DELETE_CHARACTER": "Not allowed",
    "NETWORK_MANUAL_DELETE_CHARACTER": "Not allowed",
    "NET_GAMESERVER_DELETE_CHARACTER": "Not allowed",
    "NETWORK_REPORT_CODE_TAMPER": "Not allowed",
    "ADD_OWNED_EXPLOSION": "ADD_OWNED_EXPLOSION is no longer safe to use",
    # more telemetry
    "START_BEING_BOSS": "Not allowed",
    "START_BEING_GOON": "Not allowed",
    "END_BEING_BOSS": "Not allowed",
    "END_BEING_GOON": "Not allowed",
    "HIRED_LIMO": "Not allowed",
    "ORDER_BOSS_VEHICLE": "Not allowed",
    "CHANGE_UNIFORM": "Not allowed",
    "CHANGE_GOON_LOOKING_FOR_WORK": "Not allowed",
    "SEND_METRIC_GHOSTING_TO_PLAYER": "Not allowed",
    "SEND_METRIC_VIP_POACH": "Not allowed",
    "SEND_METRIC_PUNISH_BODYGUARD": "Not allowed",
}

def get_blacklist_reason(native: str):
    if native in lua_blacklist:
        return lua_blacklist[native]
    #if "PLAYSTATS" in native:
    #    return "Not allowed"
    return None

def native_type_to_lua_type(type: str):
    if type == "void":
        return "n" # nothing
    elif type == "const char*" or type == "char*":
        return "s" # string
    elif type == "int" or type == "Any":
        return "i" # int
    elif type == "Hash":
        return "h" # hash
    elif type == "float":
        return "f" # float
    elif type == "BOOL":
        return "b" # boolean
    elif type == "Vector3" or type == "Vector3*":
        return "v" # vector
    elif "*" in type:
        return "p" # pointer
    else:
        return "i" # Ped, Entity, etc.


def generate_lua_func_signature(native: NativeFunc):
    sig = ""
    n = 0
    for arg in native.args:
        sig += chr(97 + n) + ","
        n += 1
        if n >= 26:
            n = -32 # switch to uppercase letters (97 - 30 = A)
    sig = sig[:-1]
    return sig

def generate_lua_param_string(native: NativeFunc):
    string = ""
    for arg in native.args:
        string += native_type_to_lua_type(arg.type)
    string += "=" + native_type_to_lua_type(native.return_type)
    return string

def create_lua_func(native: NativeFunc):
    blacklist_reason = get_blacklist_reason(native.name)
    sign = generate_lua_func_signature(native)
    if sign != "":
        sign = ","+sign
    using_varargs = len(native.args) > 2
    if blacklist_reason:
        return f"{native.name}=function()error('{blacklist_reason}')end,"
    return f"{native.name}=function({"..." if using_varargs else generate_lua_func_signature(native)}){"" if native.return_type == "void" else "return "}_I({native.native_index},'{generate_lua_param_string(native)}'{",..." if using_varargs else sign})end,"

# does MSVC still live in the 2000s?
def chunkstring(string, length):
    return (string[0+i:length+i] for i in range(0, len(string), length))

def create_lua_namespace(name: str, natives: list[NativeFunc]):
    string = f"{name}={{"
    for native in natives:
        string += create_lua_func(native)
    string = string[:-1] + "}"
    chunks = chunkstring(string, 15000)
    real_string = "\t"
    for chunk in chunks:
        real_string += '"' + chunk + '"'
    real_string += ",\n"
    return real_string

def create_lua_defs():
    with open("../../scripting/libraries/NativeDefs.cpp", "w+") as file:
        string = "#include \"NativeDefs.hpp\"\n\nconst char* g_LuaNativeDefs[] = \n{\n"
        for ns, natives_list in natives.items():
            string += create_lua_namespace(ns, natives_list)
        string += f"}};\n\nint g_NumLuaNativeDefs = {len(natives.items())};"
        file.write(string)

LUA_KEYWORDS = {
    "and", "break", "do", "else", "elseif", "end", "false", "for", "function",
    "goto", "if", "in", "local", "nil", "not", "or", "repeat", "return",
    "then", "true", "until", "while",
}

INTEGER_TYPES = {
    "int", "Any", "Hash", "Ped", "Vehicle", "Entity", "Object", "Player",
    "Blip", "Cam", "FireId", "Interior", "Pickup", "ScrHandle",
}

def native_type_to_luals(native_type: str, is_return: bool) -> str | None:
    """Maps a native C type to a LuaLS type annotation. Returns None for `void`
    return types so the caller can omit the @return tag."""
    if native_type == "void":
        return None if is_return else "any"
    if native_type in ("const char*", "char*"):
        return "string"
    if native_type == "Hash":
        # Hash arguments accept either a joaat'd string or an integer hash;
        # natives return the integer form.
        return "integer" if is_return else "integer|string"
    if native_type in INTEGER_TYPES:
        return "integer"
    if native_type == "BOOL":
        return "boolean"
    if native_type == "float":
        return "number"
    if native_type in ("Vector3", "Vector3*"):
        return "Vector3"
    if "*" in native_type:
        # `T*` arguments accept a `pointer` userdata (see core/scripting/
        # libraries/Pointer.cpp) or nil for NULL. Returned pointers come
        # back as `pointer` too.
        return "pointer" if is_return else "pointer|nil"
    return "integer"

def sanitize_lua_param_name(name: str) -> str:
    if not name:
        return "_"
    if name in LUA_KEYWORDS or name[0].isdigit():
        return f"p_{name}"
    return name

def generate_lua_native_stub(native: NativeFunc) -> str:
    lines = []
    blacklist_reason = get_blacklist_reason(native.name)
    if blacklist_reason:
        lines.append(f"---@deprecated {blacklist_reason}")

    param_names: list[str] = []
    for arg in native.args:
        if arg.name == "varargs":
            lines.append("---@param ... any")
            param_names.append("...")
        else:
            p_name = sanitize_lua_param_name(arg.name)
            lines.append(f"---@param {p_name} {native_type_to_luals(arg.type, False)}")
            param_names.append(p_name)

    ret = native_type_to_luals(native.return_type, True)
    if ret is not None:
        lines.append(f"---@return {ret}")

    lines.append(f"function {native.namespace}.{native.name}({', '.join(param_names)}) end")
    return "\n".join(lines)

def create_luals_natives():
    out_path = "../../../../docs/natives.lua"
    with open(out_path, "w+", encoding="utf-8") as file:
        file.write("---@meta\n")
        file.write("--- GTA native definitions for LuaLS / EmmyLua.\n")
        file.write("---\n")
        file.write("--- Each native namespace is a global table populated by `natives.load_natives()`.\n")
        file.write("--- Blacklisted natives are marked `---@deprecated`\n")
        file.write("\n")

        for ns, natives_list in natives.items():
            file.write("-- ============================================================\n")
            file.write(f"-- {ns}\n")
            file.write("-- ============================================================\n\n")
            file.write(f"---@class natives.{ns}\n")
            file.write(f"{ns} = {{}}\n\n")
            for native in natives_list:
                file.write(generate_lua_native_stub(native))
                file.write("\n\n")

if __name__ == "__main__":
    load_natives_data()
    load_crossmap_data()
    write_crossmap_header()
    write_natives_header()
    create_lua_defs()
    create_luals_natives()