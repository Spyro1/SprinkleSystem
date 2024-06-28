// ******** display.ino ********

// ======================== DECLARATIONS ========================
void PrintLabel(const char *label, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);
void PrintLabelBg(const char *label, const int x, const int y, const int fontSize, const uint16_t color = WHITE, const uint16_t bgColor = BLACK);
void PrintLabel(const int labelValue, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);
void PrintLabelBg(const int labelValue, const int x, const int y, const int fontSize, const uint16_t color = WHITE, const uint16_t bgColor = BLACK);
void PrintChar(const char charValue, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);

// ======================== DRAW FUNCTIONS ========================

void DrawMainMenu() {
  tft.fillScreen(BLACK);
  // === Main title ===
  PrintLabel(strMainTitle, CENTER_H, CENTER_V - x16, 3);
  // === Sprinkle Btn ===
  tft.fillRoundRect(MAIN_1.x, MAIN_1.y, x64, x64, RADIUS, CYAN);
  PrintLabel(strSprinkle, MAIN_1.x + x32, MAIN_1.y + x32 - 8, 1, BLACK);
  PrintLabel(strTiming, MAIN_1.x + x32, MAIN_1.y + x32 + 8, 1, BLACK);
  // === Chain Btn ===
  tft.fillRoundRect(MAIN_2.x, MAIN_2.y, x64, x64, RADIUS, PURPLE);
  PrintLabel(strChain, MAIN_2.x + x32, MAIN_2.y + x32 - 8, 1, WHITE);
  PrintLabel(strSprinkle, MAIN_2.x + x32, MAIN_2.y + x32 + 8, 1, WHITE);
  // === Test Btn ===
  tft.fillRoundRect(MAIN_3.x, MAIN_3.y, x64, x64, RADIUS, BLUE);
  PrintLabel(strTest, MAIN_3.x + x32, MAIN_3.y + x32, 1, WHITE);
  // === Settings Btn ===
  tft.fillRoundRect(MAIN_4.x, MAIN_4.y, x64, x64, RADIUS, DARKGREY);
  PrintLabel(strSettings, MAIN_4.x + x32, MAIN_4.y + x32, 1, WHITE);
  // === Clock Btn ===
  tft.fillRoundRect(MAIN_6.x, MAIN_6.y, x64, x64, RADIUS, NAVY);
  PrintLabel(strClock, MAIN_6.x + x32, MAIN_6.y + x32 - 8);
  PrintLabel(strSetting, MAIN_6.x + x32, MAIN_6.y + x32 + 8);
  // === Update mainmenu state (real time and on/off btn state) ===
  UpdateMainMenu();
}
void DrawSprinkleProfilesMenu() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strProfileSettings, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // == 1. Profile ==
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64 * 2 + MARGIN * 2, x64, RADIUS, DARKCYAN); // Relay chooser large button
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, RADIUS, BLUE);                      // Automatic setter button
  PrintLabel(strAuto, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 2);                             // Automati label
  PrintLabel(strFirstProfile, CENTER_H, SLOT_1_2.y + x32, 2);                             // 1. Profil label
  // == 2. Profile ==
  tft.fillRoundRect(SLOT_2_2.x, SLOT_2_2.y, x64 * 2 + MARGIN * 2, x64, RADIUS, DARKCYAN); // Relay chooser large button
  tft.fillRoundRect(SLOT_2_1.x, SLOT_2_1.y, x64, x64, RADIUS, BLUE);                      // Automatic setter button
  PrintLabel(strAuto, SLOT_2_1.x + x32, SLOT_2_1.y + x32, 2);                             // Automatic label
  PrintLabel(strSecondProfile, CENTER_H, SLOT_2_2.y + x32, 2);                            // 2. Profil label
  // == 3. Profile ==
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64 * 2 + MARGIN * 2, x64, RADIUS, DARKCYAN); // Relay chooser large button
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, RADIUS, BLUE);                      // Automatic setter button
  PrintLabel(strAuto, SLOT_3_1.x + x32, SLOT_3_1.y + x32, 2);                             // Automatic label
  PrintLabel(strThirdProfile, CENTER_H, SLOT_3_2.y + x32, 2);                             // 3. Profil label
  // === Update profile setter (profile states on/off btn) ===
  UpdateSprinkleProfilesMenu(); // Update on off switches
}
void DrawSprinkleRelayChooser() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  if (Controller.currentProfile == 0)
    PrintLabel(strFirstProfile, CENTER_H, x16, 2, WHITE);
  else if (Controller.currentProfile == 1)
    PrintLabel(strSecondProfile, CENTER_H, x16, 2, WHITE);
  else if (Controller.currentProfile == 2)
    PrintLabel(strThirdProfile, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // == Arrows < | > ==
  // < Left arrow
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, DARKCYAN);
  PrintChar(0x11, SLOT_3_1.x + x32, SLOT_3_1.y + x32, 3, WHITE);
  // > Right arrow
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, DARKCYAN);
  PrintChar(0x10, SLOT_3_2.x + x32, SLOT_3_2.y + x32, 3, WHITE);
  // -- Back Btn --
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED);     // Back button
  PrintLabel(strBack, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Back label
  // == Draws relay buttons and numbers to them ==
  UpdateSprinkleRelayChooser();
}
void DrawSprinkleSetter() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  char temp[20];
  sprintf(temp, "%d. Profil/%d. Rele", Controller.currentProfile + 1, Controller.currentRelay + 1);
  PrintLabel(temp, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- Hour setter --
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, x16, LIGHTGREY); // Increase hour
  PrintChar('+', SLOT_1_1.x + x32, SLOT_1_1.y + x32, 4, BLACK);        // +
  PrintLabel(strHour, COL_1_LABEL.x, COL_1_LABEL.y, 1);                // Label
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, LIGHTGREY); // Decrease hour
  PrintChar('-', SLOT_3_1.x + x32, SLOT_3_1.y + x32, 4, BLACK);        // -
  // -- Minute setter --
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, x16, LIGHTGREY); // Increase minute
  PrintChar('+', SLOT_1_2.x + x32, SLOT_1_2.y + x32, 4, BLACK);        // +
  PrintLabel(strMinute, COL_2_LABEL.x, COL_2_LABEL.y, 1);              // Label
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, LIGHTGREY); // Decrease minute
  PrintChar('-', SLOT_3_2.x + x32, SLOT_3_2.y + x32, 4, BLACK);        // -
  // -- Duration setter --
  tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y, x64, x64, x16, LIGHTGREY); // Increase duration
  PrintChar('+', SLOT_1_3.x + x32, SLOT_1_3.y + x32, 4, BLACK);        // +
  PrintLabel(strDuration, COL_3_LABEL.x, COL_3_LABEL.y, 1);            // Label
  tft.fillRoundRect(SLOT_3_3.x, SLOT_3_3.y, x64, x64, x16, LIGHTGREY); // Decrease duration
  PrintChar('-', SLOT_3_3.x + x32, SLOT_3_3.y + x32, 4, BLACK);        // -
  // -- Separator columns --
  PrintChar(':', COL_1_2_SEPARATOR.x, COL_1_2_SEPARATOR.y, 4);
  // -- Minute short "p" label --
  PrintLabel(strMinShort, COL_3_4_SEPARATOR.x - 8, COL_3_4_SEPARATOR.y , 2);
  // -- Save Btn --
  tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y, x64, x64, x16, GREEN);       // Save button
  PrintLabel(strSave, SLOT_1_4.x + x32, SLOT_1_4.y + x32, 1, DARKGREEN); // Save label
  // -- Back Btn --
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED);     // Back button
  PrintLabel(strBack, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Back label
  // -- Update Setter screen --
  UpdateSprinkleSetter();
}
void DrawSprinkleAutomatic() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  char temp[16];
  sprintf(temp, "%d. Profil Auto", Controller.currentProfile + 1);
  PrintLabel(temp, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- Hour setter --
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, x16, LIGHTGREY); // Increase hour
  PrintChar('+', SLOT_1_1.x + x32, SLOT_1_1.y + x32, 4, BLACK);        // +
  PrintLabel(strHour, COL_1_LABEL.x, COL_1_LABEL.y, 1);                // Label
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, LIGHTGREY); // Decrease hour
  PrintChar('-', SLOT_3_1.x + x32, SLOT_3_1.y + x32, 4, BLACK);        // -
  // -- Minute setter --
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, x16, LIGHTGREY); // Increase minute
  PrintChar('+', SLOT_1_2.x + x32, SLOT_1_2.y + x32, 4, BLACK);        // +
  PrintLabel(strMinute, COL_2_LABEL.x, COL_2_LABEL.y, 1);              // Label
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, LIGHTGREY); // Decrease minute
  PrintChar('-', SLOT_3_2.x + x32, SLOT_3_2.y + x32, 4, BLACK);        // -
  // -- Duration setter --
  tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y, x64, x64, x16, LIGHTGREY); // Increase duration
  PrintChar('+', SLOT_1_3.x + x32, SLOT_1_3.y + x32, 4, BLACK);        // +
  PrintLabel(strDuration, COL_3_LABEL.x, COL_3_LABEL.y, 1);            // Label
  tft.fillRoundRect(SLOT_3_3.x, SLOT_3_3.y, x64, x64, x16, LIGHTGREY); // Decrease duration
  PrintChar('-', SLOT_3_3.x + x32, SLOT_3_3.y + x32, 4, BLACK);        // -
  // -- Separator columns --
  PrintChar(':', COL_1_2_SEPARATOR.x, COL_1_2_SEPARATOR.y, 4);
  // -- From label --
  PrintLabel(strFromTag, COL_2_3_SEPARATOR.x, COL_2_3_SEPARATOR.y, 1);
  // -- By munute label --
  PrintLabel(strByMinute, COL_3_4_SEPARATOR.x + x16, COL_3_4_SEPARATOR.y, 1);
  // -- Save Btn --
  tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y, x64, x64, x16, GREEN);       // Save button
  PrintLabel(strSave, SLOT_1_4.x + x32, SLOT_1_4.y + x32, 1, DARKGREEN); // Save label
  // -- Back Btn --
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED);     // Back button
  PrintLabel(strBack, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Back label
  // -- Update Setter screen --
  UpdateSprinkleAutomatic();
}
void DrawChainSprinkleMenu() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strChain, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- From relay setter --
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, x16, LIGHTGREY); // Increase from value
  PrintChar(0x1E, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 4, BLACK);       // ↑
  PrintLabel(strFromRelay, COL_1_LABEL.x, COL_1_LABEL.y, 1);           // Label
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, LIGHTGREY); // Decrease from value
  PrintChar(0x1F, SLOT_3_1.x + x32, SLOT_3_1.y + x32, 4, BLACK);       // ↓
  // -- To relay setter --
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, x16, LIGHTGREY); // Increase to value
  PrintChar(0x1E, SLOT_1_2.x + x32, SLOT_1_2.y + x32, 4, BLACK);       // ↑
  PrintLabel(strToRelay, COL_2_LABEL.x, COL_2_LABEL.y, 1);             // Label
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, LIGHTGREY); // Decrease to value
  PrintChar(0x1F, SLOT_3_2.x + x32, SLOT_3_2.y + x32, 4, BLACK);       // ↓
  // -- Duration setter --
  tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y, x64, x64, x16, LIGHTGREY); // Increase from value
  PrintChar('+', SLOT_1_3.x + x32, SLOT_1_3.y + x32, 4, BLACK);        // +
  PrintLabel(strDuration, COL_3_LABEL.x, COL_3_LABEL.y, 1);            // Label
  tft.fillRoundRect(SLOT_3_3.x, SLOT_3_3.y, x64, x64, x16, LIGHTGREY); // Decrease to value
  PrintChar('-', SLOT_3_3.x + x32, SLOT_3_3.y + x32, 4, BLACK);        // -
  // -- Separator arrow --
  PrintChar(0x1A, COL_1_2_SEPARATOR.x, COL_1_2_SEPARATOR.y, 4);
  // -- Minute short "p" label --
  PrintLabel(strMinShort, COL_3_4_SEPARATOR.x - 8, COL_3_4_SEPARATOR.y, 2);
  // -- Start button --
  tft.fillRoundRect(SLOT_1_4.x, SLOT_1_4.y, x64, x64, x16, GREEN);
  PrintLabel(strStart, SLOT_1_4.x + x32, SLOT_1_4.y + x32, 1, DARKGREEN);
  // -- Stop Btn --
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED);     // Stop button
  PrintLabel(strStop, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Stop label
  // -- Update chain screen --
  UpdateChainSprinkleMenu();
}
void DrawTestMenu() {
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
  PrintChar(0x11, SLOT_3_1.x + x32, SLOT_3_1.y + x32, 3, WHITE);
  // > Right arrow
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, DARKCYAN);
  PrintChar(0x10, SLOT_3_2.x + x32, SLOT_3_2.y + x32, 3, WHITE);
  // -- Reset Btn --
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED); // Reset button
  // PrintChar('X', SLOT_3_4.x + x32, SLOT_3_4.y + x32, 4, WHITE);  // Reset label
  PrintLabel(strStop, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Stop label
  // Preset the currently active relays
  for (int r = 0; r < Controller.relayCount; r++)
  {
    for (int p = 0; p < PROFILE_COUNT; p++)
    {
      if (Controller.profiles[p].relays[r].state)
      {
        Controller.temporalProfile.relays[r].state = true;
        break;
      }
    }
  }
  // == Draws relay switches and numbers and labels to them ==
  UpdateTestMenu();
}
void DrawSettingsMenu() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strSettings, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- Main Switch Label --
  PrintLabel(strMainSwitch, SLOT_2_1.x + x32, SLOT_2_1.y + 8, 1);
  // -- Relay Count setter --
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, x16, LIGHTGREY); // Increase hour
  PrintChar('+', SLOT_1_2.x + x32, SLOT_1_2.y + x32, 4, BLACK); // +
  PrintLabel(strRelayCount, COL_2_LABEL.x, COL_2_LABEL.y, 1); // Label
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, LIGHTGREY); // Decrease hour
  PrintChar('-', SLOT_3_2.x + x32, SLOT_3_2.y + x32, 4, BLACK); // -
  // -- Humidity setter --
  tft.fillRoundRect(SLOT_1_3.x, SLOT_1_3.y, x64, x64, x16, LIGHTGREY); // Increase hour
  PrintChar('+', SLOT_1_3.x + x32, SLOT_1_3.y + x32, 4, BLACK);        // +
  PrintLabel(strHumidity, COL_3_LABEL.x, SLOT_2_3.y + 8, 1);           // Label
  PrintLabel(strSenitivity, COL_3_LABEL.x, COL_3_LABEL.y, 1);          // Label
  tft.fillRoundRect(SLOT_3_3.x, SLOT_3_3.y, x64, x64, x16, LIGHTGREY); // Decrease hour
  PrintChar('-', SLOT_3_3.x + x32, SLOT_3_3.y + x32, 4, BLACK);        // -
  // -- Developer settings button --
  tft.drawRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, RADIUS, WHITE);
  PrintLabel("Karban-", SLOT_3_1.x + x32, SLOT_3_1.y + x16, 1);
  PrintLabel("tartasi", SLOT_3_1.x + x32, SLOT_3_1.y + x32, 1);
  PrintLabel("panel", SLOT_3_1.x + x32, SLOT_3_1.y + x48, 1);
  // -- Back Btn --
  tft.fillRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED);      // Back button
  PrintLabel(strReset, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Back label
  // -- Update changes settings --
  UpdateSettingsMenu();
}
void DrawClockMenu() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strRealTimeSettings, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- Hour setter --
  tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, x16, LIGHTGREY); // Increase hour
  PrintChar('+', SLOT_1_1.x + x32, SLOT_1_1.y + x32, 4, BLACK);        // +
  PrintLabel(strHour, COL_1_LABEL.x, COL_1_LABEL.y, 1);                // Label
  tft.fillRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, x16, LIGHTGREY); // Decrease hour
  PrintChar('-', SLOT_3_1.x + x32, SLOT_3_1.y + x32, 4, BLACK);        // -
  // -- Minute setter --
  tft.fillRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, x16, LIGHTGREY); // Increase minute
  PrintChar('+', SLOT_1_2.x + x32, SLOT_1_2.y + x32, 4, BLACK);        // +
  PrintLabel(strMinute, COL_2_LABEL.x, COL_2_LABEL.y, 1);              // Label
  tft.fillRoundRect(SLOT_3_2.x, SLOT_3_2.y, x64, x64, x16, LIGHTGREY); // Decrease minute
  PrintChar('-', SLOT_3_2.x + x32, SLOT_3_2.y + x32, 4, BLACK);        // -
  // -- Save Btn --
  tft.fillRoundRect(SLOT_2_4.x, SLOT_2_4.y, x64, x64, x16, DARKCYAN);       // Save button
  PrintLabel(strSave, SLOT_2_4.x + x32, SLOT_2_4.y + x32, 1, WHITE); // Save label
  // Update number feilds
  UpdateClockMenu();
}
void DrawDeveloperMenu() {
  tft.fillScreen(BLACK);
  // == Home Icon ==
  PrintHomeIcon();
  // == Subtitle ==
  PrintLabel(strDeveloper, CENTER_H, x16, 2, WHITE);
  // == Line ==
  PrintDoubleLine(x32, WIDTH, WHITE);
  // -- List timed profiles button --
  tft.drawRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, RADIUS, WHITE);
  PrintLabel("List", SLOT_1_1.x + x32, SLOT_1_1.y + x16);
  PrintLabel("Timed", SLOT_1_1.x + x32, SLOT_1_1.y + x32);
  PrintLabel("Profiles", SLOT_1_1.x + x32, SLOT_1_1.y + x48);
  // -- List temporal profiles button --
  tft.drawRoundRect(SLOT_1_2.x, SLOT_1_2.y, x64, x64, RADIUS, WHITE);
  PrintLabel("List", SLOT_1_2.x + x32, SLOT_1_2.y + x16);
  PrintLabel("Temp", SLOT_1_2.x + x32, SLOT_1_2.y + x32);
  PrintLabel("Profiles", SLOT_1_2.x + x32, SLOT_1_2.y + x48);
  // -- List Controller fields --
  tft.drawRoundRect(SLOT_1_3.x, SLOT_1_3.y, x64, x64, RADIUS, WHITE);
  PrintLabel("Controller", SLOT_1_3.x + x32, SLOT_1_3.y + x16);
  PrintLabel("Stats", SLOT_1_3.x + x32, SLOT_1_3.y + x32);
  // -- Relay stats --
  tft.drawRoundRect(SLOT_1_4.x, SLOT_1_4.y, x64, x64, RADIUS, WHITE);
  PrintLabel("Relay", SLOT_1_4.x + x32, SLOT_1_4.y + x16);
  PrintLabel("Stats", SLOT_1_4.x + x32, SLOT_1_4.y + x32);
  // -- Dactory reset button --
  tft.drawRoundRect(SLOT_3_1.x, SLOT_3_1.y, x64, x64, RADIUS, BLUE);
  PrintLabel("Factory", SLOT_3_1.x + x32, SLOT_3_1.y + x16);
  PrintLabel("Reset", SLOT_3_1.x + x32, SLOT_3_1.y + x32);
  // -- Back Btn --
  tft.drawRoundRect(SLOT_3_4.x, SLOT_3_4.y, x64, x64, x16, RED);     // Back button
  PrintLabel(strBack, SLOT_3_4.x + x32, SLOT_3_4.y + x32, 1, WHITE); // Back label
}
// ======================== UPDATE FUNCTIONS ========================

void UpdateMainMenu() {
  // === Real time ===
  PrintRTCToMainScreen();
  // === Save Btn ===
  if (Controller.unsavedChanges)
  {
    tft.fillRoundRect(MAIN_5.x, MAIN_5.y, x64, x64, x16, DARKCYAN);
    PrintLabel(strSave, MAIN_5.x + x32, MAIN_5.y + x32, 1, WHITE);
  }
  else
  {
    tft.fillRoundRect(MAIN_5.x, MAIN_5.y, x64, x64, x16, GREEN);
    PrintLabel(strSaved, MAIN_5.x + x32, MAIN_5.y + x32, 1, BLACK);
  }
}

void UpdateSprinkleProfilesMenu() {
  // === Update profile switches ==
  // Iterate through the profiles
  for (uint p = 0; p < PROFILE_COUNT; p++){
    if (Controller.profiles[p].isActive) {
      tft.fillRoundRect(SLOTS[p*4+3].x, SLOTS[p*4+3].y + x16, x64, x32, RADIUS, GREEN); // On / off switch for profile
      PrintLabel(strON, SLOTS[p*4+3].x + x32, SLOTS[p*4+3].y + x32, 2, DARKGREEN);      // ON label
    }
    else {
      tft.fillRoundRect(SLOTS[p*4+3].x, SLOTS[p*4+3].y + x16, x64, x32, RADIUS, RED); // On / off switch for profile
      PrintLabel(strOFF, SLOTS[p*4+3].x + x32, SLOTS[p*4+3].y + x32, 2);              // OFF label
    }  
  }
}

void UpdateSprinkleRelayChooser() {
  tft.fillRect(0, SLOT_1_1.y, WIDTH, 2 * x64 + MARGIN, BLACK); // Clear background
  // Iterate through the relays
  for (uint r = Controller.currentPage * SELECTOR_SLOTS; r < Controller.relayCount && r < (Controller.currentPage+1) * SELECTOR_SLOTS; r++){
    // === Relay background circles ===
    tft.fillCircle(SLOTS[r % SELECTOR_SLOTS].x + x32, SLOTS[r% SELECTOR_SLOTS].y + x32, x32, MAROON);
    // === Numbers ===
    PrintLabel(r + 1, SLOTS[r % SELECTOR_SLOTS].x + x32, SLOTS[r % SELECTOR_SLOTS].y + x32, 2);
  }
  // Page number label
  char temp[10];
  sprintf(temp, "%d. oldal", Controller.currentPage + 1);
  PrintLabelBg(temp, SLOT_3_3.x + x32, SLOT_3_3.y + x32, 1);
}

void UpdateSprinkleSetter() {
  // -- Hour setter number --
  tft.fillRect(SLOT_2_1.x + 8, SLOT_2_1.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.start.hours(), SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- Minute setter number --
  tft.fillRect(SLOT_2_2.x + 8, SLOT_2_2.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.start.minutes(), SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Duration setter number --
  tft.fillRect(SLOT_2_3.x + 8, SLOT_2_3.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.duration(), SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateSprinkleAutomatic() {
  // -- Hour setter number --
  tft.fillRect(SLOT_2_1.x + 8, SLOT_2_1.y + x16, x48, x32, BLACK);
  PrintLabel(Controller.temporalSetter.start.hours(), SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- Minute setter number --
  tft.fillRect(SLOT_2_2.x + 8, SLOT_2_2.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.start.minutes(), SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Duration setter number --
  tft.fillRect(SLOT_2_3.x + 8, SLOT_2_3.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.duration(), SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateChainSprinkleMenu() {
  // -- From relay setter number --
  tft.fillRect(SLOT_2_1.x + 8, SLOT_2_1.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalFromRelay + 1, SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- To relay setter number --
  tft.fillRect(SLOT_2_2.x + 8, SLOT_2_2.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalToRelay + 1, SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Duration setter number --
  tft.fillRect(SLOT_2_3.x + 8, SLOT_2_3.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.duration(), SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateTestMenu() {
  tft.fillRect(0, SLOT_1_1.y, WIDTH, 2 * x64 + MARGIN, BLACK); // Clear background
  // Iterate through the relays
  for (uint r = Controller.currentPage * SELECTOR_SLOTS; r < Controller.relayCount && r < (Controller.currentPage+1) * SELECTOR_SLOTS; r++){
    // === Backgrounds ===
    tft.fillRect(SLOTS[r % SELECTOR_SLOTS].x + 8, SLOTS[r % SELECTOR_SLOTS].y, x48, x32, BLACK);
    // === Numbers ===
    PrintLabelBg(r + 1, SLOTS[r % SELECTOR_SLOTS].x + x32, SLOTS[r % SELECTOR_SLOTS].y + x16, 2);
    // === Relay switches and labels ===
    if (Controller.temporalProfile.relays[r].state)
    {
      tft.fillRoundRect(SLOTS[r % SELECTOR_SLOTS].x, SLOTS[r % SELECTOR_SLOTS].y + x32, x64, x32, RADIUS, GREEN); // On / off switch 0.
      PrintLabel(strON, SLOTS[r % SELECTOR_SLOTS].x + x32, SLOTS[r % SELECTOR_SLOTS].y + x48, 2);                 // ON label
    }
    else
    {
      tft.fillRoundRect(SLOTS[r % SELECTOR_SLOTS].x, SLOTS[r % SELECTOR_SLOTS].y + x32, x64, x32, RADIUS, LIGHTGREY); // On / off switch 0.
      PrintLabel(strOFF, SLOTS[r % SELECTOR_SLOTS].x + x32, SLOTS[r % SELECTOR_SLOTS].y + x48, 2, BLACK);             // OFF label
    }
  }
  // Page number label
  char temp[10];
  sprintf(temp, "%d. oldal", Controller.currentPage + 1);
  PrintLabelBg(temp, SLOT_3_3.x + x32, SLOT_3_3.y + x32, 1);
}
void UpdateSettingsMenu() {
  // === Main Switch ===
  if (Controller.mainSwitch) {
    tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, RADIUS * 2, GREEN);
    PrintLabel(strON, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 3, DARKGREEN);
  }
  else
  {
    tft.fillRoundRect(SLOT_1_1.x, SLOT_1_1.y, x64, x64, RADIUS * 2, RED);
    PrintLabel(strOFF, SLOT_1_1.x + x32, SLOT_1_1.y + x32, 3);
  }
  // -- Relay count number --
  tft.fillRect(SLOT_2_2.x, SLOT_2_2.y + x16, x64, x32, BLACK);
  PrintLabel(Controller.relayCount, SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
  // -- Humidity sensitivity number --
  tft.fillRect(SLOT_2_3.x, SLOT_2_3.y + x16, x64, x32, BLACK);
  PrintLabel(Controller.humiditySensitivity, SLOT_2_3.x + x32, SLOT_2_3.y + x32, 3);
}
void UpdateClockMenu() {
  // -- Hour setter number --
  tft.fillRect(SLOT_2_1.x + 8, SLOT_2_1.y + x16, x48, x32, BLACK);
  PrintLabel(Controller.temporalSetter.start.hours(), SLOT_2_1.x + x32, SLOT_2_1.y + x32, 3);
  // -- Minute setter number --
  tft.fillRect(SLOT_2_2.x + 8, SLOT_2_2.y + x16, x48, x32, BLACK);
  PrintLabelBg(Controller.temporalSetter.start.minutes(), SLOT_2_2.x + x32, SLOT_2_2.y + x32, 3);
}

// ---- Display helper functions ----
void PrintRTCToMainScreen() {
  char temp[9];
  sprintf(temp, "%02d:%02d:%02d", Controller.now.hour(), Controller.now.minute(), Controller.now.second());
  tft.fillRect(CENTER_H - GetTextWidth(temp, 2) / 2 - 1, CENTER_V + x16 - GetTextHeight(2) / 2 - 1, GetTextWidth(temp, 2) + 2, GetTextHeight(2) + 2, BLACK);
  PrintLabel(temp, CENTER_H, CENTER_V + x16, 2);
}
void PrintLabel(const char *label, const int x, const int y, const int fontSize, const uint16_t color) {
  tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y - GetTextHeight(fontSize) / 2);
  tft.setTextColor(color);
  tft.setTextSize(fontSize);
  tft.print(label);
}
void PrintLabelBg(const char *label, const int x, const int y, const int fontSize, const uint16_t color, const uint16_t bgColor) {
  tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y - GetTextHeight(fontSize) / 2);
  tft.setTextColor(color, bgColor);
  tft.setTextSize(fontSize);
  tft.print(label);
}
void PrintLabel(const int labelValue, const int x, const int y, const int fontSize, const uint16_t color) {
  char temp[7];
  sprintf(temp, "%d", labelValue);
  PrintLabel(temp, x, y, fontSize, color);
}
void PrintLabelBg(const int labelValue, const int x, const int y, const int fontSize, const uint16_t color, const uint16_t bgColor) {
  char temp[7];
  sprintf(temp, "%d", labelValue);
  PrintLabelBg(temp, x, y, fontSize, color, bgColor);
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
  tft.fillRect(SUBMENU_HOME_POS.x + 6, SUBMENU_HOME_POS.y + x16, 20, 14, CYAN);
  tft.fillTriangle(SUBMENU_HOME_POS.x + 2, SUBMENU_HOME_POS.y + x16, SUBMENU_HOME_POS.x + x16, SUBMENU_HOME_POS.y + 2, SUBMENU_HOME_POS.x + x32 - 2, SUBMENU_HOME_POS.y + x16, CYAN);
}
int GetTextWidth(const char *text, const int fontSize) {
  return strlen(text) * FONT_1_H * fontSize + (strlen(text) - 1) * fontSize;
}
int GetTextHeight(const int fontSize) {
  return FONT_1_V * fontSize;
}