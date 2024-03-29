// ---- display.h ----

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <SD.h>
#include <Adafruit_GFX.h> // Core graphics library
#include <TouchScreen.h>  // TouchScreen library
#include <RTClib.h>
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
#define BLACK       0x0000
#define BLUE        0x001F
#define CYAN        0x07FF
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define DARKGREY    0x7BEF
#define GREEN       0x07E0
#define GREENYELLOW 0xB7E0
#define LIGHTGREY   0xC618
#define MAGENTA     0xF81F
#define MAROON      0x7800
#define NAVY        0x000F
#define OLIVE       0x7BE0
#define ORANGE      0xFDA0
#define PINK        0xFC9F
#define PURPLE      0x780F
#define RED         0xF800
#define WHITE       0xFFFF
#define YELLOW      0xFFE0

#define BGDARKCYAN    0x032D // 0472

// Menü makrók
#define M_V 4         // Vertical margin
#define M_H 8         // Horizonatal margin
#define RADIUS 5      // Rounded rectangle corner radius
#define ICONSIZE 64   // Base Iconsize for buttons
#define OPTIONSIZE 61 // Timing long button height
#define SUBTITLE_H 38
#define x32 ICONSIZE/2
#define x16 ICONSIZE/4
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

#define strRealTimeSettings "Ido beallitas"        // Idő beállítás almenő cím
#define strHour "Ora"
#define strMinute "Perx"

// ----- Static variable declarations -----

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
//static TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
//static Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
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
    void DrawMainScreen(Adafruit_TFTLCD& tft);
    void DrawRTCSettingsSubMenu(Adafruit_TFTLCD& tft);
    void DrawPeriodSubMenu(Adafruit_TFTLCD& tft);
    void DrawTimingSubMenu(Adafruit_TFTLCD& tft);
    void DrawChainSprinkleSubMenu(Adafruit_TFTLCD& tft);
    void DrawTestSubMenu(Adafruit_TFTLCD& tft);
    void DrawSettingsSubMenu(Adafruit_TFTLCD& tft);
    void DrawHumiditySubMenu(Adafruit_TFTLCD& tft);
   

    /* ---- Common used drawing blocks ---- */


// private:
    /**
     * Prints the current time to the main screen
     */
    void PrintRTCToMainScreen(Adafruit_TFTLCD& tft, TimeSpan realTime);
    void PrintSubMenuTitle(Adafruit_TFTLCD& tft, const char *title, int fontSize, uint16_t color = WHITE);
    void PrintLabel(Adafruit_TFTLCD& tft, const char *label, int x, int y, int fontSize = 1, uint16_t color = WHITE);
    void PrintDoubleLine(Adafruit_TFTLCD& tft, int y, int width = 300);
    int GetTextWidth(const char *text, int fontSize);

    /* ---- Drawing helper function ---- */
    /**
     * @brief Draws a bitmap from the SD card to the tft display at the given coordinates.
     * @param filename Bitmap's filename from SD card
     * @param x Top left corner's x coordinate
     * @param y Top left corner's y coordinate
     * @returns Success state of function
     */
    bool bmpDraw(Adafruit_TFTLCD& tft, const char *filename, int x, int y);
    /**
     * @brief Bitmap data reading funcion (16 bits)
     * Read 16- and 32-bit types from the SD card file. BMP data is stored little-endian, Arduino is little-endian too.
     */
    uint16_t read16(File f);
    /**
     * @brief Bitamap data reading funcion (32 bits)
     * Read 16- and 32-bit types from the SD card file. BMP data is stored little-endian, Arduino is little-endian too.
     */
    uint32_t read32(File f);
// };
#endif // DISPLAY_H