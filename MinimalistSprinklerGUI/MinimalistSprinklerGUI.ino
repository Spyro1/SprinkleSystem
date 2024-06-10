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
#define PINK 0xFC9F
#define PURPLE 0x780F
#define RED 0xF800
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define BGDARKCYAN 0x032D // 0472
// Menu spacing macros
#define M_V 4    // Vertical margin
#define M_H 8    // Horizontal margin
#define RADIUS 5 // Rounded rectangle corner radius
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
// Menu button locations
#define BTN_1_1 Point(1, 1)
#define BTN_1_2 Point(2, 1)
#define BTN_1_3 Point(3, 1)
#define BTN_1_4 Point(4, 1)
#define BTN_2_1 Point(1, 2)
#define BTN_2_2 Point(2, 2)
#define BTN_2_3 Point(3, 2)
#define BTN_2_4 Point(4, 2)
#define BTN_3_1 Point(1, 3)
#define BTN_3_2 Point(2, 3)
#define BTN_3_3 Point(3, 3)
#define BTN_3_4 Point(4, 3)
// Small icon corners
#define SUBMENU_ICON_POS 4, 0
#define SUBMENU_HOME_POS 284, 0
// Submenu table corners
#define SLOT_1_1 8, 36
#define SLOT_1_2 88, 36
#define SLOT_1_3 168, 36
#define SLOT_1_4 248, 36
#define SLOT_2_1 8, 104
#define SLOT_2_2 88, 104
#define SLOT_2_3 168, 104
#define SLOT_2_4 248, 104
#define SLOT_3_1 8, 172
#define SLOT_3_2 88, 172
#define SLOT_3_3 168, 172
#define SLOT_3_4 248, 172
// SUBMENU NUM FILD POSITIONS
#define COL_1_CENTER 40, 120
#define COL_1_LABEL 40, 154
#define COL_2_CENTER 120, 120
#define COL_2_LABEL 120, 154
#define COL_3_CENTER 200, 120
#define COL_3_LABEL 200, 154
#define COL_1_2_SEPARATOR 80, 120
#define COL_2_3_SEPARATOR 160, 120
#define COL_4_LABEL_T 280, 104
#define COL_4_LABEL_B 280, 154
// BITMAPS x64
#define UP_ARROW "arw-up.bmp"
#define DOWN_ARROW "arw-dw.bmp"
#define LEFT_ARROW "arw-l.bmp"
#define RIGHT_ARROW "arw-r.bmp"
#define AUTOMATIC_ICON "automatic.bmp"
#define BTN_INACTIVE "btn-no.bmp"
#define BTN_ON "btn-on.bmp"
#define BTN_OFF "btn-off.bmp"
#define CHAIN_ICON "chain.bmp"
#define CLOCK_ICON "clock.bmp"
#define EXIT_ICON "exit.bmp"
#define HUMIDITY_ICON "humidity.bmp"
#define SETTINGS_ICON "settings.bmp"
#define SPRINKLER_ICON_ON "sprk-on.bmp"
#define SPRINKLER_ICON_OFF "sprk-off.bmp"
#define START_ICON "start.bmp"
#define OFF_SWITCH "sw-off.bmp"
#define OFF_SWITCH_LABEL "sw-off-l.bmp"
#define ON_SWITCH "sw-on.bmp"
#define ON_SWITCH_LABEL "sw-on-l.bmp"
#define TEST_ICON "test.bmp"
#define RELAY_ICON "valve.bmp"
#define OK_ICON "save.bmp"
// BITMAPS x32
#define AUTOMATIC_ICONx32 "automatic-32.bmp"
#define CHAIN_ICONx32 "chain-32.bmp"
#define CLOCK_ICONx32 "clock-32.bmp"
#define HOME_ICONx32 "home-32.bmp"
#define HUMIDITY_ICONx32 "humidity-32.bmp"
#define SETTINGS_ICONx32 "settings-32.bmp"
#define SPRINKLER_ICONx32 "sprk-32.bmp"
#define TEST_ICONx32 "test-32.bmp"
#define RELAY_ICONx32 "valve-32.bmp"
// MainScreen string macros
#define strMainTitle "Locsolorendszer" // Locsolórendszer
#define strBtnLeftTop "Locsolas"       // Locsolás
#define strBtnLeftCenter "Sorban"      // Sorban locsoolás
#define strBtnRightCenter "Teszteles"  // Tesztelés
#define strBtnRightTop "Nedvesseg"     // Nedvesség
#define strBtnLeftBottom "Beallitasok" // Beállítások
#define strBtnCenterBottom1 "Be"       // Kikapcsolt állapot
#define strBtnCenterBottom2 "Ki"       // Bekapcsolt állapot
#define strBtnRightBottom "Ido"        // Idő beállítás
// Submenu string macros
#define strRealTimeSettings "Ido beallitas" // Idő beállítás almenő cím
#define strHour "Ora"
#define strMinute "Perc"
#define strRelaynum "Releszam"
#define strRelay "Rele"
#define strDurationShort "Idot."
#define strPreiodSettings "Idozitesek" // Időzítések be-ki kapcsolási menüje
#define strFirstPeriod "1. Idoszak"
#define strSecondPeriod "2. Idoszak"
#define strThirdPeriod "3. Idoszak"
#define strFromRelay "Reletol"
#define strToRelay "Releig"
#define strDuration "Idotartam"
#define strSenitivity "Erzekenyseg"
#define strReset "Visszaallitas"
#define strSave "Mentes"
#define strBack "Vissza"
#define strStart "Start"

// ---- Macros for functionality ----
#define PROFILE_COUNT 3
#define RELAY_COUNT 16 // Relay Pins: 22,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51

// ======================== TYPE DEFINICIONS ========================
typedef unsigned char uint;
typedef uint16_t ulong;
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
RTC_DS3231 rtcDS;

// SD Card 
//SoftSpiDriver<12, 11, 13> softSpi; // Bit-Bang on the Shield pins SDFat.h v2
// SdFat SD;
//#define SD_CS SdSpiConfig(10, DEDICATED_SPI, SD_SCK_MHZ(0), &softSpi)
