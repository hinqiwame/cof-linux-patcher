# Cry of Fear Linux Patcher (Core)
> v0.0.4 - Пізніше ви дізнаєтесь, чому це "core" :)
>
![](/ass/logo.png)

Патчер для Cry of Fear на Linux, що виправляє різні помилки, замінюючи збірку гри та бібліотеки движка на виправлені версії. Патчер автоматизує процес, роблячи його простішим для користувачів, щоб застосувати необхідні модифікації. Написано на C.

## Використання (core)
> Вимоги: `git`
> 
Щоб використовувати патчер core, виконайте такі кроки:
- Клонуйте репозиторій:
  ```
  git clone https://github.com/hinqiwame/cof-linux-patcher
  ```
- Перейдіть до склонованого репозиторію:
  ```
  cd cof-linux-patcher
  ```
- Надайте патчеру права на виконання:
  ```
  chmod +x cof-patcher-core
  ```
- Запустіть патчер:
  ```
  ./cof-patcher-core
  ```
---
Процес буде виглядати приблизно так:
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

**Патчер припускає, що у вас встановлено Cry of Fear з Proton 5.13-6.** <br>
Другий аргумент після `./cof-patcher-core` має бути **ПОВНИМ** шляхом до встановлення Cry of Fear (шлях має починатися з `/home/`). Патчер перевірить наявність директорії та виконає заміну файлів. <br>
> Якщо ви встановили Cry of Fear через офіційний Steam клієнт (не flatpak або інші), типовий шлях виглядає так: `/home/your_username/.steam/steam/steamapps/common/Cry of Fear`.
>

## Додаткові аргументи
- `-h, --help`: Показати довідку та вийти.
- `-v, --version`: Показати версію збірки патчера та вийти.

## Виправлені файли
Патчер замінює кілька файлів для покращення досвіду гри Cry of Fear на Linux. Ось короткий огляд змін:
1. `cof.exe` - Заміна основного виконуваного файлу гри. [Це офіційний патч від Team Psyksckallar](https://www.moddb.com/games/cry-of-fear/downloads/cry-of-fear-crash-patch-for-64-bit-users). Використовує 64-бітну версію замість 32-бітної, що робить гру набагато стабільнішою.
2. `opengp32.dll` - Використовується для динамічного освітлення в грі. Посилання на нього виправлені в `/hw.dll` і `/cryoffear/cl_dlls/client.dll`. Wine може не мати функції `wglGetDefaultProcAddress`. Щоб це виправити, я пропатчив `opengl32.dll` Cry of Fear, змінивши команди `jne(75)` на `jmp(EB)` за такими адресами:
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

# Подяки
- [Cry of Fear](https://store.steampowered.com/app/223710/Cry_of_Fear/) - оригінальна гра <br>
- [Proton](https://github.com/ValveSoftware/Proton) - шар сумісності для запуску гри на Linux <br>
- [SC-Cry-of-Fear-Weapons-Project](https://github.com/KernCore91/-SC-Cry-of-Fear-Weapons-Project) - натхнення для README і логотипа :) <br>
- [Андреас Рённберг](https://www.facebook.com/andreas.rumpel.ronnberg) - найкраща людина в світі!!!
