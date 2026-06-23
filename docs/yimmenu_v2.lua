---@meta
--- YimMenuV2 Lua API definitions for the Lua Language Server (sumneko / LuaLS).
---
--- This file is annotations only — it is never executed. Point your language
--- server at it for autocompletion and type checking, e.g. in `.luarc.json`:
---     { "workspace.library": [ "path/to/docs" ] }
---
--- See docs/lua-api.md for prose descriptions. Natives loaded via
--- `natives.load_natives()` are listed in docs/natives.lua.

------------------------------------------------------------------------------
-- Vector3
------------------------------------------------------------------------------

---@class Vector3
---@field x number
---@field y number
---@field z number
---@overload fun(x: number, y: number, z: number): Vector3
---@overload fun(): Vector3
Vector3 = {}

---@param x? number
---@param y? number
---@param z? number
---@return Vector3
function Vector3.new(x, y, z) end

---@return number x, number y, number z
function Vector3:get_coords() end

---@return number
function Vector3:get_x() end
---@return number
function Vector3:get_y() end
---@return number
function Vector3:get_z() end

---@param value number
function Vector3:set_x(value) end
---@param value number
function Vector3:set_y(value) end
---@param value number
function Vector3:set_z(value) end

---@param other Vector3
---@return number
function Vector3:get_distance(other) end

---@return boolean
function Vector3:is_zero() end

------------------------------------------------------------------------------
-- notify
------------------------------------------------------------------------------

notify = {}

---@param title string
---@param message string
---@param duration? integer # milliseconds, default 5000
function notify.success(title, message, duration) end
---@param title string
---@param message string
---@param duration? integer
function notify.info(title, message, duration) end
---@param title string
---@param message string
---@param duration? integer
function notify.warn(title, message, duration) end
---@param title string
---@param message string
---@param duration? integer
function notify.error(title, message, duration) end

------------------------------------------------------------------------------
-- log
------------------------------------------------------------------------------

log = {}

---@param message string
function log.verbose(message) end
---@param message string
function log.info(message) end
---@param message string
function log.warn(message) end
---@param message string
function log.error(message) end
---@param message string
function log.trace(message) end

------------------------------------------------------------------------------
-- util
------------------------------------------------------------------------------

util = {}

---@param str string
---@return integer
function util.joaat(str) end

---Current Unix time in milliseconds.
---@return integer
function util.time() end

------------------------------------------------------------------------------
-- script
------------------------------------------------------------------------------

script = {}

---@param fn fun()
function script.run_in_callback(fn) end

---Yield the current callback for at least `ms` milliseconds (default 0 = one frame).
---@param ms? integer
function script.yield(ms) end

---@return boolean
function script.is_inside_callback() end

------------------------------------------------------------------------------
-- event
------------------------------------------------------------------------------

---@class menu_event
---@field PlayerLeave integer
---@field PlayerJoin integer
---@field ScriptedGameEventReceived integer
---@field ChatMessageReceived integer
---@field Unload integer
menu_event = {}

event = {}

---@param menu_event integer # a `menu_event.*` constant
---@param handler fun(...)
function event.register_handler(menu_event, handler) end

------------------------------------------------------------------------------
-- menu (UI builders)
------------------------------------------------------------------------------

---@class Submenu
local Submenu = {}

---@class Category
local Category = {}

---@class Group
local Group = {}

menu = {}

---@param name string
function menu.set_menu_name(name) end
---@param icon string
function menu.set_menu_icon(icon) end
---@return string
function menu.get_menu_name() end
---@param name? string
---@return Submenu
function menu.get_submenu(name) end
---@param name string
---@return Submenu?
function menu.find_submenu(name) end
---@param name string
---@param per_row? integer # default 7
---@return Group
function menu.create_group(name, per_row) end
---@return boolean
function menu.is_open() end
function menu.toggle() end

---@param name string
---@return Category
function Submenu:add_category(name) end
---@param name string
---@return Category?
function Submenu:find_category(name) end

---@param name string
---@param per_row? integer # default 7
---@return Group
function Category:add_group(name, per_row) end
---@param name string
---@return Group?
function Category:find_group(name) end
---Register a raw ImGui draw callback rendered every frame.
---@param fn fun()
function Category:imgui(fn) end

---@param name string
function Group:add_command(name) end
---@param name string
function Group:add_bool_command(name) end
---@param name string
---@param slider? boolean # default true
function Group:add_int_command(name, slider) end
---@param name string
---@param slider? boolean # default true
function Group:add_float_command(name, slider) end
---@param name string
function Group:add_list_command(name) end
---@param name string
---@param label string
---@param desc? string
---@param fn fun()
---@return CommandHandle
function Group:add_button(name, label, desc, fn) end
---@param name string
---@param label string
---@param desc? string
---@param default? boolean
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function Group:add_checkbox(name, label, desc, default, on_enable, on_disable) end
---@param name string
---@param label string
---@param desc? string
---@param tick fun()
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function Group:add_looped_checkbox(name, label, desc, tick, on_enable, on_disable) end
---Register a raw ImGui draw callback inside the group.
---@param fn fun()
function Group:imgui(fn) end
---Manually render the group (for standalone groups inside an `imgui` callback).
function Group:draw() end

------------------------------------------------------------------------------
-- commandmgr
------------------------------------------------------------------------------

---@class CommandHandle
local CommandHandle = {}

---@return boolean|integer|number|nil
function CommandHandle:get_value() end
---@param value boolean|integer|number
function CommandHandle:set_value(value) end
---@return string
function CommandHandle:get_name() end
---@return string
function CommandHandle:get_desc() end
---Draw the command (call from inside an ImGui callback).
function CommandHandle:draw() end

commandmgr = {}

---@param name string
---@param label string
---@param desc string
---@param on_call fun()
---@return CommandHandle
function commandmgr.add_command(name, label, desc, on_call) end
---@param name string
---@param label string
---@param desc string
---@param default? boolean
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function commandmgr.add_bool_command(name, label, desc, default, on_enable, on_disable) end
---@param name string
---@param label string
---@param desc string
---@param tick fun()
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function commandmgr.add_looped_command(name, label, desc, tick, on_enable, on_disable) end
---@param name string
---@param label string
---@param desc string
---@param min? integer
---@param max? integer
---@param default? integer
---@param on_change? fun(value: integer)
---@return CommandHandle
function commandmgr.add_int_command(name, label, desc, min, max, default, on_change) end
---@param name string
---@param label string
---@param desc string
---@param min? number
---@param max? number
---@param default? number
---@param on_change? fun(value: number)
---@return CommandHandle
function commandmgr.add_float_command(name, label, desc, min, max, default, on_change) end
---@param name string
---@param label string
---@param desc string
---@param entries table<integer, [integer, string]> # array of { key, label } pairs
---@param default? integer
---@param on_change? fun(value: integer)
---@return CommandHandle
function commandmgr.add_list_command(name, label, desc, entries, default, on_change) end
---@param name string|integer
---@return CommandHandle?
function commandmgr.get_command(name) end

------------------------------------------------------------------------------
-- memory / pointer
------------------------------------------------------------------------------

---@class pointer
---@overload fun(addr: integer): pointer
pointer = {}

---@param addr integer
---@return pointer
function pointer.new(addr) end

---@return integer
function pointer:get_address() end
---@param addr integer
function pointer:set_address(addr) end
---@return boolean
function pointer:is_null() end
---@return boolean
function pointer:is_valid() end

---@param offset integer
---@return pointer
function pointer:add(offset) end
---@param offset integer
---@return pointer
function pointer:sub(offset) end
---@param offset? integer
---@return pointer
function pointer:rip(offset) end
---@return pointer
function pointer:deref() end

---@return integer
function pointer:get_byte() end
---@return integer
function pointer:get_word() end
---@return integer
function pointer:get_int() end
---@return integer
function pointer:get_dword() end
---@return integer
function pointer:get_qword() end
---@return number
function pointer:get_float() end
---@return string
function pointer:get_string() end

---@param value integer
function pointer:set_byte(value) end
---@param value integer
function pointer:set_word(value) end
---@param value integer
function pointer:set_int(value) end
---@param value integer
function pointer:set_dword(value) end
---@param value integer
function pointer:set_qword(value) end
---@param value number
function pointer:set_float(value) end
---@param value string
function pointer:set_string(value) end

---@param value integer
---@return patch
function pointer:patch_byte(value) end
---@param value integer
---@return patch
function pointer:patch_word(value) end
---@param value integer
---@return patch
function pointer:patch_dword(value) end
---@param value integer
---@return patch
function pointer:patch_qword(value) end

---@class patch
local patch = {}
function patch:apply() end
function patch:restore() end

memory = {}

---@param pattern string # IDA-format byte signature
---@return pointer?
function memory.scan_pattern(pattern) end
---@param entity integer
---@return pointer
function memory.handle_to_ptr(entity) end
---@param ptr pointer
---@return integer
function memory.ptr_to_handle(ptr) end
---@param size integer
---@return pointer
function memory.allocate(size) end
---@param ptr pointer
function memory.free(ptr) end

------------------------------------------------------------------------------
-- Entity
------------------------------------------------------------------------------

---@class Entity
---@overload fun(handle: integer): Entity
Entity = {}

---@param handle integer
---@return Entity
function Entity.new(handle) end

---@return integer
function Entity:get_handle() end
---@return boolean
function Entity:is_valid() end
---@return boolean
function Entity:is_ped() end
---@return boolean
function Entity:is_vehicle() end
---@return boolean
function Entity:is_object() end
---@return boolean
function Entity:is_player() end
---@return boolean
function Entity:is_mission_entity() end
---@return integer
function Entity:get_model() end

---@return Vector3
function Entity:get_position() end
---@param pos Vector3
function Entity:set_position(pos) end
---@param order? integer # default 2
---@return Vector3
function Entity:get_rotation(order) end
---@param rot Vector3
---@param order? integer # default 2
function Entity:set_rotation(rot, order) end
---@return Vector3
function Entity:get_velocity() end
---@param vel Vector3
function Entity:set_velocity(vel) end
---@return number
function Entity:get_heading() end
---@param heading number
function Entity:set_heading(heading) end
---@return number
function Entity:get_speed() end
---@param enabled boolean
function Entity:set_collision(enabled) end
---@param frozen boolean
function Entity:set_frozen(frozen) end
---@return boolean
function Entity:has_interior() end

---@return boolean
function Entity:is_networked() end
---@return boolean
function Entity:is_remote() end
---@return boolean
function Entity:has_control() end
---@return integer
function Entity:get_network_object_id() end
function Entity:prevent_migration() end
function Entity:force_control() end
---Latent: requests control of the entity.
---@param timeout? integer # milliseconds, default 100
function Entity:request_control(timeout) end

---@return boolean
function Entity:is_invincible() end
---@param enabled boolean
function Entity:set_invincible(enabled) end
---@return boolean
function Entity:is_dead() end
function Entity:kill() end
---@return integer
function Entity:get_health() end
---@param health integer
function Entity:set_health(health) end
---@return integer
function Entity:get_max_health() end
---@return boolean
function Entity:is_visible() end
---@param visible boolean
function Entity:set_visible(visible) end
---@return integer
function Entity:get_alpha() end
---@param alpha integer
function Entity:set_alpha(alpha) end
function Entity:reset_alpha() end
function Entity:delete() end

------------------------------------------------------------------------------
-- Ped : Entity
------------------------------------------------------------------------------

---@class Ped : Entity
---@overload fun(handle: integer): Ped
Ped = {}

---@param handle integer
---@return Ped
function Ped.new(handle) end

---Latent: spawns a ped.
---@param model integer|string
---@param pos Vector3
---@param heading? number # default 0
---@return Ped
function Ped.create(model, pos, heading) end

---@return Vehicle
function Ped:get_vehicle() end
---@return Vehicle
function Ped:get_last_vehicle() end
---@return integer
function Ped:get_vehicle_object_id() end
---@param vehicle Vehicle
---@param seat? integer # default 0
function Ped:set_in_vehicle(vehicle, seat) end
---@return boolean
function Ped:get_ragdoll() end
---@param enabled boolean
function Ped:set_ragdoll(enabled) end
---@param bone integer
---@return Vector3
function Ped:get_bone_position(bone) end
---@return boolean
function Ped:is_enemy() end
---@return integer
function Ped:get_accuracy() end
---@param accuracy integer
function Ped:set_accuracy(accuracy) end
---@param weapon integer|string
---@param equip? boolean # default false
function Ped:give_weapon(weapon, equip) end
---@param weapon integer|string
function Ped:remove_weapon(weapon) end
---@return integer
function Ped:get_current_weapon() end
---@param weapon integer|string
---@return boolean
function Ped:has_weapon(weapon) end
---@param enabled boolean
function Ped:set_infinite_ammo(enabled) end
---@param enabled boolean
function Ped:set_infinite_clip(enabled) end
---@param weapon integer|string
function Ped:set_max_ammo_for_weapon(weapon) end
---@param pos Vector3
function Ped:teleport_to(pos) end
---@return integer
function Ped:get_armour() end
---@param armour integer
function Ped:set_armour(armour) end
---@param group integer
function Ped:set_leader_of_group(group) end
---@param group integer
function Ped:add_to_group(group) end
function Ped:remove_from_group() end
---@param group integer
---@return boolean
function Ped:is_member_of_group(group) end
function Ped:randomize_outfit() end
---@param name string
---@param duration? integer # default -1
---@param play_anim? boolean # default true
function Ped:start_scenario(name, duration, play_anim) end
---@param enabled boolean
function Ped:set_keep_task(enabled) end
function Ped:clear_damage() end
---@param time integer # seconds
function Ped:set_max_time_underwater(time) end
function Ped:set_as_cop() end

------------------------------------------------------------------------------
-- Vehicle : Entity
------------------------------------------------------------------------------

---@class Vehicle : Entity
---@overload fun(handle: integer): Vehicle
Vehicle = {}

---@param handle integer
---@return Vehicle
function Vehicle.new(handle) end

---Latent: spawns a vehicle.
---@param model integer|string
---@param pos Vector3
---@param heading? number # default 0
---@return Vehicle
function Vehicle.create(model, pos, heading) end

function Vehicle:fix() end
---@return integer
function Vehicle:get_gear() end
---@return number
function Vehicle:get_rev_ratio() end
---@return number
function Vehicle:get_speed() end
function Vehicle:upgrade() end
---@return string
function Vehicle:get_plate_text() end
---@param text string
function Vehicle:set_plate_text(text) end
---@param seat integer
---@return boolean
function Vehicle:is_seat_free(seat) end
---@return boolean
function Vehicle:supports_boost() end
---@return boolean
function Vehicle:is_boost_active() end
---@param charge? integer # default 100
function Vehicle:set_boost_charge(charge) end
---@param enabled boolean
function Vehicle:lower_stance(enabled) end
---@param distance number
---@param time integer
function Vehicle:bring_to_halt(distance, time) end
---@return boolean
function Vehicle:set_on_ground_properly() end
---@return string
function Vehicle:get_full_name() end

------------------------------------------------------------------------------
-- entities
------------------------------------------------------------------------------

entities = {}

---@return integer[]
function entities.get_all_vehicles_as_handles() end
---@return integer[]
function entities.get_all_peds_as_handles() end
---@return integer[]
function entities.get_all_objects_as_handles() end

------------------------------------------------------------------------------
-- Player / players
------------------------------------------------------------------------------

---@class Player
---@overload fun(id: integer): Player
Player = {}

---@param id integer
---@return Player
function Player.new(id) end

---@return boolean
function Player:is_valid() end
---@return boolean
function Player:is_local() end
---@return boolean
function Player:is_host() end
---@return boolean
function Player:is_modder() end
---@return integer
function Player:get_id() end
---@return string
function Player:get_name() end
---@return Ped
function Player:get_ped() end
---@return integer
function Player:get_message_id() end
---@return integer
function Player:get_rid() end
---@return string address, integer port
function Player:get_external_address() end
---@return string address, integer port
function Player:get_internal_address() end
---@return number
function Player:get_average_latency() end
---@return number
function Player:get_average_packet_loss() end
---@return integer
function Player:get_rank() end
---@return integer
function Player:get_rp() end
---@return integer
function Player:get_money() end
---@return integer
function Player:get_wanted_level() end
---@param level integer
function Player:set_wanted_level(level) end
---@return integer
function Player:get_max_armour() end
---@return integer
function Player:get_group() end
---@param visible boolean
function Player:set_visible_locally(visible) end
---@param pos Vector3
function Player:teleport_to(pos) end
---@param distance number
function Player:set_fall_distance_override(distance) end
---@param ped Ped
---@param delete_old? boolean # default true
function Player:set_ped(ped, delete_old) end

players = {}

---@return Player[]
function players.get_all() end
---@return Player
function players.get_local() end
---@return Player
function players.get_selected() end
---@param player Player
function players.set_selected(player) end
---@param rid integer
---@return Player
function players.get_by_rid(rid) end
---@param message_id integer
---@return Player
function players.get_by_message_id(message_id) end
---@return Player
function players.get_random() end

------------------------------------------------------------------------------
-- ScriptGlobal
------------------------------------------------------------------------------

---@class ScriptGlobal
---@overload fun(index: integer): ScriptGlobal
ScriptGlobal = {}

---@param index integer
---@return ScriptGlobal
function ScriptGlobal.new(index) end

---@param offset integer
---@param size? integer # array stride multiplier
---@return ScriptGlobal
function ScriptGlobal:at(offset, size) end
---@return boolean
function ScriptGlobal:can_access() end
---@return integer
function ScriptGlobal:get_int() end
---@return number
function ScriptGlobal:get_float() end
---@return string?
function ScriptGlobal:get_string() end
---@return Vector3
function ScriptGlobal:get_vector3() end
---@param value integer
function ScriptGlobal:set_int(value) end
---@param value number
function ScriptGlobal:set_float(value) end
---@param value string
---@param max_length? integer
function ScriptGlobal:set_string(value, max_length) end
---@param value Vector3
function ScriptGlobal:set_vector3(value) end

------------------------------------------------------------------------------
-- ScriptLocal
------------------------------------------------------------------------------

---@class ScriptLocal
ScriptLocal = {}

---@param script string|integer # script name or hash
---@param index integer
---@return ScriptLocal?
function ScriptLocal.new(script, index) end

---@param offset integer
---@param size? integer
---@return ScriptLocal
function ScriptLocal:at(offset, size) end
---@return integer
function ScriptLocal:get_int() end
---@return number
function ScriptLocal:get_float() end
---@return Vector3
function ScriptLocal:get_vector3() end
---@param value integer
function ScriptLocal:set_int(value) end
---@param value number
function ScriptLocal:set_float(value) end
---@param value Vector3
function ScriptLocal:set_vector3(value) end

------------------------------------------------------------------------------
-- ScriptPointer
------------------------------------------------------------------------------

---@class ScriptPointer
---@overload fun(name: string, pattern: string, offset?: integer, rip?: boolean, address?: integer): ScriptPointer
ScriptPointer = {}

---@param name string
---@param pattern string # IDA-format signature
---@param offset? integer
---@param rip? boolean
---@param address? integer
---@return ScriptPointer
function ScriptPointer.new(name, pattern, offset, rip, address) end

---@param offset integer
---@return ScriptPointer
function ScriptPointer:add(offset) end
---@param offset integer
---@return ScriptPointer
function ScriptPointer:sub(offset) end
---@return ScriptPointer
function ScriptPointer:rip() end
---@param target string|integer
---@return ScriptPointer?
function ScriptPointer:scan(target) end
---@return integer
function ScriptPointer:get_address() end
---@return string
function ScriptPointer:get_name() end

------------------------------------------------------------------------------
-- ScriptPatch
------------------------------------------------------------------------------

---@class ScriptPatch
---@overload fun(script: string|integer, name: string, pattern: string, offset: integer|integer[], patch_bytes?: integer[]): ScriptPatch
ScriptPatch = {}

---@param script string|integer
---@param name string
---@param pattern string
---@param offset integer|integer[] # offset, or patch_bytes if omitted
---@param patch_bytes? integer[] # bytes 0-255
---@return ScriptPatch
function ScriptPatch.new(script, name, pattern, offset, patch_bytes) end

function ScriptPatch:enable() end
function ScriptPatch:disable() end
function ScriptPatch:remove() end

------------------------------------------------------------------------------
-- ScriptFunction
------------------------------------------------------------------------------

---@class ScriptFunction
---@overload fun(script: string|integer, script_pointer: ScriptPointer): ScriptFunction
ScriptFunction = {}

---@param script string|integer
---@param script_pointer ScriptPointer
---@return ScriptFunction
function ScriptFunction.new(script, script_pointer) end

---Invoke the script function.
---`param_string` arg chars: `i` int32, `f` float, `h` hash, `b` bool; optional `=<r>` return type (`n`/`i`/`f`/`b`/`h`). Example: `fn:call("ii=i", 5, 10)`.
---@param param_string string
---@param ... any
---@return any
function ScriptFunction:call(param_string, ...) end

------------------------------------------------------------------------------
-- scripts
------------------------------------------------------------------------------

scripts = {}

---@param script string|integer
---@return boolean
function scripts.is_active(script) end
---@param script string|integer
---@param callback fun()
function scripts.run_as_script(script, callback) end

------------------------------------------------------------------------------
-- natives
------------------------------------------------------------------------------

natives = {}

---Load every native namespace table (PLAYER, ENTITY, VEHICLE, ...) as globals.
function natives.load_natives() end
---@return boolean
function natives.are_natives_loaded() end

------------------------------------------------------------------------------
-- network
------------------------------------------------------------------------------

network = {}

---@param hash integer|string
---@param bits integer # target player bitset
---@param format string # chars: i/f/l/h (max 36 args)
---@param ... integer|number
function network.trigger_script_event(hash, bits, format, ...) end
---@param script_hash integer|string
function network.force_script_host(script_hash) end
---@param script_hash integer|string
---@param bits integer
function network.force_script_on_player(script_hash, bits) end
---@return boolean
function network.is_session_started() end

------------------------------------------------------------------------------
-- tunables
------------------------------------------------------------------------------

tunables = {}

---@param hash integer|string
---@param value integer
function tunables.set_int(hash, value) end
---@param hash integer|string
---@param value boolean
function tunables.set_bool(hash, value) end
---@param hash integer|string
---@param value number
function tunables.set_float(hash, value) end
---@param hash integer|string
---@return integer
function tunables.get_int(hash) end
---@param hash integer|string
---@return boolean
function tunables.get_bool(hash) end
---@param hash integer|string
---@return number
function tunables.get_float(hash) end

------------------------------------------------------------------------------
-- stats
------------------------------------------------------------------------------

stats = {}

---@param name string
---@param value integer
function stats.set_int(name, value) end
---@param name string
---@param value boolean
function stats.set_bool(name, value) end
---@param name string
---@param value number
function stats.set_float(name, value) end
---@param name string
---@param value string
function stats.set_string(name, value) end
---@param name string
---@return integer
function stats.get_int(name) end
---@param name string
---@return boolean
function stats.get_bool(name) end
---@param name string
---@return number
function stats.get_float(name) end
---@param name string
---@return string
function stats.get_string(name) end
---@param index integer
---@param value integer
function stats.set_packed_int(index, value) end
---@param index integer
---@param value boolean
function stats.set_packed_bool(index, value) end
---@param index integer
---@return integer
function stats.get_packed_int(index) end
---@param index integer
---@return boolean
function stats.get_packed_bool(index) end
---@param start integer
---@param finish integer
---@param value boolean
function stats.set_packed_bool_range(start, finish, value) end
---@param name string
---@param value integer
---@param offset integer
---@param bits integer
function stats.set_masked_int(name, value, offset, bits) end
---@param name string
---@param offset integer
---@param bits integer
---@return integer
function stats.get_masked_int(name, offset, bits) end
---@param name string
---@param offset integer
---@param value boolean
function stats.set_masked_bool(name, offset, value) end
---@param name string
---@param offset integer
---@return boolean
function stats.get_masked_bool(name, offset) end

------------------------------------------------------------------------------
-- transactions
------------------------------------------------------------------------------

---@class BasketTransaction
local BasketTransaction = {}

---@param primary integer|string
---@param secondary? integer|string
---@param value integer
---@param stat_value integer
---@param quantity integer
function BasketTransaction:add_item(primary, secondary, value, stat_value, quantity) end
---Latent: run the checkout.
---@return boolean
function BasketTransaction:run() end

transactions = {}

---@param category integer|string
---@param action integer|string
---@return BasketTransaction
function transactions.create_basket(category, action) end
---@param category integer|string
---@param action integer|string
---@param item integer|string
---@param value integer
---@return boolean
function transactions.run_service(category, action, item, value) end
---@return boolean
function transactions.can_use_transactions() end

------------------------------------------------------------------------------
-- FileMgr (sandboxed to Documents/YimMenuV2/scripts)
------------------------------------------------------------------------------

FileMgr = {}

---@return string
function FileMgr.GetMenuRootPath() end
---@param path string
---@return boolean
function FileMgr.CreateDir(path) end
---@param path string
function FileMgr.DeleteFile(path) end
---@param path string
---@return boolean
function FileMgr.DoesFileExist(path) end
---@param path string
---@param extension string
---@param recursive? boolean
---@return string[]
function FileMgr.FindFiles(path, extension, recursive) end
---@param path string
---@return string
function FileMgr.ReadFileContent(path) end
---@param path string
---@param content string
---@param append? boolean
---@return boolean
function FileMgr.WriteFileContent(path, content, append) end

------------------------------------------------------------------------------
-- internal (testing only)
------------------------------------------------------------------------------

internal = {}

---@param model string
function internal.spawn_vehicle(model) end

------------------------------------------------------------------------------
-- ImGui (used inside category:imgui / group:imgui callbacks)
--
-- Value-editing widgets return the (possibly updated) value plus a changed
-- flag, e.g. `value, changed = ImGui.Checkbox("Label", value)`. Only the most
-- commonly used functions are typed here; the full set is listed in
-- docs/lua-api.md. Flag/cond/col arguments use the ImGui* enum tables.
------------------------------------------------------------------------------

ImGui = {}

-- Windows & layout
---@param name string
---@param open? boolean
---@param flags? integer
---@return boolean, boolean
function ImGui.Begin(name, open, flags) end
function ImGui.End() end
---@param name string
---@param size_x? number
---@param size_y? number
---@param border? boolean
---@param flags? integer
---@return boolean
function ImGui.BeginChild(name, size_x, size_y, border, flags) end
---@param name string
---@param id integer  explicit ImGuiID (e.g. from ImGui.GetID)
---@param size_x? number
---@param size_y? number
---@param child_flags? integer  ImGuiChildFlags
---@param window_flags? integer  ImGuiWindowFlags
---@return boolean
function ImGui.BeginChildEx(name, id, size_x, size_y, child_flags, window_flags) end
function ImGui.EndChild() end
function ImGui.BeginGroup() end
function ImGui.EndGroup() end
function ImGui.Separator() end
---@param text string
function ImGui.SeparatorText(text) end
---@param offset? number
---@param spacing? number
function ImGui.SameLine(offset, spacing) end
function ImGui.NewLine() end
function ImGui.Spacing() end
---@param x number
---@param y number
function ImGui.Dummy(x, y) end
---@param width? number
function ImGui.Indent(width) end
---@param width? number
function ImGui.Unindent(width) end
---@param disabled? boolean
function ImGui.BeginDisabled(disabled) end
function ImGui.EndDisabled() end

-- Text
---@param text string
function ImGui.Text(text) end
---@param r number
---@param g number
---@param b number
---@param a number
---@param text string
function ImGui.TextColored(r, g, b, a, text) end
---@param text string
function ImGui.TextDisabled(text) end
---@param text string
function ImGui.TextWrapped(text) end
---@param label string
---@param text string
function ImGui.LabelText(label, text) end
---@param text string
function ImGui.BulletText(text) end

-- Buttons & toggles
---@param label string
---@param size_x? number
---@param size_y? number
---@return boolean
function ImGui.Button(label, size_x, size_y) end
---@param label string
---@return boolean
function ImGui.SmallButton(label) end
---@param label string
---@param value boolean
---@return boolean value, boolean pressed
function ImGui.Checkbox(label, value) end
---@param label string
---@param active boolean
---@return boolean
function ImGui.RadioButton(label, active) end

-- Combo / list
---@param label string
---@param preview string
---@param flags? integer
---@return boolean
function ImGui.BeginCombo(label, preview, flags) end
function ImGui.EndCombo() end
---@param label string
---@param current integer
---@param items string[]
---@param items_count integer
---@param popup_max? integer
---@return integer current, boolean changed
function ImGui.Combo(label, current, items, items_count, popup_max) end
---@param label string
---@param selected? boolean
---@param flags? integer
---@param size_x? number
---@param size_y? number
---@return boolean
function ImGui.Selectable(label, selected, flags, size_x, size_y) end

-- Sliders
---@param label string
---@param value number
---@param min number
---@param max number
---@param format? string
---@return number value, boolean used
function ImGui.SliderFloat(label, value, min, max, format) end
---@param label string
---@param value integer
---@param min integer
---@param max integer
---@param format? string
---@return integer value, boolean used
function ImGui.SliderInt(label, value, min, max, format) end

-- Drags
---@param label string
---@param value number
---@param speed? number
---@param min? number
---@param max? number
---@param format? string
---@return number value, boolean used
function ImGui.DragFloat(label, value, speed, min, max, format) end
---@param label string
---@param value integer
---@param speed? number
---@param min? integer
---@param max? integer
---@param format? string
---@return integer value, boolean used
function ImGui.DragInt(label, value, speed, min, max, format) end

-- Inputs
---@param label string
---@param text string
---@param flags? integer
---@return string text, boolean changed
function ImGui.InputText(label, text, flags) end
---@param label string
---@param hint string
---@param text string
---@param flags? integer
---@return string text, boolean changed
function ImGui.InputTextWithHint(label, hint, text, flags) end
---@param label string
---@param value number
---@param step? number
---@param step_fast? number
---@param format? string
---@param flags? integer
---@return number value, boolean used
function ImGui.InputFloat(label, value, step, step_fast, format, flags) end
---@param label string
---@param value integer
---@param step? integer
---@param step_fast? integer
---@param flags? integer
---@return integer value, boolean used
function ImGui.InputInt(label, value, step, step_fast, flags) end

-- Colors
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean used
function ImGui.ColorEdit3(label, color, flags) end
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean used
function ImGui.ColorEdit4(label, color, flags) end
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean used
function ImGui.ColorPicker3(label, color, flags) end
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean used
function ImGui.ColorPicker4(label, color, flags) end

-- Trees
---@param label string
---@param text? string
---@return boolean
function ImGui.TreeNode(label, text) end
function ImGui.TreePop() end
---@param label string
---@param flags? integer
---@return boolean
function ImGui.CollapsingHeader(label, flags) end

-- Tabs
---@param id string
---@param flags? integer
---@return boolean
function ImGui.BeginTabBar(id, flags) end
function ImGui.EndTabBar() end
---@param label string
---@return boolean
function ImGui.BeginTabItem(label) end
function ImGui.EndTabItem() end

-- Tooltips & popups
function ImGui.BeginTooltip() end
function ImGui.EndTooltip() end
---@param text string
function ImGui.SetTooltip(text) end
---@param id string
---@param flags? integer
---@return boolean
function ImGui.BeginPopup(id, flags) end
function ImGui.EndPopup() end
---@param id string
---@param flags? integer
function ImGui.OpenPopup(id, flags) end
function ImGui.CloseCurrentPopup() end

-- Item queries
---@param flags? integer
---@return boolean
function ImGui.IsItemHovered(flags) end
---@return boolean
function ImGui.IsItemActive() end
---@param button? integer
---@return boolean
function ImGui.IsItemClicked(button) end

-- Misc
---@param width number
function ImGui.PushItemWidth(width) end
function ImGui.PopItemWidth() end
---@param width number
function ImGui.SetNextItemWidth(width) end
---@param id integer|string
function ImGui.PushID(id) end
function ImGui.PopID() end
---@return number x, number y
function ImGui.GetContentRegionAvail() end
---@param text string
---@return number x, number y
function ImGui.CalcTextSize(text) end
---@return number
function ImGui.GetFrameRate() end

-- Enum tables (name -> integer). Values mirror the entries registered in
-- src/core/scripting/libraries/ImGui.cpp for the bundled ImGui (1.92.x).

---@enum ImGuiWindowFlags
ImGuiWindowFlags = {
    None = 0, NoTitleBar = 1, NoResize = 2, NoMove = 4, NoScrollbar = 8,
    NoScrollWithMouse = 16, NoCollapse = 32, AlwaysAutoResize = 64,
    NoBackground = 128, NoSavedSettings = 256, NoMouseInputs = 512, MenuBar = 1024,
    HorizontalScrollbar = 2048, NoFocusOnAppearing = 4096, NoBringToFrontOnFocus = 8192,
    AlwaysVerticalScrollbar = 16384, AlwaysHorizontalScrollbar = 32768,
    NoNavInputs = 65536, NoNavFocus = 131072, UnsavedDocument = 262144,
    NoNav = 196608, NoDecoration = 43, NoInputs = 197120, ChildWindow = 16777216,
    Tooltip = 33554432, Popup = 67108864, Modal = 134217728, ChildMenu = 268435456,
    NavFlattened = 536870912,
}

---@enum ImGuiChildFlags
ImGuiChildFlags = {
    None = 0, Borders = 1, Border = 1, AlwaysUseWindowPadding = 2, ResizeX = 4,
    ResizeY = 8, AutoResizeX = 16, AutoResizeY = 32, AlwaysAutoResize = 64,
    FrameStyle = 128, NavFlattened = 256,
}

---@enum ImGuiCond
ImGuiCond = { None = 0, Always = 1, Once = 2, FirstUseEver = 4, Appearing = 8 }

---@enum ImGuiCol
ImGuiCol = {
    Text = 0, TextDisabled = 1, WindowBg = 2, ChildBg = 3, PopupBg = 4, Border = 5,
    BorderShadow = 6, FrameBg = 7, FrameBgHovered = 8, FrameBgActive = 9, TitleBg = 10,
    TitleBgActive = 11, TitleBgCollapsed = 12, MenuBarBg = 13, ScrollbarBg = 14,
    ScrollbarGrab = 15, ScrollbarGrabHovered = 16, ScrollbarGrabActive = 17, CheckMark = 18,
    SliderGrab = 19, SliderGrabActive = 20, Button = 21, ButtonHovered = 22, ButtonActive = 23,
    Header = 24, HeaderHovered = 25, HeaderActive = 26, Separator = 27, SeparatorHovered = 28,
    SeparatorActive = 29, ResizeGrip = 30, ResizeGripHovered = 31, ResizeGripActive = 32,
    InputTextCursor = 33, TabHovered = 34, Tab = 35, TabSelected = 36, TabSelectedOverline = 37,
    TabDimmed = 38, TabDimmedSelected = 39, TabDimmedSelectedOverline = 40, PlotLines = 41,
    PlotLinesHovered = 42, PlotHistogram = 43, PlotHistogramHovered = 44, TableHeaderBg = 45,
    TableBorderStrong = 46, TableBorderLight = 47, TableRowBg = 48, TableRowBgAlt = 49,
    TextLink = 50, TextSelectedBg = 51, TreeLines = 52, DragDropTarget = 53, NavCursor = 54,
    NavWindowingHighlight = 55, NavWindowingDimBg = 56, ModalWindowDimBg = 57, COUNT = 58,
    -- renamed aliases
    TabActive = 36, TabUnfocused = 38, TabUnfocusedActive = 39, NavHighlight = 54,
    ModalWindowDarkening = 57,
}

---@enum ImGuiStyleVar
ImGuiStyleVar = {
    Alpha = 0, DisabledAlpha = 1, WindowPadding = 2, WindowRounding = 3, WindowBorderSize = 4,
    WindowMinSize = 5, WindowTitleAlign = 6, ChildRounding = 7, ChildBorderSize = 8,
    PopupRounding = 9, PopupBorderSize = 10, FramePadding = 11, FrameRounding = 12,
    FrameBorderSize = 13, ItemSpacing = 14, ItemInnerSpacing = 15, IndentSpacing = 16,
    CellPadding = 17, ScrollbarSize = 18, ScrollbarRounding = 19, GrabMinSize = 20,
    GrabRounding = 21, ImageBorderSize = 22, TabRounding = 23, TabBorderSize = 24,
    TabBarBorderSize = 25, TabBarOverlineSize = 26, TableAngledHeadersAngle = 27,
    TableAngledHeadersTextAlign = 28, TreeLinesSize = 29, TreeLinesRounding = 30,
    ButtonTextAlign = 31, SelectableTextAlign = 32, SeparatorTextBorderSize = 33,
    SeparatorTextAlign = 34, SeparatorTextPadding = 35, COUNT = 36,
}

---@enum ImGuiDir
ImGuiDir = { None = -1, Left = 0, Right = 1, Up = 2, Down = 3, COUNT = 4 }

---@enum ImGuiKey
ImGuiKey = {
    Tab = 512, LeftArrow = 513, RightArrow = 514, UpArrow = 515, DownArrow = 516,
    PageUp = 517, PageDown = 518, Home = 519, End = 520, Insert = 521, Delete = 522,
    Backspace = 523, Space = 524, Enter = 525, Escape = 526,
    A = 546, C = 548, V = 567, X = 569, Y = 570, Z = 571, KeyPadEnter = 615, COUNT = 645,
}

---@enum ImGuiMouseButton
-- Keys are registered with the full ImGuiMouseButton_ prefix.
ImGuiMouseButton = {
    ImGuiMouseButton_Left = 0, ImGuiMouseButton_Right = 1,
    ImGuiMouseButton_Middle = 2, ImGuiMouseButton_COUNT = 5,
}

---@enum ImGuiMouseCursor
ImGuiMouseCursor = {
    None = -1, Arrow = 0, TextInput = 1, ResizeAll = 2, ResizeNS = 3, ResizeEW = 4,
    ResizeNESW = 5, ResizeNWSE = 6, Hand = 7, Wait = 8, Progress = 9, NotAllowed = 10, COUNT = 11,
}

---@enum ImGuiHoveredFlags
ImGuiHoveredFlags = {
    None = 0, ChildWindows = 1, RootWindow = 2, AnyWindow = 4, NoPopupHierarchy = 8,
    AllowWhenBlockedByPopup = 32, AllowWhenBlockedByActiveItem = 128,
    AllowWhenOverlappedByItem = 256, AllowWhenOverlappedByWindow = 512, AllowWhenDisabled = 1024,
    NoNavOverride = 2048, AllowWhenOverlapped = 768, RectOnly = 928, RootAndChildWindows = 3,
    ForTooltip = 4096, Stationary = 8192, DelayNone = 16384, DelayShort = 32768,
    DelayNormal = 65536, NoSharedDelay = 131072,
}

---@enum ImGuiFocusedFlags
ImGuiFocusedFlags = {
    None = 0, ChildWindows = 1, RootWindow = 2, AnyWindow = 4, RootAndChildWindows = 3,
}

---@enum ImGuiComboFlags
ImGuiComboFlags = {
    None = 0, PopupAlignLeft = 1, HeightSmall = 2, HeightRegular = 4, HeightLarge = 8,
    HeightLargest = 16, NoArrowButton = 32, NoPreview = 64, HeightMask = 30,
}

---@enum ImGuiInputTextFlags
ImGuiInputTextFlags = {
    None = 0, CharsDecimal = 1, CharsHexadecimal = 2, CharsScientific = 4, CharsUppercase = 8,
    CharsNoBlank = 16, AllowTabInput = 32, EnterReturnsTrue = 64, EscapeClearsAll = 128,
    CtrlEnterForNewLine = 256, ReadOnly = 512, Password = 1024, AlwaysOverwrite = 2048,
    AutoSelectAll = 4096, ParseEmptyRefVal = 8192, DisplayEmptyRefVal = 16384,
    NoHorizontalScroll = 32768, NoUndoRedo = 65536, ElideLeft = 131072,
    CallbackCompletion = 262144, CallbackHistory = 524288, CallbackAlways = 1048576,
    CallbackCharFilter = 2097152, CallbackResize = 4194304, CallbackEdit = 8388608,
}

---@enum ImGuiColorEditFlags
ImGuiColorEditFlags = {
    None = 0, NoAlpha = 2, NoPicker = 4, NoOptions = 8, NoSmallPreview = 16, NoInputs = 32,
    NoTooltip = 64, NoLabel = 128, NoSidePreview = 256, NoDragDrop = 512, NoBorder = 1024,
    AlphaOpaque = 2048, AlphaNoBg = 4096, AlphaPreviewHalf = 8192, AlphaBar = 65536,
    HDR = 524288, DisplayRGB = 1048576, DisplayHSV = 2097152, DisplayHex = 4194304,
    Uint8 = 8388608, Float = 16777216, PickerHueBar = 33554432, PickerHueWheel = 67108864,
    InputRGB = 134217728, InputHSV = 268435456, DefaultOptions_ = 177209344,
    DisplayMask_ = 7340032, DataTypeMask_ = 25165824, PickerMask_ = 100663296,
    InputMask_ = 402653184,
}

---@enum ImGuiTreeNodeFlags
ImGuiTreeNodeFlags = {
    None = 0, Selected = 1, Framed = 2, AllowOverlap = 4, NoTreePushOnOpen = 8,
    NoAutoOpenOnLog = 16, DefaultOpen = 32, OpenOnDoubleClick = 64, OpenOnArrow = 128,
    Leaf = 256, Bullet = 512, FramePadding = 1024, SpanAvailWidth = 2048, SpanFullWidth = 4096,
    SpanLabelWidth = 8192, SpanAllColumns = 16384, LabelSpanAllColumns = 32768,
    NavLeftJumpsToParent = 131072, CollapsingHeader = 26,
    -- renamed aliases
    AllowItemOverlap = 4, NavLeftJumpsBackHere = 131072,
}

---@enum ImGuiSelectableFlags
ImGuiSelectableFlags = {
    None = 0, DontClosePopups = 1, SpanAllColumns = 2, AllowDoubleClick = 4,
    Disabled = 8, AllowItemOverlap = 16,
}

---@enum ImGuiPopupFlags
ImGuiPopupFlags = {
    None = 0, MouseButtonLeft = 0, MouseButtonRight = 1, MouseButtonMiddle = 2,
    MouseButtonMask_ = 31, MouseButtonDefault_ = 1, NoReopen = 32,
    NoOpenOverExistingPopup = 128, NoOpenOverItems = 256, AnyPopupId = 1024,
    AnyPopupLevel = 2048, AnyPopup = 3072,
}

---@enum ImGuiTabBarFlags
ImGuiTabBarFlags = {
    None = 0, Reorderable = 1, AutoSelectNewTabs = 2, TabListPopupButton = 4,
    NoCloseWithMiddleMouseButton = 8, NoTabListScrollingButtons = 16, NoTooltip = 32,
    DrawSelectedOverline = 64, FittingPolicyResizeDown = 128, FittingPolicyScroll = 256,
    FittingPolicyMask_ = 384, FittingPolicyDefault_ = 128,
}

---@enum ImGuiTabItemFlags
ImGuiTabItemFlags = {
    None = 0, UnsavedDocument = 1, SetSelected = 2, NoCloseWithMiddleMouseButton = 4,
    NoPushId = 8, NoTooltip = 16,
}

---@enum ImGuiTableFlags
ImGuiTableFlags = {
    None = 0, Resizable = 1, Reorderable = 2, Hideable = 4, Sortable = 8, NoSavedSettings = 16,
    ContextMenuInBody = 32, RowBg = 64, BordersInnerH = 128, BordersOuterH = 256,
    BordersInnerV = 512, BordersOuterV = 1024, BordersH = 384, BordersV = 1536,
    BordersInner = 640, BordersOuter = 1280, Borders = 1920, NoBordersInBody = 2048,
    NoBordersInBodyUntilResize = 4096, SizingFixedFit = 8192, SizingFixedSame = 16384,
    SizingStretchProp = 24576, SizingStretchSame = 32768, SizingMask_ = 57344,
    NoHostExtendX = 65536, NoHostExtendY = 131072, NoKeepColumnsVisible = 262144,
    PreciseWidths = 524288, NoClip = 1048576, PadOuterX = 2097152, NoPadOuterX = 4194304,
    NoPadInnerX = 8388608, ScrollX = 16777216, ScrollY = 33554432, SortMulti = 67108864,
    SortTristate = 134217728,
}

---@enum ImGuiTableColumnFlags
ImGuiTableColumnFlags = {
    None = 0, Disabled = 1, DefaultSort = 4, WidthStretch = 8, WidthFixed = 16, NoResize = 32,
    NoReorder = 64, NoHide = 128, NoClip = 256, NoSort = 512, NoSortAscending = 1024,
    NoSortDescending = 2048, NoHeaderLabel = 4096, NoHeaderWidth = 8192,
    PreferSortAscending = 16384, PreferSortDescending = 32768, IndentEnable = 65536,
    IndentDisabled = 131072, IsEnabled = 16777216, IsVisible = 33554432, IsSorted = 67108864,
    IsHovered = 134217728, WidthMask_ = 24, IndentMask_ = 196608, StatusMask_ = 251658240,
    NoDirectResize_ = 1073741824,
}
