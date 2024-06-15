#include <Adafruit_GFX.h> // Core graphics library
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SPI.h>   // f.k. for Arduino-1.5.2
#include <SdFat.h> // Use the SdFat library
#include <RTClib.h>

// ======================== M A C R O S ========================

// ---- Debugger ---
#define DEBUG 1 // Set this to 1 to enable debug printers, 0 to disable
#if DEBUG == 1
  #define debug(str) Serial.print(F(str))
  #define debugv(V) Serial.print(V)
  #define debugln(str) Serial.println(F(str))
  #define debugvln(V) Serial.println(V)
#else
  #define debug(str)
  #define debugv(V)
  #define debugln(str)
  #define debugvln(V)
#endif

// ---- Touch Screen macros ----
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin
#define TS_MINX 920
#define TS_MINY 80
#define TS_MAXX 135
#define TS_MAXY 915
// ---- Touch Screen Pressure macros ----
#define MINPRESSURE 10
#define MAXPRESSURE 1000
// ---- TFT Display macros ----
#define LCD_CS A3
#define LCD_CD A2 // LCD_RS
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // optional
#define SD_CS 10     // SD card pin
// ---- 16 bit colors for TFT display ----
#define BLACK 0x0000
#define BLUE 0x001F
#define CYAN 0x07FF
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define DARKGREY 0x7BEF
#define GREEN 0x07E0
#define GREENYELLOW 0xB7E0
#define LIGHTGREY 0xC618
#define MAGENTA 0xF81F
#define MAROON 0x7800
#define NAVY 0x000F
#define OLIVE 0x7BE0
#define ORANGE 0xFDA0
#undef PINK
#define PINK 0xFC9F
#define PURPLE 0x780F
#define RED 0xF800
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define BGDARKCYAN 0x032D // 0472
// Menu spacing macros
#define MARGIN 8    // Margin
#define RADIUS 8 // Rounded rectangle corner radius
#define x64 64   // Base Icon size for buttons
#define x32 x64 / 2
#define x16 x64 / 4
#define OPTIONSIZE 62 // Timing long button height
#define SUBTITLE_H 38
#define CENTER_H tft.width() / 2
#define CENTER_V tft.height() / 2
#define HEIGHT tft.height()
#define WIDTH tft.width()
#define FONT_1_H 5
#define FONT_2_H FONT_1_H * 2
#define FONT_3_H FONT_1_H * 3
#define FONT_1_V 7
#define FONT_2_V FONT_1_V * 2
#define FONT_3_V FONT_1_V * 3
// Menu button counts
#define subMenuButtonCount 13
#define mainScreenButtonCount 7
// Small icon corners

// SUBMENU NUM FILD POSITIONS
// #define COL_1_CENTER 40, 120
// #define COL_1_LABEL 40, 154
// #define COL_2_CENTER 120, 120
// #define COL_2_LABEL 120, 154
// #define COL_3_CENTER 200, 120
// #define COL_3_LABEL 200, 154
// #define COL_1_2_SEPARATOR 80, 120
// #define COL_2_3_SEPARATOR 160, 120
// #define COL_4_LABEL_T 280, 104
// #define COL_4_LABEL_B 280, 154
// BITMAPS x64
// #define UP_ARROW "arw-up.bmp"
// #define DOWN_ARROW "arw-dw.bmp"
// #define LEFT_ARROW "arw-l.bmp"
// #define RIGHT_ARROW "arw-r.bmp"
// #define AUTOMATIC_ICON "automatic.bmp"
// #define BTN_INACTIVE "btn-no.bmp"
// #define BTN_ON "btn-on.bmp"
// #define BTN_OFF "btn-off.bmp"
// #define CHAIN_ICON "chain.bmp"
// #define CLOCK_ICON "clock.bmp"
// #define EXIT_ICON "exit.bmp"
// #define HUMIDITY_ICON "humidity.bmp"
// #define SETTINGS_ICON "settings.bmp"
// #define SPRINKLER_ICON_ON "sprk-on.bmp"
// #define SPRINKLER_ICON_OFF "sprk-off.bmp"
// #define START_ICON "start.bmp"
// #define OFF_SWITCH "sw-off.bmp"
// #define OFF_SWITCH_LABEL "sw-off-l.bmp"
// #define ON_SWITCH "sw-on.bmp"
// #define ON_SWITCH_LABEL "sw-on-l.bmp"
// #define TEST_ICON "test.bmp"
// #define RELAY_ICON "valve.bmp"
// #define OK_ICON "save.bmp"
// BITMAPS x32
// #define AUTOMATIC_ICONx32 "automatic-32.bmp"
// #define CHAIN_ICONx32 "chain-32.bmp"
// #define CLOCK_ICONx32 "clock-32.bmp"
// #define HOME_ICONx32 "home-32.bmp"
// #define HUMIDITY_ICONx32 "humidity-32.bmp"
// #define SETTINGS_ICONx32 "settings-32.bmp"
// #define SPRINKLER_ICONx32 "sprk-32.bmp"
// #define TEST_ICONx32 "test-32.bmp"
// #define RELAY_ICONx32 "valve-32.bmp"
// MainScreen string macros
#define strMainTitle "Locsolorendszer" // Locsolórendszer
#define strSprinkle "Locsolas"       // Locsolás
#define strChain "Sorban"      // Sorban locsoolás
#define strTest "Teszteles"  // Tesztelés
#define strHumidity "Nedvesseg"     // Nedvesség
#define strSettings "Beallitasok" // Beállítások
#define strON "Be"       // Kikapcsolt állapot
#define strOFF "Ki"       // Bekapcsolt állapot
#define strClock "Ido"        // Idő beállítás
// Submenu string macros
#define strRealTimeSettings "Ido beallitas" // Idő beállítás almenő cím
#define strHour "Ora"
#define strMinute "Perc"
#define strRelaynum "Releszam"
#define strRelay "Rele"
#define strAuto "Auto"
#define strDurationShort "Idot."
#define strProfileSettings "Profilok" // Időzítések be-ki kapcsolási menüje
#define strFirstProfile "1. Profil"
#define strSecondProfile "2. Profil"
#define strThirdProfile "3. Profil"
#define strFromRelay "Reletol"
#define strToRelay "Releig"
#define strDuration "Idotartam"
#define strSenitivity "Erzekenyseg"
#define strReset "Visszaallitas"
#define strSave "Mentes"
#define strBack "Vissza"
#define strStart "Start"

// ======================== TYPE DEFINICIONS ========================
typedef unsigned char uint;
typedef uint16_t ulong;

// ---- Macros for functionality ----
#define PROFILE_COUNT 3
#define RELAY_COUNT 16 // Relay Pins: 22,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51
uint RELAY_PINS[] = {22,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51};

// ======================== DECLARATIONS ========================

// struct Point;
// struct Relay;
// struct Profile;
// struct SystemController;

// ======================== STATIC VARIABLE DECLARATIONS ========================

// Make a Touch Screen object which senses inputted preassure
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
MCUFRIEND_kbv tft;

// RTC module
RTC_DS3231 rtc;

// SD Card 
//SoftSpiDriver<12, 11, 13> softSpi; // Bit-Bang on the Shield pins SDFat.h v2
// SdFat SD;
//#define SD_CS SdSpiConfig(10, DEDICATED_SPI, SD_SCK_MHZ(0), &softSpi)
