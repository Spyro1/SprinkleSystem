// ******** SystemController.ino ********

struct SystemController {
  // ==== Menu Variables ====
  // -- Save config vars --
  menuStyle style;               // !EEPROM! How beautiful the menu should be
  bool mainSwitch;               // !EEPROM! If true, then timing is processed, if false, then no automatic sprinkleing
  ulong humiditySensitivity;  // !EEPROM! Humidity sensitivity of the system
  Profile profiles[PROFILE_COUNT]; // !EEPROM! Time profiles when automatic sprinkeling can happen

  // -- Running config vars --
  menuStates state;            // Current state of menusystem
  uint currentPage;   // Current page of submenu
  uint currentProfile; // Which period is edited currently
  uint currentRelay;  // Which realy is edited currently

  // -- Temporal settings for chain sprinkle and testing --
  Profile temporalProfile;
  TimeSpan temporalStart;
  uint8_t temporalDuration;

  SystemController() : style(easy), mainSwitch(false), humiditySensitivity(0){
    ResetMenu();
  }
  void StartMenu(){
    ResetMenu();
    RunMenu();
  }
  void ResetMenu() {
    state = menuStates::mainMenu;
    currentPage = 0;
    currentProfile = 0;
    currentRelay = 0;
  }
  /// Updates all relays. If current time is start, then activates, if end, then deactivates those relays. 
  void UpdateRelays(TimeSpan currentTime) {
    for (int r = 0; r < RELAY_COUNT; r++) {
      for (int p = 0; p < PROFILE_COUNT; p++) {
        // === Update timed profiles ===
        // Check if current time is in between the start and end of relay timing
        bool toActivate = currentTime.hours() == profiles[p].relays[r].start.hours() && currentTime.minutes() == profiles[p].relays[r].start.minutes();
        bool toDeactivate = currentTime.hours() == profiles[p].relays[r].end().hours() && currentTime.minutes() == profiles[p].relays[r].end().minutes();
        // Set Relay State
        if (toActivate != toDeactivate) {
          if (toActivate)  { profiles[p].relays[r].SetRelayState(true); debugv(p); debug("/"); debugv(r); debug(" Realy Activated"); }
          if (toDeactivate) { profiles[p].relays[r].SetRelayState(false); debugv(p); debug("/"); debugv(r); debug(" Realy Deactivated"); }
        }
      }
      // === Update temporal profile ===
      // Check if current time is in between the start and end of relay timing
      bool toActivateTemp = currentTime.hours() == temporalProfile.relays[r].start.hours() && currentTime.minutes() == temporalProfile.relays[r].start.minutes();
      bool toDeactivateTemp = currentTime.hours() == temporalProfile.relays[r].end().hours() && currentTime.minutes() == temporalProfile.relays[r].end().minutes();
      // Set Relay State
      if (toActivateTemp != toDeactivateTemp) {
        if (toActivateTemp)  { temporalProfile.relays[r].SetRelayState(true); debug("Temp/"); debugv(r); debug(" Realy Activated"); }
        if (toDeactivateTemp) { temporalProfile.relays[r].SetRelayState(false); debug("Temp/"); debugv(r); debug(" Realy Deactivated"); }
      }
    }
  }
  void DrawStateScreen(){
    switch(state) {
      case mainMenu:
        DrawMainMenu();
        break;
      case sprinkleProfiles:
        DrawSprinkleProfilesMenu();
        break;
      case sprinkleRelays:
        DrawSprinkleRelayChoser();
        break;
      case sprinkleAuto:
        DrawSprinkleAutomatic();
        break;
      case sprinkleSetter:
        DrawSprinkleSetter();
        break;
      case chainSprinkler:
        DrawChainSprinkleMenu();
        break;
      case test:
        DrawTestMenu();
        break;
      case humidity:
        DrawHumidityMenu();
        break;
      case settings:
        DrawSettingsMenu();
        break;
      case clock:
        DrawClockMenu();
        break;
      default:
        DrawMainMenu(); // Default case if none of the above matches
        break;
    } 
  }
  void Touched(uint x, uint y){

  }
  Relay& getCurrentRelay() { return profiles[currentProfile].relays[currentRelay]; }
  void ChangeTempStartHour(uint byValue) { temporalStart = temporalStart + TimeSpan(3600 * byValue); }
  void ChangeTempStartMinute(uint byValue) { temporalStart = temporalStart + TimeSpan(60 * byValue); }
  void ChangeTempDuration(uint byValue) { temporalDuration += byValue; }
};


// Create a sprinkle system controller object
SystemController Controller;