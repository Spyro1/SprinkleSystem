// ******** display.ino ********

// ======================== DECLARATIONS ========================
void PrintLabel(const char* label, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);
void PrintLabel(const int labelValue, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);
void PrintChar(const char charValue, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);

// ======================== DRAW FUNCTIONS ========================

void DrawMainMenu(){
  tft.fillScreen(BLACK);
  // === Main title ===
  PrintLabel(strMainTitle, CENTER_H, CENTER_V - x16, 3);
  // === Sprinkle Btn ===
  tft.fillRoundRect(MAIN_1.x, MAIN_1.y, x64, x64, RADIUS, CYAN);
  PrintLabel(strSprinkle, MAIN_1.x + x32, MAIN_1.y + x32, 1, BLACK);
  // === Chain Btn ===
  tft.fillRoundRect(MAIN_2.x, MAIN_2.y, x64, x64, RADIUS, DARKCYAN);
  PrintLabel(strChain, MAIN_2.x + x32, MAIN_2.y + x32, 1, BLACK);
  // === Test Btn ===
  tft.fillRoundRect(MAIN_3.x, MAIN_3.y, x64, x64, RADIUS, GREEN);
  PrintLabel(strTest, MAIN_3.x + x32, MAIN_3.y + x32, 1, BLACK);
  // === Humidity Btn ===
  tft.fillRoundRect(MAIN_4.x, MAIN_4.y, x64, x64, RADIUS, BLUE);
  PrintLabel(strHumidity, MAIN_4.x + x32, MAIN_4.y + x32, 1, WHITE);
  // === Settings Btn ===
  tft.fillRoundRect(MAIN_5.x, MAIN_5.y, x64, x64, RADIUS, DARKGREY);
  PrintLabel(strSettings, MAIN_5.x + x32, MAIN_5.y + x32);
  // === Clock Btn ===
  tft.fillRoundRect(MAIN_7.x, MAIN_7.y, x64, x64, RADIUS, LIGHTGREY);
  PrintLabel(strClock, MAIN_7.x + x32, MAIN_7.y + x32, 1, BLACK);
  // === Update mainmenu state (real time and on/off btn state) ===
  UpdateMainMenu();
}
void DrawSprinkleProfilesMenu(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strProfileSettings, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // == 1. Profile ==
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64 * 2 + MARGIN * 2, x64, RADIUS, LIGHTGREY); // Relay chooser large button
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, RADIUS, GREENYELLOW); // Automatic setter button
  PrintLabel(strAuto, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 2); // Automati label
  PrintLabel(strFirstProfile, CENTER_H, SLOT_1_2.y + x32, 2); // 1. Profil label
  // == 2. Profile ==
  tft.fillRoundRect(SLOT_2_2.x, SLOT_2_2.y, x64 * 2 + MARGIN * 2, x64, RADIUS, LIGHTGREY); // Relay chooser large button
  tft.fillRoundRect(SLOT_2_1.x, SLOT_2_1.y, x64, x64, RADIUS, GREENYELLOW); // Automatic setter button
  PrintLabel(strAuto, SLOT_2_1.x + x32, SLOT_2_1.y + x32, 2); // Automatic label
  PrintLabel(strSecondProfile, CENTER_H, SLOT_2_2.y + x32, 2); // 2. Profil label
  // == 3. Profile ==
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64 * 2 + MARGIN * 2, x64, RADIUS, LIGHTGREY); // Relay chooser large button
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, RADIUS, GREENYELLOW); // Automatic setter button
  PrintLabel(strAuto, SLOT_3_1.x + x32, SLOT_3_1.y + x32, 2); // Automatic label
  PrintLabel(strThirdProfile, CENTER_H, SLOT_3_2.y + x32, 2); // 3. Profil label
  // === Update profile setter (profile states on/off btn) ===
  UpdateSprinkleProfilesMenu(); // Update on off switches
}
void DrawSprinkleRelayChooser(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  if (Controller.currentProfile == 0) PrintLabel(strFirstProfile, CENTER_H, 8, 2, WHITE);
  else if (Controller.currentProfile == 1) PrintLabel(strSecondProfile, CENTER_H, 8, 2, WHITE);
  else if (Controller.currentProfile == 2) PrintLabel(strThirdProfile, CENTER_H, 8, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // == Arrows < | > ==
  // < Left arrow
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, DARKCYAN);
  PrintLabel("<", SLOT_3_1.x + x32, SLOT_3_1.y + x32, 3, WHITE);
  // > Right arrow
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, DARKCYAN);
  PrintLabel(">", SLOT_3_4.x + x32, SLOT_3_4.y + x32, 3, WHITE);
  // == Draws relay buttons and numbers to them ==
  UpdateSprinkleRelayChooser();
}
void DrawSprinkleSetter(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  char temp[12];
  sprintf(temp, "%d/%d. Rele", Controller.currentProfile, Controller.currentRelay);
  PrintLabel(temp, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);

  // Code goes here ...

}
void DrawSprinkleAutomatic(){
  tft.fillScreen(BLACK);
  
}
void DrawChainSprinkleMenu(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strChain, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- From relay setter --
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, x16, LIGHTGREY); // Increase from value
  PrintChar(0x18, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 3); // ↑
  PrintLabel(strFromRelay, COL_1_LABEL.x, COL_1_LABEL.y, 1); // Label
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, LIGHTGREY); // Decrease from value
  PrintChar(0x19, SLOT_3_1.x + x32, SLOT_3_1.y + x32, 3); // ↓
  // -- To relay setter --
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, x16, LIGHTGREY); // Increase to value
  PrintChar(0x18, SLOT_1_2.x + x32, SLOT_1_2.y + x32, 3); // ↑
  PrintLabel(strToRelay, COL_2_LABEL.x, COL_2_LABEL.y, 1); // Label
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, LIGHTGREY); // Decrease to value
  PrintChar(0x19, SLOT_3_2.x + x32, SLOT_3_2.y + x32, 3); // ↓
  // -- Duration setter --
  tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y, x64, x64, x16, LIGHTGREY); // Increase from value
  PrintChar('+', SLOT_1_3.x + x32, SLOT_1_3.y + x32, 3); // +
  PrintLabel(strDuration, COL_3_LABEL.x, COL_3_LABEL.y, 1); // Label
  tft.fillRoundRect(SLOT_3_3.x, SLOT_3_3.y, x64, x64, x16, LIGHTGREY); // Decrease to value
  PrintChar('-', SLOT_3_3.x + x32, SLOT_3_3.y + x32, 3); // -
  // -- Separator arrow --
  PrintChar(0x1A, COL_1_2_SEPARATOR.x, COL_1_2_SEPARATOR.y, 3);
  // -- Start button --
  tft.fillRoundRect(SLOT_2_4.x, SLOT_2_4.y, x64, x64, x16, GREEN);
  PrintLabel(strStart, SLOT_2_4.x + x32, SLOT_2_4.y + x32, 2, BLACK);
  // -- Update chain screen --
  UpdateChainSprinkleMenu();
}
void DrawTestMenu(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strTest, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // == Arrows < | > ==
  // < Left arrow
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, DARKCYAN);
  PrintLabel("<", SLOT_3_1.x + x32, SLOT_3_1.y + x32, 3, WHITE);
  // > Right arrow
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, DARKCYAN);
  PrintLabel(">", SLOT_3_4.x + x32, SLOT_3_4.y + x32, 3, WHITE);
  // == Draws relay switches and numbers and labels to them ==
  UpdateTestMenu();
}
void DrawHumidityMenu(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strHumidity, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);

}
void DrawSettingsMenu(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strSettings, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);

}
void DrawClockMenu(){
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strRealTimeSettings, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);

}

// ======================== UPDATE FUNCTIONS ========================

void UpdateMainMenu() {
  // === Real time ===
  PrintRTCToMainScreen();
  // === Main Switch ===
  if (Controller.mainSwitch){
    tft.fillRoundRect(MAIN_6.x, MAIN_6.y, x64, x64, RADIUS * 2, GREEN);
    PrintLabel(strON, MAIN_6.x + x32, MAIN_6.y + x32, 3);
  }
  else{
    tft.fillRoundRect(MAIN_6.x, MAIN_6.y, x64, x64, RADIUS * 2, RED);
    PrintLabel(strOFF, MAIN_6.x + x32, MAIN_6.y + x32, 3);
  }
}

void UpdateSprinkleProfilesMenu() {
  // === Update profile switches ==
  // Firs row
  if (Controller.profiles[0].isActive) {
    tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y + x16, x64, x32, RADIUS, GREEN); // On / off switch for profile
    PrintLabel(strON, SLOT_1_4.x + x32, SLOT_1_4.y + x32, 2); // ON label
  } 
  else {
    tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y + x16, x64, x32, RADIUS, RED); // On / off switch for profile
    PrintLabel(strOFF, SLOT_1_4.x + x32, SLOT_1_4.y + x32, 2); // OFF label
  } 
  // Second row
  if (Controller.profiles[1].isActive){
    tft.fillRoundRect(SLOT_2_4.x, SLOT_2_4.y + x16, x64, x32, RADIUS, GREEN); // On / off switch for profile
    PrintLabel(strON, SLOT_2_4.x + x32, SLOT_2_4.y + x32, 2); // ON label
  } 
  else {
    tft.fillRoundRect(SLOT_2_4.x, SLOT_2_4.y + x16, x64, x32, RADIUS, RED); // On / off switch for profile
    PrintLabel(strOFF, SLOT_2_4.x + x32, SLOT_2_4.y + x32, 2); // OFF label
  } 
  // Third row
  if (Controller.profiles[2].isActive) {
    tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y + x16, x64, x32, RADIUS, GREEN); // On / off switch for profile
    PrintLabel(strON, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 2); // ON label
  }
  else {
    tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y + x16, x64, x32, RADIUS, RED); // On / off switch for profile
    PrintLabel(strOFF, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 2); // OFF label
  }
}

void UpdateSprinkleRelayChooser() {
  // === Relay background circles ===
  tft.fillCircle(SLOT_1_1.x + x32, SLOT_1_1.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_1_2.x + x32, SLOT_1_2.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_1_3.x + x32, SLOT_1_3.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_1_4.x + x32, SLOT_1_4.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_2_1.x + x32, SLOT_2_1.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_2_2.x + x32, SLOT_2_2.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_2_3.x + x32, SLOT_2_3.y + x32, x32, MAROON);
  tft.fillCircle(SLOT_2_4.x + x32, SLOT_2_4.y + x32, x32, MAROON);
  // === Numbers ===
  PrintLabel(Controller.currentPage * 8 + 1, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 2, SLOT_1_2.x + x32, SLOT_1_2.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 3, SLOT_1_3.x + x32, SLOT_1_3.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 4, SLOT_1_4.x + x32, SLOT_1_4.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 5, SLOT_2_1.x + x32, SLOT_2_1.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 6, SLOT_2_2.x + x32, SLOT_2_2.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 7, SLOT_2_3.x + x32, SLOT_2_3.y + x32, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 8, SLOT_2_4.x + x32, SLOT_2_4.y + x32, 2, WHITE);
}

void UpdateSprinkleSetter() {
  // -- Hour setter number --
  PrintLabel(Controller.temporalSetter.start.hours(), SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- Minute setter number --
  PrintLabel(Controller.temporalSetter.start.minutes(), SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Duration setter number --
  PrintLabel(Controller.temporalSetter.duration, SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateSprinkleAutomatic() {
   // -- Hour setter number --
  PrintLabel(Controller.temporalSetter.start.hours(), SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- Minute setter number --
  PrintLabel(Controller.temporalSetter.start.minutes(), SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Duration setter number --
  PrintLabel(Controller.temporalSetter.duration, SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateChainSprinkleMenu(){
  // -- From relay setter number --
  PrintLabel(Controller.temporalSetter.start.hours(), SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- To relay setter number --
  PrintLabel(Controller.temporalSetter.start.minutes(), SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Duration setter number --
  PrintLabel(Controller.temporalSetter.duration, SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateTestMenu() {
  // === Numbers ===
  PrintLabel(Controller.currentPage * 8 + 1, SLOT_1_1.x + x32, SLOT_1_1.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 2, SLOT_1_2.x + x32, SLOT_1_2.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 3, SLOT_1_3.x + x32, SLOT_1_3.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 4, SLOT_1_4.x + x32, SLOT_1_4.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 5, SLOT_2_1.x + x32, SLOT_2_1.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 6, SLOT_2_2.x + x32, SLOT_2_2.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 7, SLOT_2_3.x + x32, SLOT_2_3.y + x16, 2, WHITE);
  PrintLabel(Controller.currentPage * 8 + 8, SLOT_2_4.x + x32, SLOT_2_4.y + x16, 2, WHITE);
  // === Relay switches and labels ===
  // 0. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state){
    tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 0.
    PrintLabel(strON, SLOT_1_1.x + x32, SLOT_1_1.y + x48, 2); // ON label
  } 
  else {
    tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 0.
    PrintLabel(strOFF, SLOT_1_1.x + x32, SLOT_1_1.y + x48, 2); // OFF label
  }
  // 1. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state) {
    tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 1.
    PrintLabel(strON, SLOT_1_2.x + x32, SLOT_1_1.y + x48, 2); // ON label
  } 
  else {
    tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 1.
    PrintLabel(strOFF, SLOT_1_2.x + x32, SLOT_1_2.y + x48, 2); // OFF label
  }
  // 2. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state){
    tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 2.
   PrintLabel(strON, SLOT_1_3.x + x32, SLOT_1_3.y + x48, 2); // ON label
  }
  else {
    tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 2.
    PrintLabel(strOFF, SLOT_1_3.x + x32, SLOT_1_3.y + x48, 2); // OFF label
  }
  // 3. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state){
    tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 3.
    PrintLabel(strON, SLOT_1_4.x + x32, SLOT_1_4.y + x48, 2); // ON label
  } 
  else {
    tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 3.
    PrintLabel(strOFF, SLOT_1_4.x + x32, SLOT_1_4.y + x48, 2); // OFF label
  } 
  // 4. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state) {
    tft.fillRoundRect(SLOT_2_1.x, SLOT_2_1.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 4.
    PrintLabel(strON, SLOT_2_1.x + x32, SLOT_2_1.y + x48, 2); // ON label
  } 
  else {
    tft.fillRoundRect(SLOT_2_1.x, SLOT_2_1.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 4.
    PrintLabel(strOFF, SLOT_2_1.x + x32, SLOT_2_1.y + x48, 2); // OFF label
  } 
  // 5. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state) {
    tft.fillRoundRect(SLOT_2_2.x, SLOT_2_2.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 5.
    PrintLabel(strON, SLOT_2_2.x + x32, SLOT_2_1.y + x48, 2); // ON label
  }
  else {
    tft.fillRoundRect(SLOT_2_2.x, SLOT_2_2.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 5.
    PrintLabel(strOFF, SLOT_2_2.x + x32, SLOT_2_2.y + x48, 2); // OFF label
  }
  // 6. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state) { 
    tft.fillRoundRect(SLOT_2_3.x, SLOT_2_3.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 6.
    PrintLabel(strON, SLOT_2_3.x + x32, SLOT_2_3.y + x48, 2); // ON label
  }
  else  {
    tft.fillRoundRect(SLOT_2_3.x, SLOT_2_3.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 6.
    PrintLabel(strOFF, SLOT_2_3.x + x32, SLOT_2_3.y + x48, 2); // OFF label
  }
  // 7. switch
  if (Controller.temporalProfile.relays[Controller.currentPage * 8 + 1].state) {
    tft.fillRoundRect(SLOT_2_4.x, SLOT_2_4.y + x32, x64, x32, RADIUS, GREEN); // On / off switch 7.
    PrintLabel(strON, SLOT_2_4.x + x32, SLOT_2_4.y + x48, 2); // ON label
  }
  else {
    tft.fillRoundRect(SLOT_2_4.x, SLOT_2_4.y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 7.
    PrintLabel(strOFF, SLOT_2_4.x + x32, SLOT_2_4.y + x48, 2); // OFF label
  } 
  
}
void UpdateHumidityMenu() {

}
void UpdateSettingsMenu() {

}
void UpdateClockMenu() {

}


// ---- Display helper functions ----
void PrintRTCToMainScreen()
{
    char temp[9];
    sprintf(temp, "%02d:%02d:%02d", Controller.now.hour(), Controller.now.minute(), Controller.now.second());
    tft.fillRect(CENTER_H - GetTextWidth(temp, 2) / 2 - 1, CENTER_V + x16 - GetTextHeight(2) / 2 - 1, GetTextWidth(temp, 2) + 2, GetTextHeight(2) + 2, BLACK);
    PrintLabel(temp, CENTER_H, CENTER_V + x16, 2);
}

void PrintLabel(const char* label, const int x, const int y, const int fontSize, const uint16_t color)
{
  tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y - GetTextHeight(fontSize) / 2);
  tft.setTextColor(color);
  tft.setTextSize(fontSize);
  tft.print(label);
}
void PrintLabel(const int labelValue, const int x, const int y, const int fontSize, const uint16_t color) {
  char temp[7];
  sprintf(temp, "%d", labelValue);
  PrintLabel(temp, x, y, fontSize, color);
}
void PrintChar(const char charValue, const int x, const int y, const int fontSize, const uint16_t color) {
  tft.setCursor(x - FONT_1_H * fontSize / 2, y - GetTextHeight(fontSize) / 2);
  tft.setTextColor(color);
  tft.setTextSize(fontSize);
  tft.write(charValue);
}
void PrintDoubleLine(const int y, const int width, const uint16_t color) {
    tft.drawFastHLine((WIDTH - width) / 2, y, width, color); // Dupla vonal
    // tft.drawFastHLine((WIDTH - width) / 2, y + 1, width, color); // Dupla vonal
}
void PrintHomeIcon() {
  tft.fillRect(SUBMENU_HOME_POS.x + 4, SUBMENU_HOME_POS.y + x16, 24, x16, CYAN);
  tft.fillTriangle(SUBMENU_HOME_POS.x, SUBMENU_HOME_POS.y + x16, SUBMENU_HOME_POS.x + x16, SUBMENU_HOME_POS.y, SUBMENU_HOME_POS.x + x32, SUBMENU_HOME_POS.y + x16, CYAN);
}
// void PrintRelayChoserNumbering(int pageNumber, const uint16_t color)
// {
    // int i = pageNumber == 1 ? 1 : 9;
    // const int fontsize = 2;
    // PrintLabel(tft, i++, x32 + SLOT_1_1 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_1_2 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_1_3 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_1_4 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_1 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_2 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_3 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_4 + x32, fontsize, color);
// }
// void PrintNumberField(const int column, int value)
// {
//     if (column == 1)
//     {
//         tft.fillRect(-x32 + COL_1_CENTER, x64, x32, BLACK);
//         PrintLabel(value, COL_1_CENTER, 3, WHITE);
//     }
//     else if (column == 2)
//     {
//         tft.fillRect(-x32 + COL_2_CENTER, x64, x32, BLACK);
//         PrintLabel(value, COL_2_CENTER, 3);
//     }
//     else if (column == 3)
//     {
//         tft.fillRect(-x32 + COL_3_CENTER, x64, x32, BLACK);
//         PrintLabel(value, COL_3_CENTER, 3);
//     }
// }
int GetTextWidth(const char *text, const int fontSize)
{
    return strlen(text) * FONT_1_H * fontSize + (strlen(text) - 1) * fontSize;
}
int GetTextHeight(const int fontSize){
  return FONT_1_V * fontSize;
}
int GetNumWidth(const int number, const int fontSize)
{
    int lenght = floor(log10(number) + 1);
    return lenght * FONT_1_H * fontSize + (lenght - 1) * fontSize;
}
