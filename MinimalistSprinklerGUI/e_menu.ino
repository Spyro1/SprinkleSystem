// ******** menu.ino ********

// ==== Menu functions ====

void (*resetFunc)(void) = 0; // declare reset function @ address 0

void RunMenu()
{
  DrawMainMenu();
}
void ExecuteMainMenuClickEvents(const int idx)
{
  switch (idx)
  {
  case 0: // Sprinkle btn
    Controller.state = sprinkleProfiles;
    DrawSprinkleProfilesMenu();
    break;
  case 1: // Chain btn
    Controller.state = chainSprinkler;
    Controller.temporalFromRelay = 0;
    Controller.temporalToRelay = Controller.relayCount - 1;
    Controller.temporalSetter.duration = 0;
    DrawChainSprinkleMenu();
    break;
  case 2: // Test btn
    Controller.state = testSprinkler;
    DrawTestMenu();
    break;
  case 3: // Settings btn
    Controller.state = settings;
    DrawSettingsMenu();
    break;
  case 4: // Save changes button
    Controller.SaveChanges();
    UpdateMainMenu();
    break;
  case 5: // Clock btn
    Controller.state = clockSetter;
    Controller.temporalSetter.start.hour = Controller.now.hour();
    Controller.temporalSetter.start.minute = Controller.now.minute();
    DrawClockMenu();
    break;
  }
}

void ExecuteSubMenuClickEvents(const struct Point &clickPos)
{
  switch (Controller.state)
  {
  case sprinkleProfiles:
    // Automatic timing buttons
    if (clickPos == BTN_1_1 || clickPos == BTN_2_1 || clickPos == BTN_3_1)
    {
      Controller.state = sprinkleAuto;
      Controller.currentProfile = clickPos.y;
      Controller.temporalSetter = Controller.profiles[Controller.currentProfile].relays[0];
      DrawSprinkleAutomatic();
    }
    // Profile On/Off buttons
    else if (clickPos == BTN_1_4 || clickPos == BTN_2_4 || clickPos == BTN_3_4)
    {
      Controller.profiles[clickPos.y].isActive = !Controller.profiles[clickPos.y].isActive;
      UpdateSprinkleProfilesMenu();     // Updates ON/OFF button text and color
      Controller.unsavedChanges = true; // New changes were made
    }
    // Profile editor
    else if (clickPos == BTN_1_2 || clickPos == BTN_1_3 || clickPos == BTN_2_2 || clickPos == BTN_2_3 || clickPos == BTN_3_2 || clickPos == BTN_3_3)
    {
      Controller.state = sprinkleRelays;
      Controller.currentProfile = clickPos.y;
#if DEBUG == 1
      // --- Debug ---
      for (int i = 0; i < Controller.relayCount; i++)
      {
        char temp[50];
        sprintf(temp, "%d/%d:\tid: %d\tP: %d\tS: %02d:%02d\tD: %d\tState: %d", Controller.currentProfile, i, Controller.profiles[Controller.currentProfile].relays[i].id,
                Controller.profiles[Controller.currentProfile].relays[i].pin, Controller.profiles[Controller.currentProfile].relays[i].start.hours(), Controller.profiles[Controller.currentProfile].relays[i].start.minutes(),
                Controller.profiles[Controller.currentProfile].relays[i].duration(), Controller.profiles[Controller.currentProfile].relays[i].state);
        debugvln(temp);
      }
#endif
      DrawSprinkleRelayChooser(); // Draw relay chooser screen
    }
    break;
  case sprinkleRelays:
    // Navigating buttons LEFT <
    if (clickPos == BTN_3_1 && Controller.currentPage > 0) {
      Controller.currentPage--;
      UpdateSprinkleRelayChooser();
    }
    // Navigating buttons RIGHT >
    else if (clickPos == BTN_3_2 && Controller.currentPage < (Controller.relayCount-1) / 8) {
      Controller.currentPage++;
      UpdateSprinkleRelayChooser();
    }
    // Back to Profile chooser menu
    else if (clickPos == BTN_3_4)
    {
      Controller.state = sprinkleProfiles;
      DrawSprinkleProfilesMenu();
    }
    // Relay chooser buttons
    else if (clickPos.y < 2) {
      Controller.state = sprinkleSetter;
      Controller.currentRelay = ((Controller.currentPage) * SELECTOR_SLOTS) + (clickPos.y) * 4 + (clickPos.x);
      if (Controller.currentRelay < Controller.relayCount){
        Controller.temporalSetter = Controller.CurrentRelay();
        DrawSprinkleSetter();
      }
    }
    break;
  case sprinkleSetter:
    // Increase hour field
    if (clickPos == BTN_1_1)
      Controller.temporalSetter.start.hour++;
    // Decrease hour field
    else if (clickPos == BTN_3_1)
      Controller.temporalSetter.start.hour--;
    // Increase minute field
    else if (clickPos == BTN_1_2)
      Controller.temporalSetter.start.minute++;
    // Decrease minute field
    else if (clickPos == BTN_3_2)
      Controller.temporalSetter.start.minute--;
    // Increase duration field
    else if (clickPos == BTN_1_3)
      Controller.temporalSetter.duration++;
    // Decrease duration field
    else if (clickPos == BTN_3_3)
      Controller.temporalSetter.duration--;
    // Save and back
    else if (clickPos == BTN_1_4 || clickPos == BTN_3_4)
    {
      // Save pressed
      if (clickPos == BTN_1_4)
      {
        Controller.CurrentRelay() = Controller.temporalSetter;
        Controller.unsavedChanges = true;
      }
      Controller.state = sprinkleRelays;
      DrawSprinkleRelayChooser();
      break;
    }
    UpdateSprinkleSetter(); // Updates field numbers on screen (hour, minute, duration)
    break;
  case sprinkleAuto:
    // Increase hour field
    if (clickPos == BTN_1_1)
      Controller.temporalSetter.start.hour++;
    // Decrease hour field
    else if (clickPos == BTN_3_1)
      Controller.temporalSetter.start.hour--;
    // Increase minute field
    else if (clickPos == BTN_1_2)
      Controller.temporalSetter.start.minute++;
    // Decrease minute field
    else if (clickPos == BTN_3_2)
      Controller.temporalSetter.start.minute--;
    // Increase duration field
    else if (clickPos == BTN_1_3)
      Controller.temporalSetter.duration++;
    // Decrease duration field
    else if (clickPos == BTN_3_3)
      Controller.temporalSetter.duration--;
    // Save and back
    else if (clickPos == BTN_1_4 || clickPos == BTN_3_4)
    {
      // Save pressed
      if (clickPos == BTN_1_4)
      {
        for (uint r = 0; r < Controller.relayCount; r++)
        {
          Controller.profiles[Controller.currentProfile].relays[r].start = Controller.temporalSetter.start + (Controller.temporalSetter.duration() * r); // set starting time in a automatic chain
          Controller.profiles[Controller.currentProfile].relays[r].duration = Controller.temporalSetter.duration;                                        // set duration
          Controller.unsavedChanges = true;                                                                                                              // Modified automatic setting
        }
      }
      Controller.state = sprinkleProfiles;
      DrawSprinkleProfilesMenu();
      break; // Exit
    }
    UpdateSprinkleAutomatic(); // Updates field numbers on screen (hour, minute, duration)
    break;
  case chainSprinkler:
    // Increase hour field
    if (clickPos == BTN_1_1 && Controller.temporalFromRelay < Controller.temporalToRelay && Controller.temporalFromRelay < Controller.relayCount - 1)
      Controller.temporalFromRelay++;
    // Decrease hour field
    else if (clickPos == BTN_3_1 && Controller.temporalFromRelay > 0)
      Controller.temporalFromRelay--;
    // Increase minute field
    else if (clickPos == BTN_1_2 && Controller.temporalToRelay < Controller.relayCount - 1)
      Controller.temporalToRelay++;
    // Decrease minute field
    else if (clickPos == BTN_3_2 && Controller.temporalFromRelay < Controller.temporalToRelay && Controller.temporalToRelay > 0)
      Controller.temporalToRelay--;
    // Increase duration field
    else if (clickPos == BTN_1_3)
      Controller.temporalSetter.duration++;
    // Decrease duration field
    else if (clickPos == BTN_3_3)
      Controller.temporalSetter.duration--;
    // Start button pressed
    else if (clickPos == BTN_1_4)
    {
      Controller.temporalProfile.isActive = true;
      Controller.temporalSetter.start = Time(Controller.now.hour(), Controller.now.minute() + 1);
      for (uint r = 0; r < Controller.relayCount; r++)
      {
        if (r >= Controller.temporalFromRelay && r <= Controller.temporalToRelay)
        {                                                                                                                                                           // Set timing to selected range
          Controller.temporalProfile.relays[r].start = Controller.temporalSetter.start + Controller.temporalSetter.duration() * (r - Controller.temporalFromRelay); // set temporalkstarting times
          Controller.temporalProfile.relays[r].duration = Controller.temporalSetter.duration;                                                                       // set temporal chain durations
        }
        else
        { // Set zero duration to the others
          Controller.temporalProfile.relays[r].start = 0;
          Controller.temporalProfile.relays[r].duration = 0;
        }
      }
#if DEBUG == 1
      // --- Debug ---
      debugln("Chain Temp:");
      for (uint i = 0; i < Controller.relayCount; i++)
      {
        char temp[50];
        sprintf(temp, "%d:\tid: %d\tP: %d\tS: %02d:%02d\tD: %d\tState: %d", i, Controller.temporalProfile.relays[i].id, Controller.temporalProfile.relays[i].pin,
                Controller.temporalProfile.relays[i].start.hours(), Controller.temporalProfile.relays[i].start.minutes(), Controller.temporalProfile.relays[i].duration(), Controller.temporalProfile.relays[i].state);
        debugvln(temp);
      }
#endif
      Controller.state = mainMenu;
      DrawMainMenu();
      break; // Exit
    }
    // stop chain spriknle and turn off temporal profile
    else if (clickPos == BTN_3_4)
    {
      Controller.temporalProfile.isActive = false;
      for (uint r = 0; r < Controller.relayCount; r++)
      {
        Controller.temporalProfile.relays[r].SetRelayState(false);
        Controller.temporalProfile.relays[r].start = 0;
        Controller.temporalProfile.relays[r].duration = 0;
      }
      debugln("Chain stopped");
    }
    UpdateChainSprinkleMenu(); // Updates field numbers on screen (hour, minute, duration)
    break;
  case testSprinkler:
    // Navigating buttons LEFT <
    if (clickPos == BTN_3_1 && Controller.currentPage > 0) {
      Controller.currentPage--;
      UpdateTestMenu(); // Updates numbers of test switches
    }
    // Navigating buttons RIGHT >
    else if (clickPos == BTN_3_2 && Controller.currentPage < (Controller.relayCount-1) / SELECTOR_SLOTS) {
      Controller.currentPage++;
      UpdateTestMenu(); // Updates numbers of test switches
    }
    // Reset all switches to off
    else if (clickPos == BTN_3_4)
    {
      for (uint r = 0; r < Controller.relayCount; r++)
      {
        Controller.temporalProfile.relays[r].SetRelayState(false);
      }
      UpdateTestMenu(); // Updates numbers of test switches
    }
    // Test Relay chooser buttons
    else if (clickPos.y < 2)
    {
      Controller.currentRelay = ((Controller.currentPage) * SELECTOR_SLOTS) + (clickPos.x) + (clickPos.y) * 4;
      if (Controller.currentRelay < Controller.relayCount){
        Controller.temporalProfile.relays[Controller.currentRelay].SetRelayState(!Controller.temporalProfile.relays[Controller.currentRelay].state); // Switch state
        UpdateTestMenu(); // Updates the on/off state of a switch
      }
    }
    break;
  case settings:
    if (clickPos == BTN_1_1)
    {
      Controller.mainSwitch = !Controller.mainSwitch;
      Controller.unsavedChanges = true; // New changes were made
      UpdateSettingsMenu();             // Updates settings screen
    }
    // Change relay count number
    else if (clickPos == BTN_1_2 && Controller.relayCount < MAX_RELAY_COUNT) {
      Controller.relayCount++;
      Controller.unsavedChanges = true; // New changes were made
      UpdateSettingsMenu(); // Updates settings screen
    }
    else if (clickPos == BTN_3_2 && Controller.relayCount > 1) {
      Controller.relayCount--;
      Controller.unsavedChanges = true; // New changes were made
      UpdateSettingsMenu(); // Updates settings screen
    }
    // Change humidity sensitivity
    else if (clickPos == BTN_1_3)
    {
      Controller.humiditySensitivity += 4;
      Controller.unsavedChanges = true; // New changes were made
      UpdateSettingsMenu();             // Updates settings screen
    }
    else if (clickPos == BTN_3_3)
    {
      Controller.humiditySensitivity -= 4;
      Controller.unsavedChanges = true; // New changes were made
      UpdateSettingsMenu();             // Updates settings screen
    }
    // Developer button
    else if (clickPos == BTN_3_1)
    {
      Controller.state = developer;
      DrawDeveloperMenu();
    }
    else if (clickPos == BTN_3_4)
    {
      resetFunc(); // call reset
    }
    break;
  case clockSetter:
    // Increase hour field
    if (clickPos == BTN_1_1)
      Controller.temporalSetter.start.hour++;
    // Decrease hour field
    else if (clickPos == BTN_3_1)
      Controller.temporalSetter.start.hour--;
    // Increase minute field
    else if (clickPos == BTN_1_2)
      Controller.temporalSetter.start.minute++;
    // Decrease minute field
    else if (clickPos == BTN_3_2)
      Controller.temporalSetter.start.minute--;
    // Save changes
    else if (clickPos == BTN_2_4)
    {
      Controller.state = mainMenu;
      Controller.now = DateTime(2024, 1, 1, Controller.temporalSetter.start.hours(), Controller.temporalSetter.start.minutes(), 0);
      rtc.adjust(Controller.now);
      DrawMainMenu();
      break;
    }
    UpdateClockMenu(); // Updates field numbers on screen (hour, minute, duration)
    break;
  case developer:
    // -- List timed profiles button --
    if (clickPos == BTN_1_1)
    {
      Serial.println(F("= Idozitett profilok listaztasa ="));
      for (int p = 0; p < PROFILE_COUNT; p++)
      {
        Serial.print(F("- Profil "));
        Serial.print(p);
        Serial.print(F(" isActive: \t"));
        Serial.println(Controller.temporalProfile.isActive);
        Serial.println(F(". -"));
        for (uint r = 0; r < Controller.relayCount; r++)
        {
          char temp[50];
          sprintf(temp, " %d/%d:\tID: %d\tPin: %d \tS: %02d:%02d \tD: %d \tState: %d", p, r, Controller.profiles[p].relays[r].id,
                  Controller.profiles[p].relays[r].pin, Controller.profiles[p].relays[r].start.hours(), Controller.profiles[p].relays[r].start.minutes(),
                  Controller.profiles[p].relays[r].duration(), Controller.profiles[p].relays[r].state);
          Serial.println(temp);
        }
      }
    }
    // -- List temporal profiles button --
    else if (clickPos == BTN_1_2)
    {
      Serial.println(F("= Temporal profil listazasa ="));
      Serial.print(F("isActive: \t"));
      Serial.println(Controller.temporalProfile.isActive);
      for (uint i = 0; i < Controller.relayCount; i++)
      {
        char temp[50];
        sprintf(temp, " %d:\tID: %d\tPin: %d \tS: %02d:%02d \tD: %d \tState: %d", i, Controller.temporalProfile.relays[i].id, Controller.temporalProfile.relays[i].pin,
                Controller.temporalProfile.relays[i].start.hours(), Controller.temporalProfile.relays[i].start.minutes(), Controller.temporalProfile.relays[i].duration(), Controller.temporalProfile.relays[i].state);
        debugvln(temp);
      }
    }
    // -- List Controller fields --
    else if (clickPos == BTN_1_3)
    {
      Serial.println(F("= Controller mezoinek listazasa ="));
      Serial.print(F(" MainSwitch: \t\t"));
      Serial.println(Controller.mainSwitch);
      Serial.print(F(" HumiditySensitivity: \t"));
      Serial.println(Controller.humiditySensitivity);
      Serial.print(F(" now: \t\t\t"));
      Serial.print(Controller.now.hour());
      Serial.print(":");
      Serial.println(Controller.now.minute());
      Serial.print(F(" unsavedChanges: \t"));
      Serial.println(Controller.unsavedChanges);
      Serial.print(F(" temporalSetter: \t"));
      char temp[50];
      sprintf(temp, "ID: %d\tPin: %d \tS: %02d:%02d \tD: %d \tState: %d", Controller.temporalSetter.id, Controller.temporalSetter.pin, Controller.temporalSetter.start.hours(), Controller.temporalSetter.start.minutes(), Controller.temporalSetter.duration(), Controller.temporalSetter.state);
      Serial.println(temp);
    }
    else if (clickPos == BTN_1_4)
    {
      Serial.println(F("= Relek állapota ="));
      for (uint r = 0; r < Controller.relayCount; r++)
      {
        char temp[50];
        bool isActive = false;
        for (int p = 0; p < PROFILE_COUNT; p++)
        {
          if (Controller.profiles[p].relays[r].state)
          {
            isActive = true;
            break;
          }
        }
        if (Controller.temporalProfile.relays[r].state)
          isActive = true;
        sprintf(temp, " Rele: %d \tPin: %d \tState: %d", r, RELAY_PINS[r], isActive);
        Serial.println(temp);
      }
    }
    else if (clickPos == BTN_3_4)
    {
      Controller.state = settings;
      DrawSettingsMenu();
    }
    break;
  case mainMenu:
  default: // No function here
    break;
  }
}