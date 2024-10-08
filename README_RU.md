# Cry of Fear Linux Patcher (Core)
> v0.0.4 - Позже вы узнаете, почему это "core" :)
>
![](/ass/logo.png)

Патчер для Cry of Fear на Linux, исправляющий различные ошибки, заменяя сборку игры и библиотеки движка на исправленные версии. Патчер автоматизирует процесс, делая его проще для пользователей, чтобы применить необходимые модификации. Написан на C.

## Использование (core)
> Требования: `git`
> 
Чтобы использовать патчер core, выполните следующие шаги:
- Клонируйте репозиторий:
  ```
  git clone https://github.com/hinqiwame/cof-linux-patcher
  ```
- Перейдите в склонированный репозиторий:
  ```
  cd cof-linux-patcher
  ```
- Предоставьте патчеру права на выполнение:
  ```
  chmod +x cof-patcher-core
  ```
- Запустите патчер:
  ```
  ./cof-patcher-core
  ```
  
---
Процесс будет выглядеть примерно так:
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

**Патчер предполагает, что у вас установлен Cry of Fear с Proton 5.13-6.** <br>
Второй аргумент после `./cof-patcher-core` должен быть **ПОЛНЫМ** путем до установки Cry of Fear (должен начинаться с `/home/`). Патчер проверит существование директории и выполнит замену файлов. <br>
> Если вы установили Cry of Fear через официальный Steam клиент (не flatpak или другие), обычно путь выглядит так: `/home/your_username/.steam/steam/steamapps/common/Cry of Fear`.
>

## Дополнительные аргументы
- `-h, --help`: Показать справку и выйти.
- `-v, --version`: Показать версию сборки патчера и выйти.

## Исправленные файлы
Патчер заменяет несколько файлов для улучшения работы Cry of Fear на Linux. Вот краткий обзор изменений:
1. `cof.exe` - Заменяет основной исполняемый файл игры. [Это официальный патч от Team Psyksckallar](https://www.moddb.com/games/cry-of-fear/downloads/cry-of-fear-crash-patch-for-64-bit-users). Использует 64-битную версию вместо 32-битной, что делает игру гораздо более стабильной.
2. `opengp32.dll` - Используется для динамического освещения в игре. Ссылки на него исправлены в `/hw.dll` и `/cryoffear/cl_dlls/client.dll`. Wine может не иметь функции `wglGetDefaultProcAddress`. Чтобы это исправить, я пропатчил `opengl32.dll` Cry of Fear, изменив команды `jne(75)` на `jmp(EB)` по следующим адресам:
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


# Благодарности
- [Cry of Fear](https://store.steampowered.com/app/223710/Cry_of_Fear/) - оригинальная игра <br>
- [Proton](https://github.com/ValveSoftware/Proton) - слой совместимости для запуска игры на Linux <br>
- [SC-Cry-of-Fear-Weapons-Project](https://github.com/KernCore91/-SC-Cry-of-Fear-Weapons-Project) - вдохновение для README и логотипа :) <br>
- [Андреас Рённберг](https://www.facebook.com/andreas.rumpel.ronnberg) - лучший человек на свете!!!
