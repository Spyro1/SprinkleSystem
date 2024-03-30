

#include <Adafruit_GFX.h> // Core graphics library
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

#include <SPI.h> // f.k. for Arduino-1.5.2
// #define USE_SDFAT
#include <SdFat.h>                 // Use the SdFat library
SoftSpiDriver<12, 11, 13> softSpi; // Bit-Bang on the Shield pins SDFat.h v2
SdFat SD;
#define SD_CS SdSpiConfig(10, DEDICATED_SPI, SD_SCK_MHZ(0), &softSpi)
// ----- Static variable declarations -----

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
MCUFRIEND_kbv tft;

// Create Menu
Menu menuSystem = Menu(tft, SD);

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Paint!"));

  // -- Set tft panel --
  tft.reset();
  uint16_t identifier = tft.readID(); // Found ILI9341 LCD driver
  tft.begin(identifier);
  pinMode(13, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  // -- Setup SD card --
  pinMode(10, OUTPUT);    // change this to 53 on a mega  // don't follow this!!
  digitalWrite(10, HIGH); // Add this line
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS))
  {
    Serial.println(F("Failed!"));
    // return;
  }
  else
  {
    Serial.println(F("OK!"));
    // Print files
    File dir = SD.open("/");
    while (true)
    {
      File entry = dir.openNextFile();
      if (!entry)
      {
        dir.rewindDirectory();
        break;
      }
      // Serial.println((char *)entry.name());
      entry.close();
    }
    dir.rewindDirectory();
  }
  menuSystem.RunMenu();
}

void loop()
{
  // -- Check touch --s
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  // pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // pinMode(YM, OUTPUT);

  // -- Check pressed --
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    // Serial.print("X = "); Serial.print(p.x); Serial.print("\tY = "); Serial.print(p.y); // Print pushed coordinate
    //  Serial.print("\tPressure = "); Serial.println(p.z);

    // Scale from 0->1023 to tft.width
    int y = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
    int x = map(p.y, TS_MAXY, TS_MINY, tft.width(), 0);

    // Call Menu Touch to evaluate touch
    menuSystem.Touched(x, y);
    delay(300);
  }
}
