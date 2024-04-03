#include <Adafruit_GFX.h> // Core graphics library
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SPI.h>   // f.k. for Arduino-1.5.2
#include <SdFat.h> // Use the SdFat library
#include <RTClib.h>
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

// ----- Static variable declarations -----
SoftSpiDriver<12, 11, 13> softSpi; // Bit-Bang on the Shield pins SDFat.h v2
SdFat SD;
#define SD_CS SdSpiConfig(10, DEDICATED_SPI, SD_SCK_MHZ(0), &softSpi)

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Make TFT Display
MCUFRIEND_kbv tft;

// RTC module
RTC_DS3231 rtcDS;

// Create Menu
Menu menuSystem(tft, SD);

// Display sleeping mode
unsigned long lastTouched;
bool backlight = true;
#define BACKLIGHT_COOLDOWN 60000

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
  lastTouched = millis();
  debug("Size of Relay: ");
  debugvln(sizeof(Relay));
  debug("Size of Period: ");
  debugvln(sizeof(Period));
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
    // Scale from 0->1023 to tft.width
    int y = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
    int x = map(p.y, TS_MAXY, TS_MINY, tft.width(), 0);

    if (!backlight && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
    {
      menuSystem.setState(mainMenu);
      backlight = true;
      debug("Turn ON backlight");
      DrawMainScreen(tft, SD);
      // Call Menu Touch to evaluate touch
    }
    lastTouched = millis();
    menuSystem.Touched(x, y);
    delay(300);
  }
  if (backlight && (millis() - lastTouched) > BACKLIGHT_COOLDOWN)
  {
    backlight = false;
    tft.fillScreen(BLACK);
    debug("Turn OFF backlight");
  }
}
