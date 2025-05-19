# YimMenu Contribution Guide (WIP)

## Important!

PRs containing AI-generated code will NOT BE ACCEPTED! 

## Structure

- `core/` : Essential general features for the base
- `game/` : Game specific implemented things

## General tips

- Try to use Clang instead of MSVC and fix all compiler warnings
- All new features should be implemented as `Command`s. gta/features/self/Suicide.cpp contains an example of a normal `Command`, and gta/features/self/Godmode.cpp contains a `LoopedCommand` (a command that runs every frame)
- When constructing constexpr arrays, make sure to use `std::to_array` instead of relying on automatic deduction in order to prevent issues when building with Clang
- Use `static_cast` and `reinterpret_cast` instead of C-style casts
- Use `std::string_view` for immutable string parameters