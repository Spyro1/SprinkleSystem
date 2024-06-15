// ******** menu.ino ********

// ==== Declaration ====

// ==== Menu functions ====

void RunMenu(){
  DrawMainMenu();
}

void ExecuteClickEvent(const struct Point& clickPos) {
  switch(Controller.state) {
    case mainMenu:
      break;
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
      if (clickPos == BTN_1_1) Controller.CurrentRelay().start.hour++;
      // Decrease hour field
      else if (clickPos == BTN_3_1) Controller.CurrentRelay().start.hour--;
      // Increase minute field
      else if (clickPos == BTN_1_2) Controller.CurrentRelay().start.minute++;
      // Decrease minute field
      else if (clickPos == BTN_3_2) Controller.CurrentRelay().start.minute--;
      // Increase duration field
      else if (clickPos == BTN_1_3) Controller.CurrentRelay().duration++;
      // Decrease duration field
      else if (clickPos == BTN_3_3) Controller.CurrentRelay().duration--;
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
            Controller.profiles[Controller.currentProfile].relays[r].start = Controller.temporalSetter.start + Controller.temporalSetter.duration * r; // set starting time in a automatic chain
            Controller.profiles[Controller.currentProfile].relays[r].duration = Controller.temporalSetter.duration; // set duration
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
          Controller.temporalProfile.isActive = true;
          for (uint r = 0; r < RELAY_COUNT; r++) {
            Controller.temporalProfile.relays[r].start = Controller.temporalSetter.start + Controller.temporalSetter.duration * r; // set temporalkstarting times
            Controller.temporalProfile.relays[r].duration = Controller.temporalSetter.duration; // set temporal chain durations
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
      // Change humidity sensitivity
      if (clickPos == BTN_1_2) Controller.humiditySensitivity += 10;
      else if (clickPos == BTN_3_2) Controller.humiditySensitivity -= 10;
      break;
    case settings:
      break;
    case clock:
      break;

  }
}