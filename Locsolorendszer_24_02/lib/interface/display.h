// ---- display.h ----

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <SD.h>
#include <Adafruit_GFX.h> // Core graphics library
#include <TouchScreen.h>  // TouchScreen library
// #include <Adafruit_ILI9341.h>     // Hardware-specific library
// #include <SdFat.h>                // SD card & FAT filesystem library
// #include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
// #include <Adafruit_ImageReader.h> // Image-reading functions

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// ------- Touch Screen macros -------------
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

#define TS_MINX 920
#define TS_MINY 80
#define TS_MAXX 135
#define TS_MAXY 915
// ------- TFT Display macros ----------------

#define LCD_CS A3
#define LCD_CD A2 // LCD_RS
#define LCD_WR A1
#define LCD_RD A0
#define SD_CS 10
#define LCD_RESET A4 // optional

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// 16 bites szinek
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define DARKCYAN 0x032D // 0472

// Menü makrók
#define M_V 4         // Vertical margin
#define M_H 8         // Horizonatal margin
#define RADIUS 5      // Rounded rectangle corner radius
#define ICONSIZE 64   // Base Iconsize for buttons
#define OPTIONSIZE 61 // Timing long button height
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

// ----- Static variable declarations -----

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
static TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
static Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// static Adafruit_ILI9341 tft(LCD_CS, LCD_CD);

// Create SD
// SdFat SD;                        // SD card filesystem
// Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys

/* ----- Function Declarations ----- */

/* ---- Drawing fucntions ---- */

/**
 * @brief Draws the Main Screen to the tft display.
 */
void DrawMainScreen();
/**
 * @brief Draws
 */
void DrawSprinkleSubMenu();
/**
 * @brief
 */
void DrawChainSprinkleSubMenu();
/**
 * @brief Draws
 */
void DrawTestSubMenu();
/**
 * @brief Draws
 */
void DrawPeriodSubMenu();

/* ---- Common used drawing blocks ---- */

/**
 * Prints the current time to the main screen
 */
void PrintRTCToMainScreen();
void PrintSubMenuTitle(const char *title, int fontSize, uint16_t color = WHITE);
void PrintLabel(const char *label, int x, int y, int fontSize = 1, uint16_t color = WHITE);
int GetTextWidth(const char *text, int fontSize);

/* ---- Drawing helper function ---- */
/**
 * @brief Draws a bitmap from the SD card to the tft display at the given coordinates.
 * @param filename Bitmap's filename from SD card
 * @param x Top left corner's x coordinate
 * @param y Top left corner's y coordinate
 * @returns Success state of function
 */
bool bmpDraw(const char *filename, int x, int y);
/**
 * @brief Bitamap data reading funcion (16 bits)
 */
uint16_t read16(File f);
/**
 * @brief Bitamap data reading funcion (32 bits)
 */
uint32_t read32(File f);
#endif // DISPLAY_H