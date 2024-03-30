// ---- display.h ----

#ifndef DISPLAY_H
#define DISPLAY_H

#include <MCUFRIEND_kbv.h> // Hardware-specific library
#include <Adafruit_GFX.h>  // Core graphics library
#include <TouchScreen.h>   // TouchScreen library
#include <RTClib.h>
#include <SdFat.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// 16 bites szinek
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

// Menü makrók
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
#define SLOT_1_1 8, 36, x64
#define SLOT_1_2 88, 36, x64
#define SLOT_1_3 168, 36, x64
#define SLOT_1_4 248, 36, x64
#define SLOT_2_1 8, 104, x64
#define SLOT_2_2 88, 104, x64
#define SLOT_2_3 168, 104, x64
#define SLOT_2_4 248, 104, x64
#define SLOT_3_1 8, 172, x64
#define SLOT_3_2 88, 172, x64
#define SLOT_3_3 168, 172, x64
#define SLOT_3_4 248, 172, x64
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
#define COL_4_LABEL_B 280, 150
// BITMAPS
#define UP_ARROW "arw-up.bmp"
#define DOWN_ARROW "arw-dw.bmp"
#define LEFT_ARROW "arw-l.bmp"
#define RIGHT_ARROW "arw-r.bmp"
#define OK_ICON "ok.bmp"
#define EXIT_ICON "exit.bmp"
#define RUN_ICON "run.bmp"
#define TEST_ICON "test.bmp"
#define CLOCK_ICON "clock.bmp"
#define ON_SWITCH "sw-on.bmp"
#define OFF_SWITCH "sw-on.bmp"
#define ON_SWITCH_LABEL "sw-on-l.bmp"
#define OFF_SWITCH_LABEL "sw-on-l.bmp"
#define BTN_ON "btn-on.bmp"
#define BTN_OFF "btn-off.bmp"
#define SPRINKLER_ICON_ON "sprk-on.bmp"
#define SPRINKLER_ICON_OFF "sprk-off.bmp"
#define CHAIN_ICON "chain.bmp"
#define SETTINGS_ICON "settings.bmp"
#define HUMIDITY_ICON "humidity.bmp"

// String makrók
#define strMainTitle "Locsolorendszer" // Locsolórendszer
#define strBtnLeftTop "Locsolas"       // Locsolás
#define strBtnLeftCenter "Sorban"      // Sorban locsoolás
#define strBtnRightCenter "Teszteles"  // Tesztelés
#define strBtnRightTop "Nedvesseg"     // Nedvesség
#define strBtnLeftBottom "Beallitasok" // Beállítások
#define strBtnCenterBottom1 "Be"       // Kikapcsolt állapot
#define strBtnCenterBottom2 "Ki"       // Bekapcsolt állapot
#define strBtnRightBottom "Ido"        // Idő beállítás

#define strRealTimeSettings "Ido beallitas" // Idő beállítás almenő cím
#define strHour "Ora"
#define strMinute "Perc"
#define strRelay "Releszam"
#define strDurationShort "Idot."
#define strPreiodSettings "Idozitesek" // Időzítések be-ki kapcsolási menüje
#define strFirstPeriod "1. Idoszak"
#define strSecondPeriod "2. Idoszak"
#define strThirdPeriod "3. Idoszak"
#define strFromRelay "Reletol"
#define strToRelay "Releig"
#define strDuration "Idotartam"

// ----- Static variable declarations -----
// ----- SD Card init -----
#if SPI_DRIVER_SELECT != 2
#error edit SdFatConfig.h .  READ THE SKETCH INSTRUCTIONS
#endif

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
// static TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
// static MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// static Adafruit_ILI9341 tft(LCD_CS, LCD_CD);

// Create SD
// SdFat SD;                        // SD card filesystem
// Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys

// class Display{

/* ----- Function Declarations ----- */

// public:
/* ---- Drawing fucntions ---- */

/**
 * Draws the Main Screen to the tft display.
 */
void DrawMainScreen(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawRTCSettingsSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawPeriodSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawTimingSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawChainSprinkleSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawTestSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawSettingsSubMenu(MCUFRIEND_kbv &tft, SdFat &SD);
void DrawHumiditySubMenu(MCUFRIEND_kbv &tft, SdFat &SD);

/* ---- Common used drawing blocks ---- */

// private:
/**
 * Prints the current time to the main screen
 */
void PrintRTCToMainScreen(MCUFRIEND_kbv &tft, TimeSpan realTime);
void PrintSubMenuTitle(MCUFRIEND_kbv &tft, const char *title, int fontSize, uint16_t color = WHITE);
void PrintLabel(MCUFRIEND_kbv &tft, const char *label, int x, int y, int fontSize = 1, uint16_t color = WHITE);
void PrintDoubleLine(MCUFRIEND_kbv &tft, int y, int width = 320, uint16_t color = WHITE);
int GetTextWidth(const char *text, int fontSize);
void PrintBmpOrRect(MCUFRIEND_kbv &tft, SdFat &SD, const char *text, int x, int y, int size, uint16_t color = CYAN);

/* ---- Drawing helper function ---- */
/**
 * @brief Draws a bitmap from the SD card to the tft display at the given coordinates.
 * @param filename Bitmap's filename from SD card
 * @param x Top left corner's x coordinate
 * @param y Top left corner's y coordinate
 * @returns Success state of function
 */
bool bmpDraw(MCUFRIEND_kbv &tft, SdFat &SD, const char *filename, int x, int y);
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
#endif // DISPLAY_H