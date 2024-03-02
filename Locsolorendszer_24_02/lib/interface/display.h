#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

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
#define MARGIN_V 4    // Vertical margin
#define MARGIN_H 8    // Horizonatal margin
#define ICONSIZE 64   // Base Iconsize for buttons
#define OPTIONSIZE 61 // Timing long button height
#define FONT_1_H 7
#define FONT_2_H FONT_1_H * 2
#define FONT_3_H FONT_1_H * 3
#define FONT_1_V 5
#define FONT_2_V FONT_1_V * 2
#define FONT_3_V FONT_1_V * 3

// String konstansok
const char *strMainTitle = "Locsolorendszer";
const char *strBtnLeftTop = "Locsolas";       // Locsolás
const char *strBtnLeftCenter = "Sorban";      // Sorban locsoolás
const char *strBtnRightCenter = "Teszteles";  // Tesztelés
const char *strBtnRightTop = "Nedvesseg";     // Nedvesség
const char *strBtnLeftBottom = "Beallitasok"; // Beállítások
const char *strBtnCenterBottom1 = "Be";       // Kikapcsolt állapot
const char *strBtnCenterBottom2 = "Ki";       // Bekapcsolt állapot
const char *strBtnRightBottom = "Ido";        // Idő beállítás

// ----- Static variable declarations -----

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// ----- Function Declarations -----

void bmpDraw(const char *filename, int x, int y);
uint16_t read16(File f);
uint32_t read32(File f);

void DrawMainScreen(); // Főképernyő
void DrawPeriodsMenu();
void DrawTestMenu();

#endif // DISPLAY_H
