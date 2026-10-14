# YimMenuV2 Lua API

This document lists every global table, class, and function exposed to Lua scripts in YimMenuV2.

Scripts live in `%appdata%/YimMenuV2/scripts`. Each script runs in its own sandboxed Lua (LuaJIT) state with the globals below already available.

In **Settings > Lua Scripts**, click **Open Lua Scripts Folder** to open this directory in Windows Explorer.

At startup, the menu recursively loads `.lua` files beneath the scripts directory. Every descendant of a folder whose name contains the case-sensitive substring `include` (such as `include`, `includes`, or `include_helpers`) is excluded from standalone loading and hidden from the Lua Scripts menu. This includes nested subfolders. These files remain available as modules loaded through `require`.

Scripts in directory paths containing the case-sensitive substring `disabled` are discovered but not automatically loaded. They appear in the Disabled list; clicking an entry loads it. Files under `scripts/disabled` are restored to the same relative path under `scripts`. Files in other folders whose names contain `disabled` are moved to the scripts root when enabled. The leading `disabled/` folder is omitted from displayed names.

The Lua Scripts menu shows loaded scripts in the **Enabled** listbox and unloaded or never-loaded scripts in a **Disabled** listbox beside it. Paused scripts remain Enabled and are marked **(Paused)**; use **Pause/Resume** to control execution. **Disable** unloads a running script and preserves its directory structure: `scripts/foldera/folderb/test.lua` becomes `scripts/disabled/foldera/folderb/test.lua`, so it stays disabled after restarting. Enabling restores its original path. **Reload** preserves its current path. File moves refuse to overwrite existing destination files; equal filenames in different folders remain independent. Newly added scripts appear in the Disabled list after the periodic directory refresh.

## Contents

- [Conventions](#conventions)
- [Standard libraries](#standard-libraries)
- [os](#os)
- [require](#require)
- **Core / UI**: [notify](#notify) · [log](#log) · [util](#util) · [script](#script) · [event](#event) · [menu](#menu) · [commandmgr](#commandmgr) · [ImGui](#imgui)
- **Memory**: [memory](#memory) · [pointer](#pointer)
- **Math**: [Vector3](#vector3)
- **Entities**: [Entity](#entity) · [Ped](#ped) · [Vehicle](#vehicle) · [entities](#entities)
- **Players**: [Player](#player) · [players](#players)
- **Game scripts**: [ScriptGlobal](#scriptglobal) · [ScriptLocal](#scriptlocal) · [ScriptPointer](#scriptpointer) · [ScriptPatch](#scriptpatch) · [ScriptFunction](#scriptfunction) · [scripts](#scripts)
- **Natives & online**: [natives](#natives) · [network](#network) · [tunables](#tunables) · [stats](#stats) · [transactions](#transactions)
- **Files**: [FileMgr](#filemgr)
- [internal](#internal)

---

## Conventions

- `table.func(args)` — a function called on a global table, e.g. `notify.info(...)`.
- `obj:method(args)` — a method called on an object instance, e.g. `ped:set_health(100)`.
- `Class.new(...)` / `Class(...)` — a constructor that returns a new object.
- Arguments in `[brackets]` are optional. `-> type` describes the return value.
- A **hash** argument accepts either an integer hash or a string name (it's hashed with Joaat automatically).
- A **latent** call yields the current script coroutine until it finishes, so it may only be used inside a script callback.

For the following optional trailing parameters, omit the argument to select the default; an explicit `nil` is not accepted:

| Call | Omitted parameter defaults |
| --- | --- |
| `script.yield()` | `ms = 0` |
| `Entity:get_rotation()` / `Entity:set_rotation(rot)` | `order = 2` |
| `Entity:request_control()` | `timeout = 100` milliseconds |
| `Ped:set_in_vehicle(vehicle)` | `seat = 0` |
| `Ped:give_weapon(weapon)` | `equip = false` |
| `Ped:start_scenario(name)` | `duration = -1`, `play_anim = true`; supplying `play_anim` also requires an integer duration |
| `Ped.create(model, pos)` / `Vehicle.create(model, pos)` | `heading = 0` |
| `ScriptGlobal:at(offset)` / `ScriptLocal:at(offset)` | `size = 0` |
| `Vehicle:set_boost_charge()` | `charge = 100` |

---

## Standard libraries

Scripts get LuaJIT's `base`, `coroutine`, `package`, `table`, `string`, `math`, `debug`, `bit`, and `jit` libraries, plus the restricted [os](#os) library.

The `package` library supports sandboxed module loading. Direct loaders (`load`, `loadstring`, `loadfile`, `dofile`) and `package.loadlib` raise an unsupported-function error. `io` and `ffi` are unavailable. Use [FileMgr](#filemgr) for file access.

## os

Available as the global `os` table and through `require("os")`. These functions retain their normal LuaJIT behavior:

| Function | Description |
| --- | --- |
| `os.clock() -> number` | Approximate CPU time used by the process, in seconds. |
| `os.date([format], [timestamp]) -> string \| table \| nil` | Formats a Unix timestamp in seconds; defaults to the current time and format `%c`. `*t` returns a date table; prefix the format with `!` for UTC. Unsupported timestamps return nil. |
| `os.difftime(t2, t1) -> number` | Difference between two timestamps, in seconds. |
| `os.time([date_table]) -> number \| nil` | Returns Unix seconds for the current time or a local date table; unrepresentable dates return nil. |

Date tables contain `year`, `month`, `day`, `hour`, `min`, `sec`, `wday`, `yday`, and `isdst`. Months are 1–12, weekdays are 1–7 with Sunday = 1, and days of the year are 1–366. For `os.time`, `year`, `month`, and `day` are required; `hour`, `min`, and `sec` default to 12, 0, and 0. Omitted `isdst` lets the platform detect daylight saving time. `wday` and `yday` are ignored, and calendar fields are normalized according to LuaJIT/platform behavior.

`os.execute`, `os.exit`, `os.getenv`, `os.setlocale`, and `os.tmpname` raise a not-supported error. `os.rename` and `os.remove` raise an error directing scripts to [FileMgr](#filemgr); use `FileMgr.RenameFile` and `FileMgr.DeleteFile` instead.

`os` timestamps use **seconds**. `util.time()` continues to return **milliseconds**.

```lua
local timestamp = os.time()
local local_date = os.date("*t", timestamp)
local utc_date = os.date("!*t", timestamp)
local formatted = os.date("%Y-%m-%d %H:%M:%S", timestamp)
local noon = os.time({year = local_date.year, month = local_date.month, day = local_date.day})
```

## require

`require(module_name) -> any` uses Lua's standard module loading and caching in the calling script's state. Files must be descendants of `<MenuRoot>/scripts` (`%appdata%/YimMenuV2/scripts`).

- At script load, `package.path` is populated with `?.lua` and `?/init.lua` patterns for the scripts directory and its existing subfolders. The root is searched first, followed by subfolders in sorted order. Directory paths containing the case-sensitive substring `disabled` are excluded; loading through those directories is also rejected.
- `require("helpers.math")` searches for `helpers/math.lua` or `helpers/math/init.lua`. A bare name such as `require("math_helpers")` can also find `helpers/math_helpers.lua`. Reload the script after adding a new module directory to refresh its search path.
- Relative paths such as `require("helpers/math")` or `require("helpers/math.lua")` are also supported. The optional `.lua` suffix is removed before searching.
- Absolute paths, drive paths, `.` or `..` path components, and embedded NUL characters are rejected. Symbolic links and directory junctions must resolve to Lua files inside the scripts directory.
- Only Lua source files are loaded; bytecode and native modules are rejected. `package.cpath` starts empty, and the searcher list contains only the checked Lua file loader. Preload and DLL searchers are disabled. Changing `package.path` cannot enable loading files outside the scripts directory or inside disabled folders.
- The module receives its requested name as `...` and shares the caller's globals and menu APIs. Its first return value is returned by `require`; without a return value, it uses an explicitly assigned `package.loaded[name]` value or defaults to `true`.
- Truthy module results are cached in `package.loaded` by requested name for each script. Different names or path aliases have separate cache entries. Returning `false` causes the module to run again on the next call. Reloading the script clears its cache.
- Circular imports and loading errors raise Lua errors. As in standard LuaJIT, a module that fails during execution remains marked in `package.loaded`; clear its entry before retrying, or reload the script. Module initialization must not yield.

For example, create `scripts/include/greeting.lua`:

```lua
local greeting = {}
function greeting.say_hello()
    notify.info("Greeting", "Hello from a module")
end
return greeting
```

Then use it from a script:

```lua
local greeting = require("include.greeting")
greeting.say_hello()
```

---

## notify

In-game notifications. `duration` is in milliseconds (default 5000).

| Function | Description |
| --- | --- |
| `notify.success(title, message, [duration])` | Green success notification. |
| `notify.info(title, message, [duration])` | Blue info notification. |
| `notify.warn(title, message, [duration])` | Yellow warning notification. |
| `notify.error(title, message, [duration])` | Red error notification. |

---

## log

Writes to the menu log file (`cout.log`), prefixed with the script name.

| Function | Description |
| --- | --- |
| `log.verbose(message)` | Log at verbose severity. |
| `log.info(message)` | Log at info severity. |
| `log.warn(message)` | Log at warning severity. |
| `log.error(message)` | Log at FATAL severity. |
| `log.trace(message)` | Log a message together with a Lua stack traceback. |

---

## util

| Function | Description |
| --- | --- |
| `util.joaat(string) -> integer` | Returns the Joaat hash of a string. |
| `util.time() -> integer` | Returns the current Unix time in milliseconds. |
| `util.get_game_version() -> string, string` | Returns the current online version, then the game build, as strings. |

```lua
local online_version, game_build = util.get_game_version()
log.info("Online version: " .. online_version .. ", game build: " .. game_build)
```

---

## script

Controls script execution and coroutines.

| Function | Description |
| --- | --- |
| `script.run_in_callback(fn)` | Registers `fn` to run as a script callback (its own coroutine). |
| `script.yield([ms])` | Yields the current callback for at least `ms` milliseconds (default 0 = one frame). Must be called from inside a callback. |
| `script.is_inside_render_callback() -> boolean` | Returns true in a registered ImGui render callback, including container `imgui` callbacks and `menu.add_imgui`/`menu.add_always_draw_imgui`. |
| `script.is_inside_script_callback() -> boolean` | Returns true in the active managed script coroutine, including `script.run_in_callback` and queued command/tick callbacks. |
| `script.require_game_build(online_version, [game_build])` | Requires an exact online version string match and, if supplied, an exact game build string match. Raises a Lua error on a mismatch; returns no value on success. |

Call `script.require_game_build` at the top of scripts that depend on a specific version's globals, offsets, or bytecode. Both arguments are strings; omitting `game_build` or passing `nil` checks only the online version. Use `util.get_game_version()` to inspect the current versions when choosing the versions your script supports.

Use `script.run_in_callback` for managed game work. Top-level script code and coroutines created directly with `coroutine.create` return false for both checks. Render callbacks must not yield or call latent functions; `script.yield` and latent calls require a managed script callback.

---

## event

Register callbacks for menu/game events.

#### `event.register_handler(menu_event, handler)`
Calls `handler` synchronously whenever `menu_event` fires. Handlers run on the thread that dispatches the event and must not yield. Queue work that needs a script coroutine with `script.run_in_callback`.

The `menu_event` enum table holds the event IDs. Use these constants rather than hardcoded numbers.

| Event | ID | Handler arguments | Fires when |
| --- | --- | --- | --- |
| `menu_event.PlayerMgrInit` | 0 | None | The menu has populated its tracked player list during player-manager initialization. |
| `menu_event.PlayerMgrShutdown` | 1 | None | The tracked players, player data, and selection have been cleared during player-manager shutdown. |
| `menu_event.PlayerLeave` | 2 | `name: string` | A player leaves the session. |
| `menu_event.PlayerJoin` | 3 | `player_id: integer, name: string` | A player joins the session. |
| `menu_event.ScriptedGameEventReceived` | 4 | `player: Player, args: integer[]` | A scripted game event is received. |
| `menu_event.ChatMessageReceived` | 5 | `player_id: integer, message: string` | A chat message is received. |
| `menu_event.Unload` | 6 | None | The script is being unloaded or reloaded. |
| `menu_event.WndProc` | 7 | `hwnd: integer, message: integer, wparam: integer, lparam: integer` | The game window receives a Windows message. The handle and parameters are passed as integers. |

Returning `false` blocks handling of `ScriptedGameEventReceived` or `ChatMessageReceived`. Other events are notifications: return values do not block them. In particular, `WndProc` observes messages without consuming them or replacing the window procedure's result. Paused scripts do not receive events.

---

## menu

Build menu UI with submenus, categories, groups, tab bars, tabs, and collapsing headers. Most builders return a handle you keep calling methods on.

#### Top-level
| Function | Description |
| --- | --- |
| `menu.set_menu_name(name)` | Sets the script's submenu display name. |
| `menu.set_menu_icon(icon)` | Sets the script's submenu icon. |
| `menu.get_menu_name() -> string` | Returns the current submenu name. |
| `menu.get_submenu([name]) -> Submenu` | Finds or creates a submenu (defaults to the menu/script name). |
| `menu.find_submenu(name) -> Submenu \| nil` | Finds an existing submenu by name. |
| `menu.create_group(name, [per_row]) -> Group` | Creates a standalone group (drawn manually via `group:draw()`). `per_row` default 7. |
| `menu.is_open() -> boolean` | Returns true if the menu is open. |
| `menu.toggle()` | Toggles the menu open/closed and updates mouse input and cursor visibility. |
| `menu.set_mouse_override(enabled)` | Enables or releases this script's mouse override request. `enabled` must be a boolean. |
| `menu.is_mouse_overridden() -> boolean` | Returns true if any script has an active mouse override request. Opening the menu or onboarding alone does not count as an override. |
| `menu.add_imgui(fn)` | Registers a raw ImGui draw callback rendered every frame while the menu is open. |
| `menu.add_always_draw_imgui(fn)` | Registers a raw ImGui draw callback rendered every frame regardless of whether the menu is open. |

#### Mouse override ownership

An active override enables ImGui mouse input and the cursor even while the main menu is closed, and suppresses the same game controls as interacting with menu content. Cursor/input changes are applied on the next render frame. Use it for interactive windows drawn with `menu.add_always_draw_imgui`.

Each script owns one request: repeated `true` calls do not acquire additional requests, and `false` releases only the caller's request. Another script's request keeps the override active. Pause suspends a request; Resume restores it. Unload, Reload, malfunction cleanup, and script destruction release it automatically, including when another reference keeps the unloaded script object alive. Releasing the last override still leaves normal menu/onboarding mouse behavior intact.

For example, toggle an independent panel with F6:

```lua
local panel_open = false
event.register_handler(menu_event.WndProc, function(hwnd, message, wparam, lparam)
    if message == 0x0101 and wparam == 0x75 then -- WM_KEYUP, VK_F6
        panel_open = not panel_open
        menu.set_mouse_override(panel_open)
    end
end)
menu.add_always_draw_imgui(function()
    if not panel_open then return end
    local visible
    panel_open, visible = ImGui.Begin("My Lua panel", panel_open)
    if visible then ImGui.Text("Press F6 or close this window to release its mouse request.") end
    ImGui.End()
    menu.set_mouse_override(panel_open)
end)
```

Keep the panel's own state in a local variable: `menu.is_mouse_overridden()` reports the combined state of all scripts.

#### Submenu
| Method | Description |
| --- | --- |
| `submenu:add_category(name) -> Category` | Adds a category to the submenu. |
| `submenu:find_category(name) -> Category \| nil` | Finds a category by name. |

#### Category
| Method | Description |
| --- | --- |
| `category:add_group(name, [per_row]) -> Group` | Adds a group. `per_row` default 7. |
| `category:find_group(name) -> Group \| nil` | Finds a group by name. |
| `category:add_tab_bar(id) -> TabBarItem` | Adds a tab bar. Add tabs with `tab_bar:add_tab(name)`. |
| `category:add_collapsing_header(name) -> CollapsingHeaderItem` | Adds a collapsible section. |
| `category:imgui(fn)` | Registers a raw ImGui draw callback rendered every frame. |

Categories also support the `add_command`, `add_bool_command`, `add_int_command`, `add_float_command`, `add_list_command`, `add_button`, `add_checkbox`, and `add_looped_checkbox` methods below, with the same arguments and return values as groups.

#### Group
| Method | Description |
| --- | --- |
| `group:add_tab_bar(id) -> TabBarItem` | Adds a tab bar. |
| `group:add_collapsing_header(name) -> CollapsingHeaderItem` | Adds a collapsible section. |
| `group:add_command(name)` | Adds an existing command by name. |
| `group:add_bool_command(name)` | Adds an existing bool command by name. |
| `group:add_int_command(name, [slider])` | Adds an existing int command (slider default true). |
| `group:add_float_command(name, [slider])` | Adds an existing float command (slider default true). |
| `group:add_list_command(name)` | Adds an existing list command by name. |
| `group:add_button(name, label, [desc], fn) -> CommandHandle` | Creates and adds a button command. |
| `group:add_checkbox(name, label, [desc], [default], [on_enable], [on_disable]) -> CommandHandle` | Creates and adds a checkbox command. |
| `group:add_looped_checkbox(name, label, [desc], tick, [on_enable], [on_disable]) -> CommandHandle` | Creates and adds a looped checkbox (runs `tick` every frame while enabled). |
| `group:imgui(fn)` | Registers a raw ImGui draw callback inside the group. |
| `group:draw()` | Manually renders the group (for standalone groups inside an `imgui` callback). |

The command methods shared by categories, groups, tabs, and headers use the same defaults: `slider` is true and checkbox `default` is false. Pass `nil` for an optional positional argument when supplying later arguments, e.g. `add_button(name, label, nil, fn)`. Names for newly created commands must be unique across the menu.

#### TabBarItem

Add a tab bar with `category:add_tab_bar(id)` or `group:add_tab_bar(id)`.

| Method | Description |
| --- | --- |
| `tab_bar:add_tab(name) -> TabItem` | Adds a tab to the bar. |

#### TabItem

Create tabs through a `TabBarItem`.

| Method | Description |
| --- | --- |
| `tab:add_group(name, [per_row]) -> Group` | Adds a group inside a tab. `per_row` default 7. |
| `tab:add_collapsing_header(name) -> CollapsingHeaderItem` | Adds a collapsible section inside a tab. |
| `tab:add_command(name)` | Adds an existing command by name. |
| `tab:add_bool_command(name)` | Adds an existing bool command by name. |
| `tab:add_int_command(name, [slider])` | Adds an existing int command (slider default true). |
| `tab:add_float_command(name, [slider])` | Adds an existing float command (slider default true). |
| `tab:add_list_command(name)` | Adds an existing list command by name. |
| `tab:add_button(name, label, [desc], fn) -> CommandHandle` | Creates and adds a button command. |
| `tab:add_checkbox(name, label, [desc], [default], [on_enable], [on_disable]) -> CommandHandle` | Creates and adds a checkbox command. |
| `tab:add_looped_checkbox(name, label, [desc], tick, [on_enable], [on_disable]) -> CommandHandle` | Creates and adds a looped checkbox (runs `tick` every frame while enabled). |
| `tab:imgui(fn)` | Adds a raw ImGui draw callback inside the tab. |

Tab contents, including `imgui` callbacks, are drawn only while the tab is selected. Do not call `script.yield` from an `imgui` callback.

#### CollapsingHeaderItem

Add a collapsing header to a category, group, or tab.

| Method | Description |
| --- | --- |
| `header:add_group(name, [per_row]) -> Group` | Adds a group inside a collapsible section. `per_row` default 7. |
| `header:add_command(name)` | Adds an existing command by name. |
| `header:add_bool_command(name)` | Adds an existing bool command by name. |
| `header:add_int_command(name, [slider])` | Adds an existing int command (slider default true). |
| `header:add_float_command(name, [slider])` | Adds an existing float command (slider default true). |
| `header:add_list_command(name)` | Adds an existing list command by name. |
| `header:add_button(name, label, [desc], fn) -> CommandHandle` | Creates and adds a button command. |
| `header:add_checkbox(name, label, [desc], [default], [on_enable], [on_disable]) -> CommandHandle` | Creates and adds a checkbox command. |
| `header:add_looped_checkbox(name, label, [desc], tick, [on_enable], [on_disable]) -> CommandHandle` | Creates and adds a looped checkbox (runs `tick` every frame while enabled). |
| `header:imgui(fn)` | Adds a raw ImGui draw callback inside the section. |

Header contents, including `imgui` callbacks, are drawn only while the section is expanded. Commands created inside a tab or header still run when activated, and enabled looped commands keep ticking while their UI is hidden.

For example:

```lua
local category = menu.get_submenu():add_category("Options")
local tab = category:add_tab_bar("OptionsTabs"):add_tab("General")
local advanced = tab:add_collapsing_header("Advanced")
advanced:add_button("example_hello", "Say hello", nil, function()
    notify.info("Example", "Hello from the Advanced section")
end)
```

---

## commandmgr

Create commands directly (without placing them in a group). Each returns a **CommandHandle**.

For list commands, `entries` contains `{ key, label }` pairs. The default value, `get_value()`, `set_value()`, and `on_change` use the selected key, not its position in the entries array. Keys such as 10 and 20 are valid.

| Function | Description |
| --- | --- |
| `commandmgr.add_command(name, label, desc, on_call) -> CommandHandle` | Creates a one-shot command. |
| `commandmgr.add_bool_command(name, label, desc, [default], [on_enable], [on_disable]) -> CommandHandle` | Creates a toggle command. |
| `commandmgr.add_looped_command(name, label, desc, tick, [on_enable], [on_disable]) -> CommandHandle` | Creates a looped command (`tick` runs every frame while enabled). |
| `commandmgr.add_int_command(name, label, desc, [min], [max], [default], [on_change]) -> CommandHandle` | Creates an int command. |
| `commandmgr.add_float_command(name, label, desc, [min], [max], [default], [on_change]) -> CommandHandle` | Creates a float command. |
| `commandmgr.add_list_command(name, label, desc, entries, [default], [on_change]) -> CommandHandle` | Creates a list command. `entries` is an array of `{ key, label }` pairs. |
| `commandmgr.get_command(name) -> CommandHandle \| nil` | Looks up any existing command by name (built-in or Lua). |

#### CommandHandle
| Method | Description |
| --- | --- |
| `cmd:get_value() -> value` | Returns the current bool/int/float or selected list-entry key; nil for one-shot or missing commands. |
| `cmd:set_value(value)` | Sets the value and schedules callbacks. One-shot and missing commands are no-ops. |
| `cmd:get_name() -> string \| nil` | Returns the registered name/ID, or nil if the command no longer exists. |
| `cmd:get_desc() -> string \| nil` | Returns the description, or nil if the command no longer exists. |
| `cmd:call()` | Activates the underlying command's normal action; no-op if the command no longer exists. Returns no value. |
| `cmd:draw()` | Draws the command (call from inside an ImGui callback). |

For Lua one-shot commands, `call()` queues the callback on the script thread; it need not finish before `call()` returns. For Lua bool and looped commands, it toggles the enabled state. Use `set_value(value)` to change an int, float, or list value.

---

## ImGui

Immediate-mode GUI bindings, used inside ImGui draw callbacks. Most value-editing widgets return the updated value and a `changed`/`pressed` boolean, e.g. `value, changed = ImGui.Checkbox("Label", value)`. `Selectable` returns only the updated selected state; it can return true without a click when already selected. Use `IsItemClicked()` to test clicks separately.

Colors are passed as separate `r, g, b, a` numbers or as a Lua table depending on the function. Flag/condition arguments use the enum tables listed at the end.

### Overloads and return values

| Call | Returns |
| --- | --- |
| `Begin(name, [nil], [flags])` / `BeginPopupModal(name, [nil], [flags])` | `draw`; flags occupy argument 3. |
| `Begin(name, open, [flags])` / `BeginPopupModal(name, open, [flags])` | `open, draw` when `open` is a boolean. |
| `RadioButton(label, active)` | `pressed` when `active` is a boolean. |
| `RadioButton(label, value, button_value)` | `value, pressed` for integer values. |
| `CollapsingHeader(label, [flags])` | `expanded`. |
| `CollapsingHeader(label, open, [flags])` | `open, expanded` when `open` is a boolean. |
| `BeginTabItem(label)` | `selected`. |
| `BeginTabItem(label, open, [flags])` | `open, selected` when `open` is a boolean. |
| `MenuItem(label, [shortcut])` | `pressed`. |
| `MenuItem(label, shortcut, selected)` | `selected, pressed`; use `nil` for no shortcut. |
| `Combo(label, current, items, items_count, [popup_max])` | `current, changed` for a string array. |
| `Combo(label, current, items_string, [popup_max])` | `current, changed` for NUL-separated strings ending in two NUL bytes. |
| `CalcTextSize(text, [hide_text_after_double_hash], [wrap_width])` | `width, height` for the whole string; defaults are false and -1. |

`TextUnformatted(text)` and `GetID(text)` take one whole string. `PushID(id)` takes one whole string or integer. To use part of a string, create it with `string.sub` before calling these functions. For wrapped sizing, use `CalcTextSize(text, false, wrap_width)` or `CalcTextSize(text, nil, wrap_width)`.

Combo and ListBox selection indices start at 0. `BeginListBox(label, size_x, size_y)` takes both dimensions in pixels; `BeginListBox(label, items_count)` auto-sizes its height from the count. Match each successful begin call with its end call; `Begin`/`BeginChild` always require `End`/`EndChild`, even when they return false. `GetStyle()` returns a detached table of the exposed fields; editing it does not change the active style.

See [yimmenu_v2.lua](yimmenu_v2.lua) for every registered signature, including array widgets and their return types.

#### Windows & layout
`Begin`, `End`, `BeginChild`, `EndChild`, `BeginChildFrame`, `EndChildFrame`, `BeginGroup`, `EndGroup`, `Separator`, `SeparatorText`, `SameLine`, `NewLine`, `Spacing`, `Dummy`, `Indent`, `Unindent`, `BeginDisabled`, `EndDisabled`, `Columns`, `NextColumn`, `GetColumnIndex`, `GetColumnWidth`, `SetColumnWidth`, `GetColumnOffset`, `SetColumnOffset`, `GetColumnsCount`.

#### Window state
`IsWindowAppearing`, `IsWindowCollapsed`, `IsWindowFocused`, `IsWindowHovered`, `GetWindowPos`, `GetWindowSize`, `GetWindowWidth`, `GetWindowHeight`, `SetNextWindowPos`, `SetNextWindowSize`, `SetNextWindowSizeConstraints`, `SetNextWindowContentSize`, `SetNextWindowCollapsed`, `SetNextWindowFocus`, `SetNextWindowBgAlpha`, `SetWindowPos`, `SetWindowSize`, `SetWindowCollapsed`, `SetWindowFocus`, `SetWindowFontScale`.

#### Cursor & content region
`GetContentRegionMax`, `GetContentRegionAvail`, `GetWindowContentRegionMin/Max`, `GetCursorPos`, `GetCursorPosX/Y`, `SetCursorPos`, `SetCursorPosX/Y`, `GetCursorStartPos`, `GetCursorScreenPos`, `SetCursorScreenPos`, `AlignTextToFramePadding`, `GetTextLineHeight`, `GetTextLineHeightWithSpacing`, `GetFrameHeight`, `GetFrameHeightWithSpacing`.

#### Scrolling
`GetScrollX/Y`, `GetScrollMaxX/Y`, `SetScrollX/Y`, `SetScrollHereX/Y`, `SetScrollFromPosX/Y`.

#### Style stacks
`PushStyleColor`, `PopStyleColor`, `PushStyleVar`, `PopStyleVar`, `GetStyleColorVec4`, `GetStyle`, `GetFontSize`, `GetFontTexUvWhitePixel`, `PushItemWidth`, `PopItemWidth`, `SetNextItemWidth`, `CalcItemWidth`, `PushTextWrapPos`, `PopTextWrapPos`, `PushButtonRepeat`, `PopButtonRepeat`, `PushID`, `PopID`, `GetID`.

#### Text
`Text`, `TextUnformatted`, `TextColored`, `TextDisabled`, `TextWrapped`, `LabelText`, `BulletText`, `Bullet`.

#### Widgets
`Button`, `SmallButton`, `InvisibleButton`, `ArrowButton`, `Checkbox`, `RadioButton`, `ProgressBar`.

#### Combo & lists
`BeginCombo`, `EndCombo`, `Combo`, `Selectable`, `ListBox`, `BeginListBox`, `EndListBox`, `Value`.

#### Drags
`DragFloat`, `DragFloat2/3/4`, `DragInt`, `DragInt2/3/4`.

#### Sliders
`SliderFloat`, `SliderFloat2/3/4`, `SliderAngle`, `SliderInt`, `SliderInt2/3/4`, `VSliderFloat`, `VSliderInt`.

#### Inputs
`InputText`, `InputTextMultiline`, `InputTextWithHint`, `InputFloat`, `InputFloat2/3/4`, `InputInt`, `InputInt2/3/4`, `InputDouble`.

#### Colors
`ColorEdit3/4`, `ColorPicker3/4`, `ColorButton`, `SetColorEditOptions`, `ColorConvertFloat4ToU32`, `ColorConvertRGBAToU32`, `ColorConvertU32ToFloat4`, `ColorConvertRGBtoHSV`, `ColorConvertHSVtoRGB`.

#### Trees & headers
`TreeNode`, `TreeNodeEx`, `TreePush`, `TreePop`, `GetTreeNodeToLabelSpacing`, `CollapsingHeader`, `SetNextItemOpen`.

#### Menus
`BeginMenuBar`, `EndMenuBar`, `BeginMainMenuBar`, `EndMainMenuBar`, `BeginMenu`, `EndMenu`, `MenuItem`.

#### Tooltips & popups
`BeginTooltip`, `EndTooltip`, `SetTooltip`, `BeginPopup`, `BeginPopupModal`, `EndPopup`, `OpenPopup`, `OpenPopupContextItem`, `CloseCurrentPopup`, `BeginPopupContextItem`, `BeginPopupContextWindow`, `BeginPopupContextVoid`, `IsPopupOpen`.

#### Tabs
`BeginTabBar`, `EndTabBar`, `BeginTabItem`, `EndTabItem`, `SetTabItemClosed`.

#### Tables
`BeginTable`, `EndTable`, `TableNextColumn`, `TableNextRow`, `TableSetColumnIndex`, `TableSetupColumn`, `TableHeadersRow`.

#### Draw list
`AddLine`, `AddRect`, `AddRectFilled`, `AddRectFilledMultiColor`, `AddCircle`, `AddCircleFilled`, `AddTriangle`, `AddTriangleFilled`, `AddText`.

These existing `ImGui.Add*` helpers draw into the current window. For explicit targets, use borrowed `DrawList` handles:

| Function | Description |
| --- | --- |
| `ImGui.GetWindowDrawList() -> DrawList` | Returns the current window's draw list, subject to its clipping. |
| `ImGui.GetForegroundDrawList() -> DrawList` | Returns the main viewport's foreground draw list, rendered above windows. |

| DrawList method | Description |
| --- | --- |
| `list:AddText(x, y, text, r, g, b, a, [font_size], [wrap_width])` | Draws text using the current font. Omitted/nil `font_size` uses its current size; otherwise pass a positive finite pixel size. `wrap_width` is a non-negative finite pixel width; omitted/nil or 0 disables wrapping. |
| `list:AddLine(x1, y1, x2, y2, r, g, b, a, [thickness])` | Draws a line; thickness defaults to 1 pixel. |
| `list:AddRect(x1, y1, x2, y2, r, g, b, a, [rounding], [flags], [thickness])` | Draws a rectangle outline. Defaults: corner rounding 0 pixels, draw flags 0, thickness 1 pixel. |
| `list:AddRectFilled(x1, y1, x2, y2, r, g, b, a, [rounding], [flags])` | Draws a filled rectangle. Defaults: corner rounding 0 pixels, draw flags 0. With positive rounding, flags select the rounded corners. |
| `list:AddRectFilledMultiColor(x1, y1, x2, y2, upper_left, upper_right, bottom_right, bottom_left)` | Draws a filled rectangle with four packed U32 corner colors, interpolated across the rectangle. |
| `list:AddTriangle(x1, y1, x2, y2, x3, y3, r, g, b, a, [thickness])` | Draws a triangle outline; thickness defaults to 1 pixel. |
| `list:AddTriangleFilled(x1, y1, x2, y2, x3, y3, r, g, b, a)` | Draws a filled triangle; supply vertices in clockwise screen-space order. |
| `list:AddCircle(x, y, radius, r, g, b, a, [num_segments], [thickness])` | Draws a circle outline with a pixel radius. Defaults: segments 0 (automatic tessellation), thickness 1 pixel. |
| `list:AddCircleFilled(x, y, radius, r, g, b, a, [num_segments])` | Draws a filled circle with a pixel radius. Omitted/nil `num_segments` defaults to 0 for automatic tessellation. |

Coordinates are screen-space pixels. Color components must be integers from 0 to 255, including alpha. Optional draw parameters accept `nil` to select their defaults. Acquire handles inside an ImGui draw callback and obtain new ones each frame; using a handle outside its render frame raises an error. ImGui owns the draw lists; Lua does not delete them.

`AddRectFilledMultiColor` takes one packed integer per corner. Create these colors with `ImGui.ColorConvertRGBAToU32({r, g, b, a})`; the corner order is upper-left, upper-right, bottom-right, bottom-left.

To wrap text using the current font size, pass `nil` before the wrap width: `list:AddText(x, y, text, r, g, b, a, nil, 200)`.

For `AddRect` and `AddRectFilled`, corner flag bits are top-left = 16, top-right = 32, bottom-left = 64, and bottom-right = 128. Combine them with `bit.bor`. With positive rounding, flags 0 round all corners; 256 disables rounding. Omitted/nil flags use 0.

```lua
menu.add_always_draw_imgui(function()
    local foreground = ImGui.GetForegroundDrawList()
    foreground:AddRectFilled(20, 20, 260, 70, 0, 0, 0, 180, 6)
    foreground:AddRect(20, 20, 260, 70, 100, 180, 255, 255, 6, 0, 2)
    foreground:AddText(30, 30, "Overlay text", 255, 255, 255, 255, 24)
    foreground:AddLine(20, 75, 260, 75, 100, 180, 255, 255, 2)
    foreground:AddCircleFilled(280, 45, 12, 100, 180, 255, 255)
    foreground:AddCircle(280, 45, 16, 100, 180, 255, 255, 0, 2)
    foreground:AddTriangleFilled(280, 85, 296, 110, 264, 110, 100, 180, 255, 255)
    foreground:AddTriangle(315, 85, 331, 110, 299, 110, 100, 180, 255, 255, 2)
    local left = ImGui.ColorConvertRGBAToU32({100, 180, 255, 255})
    local right = ImGui.ColorConvertRGBAToU32({255, 100, 180, 255})
    foreground:AddRectFilledMultiColor(20, 85, 260, 110, left, right, right, left)
    foreground:AddText(30, 120, "This overlay text wraps to fit its width.", 255, 255, 255, 255, nil, 220)
end)
```

#### Item & input queries
`IsItemHovered`, `IsItemActive`, `IsItemFocused`, `IsItemClicked`, `IsItemVisible`, `IsItemEdited`, `IsItemActivated`, `IsItemDeactivated`, `IsItemDeactivatedAfterEdit`, `IsItemToggledOpen`, `IsAnyItemHovered/Active/Focused`, `GetItemRectMin/Max/Size`, `IsKeyDown`, `IsKeyPressed`, `IsKeyReleased`, `GetKeyPressedAmount`, `SetNextFrameWantCaptureKeyboard`, `IsMouseDown`, `IsMouseClicked`, `IsMouseReleased`, `IsMouseDoubleClicked`, `IsMouseHoveringRect`, `IsAnyMouseDown`, `GetMousePos`, `GetMousePosOnOpeningCurrentPopup`, `IsMouseDragging`, `GetMouseDragDelta`, `ResetMouseDragDelta`, `GetMouseCursor`, `SetMouseCursor`, `SetNextFrameWantCaptureMouse`.

#### Misc
`GetDisplaySize`, `GetFrameRate`, `GetTime`, `GetFrameCount`, `CalcTextSize`, `IsRectVisible`, `GetStyleColorName`, `SetItemDefaultFocus`, `SetKeyboardFocusHere`, `PushClipRect`, `PopClipRect`, `GetClipboardText`, `SetClipboardText`, `LogToTTY/File/Clipboard`, `LogFinish`, `LogButtons`, `LogText`.

#### Enum tables
Use these global tables for `flags`/`cond`/`col`/`idx` arguments (each maps a name to an integer):
`ImGuiWindowFlags`, `ImGuiChildFlags`, `ImGuiCond`, `ImGuiCol`, `ImGuiStyleVar`, `ImGuiDir`, `ImGuiKey`, `ImGuiMouseButton`, `ImGuiMouseCursor`, `ImGuiHoveredFlags`, `ImGuiFocusedFlags`, `ImGuiComboFlags`, `ImGuiInputTextFlags`, `ImGuiSliderFlags`, `ImGuiButtonFlags`, `ImGuiColorEditFlags`, `ImGuiTreeNodeFlags`, `ImGuiSelectableFlags`, `ImGuiPopupFlags`, `ImGuiTabBarFlags`, `ImGuiTabItemFlags`, `ImGuiTableFlags`, `ImGuiTableColumnFlags`, `ImGuiTableRowFlags`.

Members match the bundled ImGui definitions. `ImGuiKey` includes keyboard, gamepad, mouse, and modifier values such as `Mod_Ctrl`; digit keys use string indexing, e.g. `ImGuiKey["0"]`. Existing names such as `KeyPadEnter`, `IndentDisabled`, `HeightMask`, and the prefixed mouse-button names remain compatibility aliases of the current names.

---

## memory

Pattern scanning and heap allocation. Returns [pointer](#pointer) objects.

| Function | Description |
| --- | --- |
| `memory.scan_pattern(pattern) -> pointer \| nil` | Scans `GTA5_Enhanced.exe` for an IDA-format byte signature. |
| `memory.handle_to_ptr(entity) -> pointer` | Resolves an entity handle to its game pointer. |
| `memory.ptr_to_handle(ptr) -> integer` | Resolves a game pointer back to an entity handle. |
| `memory.allocate(size) -> pointer` | Allocates `size` zeroed bytes (auto-freed on unload). |
| `memory.free(ptr)` | Frees a block returned by `memory.allocate`. |

`memory.free` accepts only non-null allocations owned by the calling script. A foreign or already-freed non-null address raises an error. A null pointer is a no-op.

---

## pointer

A calculator over a raw memory address. Construct with `pointer(address)`. All reads/writes error on a null pointer.

#### Construction & address
| Method | Description |
| --- | --- |
| `pointer(addr) -> pointer` | Creates a pointer at an address. |
| `ptr:get_address() -> integer` | Returns the address. |
| `ptr:set_address(addr)` | Sets the address. |
| `ptr:is_null() -> boolean` | True if the address is null. |
| `ptr:is_valid() -> boolean` | True if the address is non-null. |

#### Arithmetic
| Method | Description |
| --- | --- |
| `ptr:add(offset) -> pointer` | Returns a pointer advanced by `offset` bytes. |
| `ptr:sub(offset) -> pointer` | Returns a pointer moved back by `offset` bytes. |
| `ptr:rip([offset]) -> pointer` | Follows a RIP-relative reference, then applies an optional offset. |
| `ptr:deref() -> pointer` | Reads the 64-bit value at the address and returns it as a pointer. |

#### Reads & writes
| Method | Description |
| --- | --- |
| `ptr:get_byte/word/int/dword/qword() -> integer` | Reads an integer of the given width. |
| `ptr:set_byte/word/int/dword/qword(value)` | Writes an integer of the given width. |
| `ptr:get_float() -> number` / `ptr:set_float(value)` | Reads/writes a float. |
| `ptr:get_string() -> string` / `ptr:set_string(value)` | Reads/writes a C string. |

#### Patches
`ptr:patch_byte/word/dword/qword(value) -> patch` creates an unapplied patch handle and captures the original bytes. Call `patch:apply()` to write the replacement. The patch is reversible:

| Method | Description |
| --- | --- |
| `patch:apply()` | Applies the patch. |
| `patch:restore()` | Restores the original bytes. |

---

## Vector3

A 3D float vector. Construct with `Vector3()` (zero) or `Vector3(x, y, z)` with exactly three numbers; partial or nil-filled constructors are rejected. Fields `x`, `y`, `z` are directly readable and writable (`v.x = 1.0`). Setters return no values.

| Method | Description |
| --- | --- |
| `v:get_coords() -> x, y, z` | Returns all three components. |
| `v:get_x/get_y/get_z() -> number` | Returns a single component. |
| `v:set_x/set_y/set_z(value)` | Sets a single component. |
| `v:get_distance(other) -> number` | Distance to another Vector3. |
| `v:is_zero() -> boolean` | True if all components are zero. |

---

## Entity

Base class for game entities. Construct with `Entity(handle)`. All methods below are inherited by [Ped](#ped) and [Vehicle](#vehicle).

#### Identity
| Method | Description |
| --- | --- |
| `entity:get_handle() -> integer` | Returns the script handle. |
| `entity:is_valid() -> boolean` | True if the entity exists. |
| `entity:is_ped/is_vehicle/is_object/is_player() -> boolean` | Type checks. |
| `entity:is_mission_entity() -> boolean` | True if flagged as a mission entity. |
| `entity:get_model() -> integer` | Returns the model hash. |

#### Position & movement
| Method | Description |
| --- | --- |
| `entity:get_position() -> Vector3` | World position. |
| `entity:set_position(pos)` | Sets the position. |
| `entity:get_rotation([order]) -> Vector3` | Rotation (default order 2). |
| `entity:set_rotation(rot, [order])` | Sets the rotation. |
| `entity:get_velocity() -> Vector3` / `entity:set_velocity(vel)` | Velocity. |
| `entity:get_heading() -> number` / `entity:set_heading(h)` | Heading in degrees. |
| `entity:get_speed() -> number` | Current speed. |
| `entity:set_collision(enabled)` | Toggles collision. |
| `entity:set_frozen(frozen)` | Freezes/unfreezes position. |
| `entity:has_interior() -> boolean` | True if inside an interior. |

#### Networking
| Method | Description |
| --- | --- |
| `entity:is_networked() -> boolean` | True if networked. |
| `entity:is_remote() -> boolean` | True if owned by a remote machine. |
| `entity:has_control() -> boolean` | True if locally controlled. |
| `entity:get_network_object_id() -> integer` | Network object id. |
| `entity:prevent_migration()` | Stops the entity migrating owners. |
| `entity:force_control()` | Forces local control. |
| `entity:request_control([timeout])` | **Latent.** Requests control (default 100 ms). |

#### Health & state
| Method | Description |
| --- | --- |
| `entity:is_invincible() -> boolean` / `entity:set_invincible(enabled)` | Invincibility. |
| `entity:is_dead() -> boolean` | True if dead. |
| `entity:kill()` | Kills the entity. |
| `entity:get_health() -> integer` / `entity:set_health(h)` | Health. |
| `entity:get_max_health() -> integer` | Max health. |
| `entity:is_visible() -> boolean` / `entity:set_visible(v)` | Visibility. |
| `entity:get_alpha() -> integer` / `entity:set_alpha(a)` / `entity:reset_alpha()` | Opacity (0–255). |
| `entity:delete()` | Deletes the entity. |

---

## Ped

A pedestrian. Inherits all [Entity](#entity) methods. Construct with `Ped(handle)` or spawn with `Ped.create(...)`.

| Method | Description |
| --- | --- |
| `Ped.create(model, pos, [heading]) -> Ped` | **Latent.** Spawns a ped (heading default 0). |
| `ped:get_vehicle() -> Vehicle` | Current vehicle. |
| `ped:get_last_vehicle() -> Vehicle` | Last vehicle. |
| `ped:get_vehicle_object_id() -> integer` | Network object id of the current vehicle. |
| `ped:set_in_vehicle(vehicle, [seat])` | Warps into a vehicle (seat default 0). |
| `ped:get_ragdoll() -> boolean` / `ped:set_ragdoll(enabled)` | Ragdoll toggle. |
| `ped:get_bone_position(bone) -> Vector3` | World position of a bone index. |
| `ped:is_enemy() -> boolean` | True if hostile. |
| `ped:get_accuracy() -> integer` / `ped:set_accuracy(a)` | Weapon accuracy. |
| `ped:give_weapon(weapon, [equip])` | Gives a weapon (equip default false). |
| `ped:remove_weapon(weapon)` | Removes a weapon. |
| `ped:get_current_weapon() -> integer` | Equipped weapon hash. |
| `ped:has_weapon(weapon) -> boolean` | True if the ped has the weapon. |
| `ped:set_infinite_ammo(enabled)` | Toggles infinite ammo. |
| `ped:set_infinite_clip(enabled)` | Toggles no-reload. |
| `ped:set_max_ammo_for_weapon(weapon)` | Fills ammo for a weapon. |
| `ped:teleport_to(pos)` | Teleports the ped. |
| `ped:get_armour() -> integer` / `ped:set_armour(a)` | Armour. |
| `ped:set_leader_of_group(group)` | Makes the ped a group leader. |
| `ped:add_to_group(group)` / `ped:remove_from_group()` | Group membership. |
| `ped:is_member_of_group(group) -> boolean` | Group check. |
| `ped:randomize_outfit()` | Randomizes outfit. |
| `ped:start_scenario(name, [duration], [play_anim])` | Starts a scenario by name. |
| `ped:set_keep_task(enabled)` | Keeps the assigned task. |
| `ped:clear_damage()` | Clears damage and decals. |
| `ped:set_max_time_underwater(time)` | Max underwater time (seconds). |
| `ped:set_as_cop()` | Flags the ped as a cop. |

---

## Vehicle

A vehicle. Inherits all [Entity](#entity) methods. Construct with `Vehicle(handle)` or spawn with `Vehicle.create(...)`.

| Method | Description |
| --- | --- |
| `Vehicle.create(model, pos, [heading]) -> Vehicle` | **Latent.** Spawns a vehicle (heading default 0). |
| `vehicle:fix()` | Repairs to full health. |
| `vehicle:get_gear() -> integer` | Current gear. |
| `vehicle:get_rev_ratio() -> number` | Engine rev ratio. |
| `vehicle:get_speed() -> number` | Current speed. |
| `vehicle:upgrade()` | Applies max performance upgrades. |
| `vehicle:get_plate_text() -> string` / `vehicle:set_plate_text(text)` | License plate. |
| `vehicle:is_seat_free(seat) -> boolean` | True if a seat is free. |
| `vehicle:supports_boost() -> boolean` | True if the vehicle supports boost. |
| `vehicle:is_boost_active() -> boolean` | True if boost is active. |
| `vehicle:set_boost_charge([charge])` | Sets boost charge (default 100). |
| `vehicle:lower_stance(enabled)` | Lowers/raises stance. |
| `vehicle:bring_to_halt(distance, time)` | Brings the vehicle to a stop. |
| `vehicle:set_on_ground_properly() -> boolean` | Places the vehicle on the ground. |
| `vehicle:get_full_name() -> string` | Localized display name. |

---

## entities

World pool queries. Each returns an array of integer entity handles (wrap with `Entity`, `Ped`, or `Vehicle`).

| Function | Description |
| --- | --- |
| `entities.get_all_vehicles_as_handles() -> integer[]` | All vehicles. |
| `entities.get_all_peds_as_handles() -> integer[]` | All peds. |
| `entities.get_all_objects_as_handles() -> integer[]` | All objects. |

---

## Player

A session player. Construct with `Player(id)`.

| Method | Description |
| --- | --- |
| `player:is_valid() -> boolean` | True if the slot is active. |
| `player:is_local() -> boolean` | True if this is the local player. |
| `player:is_host() -> boolean` | True if the session host. |
| `player:is_modder() -> boolean` | True if flagged as a modder. |
| `player:get_id() -> integer` | Player index. |
| `player:get_name() -> string` | Player name. |
| `player:get_ped() -> Ped` | The player's ped. |
| `player:get_message_id() -> integer` | Network message id. |
| `player:get_rid() -> integer` | Rockstar ID. |
| `player:get_external_address() -> string, integer` | External IP and port. |
| `player:get_internal_address() -> string, integer` | Internal IP and port. |
| `player:get_average_latency() -> number` | Average latency. |
| `player:get_average_packet_loss() -> number` | Average packet loss. |
| `player:get_rank() -> integer` | Level/rank. |
| `player:get_rp() -> integer` | Reputation points. |
| `player:get_money() -> integer` | Money. |
| `player:get_wanted_level() -> integer` / `player:set_wanted_level(l)` | Wanted level. |
| `player:get_max_armour() -> integer` | Max armour. |
| `player:get_group() -> integer` | Group id. |
| `player:set_visible_locally(visible)` | Local visibility. |
| `player:teleport_to(pos)` | Teleports the player. |
| `player:set_fall_distance_override(distance)` | Overrides fall distance. |
| `player:set_ped(ped, [delete_old])` | Sets the player's ped (delete old default true). |

---

## players

Session player collection.

| Function | Description |
| --- | --- |
| `players.get_all() -> Player[]` | All players in the session. |
| `players.get_local() -> Player` | The local player. |
| `players.get_selected() -> Player` | The currently selected player. |
| `players.set_selected(player)` | Sets the selected player. |
| `players.get_by_rid(rid) -> Player` | Player by Rockstar ID. |
| `players.get_by_message_id(id) -> Player` | Player by network message id. |
| `players.get_random() -> Player` | A random player. |

---

## ScriptGlobal

Reads/writes a GTA script global variable. Construct with `ScriptGlobal(index)`.

| Method | Description |
| --- | --- |
| `ScriptGlobal(index) -> ScriptGlobal` | Handle to a global by index. |
| `sg:at(offset, [size]) -> ScriptGlobal` | With omitted/zero size: `base + offset`. With nonzero size: `base + 1 + offset * size`. |
| `sg:can_access() -> boolean` | True if currently mapped and safe to use. |
| `sg:get_int/get_float() -> number` | Reads an int/float. |
| `sg:get_string() -> string \| nil` | Reads a string. |
| `sg:get_vector3() -> Vector3` | Reads three slots as a vector. |
| `sg:get_pointer() -> pointer` | Returns the address of the global slot, not the value stored in it. If inaccessible, returns a null `pointer` userdata rather than `nil`. |
| `sg:set_int/set_float(value)` | Writes an int/float. |
| `sg:set_string(value, [max_length])` | Writes a string. |
| `sg:set_vector3(v)` | Writes a vector into three slots. |

The returned pointer borrows game memory and does not keep the global mapped. Check `sg:can_access()` or `ptr:is_null()` before accessing it, and resolve it again if global memory changes.

For inaccessible globals, int/float reads return 0, vector reads return a zero vector, string reads return nil, and writes do nothing.

---

## ScriptLocal

Reads/writes a local variable in a running script thread. Construct with `ScriptLocal(script, index)` (`script` = name or hash); returns nil if the thread isn't running.

| Method | Description |
| --- | --- |
| `ScriptLocal(script, index) -> ScriptLocal \| nil` | Handle to a local in a script thread. |
| `sl:at(offset, [size]) -> ScriptLocal` | With omitted/zero size: `base + offset`. With nonzero size: `base + 1 + offset * size`. |
| `sl:get_int/get_float() -> number` | Reads an int/float. |
| `sl:get_vector3() -> Vector3` | Reads three slots as a vector. |
| `sl:get_pointer() -> pointer` | Returns the address of the local slot on the captured thread's stack, not the value stored in it. |
| `sl:set_int/set_float(value)` | Writes an int/float. |
| `sl:set_vector3(v)` | Writes a vector into three slots. |

The returned pointer borrows the thread's stack and does not keep the thread alive. Recreate the `ScriptLocal` handle and resolve its pointer again after the script stops or restarts; `get_pointer()` does not check whether the captured stack is still valid.

---

## ScriptPointer

A pattern-based address within a script's bytecode. Construct with `ScriptPointer(name, pattern, [offset], [rip], [address])`. `address` is a 32-bit bytecode offset/instruction address, not an absolute process-memory address.

| Method | Description |
| --- | --- |
| `sp:add(offset) -> ScriptPointer` | Adds to the offset used by a future scan; preserves the currently resolved address. |
| `sp:sub(offset) -> ScriptPointer` | Subtracts from the offset used by a future scan; preserves the currently resolved address. |
| `sp:rip() -> ScriptPointer` | Enables decoding a three-byte GTA bytecode address operand during the next scan; preserves the current address. |
| `sp:scan(target) -> ScriptPointer \| nil` | Scans a running script program (`target` = name/hash). No program returns nil; no pattern match returns a handle with address 0. |
| `sp:get_address() -> integer` | Resolved 32-bit bytecode offset/instruction address. |
| `sp:get_name() -> string` | Pointer name. |

---

## ScriptPatch

Patches a script's bytecode; auto-restored on script unload. Construct with `ScriptPatch(script, name, pattern, offset, patch_bytes)` — created and enabled immediately. Use `nil` or `0` in the offset slot for the default offset; the bytes table must be the fifth argument. `patch_bytes` is a nonempty array of integers (0–255).

| Method | Description |
| --- | --- |
| `patch:enable()` | Applies the patch. |
| `patch:disable()` | Reverts but keeps it registered. |
| `patch:remove()` | Reverts and unregisters. |

---

## ScriptFunction

Calls a function inside a GTA script. Construct with `ScriptFunction(script, script_pointer)`.

#### `fn:call(param_string, ...) -> any`
Invokes the function. `param_string` describes arg types (`i` int32, `f` float, `h` hash, `b` bool, `s` string) plus an optional `=<r>` return type (`n` none, `i`, `f`, `b`, `h`, `s`). Following arguments map to the type chars. Example: `fn:call("ii=i", 5, 10)`.

`s` passes a read-only, NUL-terminated string pointer that remains valid during the call; `nil` or an omitted string argument passes a null pointer. Other argument types are not converted to strings. Embedded NUL bytes terminate the text seen by the GTA function. The function must not retain or modify an argument's Lua string. `=s` copies a returned C string into Lua, or returns `nil` for a null pointer.

```lua
local text = fn:call("s=s", "example") -- String argument and string/nil result.
local label = fn:call("is=s", 5, "example") -- Mixed argument types.
fn:call("s", nil) -- Null string argument, no return value.
```

---

## scripts

| Function | Description |
| --- | --- |
| `scripts.is_active(script) -> boolean` | True if the script (name/hash) is running. |
| `scripts.run_as_script(script, callback)` | Runs `callback` in the named script's thread context. |

---

## natives

Loads the auto-generated GTA native bindings into your script.

| Function | Description |
| --- | --- |
| `natives.load_natives()` | Loads every native namespace table (`PLAYER`, `ENTITY`, `VEHICLE`, …) as globals. Raises an error if already loaded. |
| `natives.are_natives_loaded() -> boolean` | True if natives have already been loaded. |

After loading, call natives as `NAMESPACE.NATIVE_NAME(args)`, e.g. `PLAYER.PLAYER_ID()`. The full native list mirrors the standard GTA V natives — see [`natives.lua`](natives.lua) for every signature.

Check `natives.are_natives_loaded()` before loading again. Internally each generated wrapper calls `_I(index, format, ...)` with a native registration index, not a raw native hash; use the named native wrappers.

Native argument formats also accept booleans in integer slots, numbers in boolean slots, and nil/omitted values in string slots (passed as null pointers). A null native C-string result becomes Lua nil; whether a particular native can return null depends on its game contract.

---

## network

| Function | Description |
| --- | --- |
| `network.trigger_script_event(hash, bits, format, ...)` | Sends a scripted game event. `bits` = target player bitset; `format` chars `i`/`f`/`l`/`h` describe the varargs (max 36). |
| `network.force_script_host(script_hash)` | Forces the local player to host a script. |
| `network.force_script_on_player(script_hash, bits)` | Forces a script to run on the players in `bits`. |
| `network.is_session_started() -> boolean` | True if in a multiplayer session. |
| `network.join_session(session_type)` | Requests a session transition using a value from the global `session_types` table. Returns no value or completion status. |

`trigger_script_event` prepends the event hash, local player ID, and target bitset to the formatted arguments. Received argument arrays include this prefix.

#### session_types

This global enum table contains the session types accepted by `network.join_session`:

| Constant | Value | Session type |
| --- | --- | --- |
| `session_types.public` | 0 | Public |
| `session_types.solo_public` | 1 | Solo public |
| `session_types.sctv` | 13 | SCTV |
| `session_types.crew` | 3 | Crew |
| `session_types.join_crew` | 12 | Join crew |
| `session_types.closed_crew` | 2 | Closed crew |
| `session_types.closed_friend` | 6 | Closed friend |
| `session_types.find_friend` | 9 | Find friend |
| `session_types.invite_only` | 11 | Invite only |
| `session_types.solo` | 10 | Solo |

Call from a script callback to run the game work on the script thread:

```lua
script.run_in_callback(function()
    network.join_session(session_types.invite_only)
end)
```

---

## tunables

Read/write game tunables. The first argument is a tunable name or hash.

| Function | Description |
| --- | --- |
| `tunables.set_int/set_bool/set_float(hash, value)` | Writes a tunable. |
| `tunables.get_int(hash) -> integer` | Reads an int tunable (0 if not ready). |
| `tunables.get_bool(hash) -> boolean` | Reads a bool tunable. |
| `tunables.get_float(hash) -> number` | Reads a float tunable. |

---

## stats

Read/write local player stats by name or packed index.

| Function | Description |
| --- | --- |
| `stats.set_int/set_bool/set_float/set_string(name, value)` | Writes a named stat. |
| `stats.get_int/get_bool/get_float/get_string(name)` | Reads a named stat. |
| `stats.set_packed_int/set_packed_bool(index, value)` | Writes a packed stat. |
| `stats.get_packed_int/get_packed_bool(index)` | Reads a packed stat. |
| `stats.set_packed_bool_range(start, end, value)` | Sets a range of packed bools. |
| `stats.set_masked_int(name, value, offset, bits)` | Writes a bit-masked int field. |
| `stats.get_masked_int(name, offset, bits) -> integer` | Reads a bit-masked int field. |
| `stats.set_masked_bool(name, offset, value)` | Writes a single bit. |
| `stats.get_masked_bool(name, offset) -> boolean` | Reads a single bit. |

---

## transactions

GTA Online network-shop (money) transactions.

| Function | Description |
| --- | --- |
| `transactions.create_basket(category, action) -> BasketTransaction` | Creates a basket. |
| `transactions.run_service(category, action, item, value) -> boolean` | Fire-and-forget single service transaction. |
| `transactions.can_use_transactions() -> boolean` | True if the shop catalog is valid and FSL local saves are off. |

#### BasketTransaction
| Method | Description |
| --- | --- |
| `basket:add_item(primary, secondary, value, stat_value, quantity)` | Adds an item (max 70; `secondary` may be nil). |
| `basket:run() -> boolean` | **Latent.** Runs the checkout; returns success. |

---

## FileMgr

Sandboxed file access, rooted at `%appdata%/YimMenuV2/scripts`. Every path argument is relative to this folder, regardless of the script's location or the process's working directory. Use `"."` for the scripts root. Absolute, drive-relative, UNC, alternate-stream, embedded-NUL, and escaping paths raise an error; links must resolve inside the sandbox.

Pass paths such as `"config/settings.txt"` directly.

| Function | Description |
| --- | --- |
| `FileMgr.CreateDir(path) -> boolean` | Creates a directory (and parents). |
| `FileMgr.DeleteFile(path)` | Deletes a file. |
| `FileMgr.RenameFile(source, destination) -> boolean` | Renames or moves a regular file between two relative paths. Returns false on filesystem failure or if the destination exists; its parent directory must already exist. Renaming an existing file to itself succeeds. |
| `FileMgr.DoesFileExist(path) -> boolean` | True if the path exists. |
| `FileMgr.FindFiles(path, extension, [recursive]) -> string[]` | Lists regular files as paths relative to the scripts root, usable directly in other FileMgr calls. An empty extension matches every file; `lua` and `.lua` are equivalent. Recursive listing skips linked directory aliases. |
| `FileMgr.ReadFileContent(path) -> string` | Reads raw bytes ("" on failure). |
| `FileMgr.WriteFileContent(path, content, [append]) -> boolean` | Writes (or appends) to a file. |

```lua
FileMgr.CreateDir("config")
FileMgr.WriteFileContent("config/settings.txt", "saved settings")
local renamed = FileMgr.RenameFile("config/settings.txt", "config/settings.old.txt")
for _, path in ipairs(FileMgr.FindFiles("config", ".txt", true)) do
    log.info(path .. ": " .. FileMgr.ReadFileContent(path))
end
```

---

## internal

> For menu testing only — not intended for normal scripts.

| Function | Description |
| --- | --- |
| `internal.spawn_vehicle(model)` | Spawns a vehicle at the local player. |
