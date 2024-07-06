// ******** setup_loop.ino ********

// ---- Display sleeping mode ----
#define BACKLIGHT_COOLDOWN 60000
unsigned long lastTouched;
bool backlight = true;
bool refreshed = false;

// ======================== SETUP AND LOOP FUNCTIONS ========================

/**
 * @brief Setup function for initializing the system.
 */
void setup() {
  // -- Start Serial Monitor --
  Serial.begin(9600);
  Serial.println(F("Paint!"));
  
// -- Setup TFT panel --
  // tft.reset();                          // Reset the TFT panel
  debugvln(1);
  uint16_t identifier = tft.readID();   // Read the TFT panel identifier (ILI9341 LCD driver)
  debugvln(2);
  tft.begin(identifier);                // Initialize the TFT panel
  debugvln(3);
  // pinMode(13, OUTPUT);                  // Set pin 13 as an output pin
  tft.setRotation(1);                   // Set TFT panel rotation
  debugvln(4);
  // tft.fillScreen(BLACK);                // Fill the screen with black color
  debugvln(5);
  // -- Setup RTC module --
  if (!rtc.begin()) {                   // Initialize the RTC module
    Serial.println(F("Couldn't find RTC"));
  } else if (rtc.lostPower()) {         // Check if RTC lost power and set the time
    Serial.println(F("RTC is NOT running, let's set the time!"));
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  } else {                              // The RTC module works correctly
    Serial.println(F("RTC is running correctly!"));
  }
  debugvln(6);
  // -- Set pinmodes to output relays --
  for (uint i = 0; i < MAX_RELAY_COUNT; i++){
    pinMode(RELAY_PINS[i], OUTPUT);
  }
  // -- Setup Controller --
  Controller.now = rtc.now();           // Set current time in the controller
  Controller.StartMenu();               // Start the menu system in the controller
  lastTouched = millis();               // Record the current time
  debugvln(7);
}

/**
 * @brief Main loop function to run the system continuously.
 */
void loop() {
  // -- Update Real Time --
  Controller.now = rtc.now();           // Update the current time in the controller
  
  // -- Check touch --
  // digitalWrite(13, HIGH);               // Activate touch panel
  TSPoint p = ts.getPoint();            // Get touch point coordinates
  // digitalWrite(13, LOW);                // Deactivate touch panel
  pinMode(XM, OUTPUT);                  // Set pin directions for touch panel
  pinMode(YP, OUTPUT);

  // -- Check pressed --
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {  // If the screen is pressed with valid pressure
    // Scale from 0->1023 to TFT width/height
    int y = map(p.x, TS_MINX, TS_MAXX, tft.height(), 0);  // Map x coordinate
    int x = map(p.y, TS_MAXY, TS_MINY, tft.width(), 0);   // Map y coordinate

    if (!backlight && x > 0 && x < WIDTH && y > 0 && y < HEIGHT) {
      Controller.state = mainMenu;       // Set controller state to main menu
      backlight = true;                  // Turn on backlight
      debugln("GBacklight ON");
      DrawMainMenu();                    // Draw the main menu
    } else {
      Controller.Touched(x, y);          // Call touch evaluation function
    }
    lastTouched = millis();              // Record the time of the touch
    delay(300);                          // Delay for debouncing
  }

  if (backlight) {
    // -- Update clock on main screen if backlight is on --
    if (Controller.state == mainMenu && millis() % 1000 == 0) {
      PrintRTCToMainScreen();            // Print the current time to the main screen
    }
    // -- Check to turn off backlight --
    if ((millis() - lastTouched) > BACKLIGHT_COOLDOWN) {
      backlight = false;                 // Turn off backlight
      tft.fillScreen(BLACK);             // Fill the screen with black color
      debugln("Backlight OFF");
    }
  }

  // -- Update relays every minute --
  if (!refreshed && Controller.now.second() == 0) {
    Controller.UpdateRelays();           // Update relay states
    refreshed = true;                    // Set refreshed to true to only run this code once every minute
    debugln("Relays refreshed = true");
  }

  // -- Set refreshed back to false --
  if (refreshed && Controller.now.second() == 59){
    refreshed = false;                   // Reset refreshed flag
    debugln("Refreshed set back to false");
  }
}