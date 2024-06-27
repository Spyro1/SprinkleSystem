// ******** setup_loop.ino ********

// ---- Display sleeping mode ----
#define BACKLIGHT_COOLDOWN 60000
unsigned long lastTouched;
bool backlight = true;
bool refreshed = false;

// ======================== SETUP AND LOOP FUNCTIONS ========================

void setup() {
  // -- Start Serial Monitor --
  Serial.begin(9600);
  Serial.println(F("Paint!"));
  // -- Setup tft panel --
  tft.reset();
  debugln("Eljut1");
  uint16_t identifier = tft.readID(); // Found ILI9341 LCD driver
  tft.begin(identifier);
  pinMode(13, OUTPUT);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  debugln("Eljut2");
  // -- Setup RTC module --
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
  }
  else if (!rtc.lostPower()) {
    debugln("Eljut3");
    Serial.println(F("RTC is NOT running, let's set the time!"));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // -- Setup Controller --
  Controller.now = rtc.now();
  debugln("Eljut4");
  Controller.StartMenu();
  lastTouched = millis();
}

void loop() {
  // -- Update Real Time -- 
  Controller.now = rtc.now();
  // -- Check touch --
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  // pinMode(XP, OUTPUT);
  // pinMode(YM, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  // -- Check pressed --
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Scale from 0->1023 to tft.width
    int y = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);
    int x = map(p.y, TS_MAXY, TS_MINY, tft.width(), 0);

    if (!backlight && x > 0 && x < WIDTH && y > 0 && y < HEIGHT) {
      Controller.state = mainMenu;
      backlight = true;
      debugln("Backlight ON");
      DrawMainMenu();
      // Call Menu Touch to evaluate touch
    } 
    else {
      Controller.Touched(x, y); // Call touch evaluating fucntion
    }
    lastTouched = millis();
    delay(300); // Delay for touching
  }
  if (backlight) {
    // --- Update clock on main screen if backlight is on ---
    if (Controller.state == mainMenu && millis() % 1000 == 0) PrintRTCToMainScreen();
    // -- Check to turn off backlight --
    if ((millis() - lastTouched) > BACKLIGHT_COOLDOWN) {
      backlight = false;
      tft.fillScreen(BLACK);
      debugln("Backlight OFF");
    }
  }
  // --- Update relays every minute ---
  if (!refreshed && Controller.now.second() == 0) {
    Controller.UpdateRelays();
    refreshed = true; // Set refreshed to true, to only run this code once every minute
    debugln("Relays refreshed = true");
  }
  // -- Set refreshed back to flase --
  if (refreshed && Controller.now.second() == 59){
    refreshed = false;
    debugln("Refreshed set back to false");
  }
}
