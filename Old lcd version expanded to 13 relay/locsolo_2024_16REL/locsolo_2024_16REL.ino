#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

// Osztályok deklrálása
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtcDS;

// Pinek definiálása
#define JS_SW 13
#define JS_VRX A2
#define JS_VRY A1
#define RES 12
// Bemeneti változók
int JX, JY, JS; // A joystick analóg értékei, ebbe olvassuk be
enum Dir
{
    up,
    down,
    left,
    right,
    enter,
    none
};
Dir joy;                                                                                    // A joystick értéke a beolvasás után
                                                                                            // Relék tulajdonságai
const int maxTimeSpan = 60;                                                                 // Hány percig mehet max egy relé
const int numOfRelays = 16;                                                                 // A relék maximális száma
const int numOfMuxDataPins = 4;                                                             // A 16xMux adat lábai
int relPins[numOfRelays] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53}; // Relék pinei
// int muxPins[4] = {6, 5, 4, 3};                               // Data Pins of the 16xMuxer
// int muxSignalPin = 2;                                        // Signal Pin of the 16xMuxer
// int muxEnablePin = 7;                                        // Enaple Pin of the 16xMuxer
int relTime[numOfRelays];            // Relék Időtartama (0-60 terjedelem)
int StartRelTime[numOfRelays][2][2]; // Relék kezdési ideje [ID][0: Kezdési, 1: Végzési][0: óra, 1: perc]
bool relState[numOfRelays];
bool temp_relState[numOfRelays];
enum Prop
{
    GlobalState,
    Durations,
    Startings,
    States
};
// int active_rel; // Felülvizsgálás alatt
// Menü beállítások
const int changeDif = 5;
const int mainMenuSize = 4;  // Hány fő opció van a menüben
const int menuLevelSize = 3; // Milyen méllyre lehet menni a münben max
const int infoSubMenuSize = 5;
int current_rel = 0;
int menuLevel = 0;         // 0 Title screen , 1 Main menu , 2 Sub menus
int current_menu_item = 0; // (1) main menu-ben az aktív opció
int current_info_item = 0; // (2) Info submenu , aktív opció
int setclock = 0;          // 0 hour , 1 minute
int setrelay = 0;          // 0 ID, 1 E=Állapot, 2 S/h=Kezdési idő óra, 3 S/m=Kezdési idő perc, 4 T=Időtartam(perc)
const int numOfRelOptions = 5;
// Képernyő alvás
long MillisTime = 0;
long DisplayDuration = 20000;
// Functioning variables
DateTime Current_Time;
bool State = true;
// New Characters
byte arrowL[] = {B00010, B00110, B01110, B11110, B01110, B00110, B00010, B00000};
byte arrowR[] = {B01000, B01100, B01110, B01111, B01110, B01100, B01000, B00000};
byte arrowU[] = {B00000, B00000, B00000, B00000, B00100, B01110, B11111, B00000};
byte arrowD[] = {B00000, B11111, B01110, B00100, B00000, B00000, B00000, B00000};

byte u_dotted[] = {B01010, B00000, B10001, B10001, B10001, B10011, B01101, B00000};
byte o_dotted[] = {B01010, B00000, B01110, B10001, B10001, B10001, B01110, B00000};
byte o_dotted_long[] = {B00101, B01010, B01110, B10001, B10001, B10001, B01110, B00000};
byte o_dotted_big[] = {B10001, B01110, B10001, B10001, B10001, B10001, B01110, B00000};

byte aI_t[8] = {B10, B100, B1110, B1, B1111, B10001, B1111};         // á betű karakterképe
byte eI_t[8] = {B10, B100, B1110, B10001, B11111, B10000, B1110};    // é betű karakterképe
byte iI_t[8] = {B10, B100, B0, B1110, B100, B100, B1110};            // í betű karekterképe
byte oI_t[8] = {B10, B100, B1110, B10001, B10001, B10001, B1110};    // ó betű karakterképe
byte uI_t[8] = {B10, B100, B10001, B10001, B10001, B10011, B1101};   // ú betű karakterképe
byte oII_t[8] = {B00101, B01010, B0, B1110, B10001, B10001, B1110};  // ő betű karakterképe
byte uII_t[8] = {B00101, B01010, B0, B10001, B10001, B10011, B1101}; // ű betű karakterképe
// Azonosítók
int AU = 0, AD = 1; /*AL = 2, AR = 2;*/
int od = 2, odl = 3, al = 4, el = 5, il = 6, ol = 7;
int RealTime = 0, Relek = 1, Allapot = 2, Infok = 3;
// Eljárások

void ReadFromMemory(Prop which)
{
    switch (which)
    {
    case Prop::GlobalState: // 0
        State = EEPROM.read(0) == 1 ? true : false;
        break;
    case Prop::Durations: // 1-10
        for (int i = 0; i < numOfRelays; i++)
        {
            relTime[i] = EEPROM.read(i + 1); // read timespan
        }
        break;
    case Prop::Startings: // 11-20, 21-30
        for (int i = 0; i < numOfRelays; i++)
        {
            StartRelTime[i][0][0] = EEPROM.read(i + numOfRelays + 1);       // read hour
            StartRelTime[i][0][1] = EEPROM.read(i + (2 * numOfRelays) + 1); // read minute
        }
        break;
    case Prop::States: // 31-40
        for (int i = 0; i < numOfRelays; i++)
        {
            relState[i] = EEPROM.read(i + (3 * numOfRelays) + 1) == 1 ? true : false; // read relay states
            temp_relState[i] = relState[i];
        }
        break;
    default:
        break;
    }
}
void WriteToMemory(Prop which)
{
    switch (which)
    {
    case Prop::GlobalState: // 0
        EEPROM.update(0, State ? 1 : 0);
        // Serial.print("GlobalState: 0-"); Serial.println(State);
        break;
    case Prop::Durations: // 1-10
        for (int i = 0; i < numOfRelays; i++)
        {
            EEPROM.update(i + 1, relTime[i]);
            // Serial.print("Duration: "); Serial.print(i+1); Serial.print("-"); Serial.println(State);
        }
        break;
    case Prop::Startings: // 11-20, 21-30
        for (int i = 0; i < numOfRelays; i++)
        {
            EEPROM.update(i + numOfRelays + 1, StartRelTime[i][0][0]);
            EEPROM.update(i + (2 * numOfRelays) + 1, StartRelTime[i][0][1]);
            // Serial.print("Startings: "); Serial.print(i + numOfRelays + 1); Serial.print("-"); Serial.println(StartRelTime[i][0][0]);
            // Serial.print("Startings: "); Serial.print(i+ (2 * numOfRelays) + 1); Serial.print("-"); Serial.println(StartRelTime[i][0][1]);
        }
        break;
    case Prop::States: // 31-40
        for (int i = 0; i < numOfRelays; i++)
        {
            EEPROM.update(i + (3 * numOfRelays) + 1, relState[i] ? 1 : 0);
            // Serial.print("States: "); Serial.print(i+ (3 * numOfRelays) + 1); Serial.print("-"); Serial.println(relState[i]);
        }
        break;
    default:
        break;
    }
}

Dir GetInput(int X, int Y, int sw)
{
    Dir output;
    if (sw == 0)
    {
        output = Dir::enter;
    }
    else if (Y > 900)
    {
        output = Dir::down;
    }
    else if (Y < 100)
    {
        output = Dir::up;
    }
    else if (X > 900)
    {
        output = Dir::right;
    }
    else if (X < 100)
    {
        output = Dir::left;
    }
    else
    {
        output = Dir::none;
    }
    return output;
}
void print_line(int line, String text)
{
    lcd.setCursor(0, line);
    lcd.print("                 ");
    lcd.setCursor(0, line);
    lcd.print(text);
}
void ReturnToTitle()
{
    menuLevel = 0;
    current_menu_item = 0;
    current_info_item = 0;
    setclock = 0;
    setrelay = 0;
    current_rel = 0;
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Locsol");
    lcd.write(ol);
    lcd.print("rendszer");
    // lcd.setCursor(1,0);  lcd.write(odb); lcd.print("nt"); lcd.write(od); lcd.print("z"); lcd.write(odl); lcd.print("rendszer");
    lcd.setCursor(11, 1);
    lcd.print("Menu");
    lcd.print(">"); // lcd.write( AR);
}
void PrintTime(DateTime now)
{
    lcd.setCursor(1, 1);
    if (now.hour() < 10)
        lcd.print("0");
    lcd.print(now.hour());
    lcd.print(':');
    if (now.minute() < 10)
        lcd.print("0");
    lcd.print(now.minute());
    lcd.print(':');
    if (now.second() < 10)
        lcd.print("0");
    lcd.print(now.second());
}
void CalculateTiming()
{
    for (int i = 0; i < numOfRelays; i++)
    {
        // Ha a kezdési idő és az időtartam hozzá áthalad a következő órába
        if (StartRelTime[i][0][1] + relTime[i] >= 60)
        {
            // StartRelTime[i][1][0]++; // A vég óra növelése
            StartRelTime[i][1][0] = StartRelTime[i][0][0] + 1;
            // A maradék percek átvitele a következő órába
            StartRelTime[i][1][1] = (StartRelTime[i][0][1] + relTime[i]) - 60;
            // Ha átesne a 23 órán, visszaállítjuk 0 órára
            if (StartRelTime[i][1][0] >= 24)
            {
                StartRelTime[i][1][0] = 0;
            }
        }
        // Ha nem eseik át a következő órába, akkor simán hozzáadjuk
        else
        {
            StartRelTime[i][1][0] = StartRelTime[i][0][0];
            StartRelTime[i][1][1] = StartRelTime[i][0][1] + relTime[i];
        }
    }
}

// Navigációs eljárások
void move_up()
{
    if (menuLevel == 1)
    { // Main menüben naivágció fel
        if (current_menu_item > 0)
        {
            current_menu_item--;
        }
        else
        {
            current_menu_item = mainMenuSize - 1;
        }
    }
    else if (menuLevel == 2)
    {
        if (current_menu_item == RealTime) // RTC kézi beállítása
        {
            if (setclock == 0) // hour
            {
                if (Current_Time.hour() < 23)
                {
                    Current_Time = DateTime(2021, 1, 1, Current_Time.hour() + 1, Current_Time.minute(), Current_Time.second());
                }
                else
                {
                    Current_Time = DateTime(2021, 1, 1, 0, Current_Time.minute(), Current_Time.second());
                }
            }
            else if (setclock == 1) // minute
            {
                if (Current_Time.minute() < 59)
                {
                    Current_Time = DateTime(2021, 1, 1, Current_Time.hour(), Current_Time.minute() + 1, Current_Time.second());
                }
                else
                {
                    Current_Time = DateTime(2021, 1, 1, Current_Time.hour(), 0, Current_Time.second());
                }
            }
        }
        else if (current_menu_item == Allapot) // Allapot beállítása
        {
            State = !State;
        }
        else if (current_menu_item == Relek) // Relék tulajdonságainak módosítása
        {
            if (setrelay == 0)
            { // ID
                if (current_rel > numOfRelays - 2)
                {
                    current_rel = 0;
                }
                else
                {
                    current_rel++;
                }
            }
            else if (setrelay == 1)
            { // E - Állapot
                relState[current_rel] = !relState[current_rel];
            }
            else if (setrelay == 2)
            { // S-h
                if (StartRelTime[current_rel][0][0] < 23)
                {
                    StartRelTime[current_rel][0][0]++;
                }
                else
                {
                    StartRelTime[current_rel][0][0] = 0;
                }
            }
            else if (setrelay == 3)
            { // s-m
                if (StartRelTime[current_rel][0][1] < 60 - changeDif)
                {
                    StartRelTime[current_rel][0][1] += changeDif;
                }
                else
                {
                    StartRelTime[current_rel][0][1] = 0;
                }
            }
            else if (setrelay == 4)
            { // T
                if (relTime[current_rel] < maxTimeSpan)
                {
                    relTime[current_rel]++;
                }
                else
                {
                    relTime[current_rel] = 1;
                }
            }
        }
        else if (current_menu_item == Infok) // iunformációk leírása
        {
            if (current_info_item > 0)
            {
                current_info_item--;
            }
            else
            {
                current_info_item = infoSubMenuSize - 1;
            }
        }
    }
}
void move_down()
{
    if (menuLevel == 1)
    {
        if (current_menu_item < mainMenuSize - 1)
        {
            current_menu_item++;
        }
        else
        {
            current_menu_item = 0;
        }
    }
    else if (menuLevel == 2)
    {
        if (current_menu_item == RealTime) // RTC kézi beállítása
        {
            if (setclock == 0) // hour
            {
                if (Current_Time.hour() > 0)
                {
                    Current_Time = DateTime(2021, 1, 1, Current_Time.hour() - 1, Current_Time.minute(), Current_Time.second());
                }
                else
                {
                    Current_Time = DateTime(2021, 1, 1, 23, Current_Time.minute(), Current_Time.second());
                }
            }
            else // minute
            {
                if (Current_Time.minute() > 0)
                {
                    Current_Time = DateTime(2021, 1, 1, Current_Time.hour(), Current_Time.minute() - 1, Current_Time.second());
                }
                else
                {
                    Current_Time = DateTime(2021, 1, 1, Current_Time.hour(), 59, Current_Time.second());
                }
            }
        }
        else if (current_menu_item == Allapot) // Allapot beállítása
        {
            State = !State;
        }
        else if (current_menu_item == Relek) // Relék tulajdonságainak módosítása
        {
            if (setrelay == 0)
            { // ID
                if (current_rel <= 0)
                {
                    current_rel = numOfRelays - 1;
                }
                else
                {
                    current_rel--;
                }
            }
            else if (setrelay == 1)
            { // E - Állapot
                relState[current_rel] = !relState[current_rel];
            }
            else if (setrelay == 2)
            { // S-h
                if (StartRelTime[current_rel][0][0] > 0)
                {
                    StartRelTime[current_rel][0][0]--;
                }
                else
                {
                    StartRelTime[current_rel][0][0] = 23;
                }
            }
            else if (setrelay == 3)
            { // s-m
                if (StartRelTime[current_rel][0][1] > 0)
                {
                    StartRelTime[current_rel][0][1] -= changeDif;
                }
                else
                {
                    StartRelTime[current_rel][0][1] = 60 - changeDif;
                }
            }
            else if (setrelay == 4)
            { // T
                if (relTime[current_rel] > 1)
                {
                    relTime[current_rel]--;
                }
                else
                {
                    relTime[current_rel] = maxTimeSpan;
                }
            }
        }
        else if (current_menu_item == Infok) // iunformációk leírása
        {
            if (current_info_item < infoSubMenuSize - 1)
            {
                current_info_item++;
            }
            else
            {
                current_info_item = 0;
            }
        }
    }
}
void move_right()
{
    if (menuLevel < menuLevelSize - 1)
    {
        menuLevel++;
    }
    else if (menuLevel == 2)
    {
        if (current_menu_item == RealTime && setclock == 0)
        {
            setclock = 1;
        }
        else if (current_menu_item == Relek && setrelay < numOfRelOptions - 1)
        {
            setrelay++;
        }
        else if (current_menu_item == Relek && setrelay >= numOfRelOptions - 1)
        {
            setrelay = 0;
        }
    }

    if (menuLevel == 2 && current_menu_item == Relek && setrelay == 0)
    {
        ReadFromMemory(Prop::Startings);
        ReadFromMemory(Prop::Durations);
        ReadFromMemory(Prop::States);
    }
    else if (menuLevel == 1 && current_menu_item == Allapot)
    {
        ReadFromMemory(Prop::GlobalState);
    }
}
void move_left()
{
    if (setclock == 1)
    {
        setclock = 0;
    }
    else if (setrelay > 0)
    {
        setrelay--;
    }
    else if (menuLevel > 0 && setclock != 1)
    {
        menuLevel--;
    }
}
void enterPushed()
{
    if (menuLevel == 2)
    {
        if (current_menu_item == RealTime) // Real Time
        {
            Current_Time = DateTime(2024, 1, 1, Current_Time.hour(), Current_Time.minute(), 0);
            rtcDS.adjust(Current_Time);
            ReturnToTitle();
            print_line(1, "RTC Be");
            lcd.write(al);
            lcd.print("ll");
            lcd.write(il);
            lcd.print("tva");
            delay(1000);
        }
        else if (current_menu_item == Allapot) // Allapot
        {
            WriteToMemory(Prop::GlobalState); // State write to memory
            ReturnToTitle();
            print_line(1, "STATE Be");
            lcd.write(al);
            lcd.print("ll");
            lcd.write(il);
            lcd.print("tva");
            delay(1000);
        }
        else if (current_menu_item == Relek)
        {
            CalculateTiming();
            WriteToMemory(Prop::Durations);
            WriteToMemory(Prop::Startings);
            WriteToMemory(Prop::States);
            ReturnToTitle();
            print_line(1, "Rel");
            lcd.write(el);
            lcd.print("k Be");
            lcd.write(al);
            lcd.print("ll");
            lcd.write(il);
            lcd.print("tva");
            delay(1000);
        }
    }
}
void PrintMainMenuItem(int line, int m)
{
    lcd.setCursor(0, line);
    lcd.print("                 ");
    lcd.setCursor(0, line);
    if (m == RealTime) // Idő beállítása
    {
        lcd.print("Id");
        lcd.write(odl);
        lcd.print(" be");
        lcd.write(al);
        lcd.print("ll");
        lcd.write(il);
        lcd.print("t");
        lcd.write(al);
        lcd.print("s");
    }
    else if (m == Relek) // Relék beállítása
    {
        lcd.print("Rel");
        lcd.write(el);
        lcd.print("k be");
        lcd.write(al);
        lcd.print("ll");
        lcd.write(il);
        lcd.print("t"); // lcd.write(al); lcd.print("s");
    }
    else if (m == Allapot) // Állapot
    {
        lcd.print("Allapot");
    }
    else if (m == Infok) // Információk
    {
        lcd.print("Inform");
        lcd.write(al);
        lcd.print("ci");
        lcd.write(ol);
        lcd.print("k");
    }
}
void PrintInfos(int line, int m)
{
    lcd.setCursor(0, line);
    lcd.print("                 ");
    lcd.setCursor(0, line);

    switch (m)
    {
    case 0:
        lcd.print("By:Szenes Marci");
        break;
    case 1:
        lcd.print("ID=Rel");
        lcd.write(el);
        lcd.print("k azon.");
        break;
    case 2:
        lcd.print("S=Kezd");
        lcd.write(el);
        lcd.print("si id");
        lcd.write(odl);
        break;
    case 3:
        lcd.print("E=Be/Ki-Allapot");
        break;
    case 4:
        lcd.print("T=Id");
        lcd.write(odl);
        lcd.print("tartam");
        break;
    default:
        break;
    }
}
int GetNext(int i, int Size)
{
    if (i < Size - 1)
    {
        i++;
    }
    else
    {
        i = 0;
    }
    return i;
}

// Main Functions
void setup()
{
    // INIT
    Serial.begin(9600);
    // lcd.begin(16, 2);
    lcd.begin();
    lcd.backlight();
    // Pinek beállítása
    pinMode(JS_VRX, INPUT);
    pinMode(JS_VRY, INPUT);
    pinMode(JS_SW, INPUT);
    digitalWrite(JS_SW, HIGH);
    // Muxer inicializálás
    // digitalWrite(muxEnablePin, LOW);
    // digitalWrite(muxSignalPin, HIGH);
    ;
    for (int i = 0; i < numOfRelays; i++)
    {
        pinMode(relPins[i], OUTPUT);
        digitalWrite(relPins[i], HIGH);
    } // felhúzás
      // Idő beállítása
    if (!rtcDS.begin())
    {
        Serial.println("Couldn't find RTC");
        // while (1)
        //     ;
    }
    if (rtcDS.lostPower())
    {
        Serial.println("RTC lost power, lets set  the time!"); // following line sets the RTC to the date & time this sketch was compiled
        rtcDS.adjust(DateTime(F(__DATE__), F(__TIME__)));      // This line sets the RTC with an explicit date & time, for example to set
    }
    // Custom Characters
    lcd.createChar(AU, arrowU); // ↑
    lcd.createChar(AD, arrowD); // ↓
    // lcd.createChar(AL, arrowL); // ←
    // lcd.createChar(AR, arrowR); // →
    lcd.createChar(od, o_dotted); // ö
    // lcd.createChar(ud, u_dotted); // ü
    lcd.createChar(odl, o_dotted_long); // ő
    // lcd.createChar(odb, o_dotted_big); // Ö
    lcd.createChar(al, aI_t); // á
    lcd.createChar(el, eI_t); // é
    lcd.createChar(il, iI_t); // í
    lcd.createChar(ol, oI_t); // ó
                              // Értékek beolvasása memóriából
    ReadFromMemory(Prop::GlobalState);
    ReadFromMemory(Prop::Startings);
    ReadFromMemory(Prop::Durations);
    ReadFromMemory(Prop::States);
    // Debug
    // for (int i = 0; i < numOfRelays; i++)
    // {
    //     StartRelTime[i][0][0] = 15;
    //     StartRelTime[i][0][1] = 33 + i;
    //     relTime[i] = 1;
    // }

    // Kiértékelés
    CalculateTiming();
    // Title Screen
    ReturnToTitle();
    // Init vars
    MillisTime = millis();
}

void loop()
{
    // Alvó mód
    long ElapsedTime = millis() - MillisTime; // Eltelt idő kiszámítása
    if (ElapsedTime > DisplayDuration)
    {
        lcd.noDisplay();
        lcd.noBacklight();
        ReturnToTitle();
    }
    // Bemenetek olvasása
    DateTime now = rtcDS.now(); // Get current time
    JX = analogRead(JS_VRX);    // Get X axis
    JY = analogRead(JS_VRY);    // Get Y axis
    JS = digitalRead(JS_SW);    // Get push input
                                // Bemenet kiértékelése
                                Serial.print("JX="); Serial.print(JX); Serial.print(" JY="); Serial.println(JY);
    joy = GetInput(JX, JY, JS); // Evaluate input
    if (menuLevel == 0)
    {
        PrintTime(now);
        Current_Time = now;
    }
    // Relék indítása, ha megfelelő az idő
    if (State)
    {
        for (int i = 0; i < numOfRelays; i++)
        {
            if (StartRelTime[i][0][0] == Current_Time.hour() && StartRelTime[i][0][1] == Current_Time.minute() && relState[i] == true && temp_relState[i] == true)
            {
                // digitalWrite(relPins[i],HIGH);
                digitalWrite(relPins[i], LOW); // felhúzás
                // relState[i] = false;
                temp_relState[i] = false;
                Serial.print("Bekapcsol: ");
                Serial.println(relPins[i] - 1);
            }
            if (StartRelTime[i][1][0] == Current_Time.hour() && StartRelTime[i][1][1] == Current_Time.minute() && temp_relState[i] == false)
            {
                // digitalWrite(relPins[i],LOW);
                digitalWrite(relPins[i], HIGH); // Felhúzás
                // relState[i] = true;
                temp_relState[i] = true;
                Serial.print("Kikapcsol: ");
                Serial.println(relPins[i] - 1);
            }
        }
    }
    // Navigáció
    if (joy != Dir::none)
    {
        lcd.noCursor();
        if (ElapsedTime < DisplayDuration)
        {
            switch (joy)
            {
            case Dir::up:
                move_up();
                break;
            case Dir::down:
                move_down();
                break;
            case Dir::right:
                move_right();
                break;
            case Dir::left:
                move_left();
                break;
            case Dir::enter:
                enterPushed();
                break;
            default:
                break;
            }
        }
        MillisTime = millis();
        lcd.display();
        lcd.backlight();
        // Kiiratás
        if (menuLevel == 0)
        { // Title Screen
            ReturnToTitle();
        }
        else if (menuLevel == 1) // Main Menu
        {
            PrintMainMenuItem(0, current_menu_item);
            lcd.print(">"); // lcd.write(AR);
            PrintMainMenuItem(1, GetNext(current_menu_item, mainMenuSize));
            lcd.setCursor(15, 0);
            lcd.write(AU); // Up arrow
            lcd.setCursor(15, 1);
            lcd.write(AD); // Down arrow
        }
        else if (menuLevel == 2) // Submenu
        {
            lcd.clear();
            if (current_menu_item == RealTime) // Idő beállítása
            {
                lcd.setCursor(1, 0);
                lcd.print("Id");
                lcd.write(odl);
                lcd.print(" be");
                lcd.write(al);
                lcd.print("ll");
                lcd.write(il);
                lcd.print("t");
                lcd.write(al);
                lcd.print("s");
                lcd.setCursor(0, 1);
                lcd.print(Current_Time.hour());
                lcd.print(':');
                lcd.print(Current_Time.minute());
                lcd.setCursor(13, 1);
                lcd.print("OK");
                lcd.setCursor(15, 0);
                lcd.write(AU); // Up arrow
                lcd.setCursor(15, 1);
                lcd.write(AD);     // Down arrow
                if (setclock == 0) // hour
                {
                    lcd.setCursor(0, 1);
                    lcd.cursor();
                }
                else if (setclock == 1) // minute
                {
                    if (Current_Time.hour() > 9)
                    {
                        lcd.setCursor(3, 1);
                    }
                    else
                    {
                        lcd.setCursor(2, 1);
                    }
                    lcd.cursor();
                }
            }
            else if (current_menu_item == Relek)
            {
                lcd.setCursor(10, 0);
                lcd.print("Rel");
                lcd.write(el);
                lcd.print("k");
                lcd.setCursor(0, 0);
                lcd.print("ID=");
                lcd.print(current_rel + 1);
                lcd.setCursor(6, 0);
                lcd.print("E=");
                lcd.print(relState[current_rel] ? "I" : "N");
                lcd.setCursor(0, 1);
                lcd.print("S=");
                lcd.print(StartRelTime[current_rel][0][0]);
                lcd.print(':');
                lcd.print(StartRelTime[current_rel][0][1]);
                lcd.setCursor(8, 1);
                lcd.print("T=");
                lcd.print(relTime[current_rel]);
                lcd.setCursor(15, 0);
                lcd.write(AU); // Up arrow
                // if (setrelay < numOfRelOptions-1) {lcd.setCursor(13,1); lcd.print("<>");}
                // else {lcd.setCursor(14,1); lcd.print("<");} lcd.write(AD); // Down arrow
                lcd.setCursor(13, 1);
                lcd.print("<>");
                lcd.write(AD);
                // 0 ID, 1 E=Állapot, 2 S/h=Kezdési idő óra, 3 S/m=Kezdési idő perc, 4 T=Időtartam(perc)
                if (setrelay == 0)
                { // ID
                    lcd.setCursor(3, 0);
                }
                else if (setrelay == 1)
                { // E - Állapot
                    lcd.setCursor(8, 0);
                }
                else if (setrelay == 2)
                { // S-h
                    lcd.setCursor(2, 1);
                }
                else if (setrelay == 3)
                { // s-m
                    if (StartRelTime[current_rel][0][0] > 9)
                    {
                        lcd.setCursor(5, 1);
                    }
                    else
                    {
                        lcd.setCursor(4, 1);
                    }
                }
                else if (setrelay == 4)
                { // T
                    lcd.setCursor(10, 1);
                }
                lcd.cursor();
            }
            else if (current_menu_item == Allapot)
            {

                lcd.setCursor(4, 0);
                lcd.print("Allapot");
                if (State)
                {
                    print_line(1, "Bekapcsolva");
                }
                else
                {
                    print_line(1, "Kikapcsolva");
                }
                lcd.setCursor(13, 1);
                lcd.print("OK");
                lcd.setCursor(15, 0);
                lcd.write(AU); // Up arrow
                lcd.setCursor(15, 1);
                lcd.write(AD); // Down arrow
            }
            else if (current_menu_item == Infok)
            {
                PrintInfos(0, current_info_item);
                PrintInfos(1, GetNext(current_info_item, infoSubMenuSize));
            }
        }
        delay(500);
    }
}