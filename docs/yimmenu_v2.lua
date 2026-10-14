---@meta
--- YimMenuV2 Lua API definitions for the Lua Language Server (sumneko / LuaLS).
---
--- This file is annotations only — it is never executed. Point your language
--- server at it for autocompletion and type checking, e.g. in `.luarc.json`:
---     { "workspace.library": [ "path/to/docs" ] }
---
--- See docs/lua-api.md for prose descriptions. Natives loaded via
--- `natives.load_natives()` are listed in docs/natives.lua.

---Load a Lua source module beneath <MenuRoot>/scripts, sharing this script's state.
---Accepts dotted names or relative paths, with optional .lua extension.
---Searches package.path; truthy results are cached by requested name in package.loaded.
---Raises an error for invalid paths, loading failures, or circular imports.
---@param module_name string
---@return any
function require(module_name) end

---@class LuaPackage
---@field path string # Lua search patterns initialized from scripts and eligible subfolders.
---@field cpath string # Initially empty; native module searchers are disabled.
---@field loaded table<string, any> # Per-script cache, indexed by requested module name.
---@field preload table<string, function> # Preload searcher is disabled.
---@field loaders function[] # Contains only the checked Lua file searcher.
---@field searchers function[] # Alias of loaders in this LuaJIT build.
package = {}

---Locate a file using Lua search patterns; require validates containment before loading it.
---@param name string
---@param path string
---@param sep? string # default "."
---@param rep? string # default platform directory separator
---@return string? filename, string? error_message
function package.searchpath(name, path, sep, rep) end

---Disabled: raises an unsupported-function error.
---@param filename string
---@param symbol string
function package.loadlib(filename, symbol) end

------------------------------------------------------------------------------
-- os (restricted standard LuaJIT library; timestamps use seconds)
------------------------------------------------------------------------------

---@class OsDateInput
---@field year integer
---@field month integer # 1..12
---@field day integer # day of the month
---@field hour? integer # default 12
---@field min? integer # default 0
---@field sec? integer # default 0
---@field isdst? boolean # omitted/nil: detect daylight saving time
---@field wday? integer # ignored by os.time
---@field yday? integer # ignored by os.time

---@class OsDateTable: OsDateInput
---@field hour integer
---@field min integer
---@field sec integer
---@field wday integer # 1..7; Sunday=1
---@field yday integer # 1..366
---@field isdst? boolean # daylight saving time flag

---Approximate process CPU time in seconds; normal LuaJIT behavior.
---@return number
function os.clock() end

---Normal LuaJIT date formatting; defaults to current local time and format "%c".
---"*t" returns a local date table; "!*t" returns a UTC date table.
---Unsupported timestamps return nil. Available through require("os") too.
---@overload fun(format: '"*t"', timestamp?: integer): OsDateTable?
---@overload fun(format: '"!*t"', timestamp?: integer): OsDateTable?
---@param format? string
---@param timestamp? integer # Unix seconds
---@return string|OsDateTable|nil
function os.date(format, timestamp) end

---Returns t2-t1 in seconds; normal LuaJIT behavior.
---@param t2 number
---@param t1 number
---@return number
function os.difftime(t2, t1) end

---Unix seconds; omitted/nil table selects current time. Normal LuaJIT local-time behavior.
---Calendar fields are normalized; unsupported dates return nil.
---@param date_table? OsDateInput
---@return integer?
function os.time(date_table) end

---Disabled: raises a not-supported error.
---@param command? string
---@return never
function os.execute(command) end

---Disabled: raises a not-supported error.
---@param code? integer|boolean
---@param close? boolean
---@return never
function os.exit(code, close) end

---Disabled: raises a not-supported error.
---@param name string
---@return never
function os.getenv(name) end

---Disabled: raises a not-supported error.
---@param locale string|nil
---@param category? string
---@return never
function os.setlocale(locale, category) end

---Disabled: raises a not-supported error.
---@return never
function os.tmpname() end

---Disabled: raises an error directing callers to FileMgr.RenameFile.
---@param source string
---@param destination string
---@return never
function os.rename(source, destination) end

---Disabled: raises an error directing callers to FileMgr.DeleteFile.
---@param path string
---@return never
function os.remove(path) end

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

---@overload fun(): Vector3
---@param x number
---@param y number
---@param z number
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

---Return the current online version, followed by the game build, as strings.
---@return string online_version, string game_build
function util.get_game_version() end

------------------------------------------------------------------------------
-- script
------------------------------------------------------------------------------

script = {}

---@param fn fun()
function script.run_in_callback(fn) end

---Yield a managed callback; omitting ms selects 0 (one frame). Explicit nil is rejected.
---@overload fun()
---@param ms integer
function script.yield(ms) end

---True while executing a registered ImGui render callback. This callback must not yield.
---@return boolean
function script.is_inside_render_callback() end

---True only in the active managed script coroutine; includes command/tick callbacks.
---Top-level code and coroutines created directly with coroutine.create return false.
---@return boolean
function script.is_inside_script_callback() end

---Require exact version string matches; raises a Lua error on a mismatch.
---Omit game_build or pass nil to check only the online version.
---@param online_version string
---@param game_build? string
function script.require_game_build(online_version, game_build) end

------------------------------------------------------------------------------
-- event
------------------------------------------------------------------------------

---@class menu_event
---@field PlayerMgrInit 0 # handler(); tracked player list populated during manager initialization.
---@field PlayerMgrShutdown 1 # handler(); tracked players, data and selection cleared.
---@field PlayerLeave 2 # handler(name: string).
---@field PlayerJoin 3 # handler(player_id: integer, name: string).
---@field ScriptedGameEventReceived 4 # handler(player: Player, args: integer[]); false blocks handling.
---@field ChatMessageReceived 5 # handler(player_id: integer, message: string); false blocks handling.
---@field Unload 6 # handler(); script unload or reload.
---@field WndProc 7 # handler(hwnd: integer, message: integer, wparam: integer, lparam: integer); observational.
menu_event = {}

event = {}

---Runs synchronously on the event's dispatch thread; handlers must not yield.
---Use script.run_in_callback for work that needs a script coroutine.
---Return false to block scripted-event/chat handling; other return values are ignored.
---Paused scripts do not receive events. Use enum constants rather than hardcoded IDs.
---@overload fun(menu_event: 0|1|6, handler: fun())
---@overload fun(menu_event: 2, handler: fun(name: string))
---@overload fun(menu_event: 3, handler: fun(player_id: integer, name: string))
---@overload fun(menu_event: 4, handler: fun(player: Player, args: integer[]): boolean?)
---@overload fun(menu_event: 5, handler: fun(player_id: integer, message: string): boolean?)
---@overload fun(menu_event: 7, handler: fun(hwnd: integer, message: integer, wparam: integer, lparam: integer))
---@param menu_event integer # a `menu_event.*` constant
---@param handler fun(...): boolean?
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

---@class TabBarItem
local TabBarItem = {}

---@class TabItem
local TabItem = {}

---@class CollapsingHeaderItem
local CollapsingHeaderItem = {}

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
---Toggle the menu open/closed and update mouse input and cursor visibility.
function menu.toggle() end
---Set this script's mouse override request; repeated calls are idempotent.
---Enables ImGui cursor/mouse input with the menu closed and suppresses game controls.
---Applied on the next render frame. False releases only this script's request.
---Pause suspends it, Resume restores it; unload/reload/malfunction/destruction release it.
---@param enabled boolean
function menu.set_mouse_override(enabled) end
---True when any script has an active mouse override request.
---Menu/onboarding visibility alone does not count; another owner may keep this true.
---@return boolean
function menu.is_mouse_overridden() end
---Register a raw ImGui draw callback rendered every frame while the menu is open.
---@param fn fun()
function menu.add_imgui(fn) end
---Register a raw ImGui draw callback rendered every frame regardless of whether the menu is open.
---@param fn fun()
function menu.add_always_draw_imgui(fn) end

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
---@param id string
---@return TabBarItem
function Category:add_tab_bar(id) end
---@param name string
---@return CollapsingHeaderItem
function Category:add_collapsing_header(name) end
---@param name string
function Category:add_command(name) end
---@param name string
function Category:add_bool_command(name) end
---@param name string
---@param slider? boolean # default true
function Category:add_int_command(name, slider) end
---@param name string
---@param slider? boolean # default true
function Category:add_float_command(name, slider) end
---@param name string
function Category:add_list_command(name) end
---@param name string
---@param label string
---@param desc? string
---@param fn fun()
---@return CommandHandle
function Category:add_button(name, label, desc, fn) end
---@param name string
---@param label string
---@param desc? string
---@param default? boolean
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function Category:add_checkbox(name, label, desc, default, on_enable, on_disable) end
---@param name string
---@param label string
---@param desc? string
---@param tick fun()
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function Category:add_looped_checkbox(name, label, desc, tick, on_enable, on_disable) end
---Register a raw ImGui draw callback rendered every frame.
---@param fn fun()
function Category:imgui(fn) end

---@param id string
---@return TabBarItem
function Group:add_tab_bar(id) end
---@param name string
---@return CollapsingHeaderItem
function Group:add_collapsing_header(name) end
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

-- TabBarItem

---@param name string
---@return TabItem
function TabBarItem:add_tab(name) end

-- TabItem

---@param name string
---@param per_row? integer # default 7
---@return Group
function TabItem:add_group(name, per_row) end
---@param name string
---@return CollapsingHeaderItem
function TabItem:add_collapsing_header(name) end
---@param name string
function TabItem:add_command(name) end
---@param name string
function TabItem:add_bool_command(name) end
---@param name string
---@param slider? boolean # default true
function TabItem:add_int_command(name, slider) end
---@param name string
---@param slider? boolean # default true
function TabItem:add_float_command(name, slider) end
---@param name string
function TabItem:add_list_command(name) end
---@param name string
---@param label string
---@param desc? string
---@param fn fun()
---@return CommandHandle
function TabItem:add_button(name, label, desc, fn) end
---@param name string
---@param label string
---@param desc? string
---@param default? boolean
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function TabItem:add_checkbox(name, label, desc, default, on_enable, on_disable) end
---@param name string
---@param label string
---@param desc? string
---@param tick fun()
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function TabItem:add_looped_checkbox(name, label, desc, tick, on_enable, on_disable) end
---Draw only while this tab is selected. This callback must not yield.
---@param fn fun()
function TabItem:imgui(fn) end

-- CollapsingHeaderItem

---@param name string
---@param per_row? integer # default 7
---@return Group
function CollapsingHeaderItem:add_group(name, per_row) end
---@param name string
function CollapsingHeaderItem:add_command(name) end
---@param name string
function CollapsingHeaderItem:add_bool_command(name) end
---@param name string
---@param slider? boolean # default true
function CollapsingHeaderItem:add_int_command(name, slider) end
---@param name string
---@param slider? boolean # default true
function CollapsingHeaderItem:add_float_command(name, slider) end
---@param name string
function CollapsingHeaderItem:add_list_command(name) end
---@param name string
---@param label string
---@param desc? string
---@param fn fun()
---@return CommandHandle
function CollapsingHeaderItem:add_button(name, label, desc, fn) end
---@param name string
---@param label string
---@param desc? string
---@param default? boolean
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function CollapsingHeaderItem:add_checkbox(name, label, desc, default, on_enable, on_disable) end
---@param name string
---@param label string
---@param desc? string
---@param tick fun()
---@param on_enable? fun()
---@param on_disable? fun()
---@return CommandHandle
function CollapsingHeaderItem:add_looped_checkbox(name, label, desc, tick, on_enable, on_disable) end
---Draw only while this section is expanded. This callback must not yield.
---@param fn fun()
function CollapsingHeaderItem:imgui(fn) end

------------------------------------------------------------------------------
-- commandmgr
------------------------------------------------------------------------------

---@class CommandHandle
local CommandHandle = {}

---Returns the value or selected list-entry key; nil for one-shot/missing commands.
---@return boolean|integer|number|nil
function CommandHandle:get_value() end
---Schedules change callbacks. One-shot and missing commands are no-ops.
---@param value boolean|integer|number
function CommandHandle:set_value(value) end
---Return the registered name/ID, or nil if the command no longer exists.
---@return string?
function CommandHandle:get_name() end
---@return string?
function CommandHandle:get_desc() end
---Activates the command's normal action; missing commands are a no-op. Returns no values.
---Lua one-shot callbacks are queued; Lua bool/looped commands toggle their enabled state.
function CommandHandle:call() end
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
---@param default? integer # selected entry key
---@param on_change? fun(value: integer) # receives the selected entry key
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

---Captures original bytes and creates an unapplied patch; call apply() to write it.
---@param value integer
---@return patch
function pointer:patch_byte(value) end
---Captures original bytes and creates an unapplied patch; call apply() to write it.
---@param value integer
---@return patch
function pointer:patch_word(value) end
---Captures original bytes and creates an unapplied patch; call apply() to write it.
---@param value integer
---@return patch
function pointer:patch_dword(value) end
---Captures original bytes and creates an unapplied patch; call apply() to write it.
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
---Frees only a block allocated by this script; a null pointer is a no-op.
---Foreign or already-freed non-null addresses raise an error.
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
---@overload fun(self: Entity): Vector3
---@param order integer # omitted default 2; nil rejected
---@return Vector3
function Entity:get_rotation(order) end
---@param rot Vector3
---@overload fun(self: Entity, rot: Vector3)
---@param order integer # omitted default 2; nil rejected
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
---@overload fun(self: Entity)
---@param timeout integer # milliseconds, omitted default 100; nil rejected
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
---@overload fun(model: integer|string, pos: Vector3): Ped
---@param model integer|string
---@param pos Vector3
---@param heading number # omitted default 0; nil rejected
---@return Ped
function Ped.create(model, pos, heading) end

---@return Vehicle
function Ped:get_vehicle() end
---@return Vehicle
function Ped:get_last_vehicle() end
---@return integer
function Ped:get_vehicle_object_id() end
---@param vehicle Vehicle
---@overload fun(self: Ped, vehicle: Vehicle)
---@param seat integer # omitted default 0; nil rejected
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
---@overload fun(self: Ped, weapon: integer|string)
---@param equip boolean # omitted default false; nil rejected
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
---@overload fun(self: Ped, name: string)
---@overload fun(self: Ped, name: string, duration: integer)
---@param duration integer # omitted default -1; nil rejected
---@param play_anim boolean # omitted default true; nil rejected
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
---@overload fun(model: integer|string, pos: Vector3): Vehicle
---@param model integer|string
---@param pos Vector3
---@param heading number # omitted default 0; nil rejected
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
---@overload fun(self: Vehicle)
---@param charge integer # omitted: 100; nil is rejected
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

---Inaccessible slots read as 0/zero vector/nil string; writes are ignored.
---@param index integer
---@return ScriptGlobal
function ScriptGlobal.new(index) end

---size=0/omitted: base+offset; nonzero size: base+1+offset*size.
---@overload fun(self: ScriptGlobal, offset: integer): ScriptGlobal
---@param offset integer
---@param size integer # omitted: 0; nil is rejected
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
---Address of the global slot, not its stored value; null pointer userdata if inaccessible.
---Borrows game memory. Check can_access()/is_null() and resolve again if globals change.
---@return pointer
function ScriptGlobal:get_pointer() end
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
---@overload fun(script: string|integer, index: integer): ScriptLocal?
ScriptLocal = {}

---@param script string|integer # script name or hash
---@param index integer
---@return ScriptLocal?
function ScriptLocal.new(script, index) end

---size=0/omitted: base+offset; nonzero size: base+1+offset*size.
---@overload fun(self: ScriptLocal, offset: integer): ScriptLocal
---@param offset integer
---@param size integer # omitted: 0; nil is rejected
---@return ScriptLocal
function ScriptLocal:at(offset, size) end
---@return integer
function ScriptLocal:get_int() end
---@return number
function ScriptLocal:get_float() end
---@return Vector3
function ScriptLocal:get_vector3() end
---Address of the local slot on the captured thread's stack, not its stored value.
---Borrows memory; does not validate the stack or keep the thread alive.
---Recreate the handle and resolve again after the script stops or restarts.
---@return pointer
function ScriptLocal:get_pointer() end
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
---@param address? integer # 32-bit script bytecode offset, not a process-memory address
---@return ScriptPointer
function ScriptPointer.new(name, pattern, offset, rip, address) end

---Returns a copy with a new future scan offset; preserves the resolved address.
---@param offset integer
---@return ScriptPointer
function ScriptPointer:add(offset) end
---Returns a copy with a new future scan offset; preserves the resolved address.
---@param offset integer
---@return ScriptPointer
function ScriptPointer:sub(offset) end
---Enables three-byte script address operand decoding on a future scan.
---Preserves the resolved address until scanning again.
---@return ScriptPointer
function ScriptPointer:rip() end
---No loaded target: nil. Pattern not found: handle with address 0.
---@param target string|integer
---@return ScriptPointer?
function ScriptPointer:scan(target) end
---@return integer # 32-bit script bytecode offset, not a process-memory address
function ScriptPointer:get_address() end
---@return string
function ScriptPointer:get_name() end

------------------------------------------------------------------------------
-- ScriptPatch
------------------------------------------------------------------------------

---@class ScriptPatch
---@overload fun(script: string|integer, name: string, pattern: string, offset: integer|nil, patch_bytes: integer[]): ScriptPatch
ScriptPatch = {}

---@param script string|integer
---@param name string
---@param pattern string
---@param offset integer|nil # pass nil or 0 for no offset; retain this positional slot
---@param patch_bytes integer[] # nonempty array of bytes 0-255, always argument 5
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
---`param_string` arg chars: `i` int32, `f` float, `h` hash, `b` bool, `s` string; optional `=<r>` return type (`n`/`i`/`f`/`b`/`h`/`s`).
---String arguments are borrowed read-only C strings, valid during the call; nil/omitted strings pass NULL.
---Embedded NUL bytes terminate the text. The GTA function must not retain or modify argument strings.
---`=s` copies the returned C string into Lua, or returns nil for NULL.
---Examples: `fn:call("ii=i", 5, 10)`, `fn:call("s=s", "example")`.
---@param param_string string
---@param ... number|boolean|string|nil
---@return any # Determined by the format: number, boolean, string, nil, or no return value.
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
---Raises an error if already loaded; guard with are_natives_loaded().
function natives.load_natives() end
---@return boolean
function natives.are_natives_loaded() end

------------------------------------------------------------------------------
-- network
------------------------------------------------------------------------------

network = {}

---@enum session_types
session_types = {
    public = 0,
    solo_public = 1,
    sctv = 13,
    crew = 3,
    join_crew = 12,
    closed_crew = 2,
    closed_friend = 6,
    find_friend = 9,
    invite_only = 11,
    solo = 10,
}

---Transmits { hash, local_player_id, bits, ...formatted_args }.
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
---Request a session transition from a script callback; returns no completion status.
---@param session_type session_types
function network.join_session(session_type) end

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
-- FileMgr (all paths relative to <MenuRoot>/scripts)
------------------------------------------------------------------------------

FileMgr = {}

---Every path is relative to scripts; use "." for the root.
---Absolute/drive/UNC/stream/NUL paths and paths escaping through .. or links are rejected.
---@param path string # relative directory path
---@return boolean
function FileMgr.CreateDir(path) end
---@param path string
function FileMgr.DeleteFile(path) end
---Rename/move a regular file; destination parent must exist. Never overwrites another file.
---Returns false for filesystem failures/destination collisions; same-file rename succeeds.
---@param source string # relative source file path
---@param destination string # relative destination file path
---@return boolean
function FileMgr.RenameFile(source, destination) end
---@param path string
---@return boolean
function FileMgr.DoesFileExist(path) end
---Results are relative to scripts and usable directly with other FileMgr functions.
---Empty extension matches all files. Recursive enumeration skips linked directories.
---@param path string # relative directory path; "." lists the scripts root
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
-- Most value-editing widgets return the updated value plus a changed flag.
-- Selectable returns only selected state. Overloaded widgets may change their
-- return arity. Flag/cond/col arguments use the ImGui* enum tables.
------------------------------------------------------------------------------

ImGui = {}

---Borrowed ImGui draw-list handle; acquire a new one each render frame.
---Screen-space coordinates in pixels. RGBA components must be integers in [0, 255].
---@class DrawList
local DrawList = {}

---Current window's clipped draw list. Call inside an ImGui render callback.
---@return DrawList
function ImGui.GetWindowDrawList() end
---Main viewport's foreground draw list, rendered above windows.
---@return DrawList
function ImGui.GetForegroundDrawList() end
---Uses the current font; omitted/nil font_size uses its current size.
---Omitted/nil wrap_width defaults to 0 (no wrapping); positive widths wrap in pixels.
---@param x number
---@param y number
---@param text string
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param font_size? number # positive size in pixels
---@param wrap_width? number # non-negative finite pixel width; default 0
function DrawList:AddText(x, y, text, r, g, b, a, font_size, wrap_width) end
---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param thickness? number # default 1 pixel
function DrawList:AddLine(x1, y1, x2, y2, r, g, b, a, thickness) end
---Draws a rectangle outline on this handle's window or foreground draw list.
---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param rounding? number # default 0 pixels
---@param flags? integer # default 0; ImGui draw flags
---@param thickness? number # default 1 pixel
function DrawList:AddRect(x1, y1, x2, y2, r, g, b, a, rounding, flags, thickness) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param rounding? number # default 0 pixels
---@param flags? integer # ImGui draw flags; default 0 (all corners when rounding > 0)
function DrawList:AddRectFilled(x1, y1, x2, y2, r, g, b, a, rounding, flags) end

---Interpolates four packed U32 corner colors across a filled rectangle.
---Create colors with ImGui.ColorConvertRGBAToU32({r, g, b, a}).
---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param upper_left integer # packed U32 color
---@param upper_right integer # packed U32 color
---@param bottom_right integer # packed U32 color
---@param bottom_left integer # packed U32 color
function DrawList:AddRectFilledMultiColor(x1, y1, x2, y2, upper_left, upper_right, bottom_right, bottom_left) end

---Draws a triangle outline on this handle's window or foreground draw list.
---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param x3 number
---@param y3 number
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param thickness? number # default 1 pixel
function DrawList:AddTriangle(x1, y1, x2, y2, x3, y3, r, g, b, a, thickness) end

---Draws a filled triangle; supply vertices in clockwise screen-space order.
---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param x3 number
---@param y3 number
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
function DrawList:AddTriangleFilled(x1, y1, x2, y2, x3, y3, r, g, b, a) end

---Draws a circle outline on this handle's window or foreground draw list.
---@param x number
---@param y number
---@param radius number # pixels
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param num_segments? integer # default 0: automatic tessellation
---@param thickness? number # default 1 pixel
function DrawList:AddCircle(x, y, radius, r, g, b, a, num_segments, thickness) end

---Draws a filled circle on this handle's window or foreground draw list.
---@param x number
---@param y number
---@param radius number # pixels
---@param r integer # 0..255
---@param g integer # 0..255
---@param b integer # 0..255
---@param a integer # 0..255
---@param num_segments? integer # default 0: automatic tessellation
function DrawList:AddCircleFilled(x, y, radius, r, g, b, a, num_segments) end

---@class ImGuiVec2
---@field x number
---@field y number

---@class ImGuiStyleSnapshot
---@field Alpha number
---@field DisabledAlpha number
---@field WindowPadding ImGuiVec2
---@field WindowRounding number
---@field WindowBorderSize number
---@field WindowMinSize ImGuiVec2
---@field WindowTitleAlign ImGuiVec2
---@field ChildRounding number
---@field ChildBorderSize number
---@field PopupRounding number
---@field PopupBorderSize number
---@field FramePadding ImGuiVec2
---@field FrameRounding number
---@field FrameBorderSize number
---@field ItemSpacing ImGuiVec2
---@field ItemInnerSpacing ImGuiVec2
---@field CellPadding ImGuiVec2
---@field IndentSpacing number
---@field ScrollbarSize number
---@field ScrollbarRounding number
---@field GrabMinSize number
---@field GrabRounding number
---@field ButtonTextAlign ImGuiVec2
---@field SelectableTextAlign ImGuiVec2


-- Internal / drawing
---Draws on the current window; integer RGBA components use 0..255.
---@param x number
---@param y number
---@param radius number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param segments? integer
---@param thickness? number
function ImGui.AddCircle(x, y, radius, r, g, b, a, segments, thickness) end

---@param x number
---@param y number
---@param radius number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param segments? integer
function ImGui.AddCircleFilled(x, y, radius, r, g, b, a, segments) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param thickness? number
function ImGui.AddLine(x1, y1, x2, y2, r, g, b, a, thickness) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param rounding? number
---@param flags? integer
---@param thickness? number
function ImGui.AddRect(x1, y1, x2, y2, r, g, b, a, rounding, flags, thickness) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param rounding? number
---@param flags? integer
function ImGui.AddRectFilled(x1, y1, x2, y2, r, g, b, a, rounding, flags) end

---Corner colors are packed U32 values, e.g. ColorConvertRGBAToU32({r,g,b,a}).
---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param upper_left integer
---@param upper_right integer
---@param bottom_right integer
---@param bottom_left integer
function ImGui.AddRectFilledMultiColor(x1, y1, x2, y2, upper_left, upper_right, bottom_right, bottom_left) end

---@param x number
---@param y number
---@param text string
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param font_size? number # positive finite pixels; omitted/nil: current font size
---@param wrap_width? number # non-negative finite pixels; omitted/nil/0: no wrapping
function ImGui.AddText(x, y, text, r, g, b, a, font_size, wrap_width) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param x3 number
---@param y3 number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
---@param thickness? number
function ImGui.AddTriangle(x1, y1, x2, y2, x3, y3, r, g, b, a, thickness) end

---@param x1 number
---@param y1 number
---@param x2 number
---@param y2 number
---@param x3 number
---@param y3 number
---@param r integer
---@param g integer
---@param b integer
---@param a integer
function ImGui.AddTriangleFilled(x1, y1, x2, y2, x3, y3, r, g, b, a) end


-- Tables
---@param id string
---@param columns integer
---@param flags? ImGuiTableFlags # omitted/nil: None
---@param outer_size_x? number # outer width in pixels; omitted/nil: 0 (available width)
---@param outer_size_y? number # outer height in pixels; omitted/nil: 0 (ImGui default sizing)
---@param inner_width? number # content width for horizontal scrolling; omitted/nil: 0
---@return boolean visible
function ImGui.BeginTable(id, columns, flags, outer_size_x, outer_size_y, inner_width) end

function ImGui.EndTable() end

function ImGui.TableNextColumn() end

---@param row_flags? ImGuiTableRowFlags # omitted/nil: None
---@param min_row_height? number # minimum height in pixels; omitted/nil: 0
function ImGui.TableNextRow(row_flags, min_row_height) end

---@param column integer
---@return boolean visible
function ImGui.TableSetColumnIndex(column) end

---Sets a column label, flags, initial width or stretch weight and user ID before submitting rows.
---Omitted/nil optional arguments default to 0; fractional sizing is supported.
---@param label string
---@param flags? ImGuiTableColumnFlags # default 0
---@param init_width_or_weight? number # WidthFixed: pixels; WidthStretch: relative weight; default 0
---@param user_id? integer # application-defined column ID; default 0
function ImGui.TableSetupColumn(label, flags, init_width_or_weight, user_id) end

function ImGui.TableHeadersRow() end


-- Color conversions
---Four float components in 0..1.
---@param color number[]
---@return integer
function ImGui.ColorConvertFloat4ToU32(color) end

---Four integer components in 0..255.
---@param color integer[]
---@return integer
function ImGui.ColorConvertRGBAToU32(color) end

---Returns four float components in 0..1.
---@param color integer
---@return number[]
function ImGui.ColorConvertU32ToFloat4(color) end

---@param r number
---@param g number
---@param b number
---@return number h, number s, number v
function ImGui.ColorConvertRGBtoHSV(r, g, b) end

---@param h number
---@param s number
---@param v number
---@return number r, number g, number b
function ImGui.ColorConvertHSVtoRGB(h, s, v) end


-- Display
---@return number width, number height
function ImGui.GetDisplaySize() end

---@return number
function ImGui.GetFrameRate() end


-- Windows
---With an open boolean, returns open, draw. Without it, returns draw only; flags stay in slot 3.
---@overload fun(name: string, open?: nil, flags?: integer): boolean
---@param name string
---@param open boolean
---@param flags? integer
---@return boolean open, boolean draw
function ImGui.Begin(name, open, flags) end

function ImGui.End() end

---@param name string
---@param size_x? number
---@param size_y? number
---@param border? boolean
---@param flags? integer
---@return boolean visible
function ImGui.BeginChild(name, size_x, size_y, border, flags) end

function ImGui.EndChild() end


-- Window utilities
---@return boolean
function ImGui.IsWindowAppearing() end

---@return boolean
function ImGui.IsWindowCollapsed() end

---@param flags? integer
---@return boolean
function ImGui.IsWindowFocused(flags) end

---@param flags? integer
---@return boolean
function ImGui.IsWindowHovered(flags) end

---@return number x, number y
function ImGui.GetWindowPos() end

---@return number width, number height
function ImGui.GetWindowSize() end

---@return number
function ImGui.GetWindowWidth() end

---@return number
function ImGui.GetWindowHeight() end

---@param x number
---@param y number
---@param cond? integer
---@param pivot_x? number
---@param pivot_y? number
function ImGui.SetNextWindowPos(x, y, cond, pivot_x, pivot_y) end

---@param width number
---@param height number
---@param cond? integer
function ImGui.SetNextWindowSize(width, height, cond) end

---@param min_x number
---@param min_y number
---@param max_x number
---@param max_y number
function ImGui.SetNextWindowSizeConstraints(min_x, min_y, max_x, max_y) end

---@param width number
---@param height number
function ImGui.SetNextWindowContentSize(width, height) end

---@param collapsed boolean
---@param cond? integer
function ImGui.SetNextWindowCollapsed(collapsed, cond) end

function ImGui.SetNextWindowFocus() end

---@param alpha number
function ImGui.SetNextWindowBgAlpha(alpha) end

---@overload fun(name: string, x: number, y: number, cond?: integer)
---@param x number
---@param y number
---@param cond? integer
function ImGui.SetWindowPos(x, y, cond) end

---@overload fun(name: string, width: number, height: number, cond?: integer)
---@param width number
---@param height number
---@param cond? integer
function ImGui.SetWindowSize(width, height, cond) end

---@overload fun(name: string, collapsed: boolean, cond?: integer)
---@param collapsed boolean
---@param cond? integer
function ImGui.SetWindowCollapsed(collapsed, cond) end

---@param name? string
function ImGui.SetWindowFocus(name) end

---@param scale number
function ImGui.SetWindowFontScale(scale) end


-- Content region
---@return number x, number y
function ImGui.GetContentRegionMax() end

---@return number x, number y
function ImGui.GetContentRegionAvail() end

---@return number x, number y
function ImGui.GetWindowContentRegionMin() end

---@return number x, number y
function ImGui.GetWindowContentRegionMax() end


-- Scrolling
---@return number
function ImGui.GetScrollX() end

---@return number
function ImGui.GetScrollY() end

---@return number
function ImGui.GetScrollMaxX() end

---@return number
function ImGui.GetScrollMaxY() end

---@param scroll number
function ImGui.SetScrollX(scroll) end

---@param scroll number
function ImGui.SetScrollY(scroll) end

---center_ratio defaults to 0.5.
---@param center_ratio? number
function ImGui.SetScrollHereX(center_ratio) end

---center_ratio defaults to 0.5.
---@param center_ratio? number
function ImGui.SetScrollHereY(center_ratio) end

---center_ratio defaults to 0.5.
---@param local_pos number
---@param center_ratio? number
function ImGui.SetScrollFromPosX(local_pos, center_ratio) end

---center_ratio defaults to 0.5.
---@param local_pos number
---@param center_ratio? number
function ImGui.SetScrollFromPosY(local_pos, center_ratio) end


-- Parameter stacks (shared)
---Float RGBA components use 0..1.
---@param index integer
---@param r number
---@param g number
---@param b number
---@param a number
function ImGui.PushStyleColor(index, r, g, b, a) end

---count defaults to 1.
---@param count? integer
function ImGui.PopStyleColor(count) end

---@overload fun(index: integer, x: number, y: number)
---@param index integer
---@param value number
function ImGui.PushStyleVar(index, value) end

---count defaults to 1.
---@param count? integer
function ImGui.PopStyleVar(count) end

---@param index integer
---@return number r, number g, number b, number a
function ImGui.GetStyleColorVec4(index) end

---@return number
function ImGui.GetFontSize() end

---@return number x, number y
function ImGui.GetFontTexUvWhitePixel() end


-- Parameter stacks (current window)
---@param width number
function ImGui.PushItemWidth(width) end

function ImGui.PopItemWidth() end

---@param width number
function ImGui.SetNextItemWidth(width) end

---@return number
function ImGui.CalcItemWidth() end

---wrap_pos defaults to 0.
---@param wrap_pos? number
function ImGui.PushTextWrapPos(wrap_pos) end

function ImGui.PopTextWrapPos() end

---@param repeat_buttons boolean
function ImGui.PushButtonRepeat(repeat_buttons) end

function ImGui.PopButtonRepeat() end


-- Cursor / layout
function ImGui.Separator() end

---@param text string
function ImGui.SeparatorText(text) end

---disabled defaults to true.
---@param disabled? boolean
function ImGui.BeginDisabled(disabled) end

function ImGui.EndDisabled() end

---Detached snapshot of the exposed style fields; modifying it does not change ImGui.
---@return ImGuiStyleSnapshot
function ImGui.GetStyle() end

---Defaults: offset=0, spacing=-1.
---@param offset? number
---@param spacing? number
function ImGui.SameLine(offset, spacing) end

function ImGui.NewLine() end

function ImGui.Spacing() end

---@param width number
---@param height number
function ImGui.Dummy(width, height) end

---width defaults to 0 (style indent spacing).
---@param width? number
function ImGui.Indent(width) end

---width defaults to 0 (style indent spacing).
---@param width? number
function ImGui.Unindent(width) end

function ImGui.BeginGroup() end

function ImGui.EndGroup() end

---@return number x, number y
function ImGui.GetCursorPos() end

---@return number
function ImGui.GetCursorPosX() end

---@return number
function ImGui.GetCursorPosY() end

---@param x number
---@param y number
function ImGui.SetCursorPos(x, y) end

---@param x number
function ImGui.SetCursorPosX(x) end

---@param y number
function ImGui.SetCursorPosY(y) end

---@return number x, number y
function ImGui.GetCursorStartPos() end

---@return number x, number y
function ImGui.GetCursorScreenPos() end

---@param x number
---@param y number
function ImGui.SetCursorScreenPos(x, y) end

function ImGui.AlignTextToFramePadding() end

---@return number
function ImGui.GetTextLineHeight() end

---@return number
function ImGui.GetTextLineHeightWithSpacing() end

---@return number
function ImGui.GetFrameHeight() end

---@return number
function ImGui.GetFrameHeightWithSpacing() end


-- ID stack
---Pushes one whole string or integer onto the ID stack.
---@param id string|integer
function ImGui.PushID(id) end

function ImGui.PopID() end

---Hashes one whole string in the current ID stack.
---@param id string
---@return integer
function ImGui.GetID(id) end


-- Text widgets
---Renders one whole string without format substitution.
---@param text string
function ImGui.TextUnformatted(text) end

---@param text string
function ImGui.Text(text) end

---Float RGBA components use 0..1.
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


-- Main widgets
---@param label string
---@param size_x? number
---@param size_y? number
---@return boolean pressed
function ImGui.Button(label, size_x, size_y) end

---@param label string
---@return boolean pressed
function ImGui.SmallButton(label) end

---@param id string
---@param size_x number
---@param size_y number
---@param flags? ImGuiButtonFlags # omitted/nil: None (left mouse button)
---@return boolean pressed
function ImGui.InvisibleButton(id, size_x, size_y, flags) end

---@param id string
---@param direction integer
---@return boolean pressed
function ImGui.ArrowButton(id, direction) end

---@param label string
---@param value boolean
---@return boolean value, boolean changed
function ImGui.Checkbox(label, value) end

---@overload fun(label: string, active: boolean): boolean
---@param label string
---@param value integer
---@param button_value integer
---@return integer value, boolean pressed
function ImGui.RadioButton(label, value, button_value) end

---Defaults: size_x=-FLT_MIN, size_y=0, overlay=nil.
---@param fraction number
---@param size_x? number
---@param size_y? number
---@param overlay? string
function ImGui.ProgressBar(fraction, size_x, size_y, overlay) end

function ImGui.Bullet() end


-- Combo
---@param label string
---@param preview string
---@param flags? integer
---@return boolean open
function ImGui.BeginCombo(label, preview, flags) end

function ImGui.EndCombo() end

---current uses a zero-based index. String form uses NUL-separated items, ending with two NUL bytes.
---@overload fun(label: string, current: integer, items: string, popup_max?: integer): integer, boolean
---@param label string
---@param current integer
---@param items string[]
---@param items_count integer
---@param popup_max? integer
---@return integer current, boolean changed
function ImGui.Combo(label, current, items, items_count, popup_max) end


-- Drag
---Defaults: speed=1, min=0, max=0, format="%.3f".
---@param label string
---@param value number
---@param speed? number
---@param min? number
---@param max? number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number value, boolean changed
function ImGui.DragFloat(label, value, speed, min, max, format, flags) end

---2 components; returns a new array. Defaults: speed=1, min=0, max=0, format="%.3f".
---@param label string
---@param value number[]
---@param speed? number
---@param min? number
---@param max? number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number[] value, boolean changed
function ImGui.DragFloat2(label, value, speed, min, max, format, flags) end

---3 components; returns a new array. Defaults: speed=1, min=0, max=0, format="%.3f".
---@param label string
---@param value number[]
---@param speed? number
---@param min? number
---@param max? number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number[] value, boolean changed
function ImGui.DragFloat3(label, value, speed, min, max, format, flags) end

---4 components; returns a new array. Defaults: speed=1, min=0, max=0, format="%.3f".
---@param label string
---@param value number[]
---@param speed? number
---@param min? number
---@param max? number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number[] value, boolean changed
function ImGui.DragFloat4(label, value, speed, min, max, format, flags) end

---Defaults: speed=1, min=0, max=0, format="%d".
---@param label string
---@param value integer
---@param speed? number
---@param min? integer
---@param max? integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer value, boolean changed
function ImGui.DragInt(label, value, speed, min, max, format, flags) end

---2 components; returns a new array. Defaults: speed=1, min=0, max=0, format="%d".
---@param label string
---@param value integer[]
---@param speed? number
---@param min? integer
---@param max? integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer[] value, boolean changed
function ImGui.DragInt2(label, value, speed, min, max, format, flags) end

---3 components; returns a new array. Defaults: speed=1, min=0, max=0, format="%d".
---@param label string
---@param value integer[]
---@param speed? number
---@param min? integer
---@param max? integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer[] value, boolean changed
function ImGui.DragInt3(label, value, speed, min, max, format, flags) end

---4 components; returns a new array. Defaults: speed=1, min=0, max=0, format="%d".
---@param label string
---@param value integer[]
---@param speed? number
---@param min? integer
---@param max? integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer[] value, boolean changed
function ImGui.DragInt4(label, value, speed, min, max, format, flags) end


-- Sliders
---Default format: "%.3f".
---@param label string
---@param value number
---@param min number
---@param max number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number value, boolean changed
function ImGui.SliderFloat(label, value, min, max, format, flags) end

---2 components; returns a new array. Default format: "%.3f".
---@param label string
---@param value number[]
---@param min number
---@param max number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number[] value, boolean changed
function ImGui.SliderFloat2(label, value, min, max, format, flags) end

---3 components; returns a new array. Default format: "%.3f".
---@param label string
---@param value number[]
---@param min number
---@param max number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number[] value, boolean changed
function ImGui.SliderFloat3(label, value, min, max, format, flags) end

---4 components; returns a new array. Default format: "%.3f".
---@param label string
---@param value number[]
---@param min number
---@param max number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number[] value, boolean changed
function ImGui.SliderFloat4(label, value, min, max, format, flags) end

---Defaults: min_degrees=-360, max_degrees=360, format="%.0f deg".
---@param label string
---@param radians number
---@param min_degrees? number
---@param max_degrees? number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number radians, boolean changed
function ImGui.SliderAngle(label, radians, min_degrees, max_degrees, format, flags) end

---Default format: "%d".
---@param label string
---@param value integer
---@param min integer
---@param max integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer value, boolean changed
function ImGui.SliderInt(label, value, min, max, format, flags) end

---2 components; returns a new array. Default format: "%d".
---@param label string
---@param value integer[]
---@param min integer
---@param max integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer[] value, boolean changed
function ImGui.SliderInt2(label, value, min, max, format, flags) end

---3 components; returns a new array. Default format: "%d".
---@param label string
---@param value integer[]
---@param min integer
---@param max integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer[] value, boolean changed
function ImGui.SliderInt3(label, value, min, max, format, flags) end

---4 components; returns a new array. Default format: "%d".
---@param label string
---@param value integer[]
---@param min integer
---@param max integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer[] value, boolean changed
function ImGui.SliderInt4(label, value, min, max, format, flags) end

---@param label string
---@param size_x number
---@param size_y number
---@param value number
---@param min number
---@param max number
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return number value, boolean changed
function ImGui.VSliderFloat(label, size_x, size_y, value, min, max, format, flags) end

---@param label string
---@param size_x number
---@param size_y number
---@param value integer
---@param min integer
---@param max integer
---@param format? string
---@param flags? ImGuiSliderFlags # omitted/nil: None
---@return integer value, boolean changed
function ImGui.VSliderInt(label, size_x, size_y, value, min, max, format, flags) end


-- Input with keyboard
---@param label string
---@param text string
---@param flags? integer
---@return string text, boolean changed
function ImGui.InputText(label, text, flags) end

---@param label string
---@param text string
---@param size_x? number
---@param size_y? number
---@param flags? integer
---@return string text, boolean changed
function ImGui.InputTextMultiline(label, text, size_x, size_y, flags) end

---@param label string
---@param hint string
---@param text string
---@param flags? integer
---@return string text, boolean changed
function ImGui.InputTextWithHint(label, hint, text, flags) end

---Defaults: step=0, step_fast=0.
---@param label string
---@param value number
---@param step? number
---@param step_fast? number
---@param format? string
---@param flags? integer
---@return number value, boolean changed
function ImGui.InputFloat(label, value, step, step_fast, format, flags) end

---2 components; returns a new array.
---@param label string
---@param value number[]
---@param format? string
---@param flags? integer
---@return number[] value, boolean changed
function ImGui.InputFloat2(label, value, format, flags) end

---3 components; returns a new array.
---@param label string
---@param value number[]
---@param format? string
---@param flags? integer
---@return number[] value, boolean changed
function ImGui.InputFloat3(label, value, format, flags) end

---4 components; returns a new array.
---@param label string
---@param value number[]
---@param format? string
---@param flags? integer
---@return number[] value, boolean changed
function ImGui.InputFloat4(label, value, format, flags) end

---Defaults: step=1, step_fast=100.
---@param label string
---@param value integer
---@param step? integer
---@param step_fast? integer
---@param flags? integer
---@return integer value, boolean changed
function ImGui.InputInt(label, value, step, step_fast, flags) end

---2 components; returns a new array.
---@param label string
---@param value integer[]
---@param flags? integer
---@return integer[] value, boolean changed
function ImGui.InputInt2(label, value, flags) end

---3 components; returns a new array.
---@param label string
---@param value integer[]
---@param flags? integer
---@return integer[] value, boolean changed
function ImGui.InputInt3(label, value, flags) end

---4 components; returns a new array.
---@param label string
---@param value integer[]
---@param flags? integer
---@return integer[] value, boolean changed
function ImGui.InputInt4(label, value, flags) end

---Defaults: step=0, step_fast=0, format="%.6f".
---@param label string
---@param value number
---@param step? number
---@param step_fast? number
---@param format? string
---@param flags? integer
---@return number value, boolean changed
function ImGui.InputDouble(label, value, step, step_fast, format, flags) end


-- Color editor / picker
---3 float color components in 0..1; returns a new array.
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean changed
function ImGui.ColorEdit3(label, color, flags) end

---4 float color components in 0..1; returns a new array.
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean changed
function ImGui.ColorEdit4(label, color, flags) end

---3 float color components in 0..1; returns a new array.
---@param label string
---@param color number[]
---@param flags? integer
---@return number[] color, boolean changed
function ImGui.ColorPicker3(label, color, flags) end

---4 float color components in 0..1; returns a new array.
---@param label string
---@param color number[]
---@param flags? integer
---@param reference_color? number[] # four float components in 0..1 for the original-color preview; omitted/nil: no reference
---@return number[] color, boolean changed
function ImGui.ColorPicker4(label, color, flags, reference_color) end

---Four float color components in 0..1.
---@param id string
---@param color number[]
---@param flags? integer
---@param size_x? number
---@param size_y? number
---@return boolean pressed
function ImGui.ColorButton(id, color, flags, size_x, size_y) end

---@param flags integer
function ImGui.SetColorEditOptions(flags) end


-- Trees
---@param label string
---@param text? string
---@return boolean open
function ImGui.TreeNode(label, text) end

---@param label string
---@param flags? integer
---@param text? string
---@return boolean open
function ImGui.TreeNodeEx(label, flags, text) end

---@param id string
function ImGui.TreePush(id) end

function ImGui.TreePop() end

---@return number
function ImGui.GetTreeNodeToLabelSpacing() end

---@overload fun(label: string, flags?: integer): boolean
---@param label string
---@param open boolean
---@param flags? integer
---@return boolean open, boolean expanded
function ImGui.CollapsingHeader(label, open, flags) end

---@param open boolean
---@param cond? integer
function ImGui.SetNextItemOpen(open, cond) end


-- Selectables
---Returns the updated selected state only. Use IsItemClicked() to query the click.
---@param label string
---@param selected? boolean
---@param flags? integer
---@param size_x? number
---@param size_y? number
---@return boolean selected
function ImGui.Selectable(label, selected, flags, size_x, size_y) end


-- List boxes
---current uses a zero-based index; height_in_items defaults to -1.
---@param label string
---@param current integer
---@param items string[]
---@param items_count integer
---@param height_in_items? integer
---@return integer current, boolean changed
function ImGui.ListBox(label, current, items, items_count, height_in_items) end

---Pixel-size form requires both dimensions. The two-argument form auto-sizes from an item count.
---@overload fun(label: string, items_count: integer): boolean
---@param label string
---@param size_x number
---@param size_y number
---@return boolean visible
function ImGui.BeginListBox(label, size_x, size_y) end

function ImGui.EndListBox() end


-- Value()
---A nil prefix does nothing. Numeric values use the float overload.
---@param prefix string|nil
---@param value number|boolean
---@param float_format? string
function ImGui.Value(prefix, value, float_format) end


-- Menus
---@return boolean open
function ImGui.BeginMenuBar() end

function ImGui.EndMenuBar() end

---@return boolean open
function ImGui.BeginMainMenuBar() end

function ImGui.EndMainMenuBar() end

---enabled defaults to true.
---@param label string
---@param enabled? boolean
---@return boolean open
function ImGui.BeginMenu(label, enabled) end

function ImGui.EndMenu() end

---@overload fun(label: string, shortcut?: string): boolean
---@param label string
---@param shortcut string|nil
---@param selected boolean
---@return boolean selected, boolean pressed
function ImGui.MenuItem(label, shortcut, selected) end


-- Tooltips
function ImGui.BeginTooltip() end

function ImGui.EndTooltip() end

---@param text string
function ImGui.SetTooltip(text) end


-- Popups / modals
---@param id string
---@param flags? integer
---@return boolean open
function ImGui.BeginPopup(id, flags) end

---Without an open boolean, returns draw only; flags stay in slot 3.
---@overload fun(name: string, open?: nil, flags?: integer): boolean
---@param name string
---@param open boolean
---@param flags? integer
---@return boolean open, boolean draw
function ImGui.BeginPopupModal(name, open, flags) end

function ImGui.EndPopup() end

---@param id string
---@param flags? integer
function ImGui.OpenPopup(id, flags) end

---Requests opening on an item click; always returns true. flags defaults to 1.
---@param id? string
---@param flags? integer
---@return boolean
function ImGui.OpenPopupContextItem(id, flags) end

function ImGui.CloseCurrentPopup() end

---flags defaults to 1 (right mouse button).
---@param id? string
---@param flags? integer
---@return boolean open
function ImGui.BeginPopupContextItem(id, flags) end

---flags defaults to 1 (right mouse button).
---@param id? string
---@param flags? integer
---@return boolean open
function ImGui.BeginPopupContextWindow(id, flags) end

---flags defaults to 1 (right mouse button).
---@param id? string
---@param flags? integer
---@return boolean open
function ImGui.BeginPopupContextVoid(id, flags) end

---@param id string
---@param flags? integer
---@return boolean
function ImGui.IsPopupOpen(id, flags) end


-- Columns
---Defaults: count=1, id=nil, border=true.
---@param count? integer
---@param id? string
---@param border? boolean
function ImGui.Columns(count, id, border) end

function ImGui.NextColumn() end

---@return integer
function ImGui.GetColumnIndex() end

---index defaults to -1 (current column).
---@param index? integer
---@return number
function ImGui.GetColumnWidth(index) end

---@param index integer
---@param width number
function ImGui.SetColumnWidth(index, width) end

---index defaults to -1 (current column).
---@param index? integer
---@return number
function ImGui.GetColumnOffset(index) end

---@param index integer
---@param offset number
function ImGui.SetColumnOffset(index, offset) end

---@return integer
function ImGui.GetColumnsCount() end


-- Tab bars
---@param id string
---@param flags? integer
---@return boolean open
function ImGui.BeginTabBar(id, flags) end

function ImGui.EndTabBar() end

---@overload fun(label: string): boolean
---@param label string
---@param open boolean
---@param flags? integer
---@return boolean open, boolean selected
function ImGui.BeginTabItem(label, open, flags) end

function ImGui.EndTabItem() end

---@param label string
function ImGui.SetTabItemClosed(label) end


-- Logging
---depth defaults to -1.
---@param depth? integer
function ImGui.LogToTTY(depth) end

---Defaults: depth=-1, filename=nil.
---@param depth? integer
---@param filename? string
function ImGui.LogToFile(depth, filename) end

---depth defaults to -1.
---@param depth? integer
function ImGui.LogToClipboard(depth) end

function ImGui.LogFinish() end

function ImGui.LogButtons() end

---@param text string
function ImGui.LogText(text) end


-- Clipping
---@param min_x number
---@param min_y number
---@param max_x number
---@param max_y number
---@param intersect boolean
function ImGui.PushClipRect(min_x, min_y, max_x, max_y, intersect) end

function ImGui.PopClipRect() end


-- Focus / activation
function ImGui.SetItemDefaultFocus() end

---offset defaults to 0.
---@param offset? integer
function ImGui.SetKeyboardFocusHere(offset) end


-- Item utilities
---@param flags? integer
---@return boolean
function ImGui.IsItemHovered(flags) end

---@return boolean
function ImGui.IsItemActive() end

---@return boolean
function ImGui.IsItemFocused() end

---button defaults to 0 (left).
---@param button? integer
---@return boolean
function ImGui.IsItemClicked(button) end

---@return boolean
function ImGui.IsItemVisible() end

---@return boolean
function ImGui.IsItemEdited() end

---@return boolean
function ImGui.IsItemActivated() end

---@return boolean
function ImGui.IsItemDeactivated() end

---@return boolean
function ImGui.IsItemDeactivatedAfterEdit() end

---@return boolean
function ImGui.IsItemToggledOpen() end

---@return boolean
function ImGui.IsAnyItemHovered() end

---@return boolean
function ImGui.IsAnyItemActive() end

---@return boolean
function ImGui.IsAnyItemFocused() end

---@return number x, number y
function ImGui.GetItemRectMin() end

---@return number x, number y
function ImGui.GetItemRectMax() end

---@return number x, number y
function ImGui.GetItemRectSize() end


-- Miscellaneous utilities
---@overload fun(min_x: number, min_y: number, max_x: number, max_y: number): boolean
---@param size_x number
---@param size_y number
---@return boolean
function ImGui.IsRectVisible(size_x, size_y) end

---@return number
function ImGui.GetTime() end

---@return integer
function ImGui.GetFrameCount() end

---@param index integer
---@return string
function ImGui.GetStyleColorName(index) end

---@param id integer
---@param size_x number
---@param size_y number
---@param flags? integer
---@return boolean visible
function ImGui.BeginChildFrame(id, size_x, size_y, flags) end

function ImGui.EndChildFrame() end


-- Text utilities
---Measures the whole string; use string.sub beforehand to measure a substring.
---@param text string
---@param hide_text_after_double_hash? boolean # default false
---@param wrap_width? number # default -1
---@return number width, number height
function ImGui.CalcTextSize(text, hide_text_after_double_hash, wrap_width) end


-- Keyboard inputs
---@param key integer
---@return boolean
function ImGui.IsKeyDown(key) end

---repeat_key defaults to true.
---@param key integer
---@param repeat_key? boolean
---@return boolean
function ImGui.IsKeyPressed(key, repeat_key) end

---@param key integer
---@return boolean
function ImGui.IsKeyReleased(key) end

---@param key integer
---@param repeat_delay number
---@param repeat_rate number
---@return integer
function ImGui.GetKeyPressedAmount(key, repeat_delay, repeat_rate) end

---want_capture defaults to true.
---@param want_capture? boolean
function ImGui.SetNextFrameWantCaptureKeyboard(want_capture) end


-- Mouse inputs
---@param button integer
---@return boolean
function ImGui.IsMouseDown(button) end

---repeat_click defaults to false.
---@param button integer
---@param repeat_click? boolean
---@return boolean
function ImGui.IsMouseClicked(button, repeat_click) end

---@param button integer
---@return boolean
function ImGui.IsMouseReleased(button) end

---@param button integer
---@return boolean
function ImGui.IsMouseDoubleClicked(button) end

---clip defaults to true.
---@param min_x number
---@param min_y number
---@param max_x number
---@param max_y number
---@param clip? boolean
---@return boolean
function ImGui.IsMouseHoveringRect(min_x, min_y, max_x, max_y, clip) end

---@return boolean
function ImGui.IsAnyMouseDown() end

---@return number x, number y
function ImGui.GetMousePos() end

---@return number x, number y
function ImGui.GetMousePosOnOpeningCurrentPopup() end

---lock_threshold defaults to -1 (style threshold).
---@param button integer
---@param lock_threshold? number
---@return boolean
function ImGui.IsMouseDragging(button, lock_threshold) end

---Defaults: button=0, lock_threshold=-1.
---@param button? integer
---@param lock_threshold? number
---@return number x, number y
function ImGui.GetMouseDragDelta(button, lock_threshold) end

---button defaults to 0 (left).
---@param button? integer
function ImGui.ResetMouseDragDelta(button) end

---@return integer
function ImGui.GetMouseCursor() end

---@param cursor integer
function ImGui.SetMouseCursor(cursor) end

---want_capture defaults to true.
---@param want_capture? boolean
function ImGui.SetNextFrameWantCaptureMouse(want_capture) end


-- Clipboard
---@return string?
function ImGui.GetClipboardText() end

---@param text string
function ImGui.SetClipboardText(text) end

-- Enum tables (name -> integer). Values mirror the entries registered in
-- src/core/scripting/libraries/ImGui.cpp using the bundled ImGui header.
-- Existing legacy aliases are retained for script compatibility.

---@enum ImGuiWindowFlags
ImGuiWindowFlags = {
    None = 0, NoTitleBar = 1, NoResize = 2, NoMove = 4, NoScrollbar = 8, NoScrollWithMouse = 16,
    NoCollapse = 32, AlwaysAutoResize = 64, NoBackground = 128, NoSavedSettings = 256,
    NoMouseInputs = 512, MenuBar = 1024, HorizontalScrollbar = 2048, NoFocusOnAppearing = 4096,
    NoBringToFrontOnFocus = 8192, AlwaysVerticalScrollbar = 16384,
    AlwaysHorizontalScrollbar = 32768, NoNavInputs = 65536, NoNavFocus = 131072,
    UnsavedDocument = 262144, NoNav = 196608, NoDecoration = 43, NoInputs = 197120,
    ChildWindow = 16777216, Tooltip = 33554432, Popup = 67108864, Modal = 134217728,
    ChildMenu = 268435456, NavFlattened = 536870912, AlwaysUseWindowPadding = 1073741824,
}

---@enum ImGuiChildFlags
ImGuiChildFlags = {
    None = 0, Borders = 1, AlwaysUseWindowPadding = 2, ResizeX = 4, ResizeY = 8, AutoResizeX = 16,
    AutoResizeY = 32, AlwaysAutoResize = 64, FrameStyle = 128, NavFlattened = 256, Border = 1,
}

---@enum ImGuiCond
ImGuiCond = {
    None = 0, Always = 1, Once = 2, FirstUseEver = 4, Appearing = 8,
}

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
ImGuiDir = {
    None = -1, Left = 0, Right = 1, Up = 2, Down = 3, COUNT = 4,
}

---@enum ImGuiKey
ImGuiKey = {
    None = 0, NamedKey_BEGIN = 512, Tab = 512, LeftArrow = 513, RightArrow = 514, UpArrow = 515,
    DownArrow = 516, PageUp = 517, PageDown = 518, Home = 519, End = 520, Insert = 521,
    Delete = 522, Backspace = 523, Space = 524, Enter = 525, Escape = 526, LeftCtrl = 527,
    LeftShift = 528, LeftAlt = 529, LeftSuper = 530, RightCtrl = 531, RightShift = 532,
    RightAlt = 533, RightSuper = 534, Menu = 535, ["0"] = 536, ["1"] = 537, ["2"] = 538,
    ["3"] = 539, ["4"] = 540, ["5"] = 541, ["6"] = 542, ["7"] = 543, ["8"] = 544, ["9"] = 545,
    A = 546, B = 547, C = 548, D = 549, E = 550, F = 551, G = 552, H = 553, I = 554, J = 555,
    K = 556, L = 557, M = 558, N = 559, O = 560, P = 561, Q = 562, R = 563, S = 564, T = 565,
    U = 566, V = 567, W = 568, X = 569, Y = 570, Z = 571, F1 = 572, F2 = 573, F3 = 574, F4 = 575,
    F5 = 576, F6 = 577, F7 = 578, F8 = 579, F9 = 580, F10 = 581, F11 = 582, F12 = 583, F13 = 584,
    F14 = 585, F15 = 586, F16 = 587, F17 = 588, F18 = 589, F19 = 590, F20 = 591, F21 = 592,
    F22 = 593, F23 = 594, F24 = 595, Apostrophe = 596, Comma = 597, Minus = 598, Period = 599,
    Slash = 600, Semicolon = 601, Equal = 602, LeftBracket = 603, Backslash = 604,
    RightBracket = 605, GraveAccent = 606, CapsLock = 607, ScrollLock = 608, NumLock = 609,
    PrintScreen = 610, Pause = 611, Keypad0 = 612, Keypad1 = 613, Keypad2 = 614, Keypad3 = 615,
    Keypad4 = 616, Keypad5 = 617, Keypad6 = 618, Keypad7 = 619, Keypad8 = 620, Keypad9 = 621,
    KeypadDecimal = 622, KeypadDivide = 623, KeypadMultiply = 624, KeypadSubtract = 625,
    KeypadAdd = 626, KeypadEnter = 627, KeypadEqual = 628, AppBack = 629, AppForward = 630,
    Oem102 = 631, GamepadStart = 632, GamepadBack = 633, GamepadFaceLeft = 634,
    GamepadFaceRight = 635, GamepadFaceUp = 636, GamepadFaceDown = 637, GamepadDpadLeft = 638,
    GamepadDpadRight = 639, GamepadDpadUp = 640, GamepadDpadDown = 641, GamepadL1 = 642,
    GamepadR1 = 643, GamepadL2 = 644, GamepadR2 = 645, GamepadL3 = 646, GamepadR3 = 647,
    GamepadLStickLeft = 648, GamepadLStickRight = 649, GamepadLStickUp = 650,
    GamepadLStickDown = 651, GamepadRStickLeft = 652, GamepadRStickRight = 653,
    GamepadRStickUp = 654, GamepadRStickDown = 655, MouseLeft = 656, MouseRight = 657,
    MouseMiddle = 658, MouseX1 = 659, MouseX2 = 660, MouseWheelX = 661, MouseWheelY = 662,
    ReservedForModCtrl = 663, ReservedForModShift = 664, ReservedForModAlt = 665,
    ReservedForModSuper = 666, NamedKey_END = 667, Mod_None = 0, Mod_Ctrl = 4096, Mod_Shift = 8192,
    Mod_Alt = 16384, Mod_Super = 32768, Mod_Mask_ = 61440, NamedKey_COUNT = 155, COUNT = 667,
    Mod_Shortcut = 4096, ModCtrl = 4096, ModShift = 8192, ModAlt = 16384, ModSuper = 32768,
    KeyPadEnter = 627,
}

---@enum ImGuiMouseButton
ImGuiMouseButton = {
    Left = 0, Right = 1, Middle = 2, COUNT = 5, ImGuiMouseButton_COUNT = 5,
    ImGuiMouseButton_Left = 0, ImGuiMouseButton_Middle = 2, ImGuiMouseButton_Right = 1,
}

---@enum ImGuiMouseCursor
ImGuiMouseCursor = {
    None = -1, Arrow = 0, TextInput = 1, ResizeAll = 2, ResizeNS = 3, ResizeEW = 4, ResizeNESW = 5,
    ResizeNWSE = 6, Hand = 7, Wait = 8, Progress = 9, NotAllowed = 10, COUNT = 11,
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
    None = 0, ChildWindows = 1, RootWindow = 2, AnyWindow = 4, NoPopupHierarchy = 8,
    RootAndChildWindows = 3,
}

---@enum ImGuiComboFlags
ImGuiComboFlags = {
    None = 0, PopupAlignLeft = 1, HeightSmall = 2, HeightRegular = 4, HeightLarge = 8,
    HeightLargest = 16, NoArrowButton = 32, NoPreview = 64, WidthFitPreview = 128,
    HeightMask_ = 30, HeightMask = 30,
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

---@enum ImGuiSliderFlags
ImGuiSliderFlags = {
    None = 0,
    Logarithmic = 32,
    NoRoundToFormat = 64,
    NoInput = 128,
    WrapAround = 256,
    ClampOnInput = 512,
    ClampZeroRange = 1024,
    NoSpeedTweaks = 2048,
    AlwaysClamp = 1536,
    InvalidMask_ = 0x7000000F,
}

---@enum ImGuiButtonFlags
ImGuiButtonFlags = {
    None = 0,
    MouseButtonLeft = 1,
    MouseButtonRight = 2,
    MouseButtonMiddle = 4,
    MouseButtonMask_ = 7,
    EnableNav = 8,
}

---@enum ImGuiColorEditFlags
ImGuiColorEditFlags = {
    None = 0, NoAlpha = 2, NoPicker = 4, NoOptions = 8, NoSmallPreview = 16, NoInputs = 32,
    NoTooltip = 64, NoLabel = 128, NoSidePreview = 256, NoDragDrop = 512, NoBorder = 1024,
    AlphaOpaque = 2048, AlphaNoBg = 4096, AlphaPreviewHalf = 8192, AlphaBar = 65536, HDR = 524288,
    DisplayRGB = 1048576, DisplayHSV = 2097152, DisplayHex = 4194304, Uint8 = 8388608,
    Float = 16777216, PickerHueBar = 33554432, PickerHueWheel = 67108864, InputRGB = 134217728,
    InputHSV = 268435456, DefaultOptions_ = 177209344, AlphaMask_ = 14338, DisplayMask_ = 7340032,
    DataTypeMask_ = 25165824, PickerMask_ = 100663296, InputMask_ = 402653184, AlphaPreview = 0,
}

---@enum ImGuiTreeNodeFlags
ImGuiTreeNodeFlags = {
    None = 0, Selected = 1, Framed = 2, AllowOverlap = 4, NoTreePushOnOpen = 8,
    NoAutoOpenOnLog = 16, DefaultOpen = 32, OpenOnDoubleClick = 64, OpenOnArrow = 128, Leaf = 256,
    Bullet = 512, FramePadding = 1024, SpanAvailWidth = 2048, SpanFullWidth = 4096,
    SpanLabelWidth = 8192, SpanAllColumns = 16384, LabelSpanAllColumns = 32768,
    NavLeftJumpsToParent = 131072, CollapsingHeader = 26, DrawLinesNone = 262144,
    DrawLinesFull = 524288, DrawLinesToNodes = 1048576, NavLeftJumpsBackHere = 131072,
    SpanTextWidth = 8192, AllowItemOverlap = 4,
}

---@enum ImGuiSelectableFlags
ImGuiSelectableFlags = {
    None = 0, NoAutoClosePopups = 1, SpanAllColumns = 2, AllowDoubleClick = 4, Disabled = 8,
    AllowOverlap = 16, Highlight = 32, DontClosePopups = 1, AllowItemOverlap = 16,
}

---@enum ImGuiPopupFlags
ImGuiPopupFlags = {
    None = 0, MouseButtonLeft = 0, MouseButtonRight = 1, MouseButtonMiddle = 2,
    MouseButtonMask_ = 31, MouseButtonDefault_ = 1, NoReopen = 32, NoOpenOverExistingPopup = 128,
    NoOpenOverItems = 256, AnyPopupId = 1024, AnyPopupLevel = 2048, AnyPopup = 3072,
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
    None = 0, UnsavedDocument = 1, SetSelected = 2, NoCloseWithMiddleMouseButton = 4, NoPushId = 8,
    NoTooltip = 16, NoReorder = 32, Leading = 64, Trailing = 128, NoAssumedClosure = 256,
}

---@enum ImGuiTableFlags
ImGuiTableFlags = {
    None = 0, Resizable = 1, Reorderable = 2, Hideable = 4, Sortable = 8, NoSavedSettings = 16,
    ContextMenuInBody = 32, RowBg = 64, BordersInnerH = 128, BordersOuterH = 256,
    BordersInnerV = 512, BordersOuterV = 1024, BordersH = 384, BordersV = 1536, BordersInner = 640,
    BordersOuter = 1280, Borders = 1920, NoBordersInBody = 2048, NoBordersInBodyUntilResize = 4096,
    SizingFixedFit = 8192, SizingFixedSame = 16384, SizingStretchProp = 24576,
    SizingStretchSame = 32768, NoHostExtendX = 65536, NoHostExtendY = 131072,
    NoKeepColumnsVisible = 262144, PreciseWidths = 524288, NoClip = 1048576, PadOuterX = 2097152,
    NoPadOuterX = 4194304, NoPadInnerX = 8388608, ScrollX = 16777216, ScrollY = 33554432,
    SortMulti = 67108864, SortTristate = 134217728, HighlightHoveredColumn = 268435456,
    SizingMask_ = 57344,
}

---@enum ImGuiTableRowFlags
ImGuiTableRowFlags = {
    None = 0,
    Headers = 1,
}

---@enum ImGuiTableColumnFlags
ImGuiTableColumnFlags = {
    None = 0, Disabled = 1, DefaultHide = 2, DefaultSort = 4, WidthStretch = 8, WidthFixed = 16,
    NoResize = 32, NoReorder = 64, NoHide = 128, NoClip = 256, NoSort = 512,
    NoSortAscending = 1024, NoSortDescending = 2048, NoHeaderLabel = 4096, NoHeaderWidth = 8192,
    PreferSortAscending = 16384, PreferSortDescending = 32768, IndentEnable = 65536,
    IndentDisable = 131072, AngledHeader = 262144, IsEnabled = 16777216, IsVisible = 33554432,
    IsSorted = 67108864, IsHovered = 134217728, WidthMask_ = 24, IndentMask_ = 196608,
    StatusMask_ = 251658240, NoDirectResize_ = 1073741824, IndentDisabled = 131072,
}
