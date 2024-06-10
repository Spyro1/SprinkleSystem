// ******** menu.ino ********

// ==== Declaration ====

// ==== Menu functions ====

void RunMenu(){
  DrawMainMenu();
}

void ExecuteClickEvent(const struct Point& clickPos) {
  switch(Controller.state) {
    case sprinkleProfiles:
      // Automatic timing button
      if (clickPos == BTN_1_1 || clickPos == BTN_2_1 || clickPos == BTN_3_1) {
        debugln("AutomaticTiming_Clicked");
        Controller.state = sprinkleAuto;
        Controller.currentProfile = clickPos.y;
        Controller.DrawStateScreen();
      }
      // Period On/Off buttons
      else if (clickPos == BTN_1_4 || clickPos == BTN_2_4 || clickPos == BTN_3_4) {
        int indexer = clickPos.y - 1;
        Controller.profiles[indexer].isActive = !Controller.profiles[indexer].isActive;
        Controller.UpdateStatesScreen(); // Updates ON/OFF button text and color
      }
      // Period editor
      else if (clickPos == BTN_1_2 || clickPos == BTN_1_3 || clickPos == BTN_2_2 || clickPos == BTN_2_3 || clickPos == BTN_3_2 || clickPos == BTN_3_3) {
        Controller.currentProfile = clickPos.y;
        Controller.state = sprinkleRelays;
        Controller.DrawStateScreen();
      }
      break;
    case sprinkleRelays:
      // Navigating buttons < | >
      if (clickPos == BTN_3_1 || clickPos == BTN_3_4) {
        Controller.currentPage = Controller.currentPage == 1 ? 2 : 1;
        Controller.DrawStateScreen();
      }
      // Relay chooser buttons
      else if (clickPos.y < 3) {
        Controller.state = sprinkleSetter;
        Controller.currentRelay = ((Controller.currentPage - 1) * 8) + clickPos.x + (clickPos.y - 1) * 4;
        Controller.DrawStateScreen();
      }
      break;
    case sprinkleSetter:
      // Increase hour field
      if (clickPos == BTN_1_1) Controller.CurrentRelay().ChangeStartHour(1);
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.CurrentRelay().ChangeStartHour(-1);
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.CurrentRelay().ChangeStartMinute(1);
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.CurrentRelay().ChangeStartMinute(-1);
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.CurrentRelay().ChangeDuration(1);
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.CurrentRelay().ChangeDuration(-1);
      // Save and back
      else if (clickPos == BTN_1_4 || clickPos == BTN_3_4) {
        // Save pressed
        if (clickPos == BTN_1_4) SaveRelayData(Controller.CurrentRelay(), Controller.currentRelay, Controller.currentProfile);
        // Reload relay data upon exit
        else if (clickPos == BTN_3_4) LoadRelayData(Controller.CurrentRelay(), Controller.currentRelay, Controller.currentProfile);
        Controller.state = sprinkleRelays;
      }
      break;
    case sprinkleAuto:
      // Increase hour field
      if (clickPos == BTN_1_1) Controller.ChangeTempStartHour(1);
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.ChangeTempStartHour(-1);
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.ChangeTempStartMinute(1);
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.ChangeTempStartMinute(-1);
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.ChangeTempDuration(1);
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.ChangeTempDuration(-1);
      // Save and back
      else if (clickPos == BTN_1_4 || clickPos == BTN_3_4) {
        // Save pressed
        if (clickPos == BTN_1_4) {
          for (int r = 0; r < RELAY_COUNT; r++) {
            Controller.profiles[Controller.currentProfile].relays[r].start = Controller.temporalStart + Controller.temporalDuration * r; // set starting time in a automatic chain
            Controller.profiles[Controller.currentProfile].relays[r].duration = Controller.temporalDuration * r; // set duration
            SaveRelayData(Controller.profiles[Controller.currentProfile].relays[r], Controller.currentProfile, r); // Saves changed data to EEPROM
          }
        }
        Controller.state = sprinkleProfiles;
        Controller.DrawStateScreen();
        break; // Exit
      }
      Controller.UpdateStatesScreen(); // Updates field numbers on screen (hour, minute, duration)
      break;
    case chainSprinkler:
      // Increase hour field
      if (clickPos == BTN_1_1) Controller.ChangeTempStartHour(1);
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.ChangeTempStartHour(-1);
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.ChangeTempStartMinute(1);
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.ChangeTempStartMinute(-1);
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.ChangeTempDuration(1);
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.ChangeTempDuration(-1);
      // Save and back
      else if (clickPos == BTN_1_4 || clickPos == BTN_3_4) {
        // Save pressed
        if (clickPos == BTN_1_4) {
          Controller.temporalProfile.isActive = true;
          for (int r = 0; r < RELAY_COUNT; r++) {
            Controller.temporalProfile.relays[r].start = Controller.temporalStart + Controller.temporalDuration * r; // set temporalkstarting times
            Controller.temporalProfile.relays[r].duration = Controller.temporalDuration * r; // set temporal chain durations
          }
        }
        Controller.state = sprinkleProfiles;
        Controller.DrawStateScreen();
        break; // Exit
      }
      Controller.UpdateStatesScreen(); // Updates field numbers on screen (hour, minute, duration)
      break;
    case test:
      // Navigating buttons < | >
      if (clickPos == BTN_3_1 || clickPos == BTN_3_4) {
        Controller.currentPage = Controller.currentPage == 1 ? 2 : 1;
        Controller.UpdateStatesScreen(); // Updates numbers of test switches
      }
      // Reset all switches to off
      else if (clickPos == BTN_3_2){
        for (int r = 0; r < RELAY_COUNT; r++){
          Controller.temporalProfile.relays[r].SetRelayState(false);
        }
      }
      // Test Relay chooser buttons
      else if (clickPos.y < 3) {
        Controller.currentRelay = ((Controller.currentPage - 1) * 8) + clickPos.x + (clickPos.y - 1) * 4;
        Controller.temporalProfile.relays[Controller.currentRelay].SetRelayState(!Controller.temporalProfile.relays[Controller.currentRelay].state); // Switch state
        Controller.UpdateStatesScreen(); // Updates the on/off state of a switch
      }
      break;
    case humidity:
      break;
    case settings:
      break;
    case clock:
      break;

  }
}