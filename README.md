# YimMenuV2

Experimental menu for GTA 5: Enhanced

## How to use

1. Download YimMenuV2 from [GitHub Releases](https://github.com/YimMenu/YimMenuV2/releases/tag/nightly)
2. Download an injector, such as [Xenos](https://www.unknowncheats.me/forum/general-programming-and-reversing/124013-xenos-injector-v2-3-2-a.html)
3. Open Rockstar Launcher, select Grand Theft Auto V Enhanced, go to settings, and disable BattlEye. If you are using Steam or Epic Games, you may have to pass the -nobattleye command line parameter as well
4. Launch GTA V, use your injector to inject YimMenuV2.dll at the main menu, then you may load into online

## How to open the menu?

Press the `INSERT` key or `Ctrl+\` to open the menu
 
## Common issues

### I can't load into the game with FSL

FSL is currently unmaintained and will not work for Grand Theft Auto V Enhanced. To fix this, disable FSL by removing WINMM.dll from your GTA launch directory 

### I keep getting desynced from public sessions every five minutes

We currently do not have a BattlEye bypass, and legitimate hosts will eventually remove you due to a heartbeat failure. There is currently no way to stop this other than using an actual (private) bypass

### I removed FSL and the game doesn't start up anymore

This is a known issue; delete "Documents/GTAV Enhanced/Profiles" to fix