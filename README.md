# Locsolórendszer v2024

> Készítette: Szenes Marton

Ez a projekt azért készült el, hogy lehetővé tegye automatikusan, az időzített permetezést (locsolást) telepített locsolófejekkel a kertben.
Számos üzemmóddal rendelkezik, mint például külön relé időzítés, automatikus időzítés, több profil, teszt üzemmód, sorban locsolás és még sok más.

![SprinkleSystemMainScreen](Documentacion/screenshots/mainMenuScreen.png)
_Főképernyő_

## Felhasználóknak

Ha az elektronikai rendszer telepítve van, akkor a [Felhasználói kézikönyvben](Documentacion/UserManual.md) tekintheti meg a locsolórendszer használatát.
Bármilyen kérdés esetén írjon issue-t.

## Fejlesztőknek

Az elektronikai rendszer megfelelő telepítése után kövesse a következő lépéseket a projekt **Arduino Mega 2560**-ra való feltöltéséhez:
1. Nyissa meg a [MinimalistSprinklerGUI.ino](MinimalistSprinklerGUI/MinimalistSprinklerGUI.ino) fájlt az **Arduino IDE**-ban, és várja meg, amíg az egész projekt betöltődik.
2. Győződjön meg arról, hogy minden szükséges könyvtár telepítve van az eszközén:
   - `Adafruit_GFX.h` - Alap grafikus könyvtár alakzatok megjelenítéséhez
   - `MCUFRIEND_kbv.h` - 2,8"-os TFT-kijelző könyvtára a képernyőn való megjelenítéshez
   - `TouchScreen.h` - 2,8" érintőképernyő könyvtár a felhasználói bevitelhez
   - `SPI.h` - egy buszkönyvtár az óramodullal való kommunikációhoz
   - `SdFat.h` - könyvtár a kijelzőpanelen lévő SD-kártyanyílással való kommunikációhoz
   - `RTClib.h` - valós idejű óra modul könyvtára az SCL-SDA kommunikációhoz
3. Fordítsa le a projektet. Ha bármilyen hibát ír ki a könyvtárakkal kapcsolatban, próbálja meg telepíteni a fennmaradó könyvtárakat, vagy forduljon hozzám további utasításokért.
4. Válassza ki a csatlakoztatott soros portot és az Arduino modellt a képernyő tetején található legördülő menüből.
5. Töltse fel a projektet az Arduinora. Ha minden megfelelően működik, látnia kell, hogy a képernyő néhányszor felvillan, majd egy fekete képernyőt, ezután pedig a fent látható főképernyő jelenik meg.

A projekt alaposabb megértéséhez tekintse meg a [Fejlesztői dokumentációt](Documentacion/DevDoc.md).

## Villanyszerelőkenk

Ez a projekt jelenleg legfeljebb 16 kapcsolórelét tud támogatni. Ehhez a projekthez a következő összetevőkre lesz szüksége:

- 2,8"-os TFT-kijelző shield (ILI9341 LDC meghajtóval)
- RTC modul (DS3231)
- max 16 relé kapcsoló (lehet kevesebb is)
- Jumper kábelek
- 5-7V tápegység Arduinohoz
- 7-12V-os tápellátás a relékhez

### Kapcsolási rajz

![Schematic](assets/Schematics/Locsolorendszer-mega-kapcsolas.png)
