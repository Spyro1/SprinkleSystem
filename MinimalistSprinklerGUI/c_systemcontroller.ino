// ******** SystemController.ino ********

struct SystemController {
  // ==== Menu Variables ====
  // -- Save config vars --
  menuStyle style;                  // !EEPROM! How beautiful the menu should be
  bool mainSwitch;                  // !EEPROM! If true, then timing is processed, if false, then no automatic sprinkling
  Range1024 humiditySensitivity;        // !EEPROM! Humidity sensitivity of the system
  Profile profiles[PROFILE_COUNT];  // !EEPROM! Time profiles when automatic sprinkling can happen

  // -- Running config vars --
  DateTime now;        // Current real time
  menuStates state;    // Current state of the menu
  uint currentPage;    // Current page of submenu
  uint currentProfile; // Which period is edited currently
  uint currentRelay;   // Which really is edited currently

  // -- Temporal settings for chain sprinkle and testing --
  Profile temporalProfile;
  Relay temporalSetter;
  // Time temporalStart;
  // uint temporalDuration;

  // -- Constructor --
  SystemController() : style(easy), mainSwitch(false), humiditySensitivity(0){
    // Load variables from EEPROM
      unsigned char helperStyle;
      LoadStyle(helperStyle);
      style = (menuStyle)helperStyle;
      LoadMainSwitch(mainSwitch);
      LoadHumidity(humiditySensitivity);
      for (uint p = 0; p < PROFILE_COUNT; p++){
        LoadProfileData(profiles[p], p);
      }
    // Reaset running config
    ResetMenu();
  }
  // -- Functions --
  void StartMenu(){
    ResetMenu();
    RunMenu();
  }

  void ResetMenu() {
    state = menuStates::mainMenu;
    currentPage = 0;
    currentProfile = 0;
    currentRelay = 0;
    temporalProfile.isActive = false;
    temporalSetter.start = Time(0,0);
    temporalSetter.duration = 0;
  }
  /// Updates all relays. If current time is start, then activates, if end, then deactivates those relays. 
  void UpdateRelays(struct Time& currentTime) {
    for (int r = 0; r < RELAY_COUNT; r++) {
      for (int p = 0; p < PROFILE_COUNT && profiles[p].isActive; p++) {
        // === Update timed profiles ===
        // Check if current time is in between the start and end of relay timing
        bool toActivate = currentTime.hours() == profiles[p].relays[r].start.hours() && currentTime.minutes() == profiles[p].relays[r].start.minutes();
        bool toDeactivate = currentTime.hours() == profiles[p].relays[r].end().hours() && currentTime.minutes() == profiles[p].relays[r].end().minutes();
        // Set Relay State
        if (toActivate != toDeactivate) {
          if (toActivate)  { profiles[p].relays[r].SetRelayState(true); debugv(p); debug("/"); debugv(r); debug(" Relay Activated"); }
          if (toDeactivate) { profiles[p].relays[r].SetRelayState(false); debugv(p); debug("/"); debugv(r); debug(" Relay Deactivated"); }
        }
      }
      // === Update temporal profile ===
      if (temporalProfile.isActive){
        // Check if current time is in between the start and end of relay timing
        bool toActivateTemp = currentTime.hours() == temporalProfile.relays[r].start.hours() && currentTime.minutes() == temporalProfile.relays[r].start.minutes();
        bool toDeactivateTemp = currentTime.hours() == temporalProfile.relays[r].end().hours() && currentTime.minutes() == temporalProfile.relays[r].end().minutes();
        // Set Relay State
        if (toActivateTemp != toDeactivateTemp) {
          if (toActivateTemp)  { temporalProfile.relays[r].SetRelayState(true); debug("Temp/"); debugv(r); debug(" Relay Activated"); }
          if (toDeactivateTemp) { temporalProfile.relays[r].SetRelayState(false); debug("Temp/"); debugv(r); debug(" Relay Deactivated"); }
        }
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
        DrawSprinkleRelayChooser();
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
  void UpdateStatesScreen(){

  }
  void Touched(uint x, uint y){
    ExecuteClickEvent({x,y});
  }
  Relay& CurrentRelay() { return profiles[currentProfile].relays[currentRelay]; }
  // void ChangeTempStartHour(uint byValue) { temporalStart = temporalStart + TimeSpan(3600 * byValue); }
  // void ChangeTempStartMinute(uint byValue) { temporalStart = temporalStart + TimeSpan(60 * byValue); }
  // void ChangeTempDuration(uint byValue) { temporalDuration += byValue; }
};


// Create a sprinkle system controller object
SystemController Controller;