#include "display.h"
#include "menu.h"
// == Functions ==

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Start program!"));

  tft.reset();
  uint16_t identifier = tft.readID(); // Found ILI9341 LCD driver
  tft.begin(identifier);

  // Set tft panel
  pinMode(13, OUTPUT);
  tft.setRotation(3);
  tft.fillScreen(BLACK);

  // Setup SD card
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS))
  {
    Serial.println(F("Failed!"));
    // return;
  }
  else
    Serial.println(F("OK!"));

  // listSD();

  DrawMainScreen();
  // DrawPeriodsMenu();
  delay(2000);
  digitalWrite(5, LOW);
  delay(2000);
  digitalWrite(5, HIGH);
}

void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  // pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    /*
    Serial.print("\tPressure = "); Serial.println(p.z);
    */

    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    Serial.print(" (");
    Serial.print(p.x);
    Serial.print(", ");
    Serial.print(p.y);
    Serial.println(")");
  }
}
