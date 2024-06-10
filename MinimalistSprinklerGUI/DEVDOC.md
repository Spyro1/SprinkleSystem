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
- Időzítések: **[6]** : 1.időszak, 2.időszak, 3.időszak, 1.On/Off, 2.On/Off, 3.On/Off
- Időszak beállítás: **[8]** : Relé fel, Relé le, óra fel, óra le, perc fel, perc le, időtartam fel, időtartam le
- Sorban: **[7]** V: Indítás, relétől fel, relétől le, reléig fel, reléig le, időtartam fel, időtartam le
- Tesztelés **[10]** : (1-8) (9-16) kapcsoló, lapozás előre, lapozás vissza

### Gombok kiosztása

## Osztályszerkezet

```mermaid
classDiagram

    class menuStates{
        <<enumeration>>
        mainMenu, 
        sprinkleProfiles, 
        sprinkleRelays, 
        sprinkleAuto,
        sprinkleSetter,
        chainSprinkler,
        test,
        humidity,
        settings,
        clock
    }
    class menuStyle{
        <<enumeration>>
        easy,
        medium,
        quality
    }
    class Relay{
        - idCounter: uint$
        + id: uint
        + pin: uint
        + duration: uint 
        + start: TimeSpan
        + Relay()
        + Relay(ID, Start, Duration, Pin)
        + end() TimeSpan
    }
    class Profile{
        + isActive: bool
        + relays: Relay[]
    }
    class display{
      <<interface>>
        + DrawMainMenu()
        + DrawSprinkleProfilesMenu()
        + DrawSprinkleRelayChoser()
        + DrawSprinkleSetter()
        + DrawChainSprinkleMenu()
        + DrawTestMenu()
        + DrawHumidityMenu()
        + DrawSettingsMenu()
        + DrawClockMenu()
    }
    class Point{
      + x: int
      + y: int
      + Point(x, y)
      + op==() bool
      + op!=() bool
      + op=() Point&
    }
    class Size{
      + Size(width, height)
    }
    
    class System{
        + style: menuStyle
        + state: menuStates
        + mainswitch: bool
        + humiditySensitivity: uint
        + profiles: Profile
        + currentPage: uint
        + currentProfile: uint
        + currentRelay: uint
        + temporalProfile: Profile
        + temporalStart: TimeSpan
        + temporalDuration: uint
        + System()
        + Reset()
        + UpdateRelays(currentTime)
        + getSelectedRelay()
        
        
    }
    
    
    System --> menuStyle
    System --> menuStates
    System *-- Profile
    System --> display
    
    Profile *-- Relay
    
    Point <|-- Size

```


```mermaid
stateDiagram
%%    direction LR
    state mainMenu{
        sprinkle
        chain
        test
        humidity
        settings
        mainSwitch
        clock
    }
    sprinkle --> sprinkleProfiles
    state sprinkleProfiles{
        automatic_1_3
        profile_1_3
        profileSwitch_1_3
    }
    automatic_1_3 --> sprinkleAuto
    state sprinkleAuto{
        setHourAuto
        setMinuteAuto
        setDurationAuto
        saveAutomatic
    }
    profile_1_3 --> sprinkleRelays
    state sprinkleRelays{
        relays_1_8
        left
        right
    }
    relays_1_8 --> sprinkleSetter
    state sprinkleSetter{
        setHour
        setMinute
        setDuration
    }
    chain --> chainSprinkle
    state chainSprinkle{
        setStartChain
        setEndChain
        setChainDuration
    }
    
```


