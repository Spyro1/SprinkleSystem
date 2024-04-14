// ---- display.h ----

#ifndef DISPLAY_H
#define DISPLAY_H

#include <MCUFRIEND_kbv.h> // Hardware-specific library
#include <Adafruit_GFX.h>  // Core graphics library
#include <TouchScreen.h>   // TouchScreen library
#include <RTClib.h>
#include <SdFat.h>
#include "types.h"

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// 16 bit Colors fot TFT display
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
// #define PINK 0xFC9F
#define PURPLE 0x780F
#define RED 0xF800
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define BGDARKCYAN 0x032D // 0472

// Menu spacing macros
#define M_V 4    // Vertical margin
#define M_H 8    // Horizonatal margin
#define RADIUS 5 // Rounded rectangle corner radius
#define x64 64   // Base Iconsize for buttons
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
// Small icon corners
#define SUBMENUICON_POS 4, 0
#define SUBMENUHOME_POS 284, 0
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
#define COL_1_2_SEPERATOR 80, 120
#define COL_2_3_SEPERATOR 160, 120
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

/* ---- Drawing fucntions ---- */
/**
 * Draws the Main Screen to the tft display.
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawMainScreen(MCUFRIEND_kbv &tft, SdFat &SD);
/**
 * Draws the settings for real time
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawRTCSettingsSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
/**
 *  Draws period chooser submenu
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawPeriodSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
/**
 * Draws 1-8, 9-16 relay to the screen to chose time setting submenu
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawRelayChooserSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, int periodNumber);
/**
 * Draws the relay's time and duration setting submenu
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawRelayTimingSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
/**
 * Draws chain sprinkle setting submenu
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawChainSprinkleSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
/**
 * Draws 1-8, 9-16 Switches to test the sprinkler system
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawTestSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
/**
 * Draws the settings menu for the system
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawSettingsSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
/**
 * Draws the humidity sensitivity settings for the system
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 */
void DrawHumiditySubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
/**
 *  Draws the automatic timing setting submenu
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 * @param periodNumber Which period to set the timing to, and display the title
 */
void DrawAutomaticTimingSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
/* ---- Common used drawing blocks ---- */

/**
 * Prints the current time to the main screen
 * @param tft Reference to tft display
 * @param realTime Reference to real time
 */
void PrintRTCToMainScreen(MCUFRIEND_kbv &tft, const TimeSpan &realTime);
/**
 * Prints the title to a submenu
 * @param tft Reference to tft display
 * @param title Name of the submenu to display
 * @param fontSize Title font size
 * @param color Color of the text
 */
void PrintSubMenuTitle(MCUFRIEND_kbv &tft, const char *title, int fontSize, const uint16_t color = WHITE);
/**
 * Prints the given text to the display at the given coordinates
 * @param tft Reference to tft display
 * @param label Text to display
 * @param x x coordinate - center of the text
 * @param y y coordinate - top of the text
 * @param fontSize Text font size
 * @param color Color of the text
 */
void PrintLabel(MCUFRIEND_kbv &tft, const char *label, int x, int y, int fontSize = 1, const uint16_t color = WHITE);
void PrintLabel(MCUFRIEND_kbv &tft, int labelValue, int x, int y, int fontSize = 1, const uint16_t color = WHITE);
/**
 * Prints the Line below the submenu title
 * @param tft Reference to tft display
 * @param y y coordinate of the line from the top
 * @param width Width of the line, default is screen width
 * @param color Color of the line, default is WHITE
 */
void PrintDoubleLine(MCUFRIEND_kbv &tft, const int y, const int width = 320, const uint16_t color = WHITE);
void PrintRelayChoserNumbering(MCUFRIEND_kbv &tft, SdFat &SD, int pageNumber, const uint16_t color = WHITE);
void PrintNumberField(MCUFRIEND_kbv &tft, const int column, int value = 0);
/**
 * Calculates the text width in pixels of the given string
 * @param text Text calculate the width
 * @param fontSize Text font size
 * @return Width of string in pixels
 */
int GetTextWidth(const char *text, const int fontSize);
int GetNumWidth(const int number, const int fontSize);
/**
 * Prints the desired bitmap to the display at coordinates or a rounded square if not found on SD card
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 * @param text
 * @param x
 * @param y
 * @param size
 * @param color
 */
void PrintBmpOrRect(MCUFRIEND_kbv &tft, SdFat &SD, const char *text, const int x, const int y, const int size = x64, const uint16_t color = CYAN);

/* ---- Drawing helper function ---- */
/**
 * @brief Draws a bitmap from the SD card to the tft display at the given coordinates.
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 * @param filename Bitmap's filename from SD card
 * @param x Top left corner's x coordinate
 * @param y Top left corner's y coordinate
 * @returns Success state of function
 */
bool bmpDraw(MCUFRIEND_kbv &tft, SdFat &SD, const char *filename, int x, int y);
/**
 * @brief Draws a bitmap from the SD card to the tft display at the given coordinates.
 * @param tft Reference to tft display
 * @param SD Reference to SD card
 * @param nm Bitmap's filename from SD card
 * @param x Top left corner's x coordinate
 * @param y Top left corner's y coordinate
 * @return Success state of function encoded. 0 is success
 */
uint8_t showBMP(MCUFRIEND_kbv &tft, SdFat &SD, const char *nm, int x, int y);
/**
 * @brief Bitmap data reading funcion (16 bits)
 * Read 16- and 32-bit types from the SD card file. BMP data is stored little-endian, Arduino is little-endian too.
 */
uint16_t read16(File &f);
/**
 * @brief Bitamap data reading funcion (32 bits)
 * Read 16- and 32-bit types from the SD card file. BMP data is stored little-endian, Arduino is little-endian too.
 */
uint32_t read32(File &f);
// };

/* ---- Icon Drawing Functions ---- */
/**
 * @param tft Reference to tft display
 * @param p Top left corner of the icon
 */
void DrawIconRelay(MCUFRIEND_kbv &tft, const int x, const int y);
#endif // DISPLAY_H