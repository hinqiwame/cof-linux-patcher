# Cry of Fear Linux Patcher (Core)
> v0.0.4 - You will find out why it's "core" now later :)
> 
![](/ass/logo.png)

A patcher for Cry of Fear on Linux, addressing various bugs by replacing game build and engine libraries with patched versions. The patcher automates the process, making it easier for users to apply the necessary modifications. Written in C.
> Вы также можете прочитать этот README на [Русском](README_RU.md) або прочитати його [Українською](README_UA.md) мовою.
>

## Usage (core)
> Prerequisites: `git`
> 
To use the core patcher follow these steps:
- Clone the repository:
  ```
  git clone https://github.com/hinqiwame/cof-linux-patcher
  ```
- Navigate to the cloned repo:
  ```
  cd cof-linux-patcher
  ```
- Grant patcher executable permissions:
  ```
  chmod +x cof-patcher-core
  ```
- Run the patcher:
  ```
  ./cof-patcher-core
  ```
---
The whole process will look similar to this:
```
[hinqiwame@icantstopbleeding cof-linux-patcher]$ ./cof-patcher-core ~/.steam/steam/steamapps/common/Cry\ of\ Fear/
[*] Checking provided directory...
[+] Directory check passed
[*] Moving files...
[*] Replacing cof.exe...
[+] cof.exe replaced!
[~] Deleting opengl32.dll in the OG directory...
[+] opengl32.dll removed!
[*] Moving opengp32.dll...
[+] opengp32.dll moved!
[*] Replacing hw.dll...
[+] hw.dll replaced!
[*] Replacing client.dll...
[+] client.dll replaced!
[*] Everything is done. Happy halloween! :)
```
<br>

**Patcher assumes that you have installed Cry of Fear along with the Proton 5.13-6.** <br> 
The second argument after `./cof-patcher-core` should be the **FULL** path to your Cry of Fear installation (should begin with `/home/`). Patcher will check the directory's existence and proceed with the file replacements. <br>
> If you install Cry of Fear through official Steam client (not flatpak or whatever), typically the path is `/home/$USER/.steam/steam/steamapps/common/Cry\ of\ Fear/`.
>

## Optional Arguments
- `-h, --help`: Display the help message and exit.
- `-v, --version`: Display the version of the patcher build and exit.

## Patched files
The patcher replaces several files to improve the Cry of Fear experience on Linux. Here's a summary of the modifications:
1. `cof.exe` - Replaces the main game executable. [It is an official patch from Team Psyksckallar](https://www.moddb.com/games/cry-of-fear/downloads/cry-of-fear-crash-patch-for-64-bit-users). Uses x64 bit instead of x32, makes the game generally much more stable.
2. `opengp32.dll` - Used for dynamic lighting in the game. References to it are corrected in `/hw.dll` and `/cryoffear/cl_dlls/client.dll`. Wine may lack the `wglGetDefaultProcAddress` function. To address this, I've patched Cry of Fear's `opengl32.dll` by changing occurrences of `jne(75)` to `jmp(EB)` at the specific addresses:
```
Address     To    From
000066DB    EB    75
00006702    EB    75
00006728    EB    75
0000674F    EB    75
00006776    EB    75
0000679C    EB    75
000067EA    EB    75
00006810    EB    75
00006837    EB    75
0000685E    EB    75
000068AB    EB    75
000068F8    EB    75
0000691F    EB    75
00006943    EB    75
00006966    EB    75
0000698A    EB    75
```

# Credits
- [Cry of Fear](https://store.steampowered.com/app/223710/Cry_of_Fear/) - original game <br>
- [Proton](https://github.com/ValveSoftware/Proton) - compability layer for running the game on Linux <br>
- [SC-Cry-of-Fear-Weapons-Project](https://github.com/KernCore91/-SC-Cry-of-Fear-Weapons-Project) - README inspiration and logo :) <br>
- [Andreas Rönnberg](https://www.facebook.com/andreas.rumpel.ronnberg) - Best person ever!!!
