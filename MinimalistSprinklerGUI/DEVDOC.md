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
    direction TB
    class menuStates{
        <<enumeration>>
        mainMenu,
        sprinkleProfiles,
        sprinkleRelays,
        sprinkleAuto,
        sprinkleSetter,
        chainSprinkler,
        testSprinkler,
        settings,
        clockSetter,
        developer
    }
    class Point {
        +int x
        +int y
        +Point(int x = 0, int y = 0)
        +Point(const Point &p)
        +operator==(const Point &p) bool
        +operator!=(const Point &p) bool
        +operator=(const Point &p) Point &
    }
    class RangeInt~min; max~{
        + value: int
        + min: int$
        + max: int$
        + range: int$
        + RangeInt(value)
        + setValue(value) void
        + getValue(): int
        + op()() RangeInt&
        + op=(value) RangeInt&
        + op+=(value) RangeInt&
        + op-=(value) RangeInt&
        + op++() RangeInt&
        + op--() RangeInt&
    }
    class Range60~0;59~{
        + Range60(value)
    }
    class Range24~0;23~{
        + Range24(value)
    }
    class Time{
        + hour: Range24
        + minute: Range60
        + Time(h, m)
        + hours() int
        + minutes() int
        + op+=(value) Time&
        + op-=(value) Time&
        + op+(value) Time
        + op-(value) Time      
    }
    class TouchButton{
        + pos: Point
        + size: Point
        + TouchButton(x, y, w, h)
        + isPressed(x, y) bool
    }
    class Relay{
        - idCounter: uint$
        + id: uint
        + pin: uint
        + duration: uint 
        + start: Time
        + Relay()
        + Relay(ID, Start, Duration, Pin)
        + end() Time
        + SetRelayState(state) void
    }
    class Profile{
        + isActive: bool
        + relays: Relay[]
    }
    class SystemController{
        + style: menuStyle
        + mainswitch: bool
        + humiditySensitivity: Range1024
        + profiles: Profile[]
        + now: DateTime
        + state: menuStates
        + currentPage: uint
        + currentProfile: uint
        + currentRelay: uint
        + temporalProfile: Profile
        + temporalSetter: Relay
        + SystemController()
        + StartMenu() void
        + ResetMenu() void
        + CurrentRelay() Relay&        
        + UpdateRelays(currentTime)
        + DrawStateScreen() void
        + UpdateStatesScreen() void
        + Touched(x, y) void
    }

    RangeInt <|-- Range24
    Time *-- Range24
    Time *-- Range60
    RangeInt <|-- Range60
    RangeInt <|-- Range1024

    SystemController *-- Range1024
    SystemController *-- Profile
    SystemController *-- Relay
    
    Profile *-- Relay
    
    TouchButton *-- Point   
    
    SystemController *-- menuStyle
    SystemController *-- menuStates
    
    SystemController --> display
    SystemController --> menu
    SystemController --> memory
    
    menu --> memory
    
    class display{
        <<functions>>
        + DrawMainMenu()
        + DrawSprinkleProfilesMenu()
        + DrawSprinkleRelayChoser()
        + DrawSprinkleAutomatic()
        + DrawSprinkleSetter()
        + DrawChainSprinkleMenu()
        + DrawTestMenu()
        + DrawHumidityMenu()
        + DrawSettingsMenu()
        + DrawClockMenu()
    }
    class menu{
        <<functions>>
        + RunMenu()
        + ExecuteClickEvent(clickPos)
    }
    class memory{
        <<functions>>
        + SaveStyle(style)
        + LoadStyle(style&) 
        + SaveMainSwitch(mainSwitch) 
        + LoadMainSwitch(mainSwitch&)
        + SaveHumidity(humidity)
        + LoadHumidity(humidity&)
        + SaveProfileData(profile, profileNum)
        + LoadProfileData(profile&, profileNum)
        + SaveRelayData(relay, profileNum, relayNum)
        + LoadRelayData(relay&, profileNum, relayNum)
    }
    

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


