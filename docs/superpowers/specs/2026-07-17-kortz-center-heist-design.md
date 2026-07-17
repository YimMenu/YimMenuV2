# Kortz Center Heist Tab — Design Spec

**Date:** 2026-07-17
**Project:** YimMenuV2
**Status:** Approved

## Overview

Add a "Kortz Center Heist" tab to the existing Heist modifier menu. Exposes all relevant GTA Online MPX_K26_* stats as UI controls, following the same pattern as Cayo Perico, Diamond Casino, Doomsday, and Apartment heist tabs.

## Files

| File | Purpose |
|------|---------|
| `src/game/features/recovery/Heist/KortzCenterHeist.cpp` | Command definitions (IntCommand, BoolCommand, ListCommand, Command subclasses) |
| `src/game/frontend/submenus/Recovery/Heist/KortzCenterHeist.hpp` | Header — declares `RenderKortzCenterHeistMenu()` |
| `src/game/frontend/submenus/Recovery/Heist/KortzCenterHeist.cpp` | UI construction — Groups, Items, Layout |
| `src/game/frontend/submenus/Recovery/HeistModifier.cpp` | Add include + tab item to heist tab bar |

No CMake changes needed — `file(GLOB_RECURSE)` auto-picks up new .cpp/.hpp.

## Stats Reference

All stats use the `MPX_` prefix (multiplayer character index, resolved at runtime by Stats::SetInt).

| Stat | Type | Purpose |
|------|------|---------|
| `MPX_K26_GENERAL_BS` | Bitfield (-1) | General purchases. Bits 5-8: Guard Routes, Glass Cutter, Power Drills, EMP Charges |
| `MPX_K26_GENERAL_BS2` | Auto-set | Updates via Planning Board. Set to -1 in Setup. |
| `MPX_K26_ROBBERY_PROG` | Bitfield (-1) | 16 bits for prep work completion flags |
| `MPX_K26_HEIST_TARGET` | Int 0-26 | Primary target artwork selection |
| `MPX_K26_SCOPING_BS` | Bitfield (-1) | Secondary targets scoped |
| `MPX_K26_POI_BS` | Bitfield (-1) | Points of Interest scoped (guard routes, glass cutter, EMP) |

## UI Layout

Tab name: `"Kortz Center Heist"`

### Primary Target (Group)
- `ListCommand` — 27 options mapping to MPX_K26_HEIST_TARGET values 0-26

### General (Group)
- `BoolCommand` — Guard Routes Purchased (GENERAL_BS bit 5)
- `BoolCommand` — Glass Cutter Purchased (GENERAL_BS bit 6)
- `BoolCommand` — Power Drills Purchased (GENERAL_BS bit 7)
- `BoolCommand` — EMP Charges Purchased (GENERAL_BS bit 8)

### Prep Work (Group)
16 BoolCommands, each mapping to one MPX_K26_ROBBERY_PROG bit:

| Bit | Prep Item |
|-----|-----------|
| 0 | Scope Out Kortz Center |
| 1 | Alpha Mail Disguise |
| 2 | Hazmat Suit |
| 3 | Staff Key Card |
| 4 | Tactical Equipment |
| 5 | Hacking Device |
| 6 | Access Code |
| 7 | Unmarked Weapons |
| 8 | Armored Caracara |
| 9 | Annihilator Stealth |
| 10 | Manchez |
| 11 | EMP Charges |
| 12 | Guard Shipments |
| 13 | Guard Routes |
| 14 | Glass Cutter |
| 15 | Power Drills |

### Scoping (Group)
- `BoolCommand` — Secondary Targets Scoped (SCOPING_BS = -1)
- `BoolCommand` — POI Scoped (POI_BS = -1)

### Action
- `Command` — **Setup** button: writes all above state to MPX_K26_* stats via `Stats::SetInt`

## Command Naming Convention

Prefix all command IDs with `kortzcenterheist`:
- `kortzcenterheistprimarytarget` — ListCommand
- `kortzcenterheistguardroutes` — BoolCommand (GENERAL_BS bit 5)
- `kortzcenterheistglasscutter` — BoolCommand (GENERAL_BS bit 6)
- `kortzcenterheistpowerdrills` — BoolCommand (GENERAL_BS bit 7)
- `kortzcenterheistempcharges` — BoolCommand (GENERAL_BS bit 8)
- `kortzcenterheistscopeout` — BoolCommand (ROBBERY_PROG bit 0)
- ... (one per prep bit)
- `kortzcenterheistscopesecondary` — BoolCommand (SCOPING_BS)
- `kortzcenterheistscopepoi` — BoolCommand (POI_BS)
- `kortzcenterheistsetup` — Command (Setup)

## Behavior

**Setup Command:**
1. Read state from all commands
2. Build GENERAL_BS bitfield (start at -1, clear/set bits 5-8)
3. Build ROBBERY_PROG bitfield based on 16 bools
4. Write all stats:
   - `Stats::SetInt("MPX_K26_GENERAL_BS", generalBits)`
   - `Stats::SetInt("MPX_K26_GENERAL_BS2", -1)`
   - `Stats::SetInt("MPX_K26_ROBBERY_PROG", robberyProgBits)`
   - `Stats::SetInt("MPX_K26_HEIST_TARGET", targetValue)`
   - `Stats::SetInt("MPX_K26_SCOPING_BS", scopingValue)`
   - `Stats::SetInt("MPX_K26_POI_BS", poiValue)`

## Registration

In `HeistModifier.cpp`:
- Add `#include "Heist/KortzCenterHeist.hpp"`
- Add `heistTabBar->AddItem(RenderKortzCenterHeistMenu());`
