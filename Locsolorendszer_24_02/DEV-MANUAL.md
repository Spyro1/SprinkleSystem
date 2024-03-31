# Locsolórendszer 2024-es változat

> Készítette: Szenes Márton

---

## Menürendszer

- MainScreen
  - Locsolás (BTN)
  - Sorban (BTN)
  - Tesztelés (BTN)
  - Nedvesség (BTN)
  - Beállítások (BTN)
  - Ki/Be (BTN)
  - Idő (BTN)
    - home
    - óra ↑ (BTN)
    - óra ↓ (BTN)
    - perc ↑ (BTN)
    - perc ↓ (BTN)
-

## Gombok

- Általánosak: [] : vissza, mentés
- MainScreen: **[7]** : Locsolás, Sorban, Tesztelés, Nedvesség, Időzítés, Be/Ki, Idő
- Idő beállítás: **[4]** : óra fel, óra le, perc fel, perc le
- Időszakok: **[6]** : 1.időszak, 2.időszak, 3.időszak, 1.On/Off, 2.On/Off, 3.On/Off
- Időzítés beállítás: **[8]** : Relé fel, Relé le, óra fel, óra le, perc fel, perc le, időtartam fel, időtartam le
- Sorban: **[7]** V: Indítás, relétől fel, relétől le, reléig fel, reléig le, időtartam fel, időtartam le
- Tesztelés **[10]** : (1-8) (9-16) kapcsoló, lapozás előre, lapozás vissza
- Nedvesség :
- Beállítások :

### Gombok kiosztása

## Osztályszerkezet

```mermaid
classDiagram

    class main{

    }
    class relay{

    }
    class Menu{
      + State: menuState
      + mainSwitch: bool
      + Menu(tft, SD)
      + RunMenu() void
      + Touched(x, y) void
    }
    class display{
      <<functions>>
        + DrawMainScreen()
        + DrawSprinkleSubMenu()
        + DrawChainSprinkleSubMenu()
        + DrawTestSubMenu()
        + DrawPeriodSubMenu()
    }
    class Point{
      + x: int
      + y: int
    }
    class Size{
      + width: int
      + height: int
    }
    class TouchButton{
      - pos: Point
      - size: Size
      - tft: &TFT_Display
      - SD: &SdFat
      + TouchButton()
      + isPressed(x, y) bool
      + activate() void
      + ifPressedThenActivate(x, y) bool
    }

    Menu *-- TouchButton

    TouchButton o-- Point
    TouchButton o-- Size

```
