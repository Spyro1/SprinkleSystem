// ---- main.h ----

#ifndef MAIN_H
#define MAIN_H

/* #include <Adafruit_GFX.h> // Core graphics library
// #include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "menu.h"
#include "display.h"

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
// #define SD_CS 10     // 10
#define LCD_RESET A4 // optional

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#include <SPI.h>   // f.k. for Arduino-1.5.2
#include <SdFat.h> // Use the SdFat library

SoftSpiDriver<12, 11, 13> softSpi; // Bit-Bang on the Shield pins SDFat.h v2
SdFat SD;
#define SD_CS SdSpiConfig(10, DEDICATED_SPI, SD_SCK_MHZ(0), &softSpi)
// ----- Static variable declarations -----

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
MCUFRIEND_kbv tft; */

#endif