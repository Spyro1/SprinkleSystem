// ******** menu.ino ********

// ==== Declaration ====

// ==== Menu functions ====

void RunMenu(){
  DrawMainMenu();
}
void ExecuteMainMenuClickEvents(const int idx){
  switch (idx){
    case 0: // Sprinkle btn
      Controller.state = sprinkleProfiles;
      Controller.DrawStateScreen();
      break;
    case 1: // Chain btn
      Controller.state = chainSprinkler;
      Controller.temporalFromRelay = 0;
      Controller.temporalToRelay = RELAY_COUNT - 1;
      Controller.temporalSetter.duration = 0;
      Controller.temporalProfile.isActive = false;
      for (uint i = 0; i < RELAY_COUNT; i++){
        Controller.temporalProfile.relays[i].reset();
        Controller.temporalProfile.relays[i].SetRelayState(false);
      }
      Controller.DrawStateScreen();
      break;
    case 2: // Test btn
      Controller.state = testSprinkler;
      // Setup every switch for current state
      // for (uint i = 0; i < RELAY_COUNT; i++) {
      //   bool isActive = false;
      //   for(uint p = 0; p < PROFILE_COUNT; p++){
      //     if (Controller.profiles[p].relays[i].state) { isActive = true; break; }
      //   }
      //   Controller.temporalProfile.relays[i].state = isActive;
      // }
      Controller.DrawStateScreen();
      break;
    case 3: // Settings btn
      Controller.state = settings;
      Controller.DrawStateScreen();
      break;
    case 4: // Save changes button
      Controller.SaveChanges();
      UpdateMainMenu();
      break;
    case 5: // Clock btn
      Controller.state = clockSetter;
      Controller.temporalSetter.start.hour = Controller.now.hour();
      Controller.temporalSetter.start.minute = Controller.now.minute();
      Controller.DrawStateScreen();
      break;
  }
}

void ExecuteSubMenuClickEvents(const struct Point& clickPos) {
  switch(Controller.state) {
    case sprinkleProfiles:
      // Automatic timing buttons
      if (clickPos == BTN_1_1 || clickPos == BTN_2_1 || clickPos == BTN_3_1) {
        // debugv(clickPos.y); debugln(". AutoTiming_Clicked"); // Debug
        Controller.state = sprinkleAuto;
        Controller.currentProfile = clickPos.y;
        Controller.temporalSetter = Controller.profiles[Controller.currentProfile].relays[0];
        Controller.DrawStateScreen();
      }
      // Profile On/Off buttons
      else if (clickPos == BTN_1_4 || clickPos == BTN_2_4 || clickPos == BTN_3_4) {
        // debugv(clickPos.y); debugln(". Profile_Clicked"); // Debug
        Controller.profiles[clickPos.y].isActive = !Controller.profiles[clickPos.y].isActive;
        Controller.UpdateStateScreen(); // Updates ON/OFF button text and color
        Controller.unsavedChanges = true; // New changes were made
      }
      // Profile editor
      else if (clickPos == BTN_1_2 || clickPos == BTN_1_3 || clickPos == BTN_2_2 || clickPos == BTN_2_3 || clickPos == BTN_3_2 || clickPos == BTN_3_3) {
        Controller.state = sprinkleRelays;
        Controller.currentProfile = clickPos.y;
        // --- Debug ---
        for(int i = 0; i < RELAY_COUNT; i++){
          char temp[50];
          sprintf(temp, "%d/%d:\tid: %d\tP: %d\tS: %02d:%02d\tD: %d\tState: %d", Controller.currentProfile, i, Controller.profiles[Controller.currentProfile].relays[i].id, 
          Controller.profiles[Controller.currentProfile].relays[i].pin, Controller.profiles[Controller.currentProfile].relays[i].start.hours(), Controller.profiles[Controller.currentProfile].relays[i].start.minutes(),
          Controller.profiles[Controller.currentProfile].relays[i].duration(), Controller.profiles[Controller.currentProfile].relays[i].state);
          debugvln(temp);
        }
        Controller.DrawStateScreen(); // Draw relay chooser screen
      }
      break;
    case sprinkleRelays:
      // Navigating buttons < | >
      if (clickPos == BTN_3_1 || clickPos == BTN_3_2) {
        Controller.currentPage = Controller.currentPage == 0 ? 1 : 0;
        Controller.UpdateStateScreen();
      }
      // Back to Profile chooser menu
      else if (clickPos == BTN_3_4){
        Controller.state = sprinkleProfiles;
        Controller.DrawStateScreen();
      }
      // Relay chooser buttons
      else if (clickPos.y < 2) {
        Controller.state = sprinkleSetter;
        Controller.currentRelay = ((Controller.currentPage) * 8) + (clickPos.y) * 4 + (clickPos.x);
        Controller.temporalSetter = Controller.CurrentRelay(); // .profiles[Controller.currentProfile].relays[Controller.currentRelay];
        Controller.DrawStateScreen();
      }
      break;
    case sprinkleSetter:
      // Increase hour field
      if (clickPos == BTN_1_1) Controller.temporalSetter.start.hour++;
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.temporalSetter.start.hour--;
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.temporalSetter.start.minute++;
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.temporalSetter.start.minute--;
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.temporalSetter.duration++;
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.temporalSetter.duration--;
      // Save and back
      else if (clickPos == BTN_1_4 || clickPos == BTN_3_4) {
        // Save pressed
        if (clickPos == BTN_1_4) {
          Controller.CurrentRelay() = Controller.temporalSetter;
          Controller.unsavedChanges = true; 
        }
          // new changes were made // SaveRelayData(Controller.CurrentRelay(), Controller.currentRelay, Controller.currentProfile);
        // NOO // Reload relay data upon exit
        //else if (clickPos == BTN_3_4) LoadRelayData(Controller.CurrentRelay(), Controller.currentRelay, Controller.currentProfile);
        Controller.state = sprinkleRelays;
        Controller.DrawStateScreen();
        break;
      }
      Controller.UpdateStateScreen(); // Updates field numbers on screen (hour, minute, duration)
      break;
    case sprinkleAuto:
      // Increase hour field
      if (clickPos == BTN_1_1) Controller.temporalSetter.start.hour++;
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.temporalSetter.start.hour--;
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.temporalSetter.start.minute++;
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.temporalSetter.start.minute--;
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.temporalSetter.duration++;
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.temporalSetter.duration--;
      // Save and back
      else if (clickPos == BTN_1_4 || clickPos == BTN_3_4) {
        // Save pressed
        if (clickPos == BTN_1_4) {
          for (uint r = 0; r < RELAY_COUNT; r++) {
            Controller.profiles[Controller.currentProfile].relays[r].start = Controller.temporalSetter.start + (Controller.temporalSetter.duration() * r); // set starting time in a automatic chain
            Controller.profiles[Controller.currentProfile].relays[r].duration = Controller.temporalSetter.duration; // set duration
            Controller.unsavedChanges = true; // Modified automatic setting
            //SaveRelayData(Controller.profiles[Controller.currentProfile].relays[r], Controller.currentProfile, r); // Saves changed data to EEPROM
          }
        }
        Controller.state = sprinkleProfiles;
        Controller.DrawStateScreen();
        break; // Exit
      }
      Controller.UpdateStateScreen(); // Updates field numbers on screen (hour, minute, duration)
      break;
    case chainSprinkler:
      // Increase hour field
      if (clickPos == BTN_1_1 && Controller.temporalFromRelay < Controller.temporalToRelay && Controller.temporalFromRelay < RELAY_COUNT - 1) Controller.temporalFromRelay++;
      // Decrease hour field
      else if (clickPos == BTN_3_1 && Controller.temporalFromRelay > 0) Controller.temporalFromRelay--;
      // Increase minute field
      else if (clickPos == BTN_1_2 && Controller.temporalToRelay < RELAY_COUNT - 1) Controller.temporalToRelay++;
      // Decrease minute field
      else if (clickPos == BTN_3_2 && Controller.temporalFromRelay < Controller.temporalToRelay && Controller.temporalToRelay > 0) Controller.temporalToRelay--;
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.temporalSetter.duration++;
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.temporalSetter.duration--;
      // Start button pressed
      else if (clickPos == BTN_2_4) {
        Controller.temporalProfile.isActive = true;
        Controller.temporalSetter.start = Time(Controller.now.hour(), Controller.now.minute());
        for (uint r = 0; r < RELAY_COUNT; r++) {
          Controller.temporalProfile.relays[r].start = Controller.temporalSetter.start + Controller.temporalSetter.duration() * r; // set temporalkstarting times
          Controller.temporalProfile.relays[r].duration = Controller.temporalSetter.duration; // set temporal chain durations
        }        
        // --- Debug ---
        debugln("Chain Temp:");
        for(int i = 0; i < RELAY_COUNT; i++){
          char temp[50];
          sprintf(temp, "%d:\tid: %d\tP: %d\tS: %02d:%02d\tD: %d\tState: %d", i, Controller.temporalProfile.relays[i].id, Controller.temporalProfile.relays[i].pin,
          Controller.temporalProfile.relays[i].start.hours(), Controller.temporalProfile.relays[i].start.minutes(), Controller.temporalProfile.relays[i].duration(), Controller.temporalProfile.relays[i].state);
          debugvln(temp);
        }
        Controller.state = mainMenu;
        Controller.DrawStateScreen();
        break; // Exit
      }
      Controller.UpdateStateScreen(); // Updates field numbers on screen (hour, minute, duration)
      break;
    case testSprinkler:
      // Navigating buttons < | >
      if (clickPos == BTN_3_1 || clickPos == BTN_3_2) {
        Controller.currentPage = Controller.currentPage == 0 ? 1 : 0;
        Controller.UpdateStateScreen(); // Updates numbers of test switches
      }
      // Reset all switches to off
      else if (clickPos == BTN_3_4){
        for (int r = 0; r < RELAY_COUNT; r++){
          Controller.temporalProfile.relays[r].SetRelayState(false);
        }
        Controller.UpdateStateScreen(); // Updates numbers of test switches
      }
      // Test Relay chooser buttons
      else if (clickPos.y < 2) {
        Controller.currentRelay = ((Controller.currentPage) * 8) + (clickPos.x) + (clickPos.y) * 4;
        Controller.temporalProfile.relays[Controller.currentRelay].SetRelayState(!Controller.temporalProfile.relays[Controller.currentRelay].state); // Switch state
        Controller.UpdateStateScreen(); // Updates the on/off state of a switch
      }
      break;
    case settings:
      if (clickPos == BTN_1_2){
        Controller.mainSwitch = !Controller.mainSwitch;
        Controller.unsavedChanges = true; // New changes were made
        Controller.UpdateStateScreen(); // Updates settings screen
      }
      // Change humidity sensitivity
      if (clickPos == BTN_1_3) {
        Controller.humiditySensitivity += 4;
        Controller.unsavedChanges = true; // New changes were made
        Controller.UpdateStateScreen(); // Updates settings screen
      }
      else if (clickPos == BTN_3_3){
        Controller.humiditySensitivity -= 4;
        Controller.unsavedChanges = true; // New changes were made
        Controller.UpdateStateScreen(); // Updates settings screen
      }
      break;
    case clockSetter:
      // Increase hour field
      if (clickPos == BTN_1_1) Controller.temporalSetter.start.hour++;
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.temporalSetter.start.hour--;
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.temporalSetter.start.minute++;
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.temporalSetter.start.minute--;
      // Save changes
      else if (clickPos == BTN_2_4) {
        Controller.state = mainMenu;
        Controller.now = DateTime(2024,1,1, Controller.temporalSetter.start.hours(), Controller.temporalSetter.start.minutes(), 0);
        rtc.adjust(Controller.now);
        Controller.DrawStateScreen();
        break;
      }
      Controller.UpdateStateScreen(); // Updates field numbers on screen (hour, minute, duration)
      break;
    case mainMenu: 
    default: // No function here
      break;
  }
}