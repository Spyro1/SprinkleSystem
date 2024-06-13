// ******** setup_loop.ino ********

// ---- Display sleeping mode ----
#define BACKLIGHT_COOLDOWN 60000
unsigned long lastTouched;
bool backlight = true;

// ======================== SETUP AND LOOP FUNCTIONS ========================

void setup()
{
  // -- Start Serial Monitor --
  Serial.begin(9600);
  Serial.println(F("Paint!"));

  // -- Setup tft panel --
  tft.reset();
  uint16_t identifier = tft.readID(); // Found ILI9341 LCD driver
  tft.begin(identifier);
  pinMode(13, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  // -- Setup SD card --
  /*pinMode(10, OUTPUT);    // change this to 53 on a mega  // don't follow this!!
  digitalWrite(10, HIGH); // Add this line
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS))  {
    Serial.println(F("Failed!"));
  }
  else  {
    Serial.println(F("OK!"));
    // Print files
    #if DEBUG == 1
      File dir = SD.open("/");
      while (true)
      {
        File entry = dir.openNextFile();
        if (!entry)
        {
          dir.rewindDirectory();
          break;
        }
        entry.close();
      }
      dir.rewindDirectory();
    #endif
  }*/

  // -- Setup RTC module --
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  else if (!rtc.lostPower()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // -- Setup Controller --
  Controller.now = rtc.now();
  Controller.StartMenu();
  lastTouched = millis();
}

void loop()
{

  // -- Check touch --s
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  // pinMode(XP, OUTPUT);
  // pinMode(YM, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  // -- Check pressed --
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    // Scale from 0->1023 to tft.width
    int y = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
    int x = map(p.y, TS_MAXY, TS_MINY, tft.width(), 0);

    if (!backlight && x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
    {
      Controller.state = mainMenu;
      backlight = true;
      debugln("Backlight ON");
      Controller.DrawStateScreen();
      // Call Menu Touch to evaluate touch
    }
    lastTouched = millis();
    Controller.Touched(x, y); // Call touch evaluating fucntion
    delay(300);               // Delay for touching
  }
  if (backlight && (millis() - lastTouched) > BACKLIGHT_COOLDOWN)
  {
    backlight = false;
    tft.fillScreen(BLACK);
    debugln("Backlight OFF");
  }
  if (backlight)
  {
    // menuSystem.UpdateClock();
  }
  if (millis() % 1000){
    Controller.now = rtc.now();
  }
}