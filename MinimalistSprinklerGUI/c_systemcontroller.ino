// ******** SystemController.ino ********

struct SystemController {
  // ==== Menu Variables ====
  // -- Save config vars --
  menuStyle style;                  // !EEPROM! How beautiful the menu should be
  bool mainSwitch;                  // !EEPROM! If true, then timing is processed, if false, then no automatic sprinkling
  uint humiditySensitivity;         // !EEPROM! Humidity sensitivity of the system
  Profile profiles[PROFILE_COUNT];  // !EEPROM! Time profiles when automatic sprinkling can happen

  // -- Running config vars --
  DateTime now;        // Current real time
  menuStates state;    // Current state of the menu
  uint currentPage;    // Current page of submenu
  uint currentProfile; // Which period is edited currently
  uint currentRelay;   // Which really is edited currently
  bool unsavedChanges; // Indicates if there is unsaved changes

  // -- Temporal settings for chain sprinkle and testing --
  Profile temporalProfile;
  Relay temporalSetter;
  uint temporalFromRelay;
  uint temporalToRelay;
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
    state = menuStates::mainMenu;
    ResetMenu();
    RunMenu();
  }

  void ResetMenu() {
    currentPage = 0;
    currentProfile = 0;
    currentRelay = 0;
    temporalProfile.isActive = false;
    temporalSetter.start = Time(0,0);
    for (uint i = 0; i < RELAY_COUNT; i++)
      temporalProfile.relays[i].reset();
    temporalSetter.duration = 0;
    temporalFromRelay = 0;
    temporalToRelay = RELAY_COUNT - 1;
  }
  /// Updates all relays. If current time is start, then activates, if end, then deactivates those relays. 
  void UpdateRelays() {
    if (mainSwitch) { // If the main switch is on
      for (uint r = 0; r < RELAY_COUNT; r++) {
        for (uint p = 0; p < PROFILE_COUNT && profiles[p].isActive; p++) {
          // === Update timed profiles ===
          bool toActivate = now.hour() == profiles[p].relays[r].start.hours() && now.minute() == profiles[p].relays[r].start.minutes();
          if (toActivate)  { profiles[p].relays[r].SetRelayState(true); debugv(p); debug("/"); debugv(r); debugln(" Relay Activated"); }
          
          bool toDeactivate = now.hour() == profiles[p].relays[r].end().hours() && now.minute() == profiles[p].relays[r].end().minutes();
          if (toDeactivate) { profiles[p].relays[r].SetRelayState(false); debugv(p); debug("/"); debugv(r); debugln(" Relay Deactivated"); }
        }
        // === Update temporal profile ===
        if (temporalProfile.isActive){
          bool toActivateTemp = now.hour() == temporalProfile.relays[r].start.hours() && now.minute() == temporalProfile.relays[r].start.minutes();
          if (toActivateTemp)  { temporalProfile.relays[r].SetRelayState(true); debug("Temp/"); debugv(r); debugln(" Relay Activated"); }
          
          bool toDeactivateTemp = now.hour() == temporalProfile.relays[r].end().hours() && now.minute() == temporalProfile.relays[r].end().minutes();
          if (toDeactivateTemp) { temporalProfile.relays[r].SetRelayState(false); debug("Temp/"); debugv(r); debugln(" Relay Deactivated"); }
        }
      }
    }
  }
  void DrawStateScreen(){
    switch(state) {
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
      case testSprinkler:
        DrawTestMenu();
        break;
        break;
      case settings:
        DrawSettingsMenu();
        break;
      case clockSetter:
        DrawClockMenu();
        break;
      case mainMenu:
      default:
        DrawMainMenu(); // Default case if none of the above matches
        break;
    } 
  }
  void UpdateStateScreen(){
    switch(state) {
      case sprinkleProfiles:
        UpdateSprinkleProfilesMenu();
        break;
      case sprinkleRelays:
        UpdateSprinkleRelayChooser();
        break;
      case sprinkleAuto:
        UpdateSprinkleAutomatic();
        break;
      case sprinkleSetter:
        UpdateSprinkleSetter();
        break;
      case chainSprinkler:
        UpdateChainSprinkleMenu();
        break;
      case testSprinkler:
        UpdateTestMenu();
        break;
      case settings:
        UpdateSettingsMenu();
        break;
      case clockSetter:
        UpdateClockMenu();
        break;
      case mainMenu:
      default:
        UpdateMainMenu(); // Default case if none of the above matches
        break;
    } 
  }
  void Touched(int x, int y){
    // If the state is mainMenu 
    if (state == mainMenu){
      for (uint i = 0; i < mainScreenButtonCount; i++){
        if (mainBtns[i].isPressed(x, y)){
          ExecuteMainMenuClickEvents(i);
          break;
        }
      }
    }
    // If the state is a subMenu
    else if (homeBtn.isPressed(x,y)){
      state = mainMenu; // Go back to main Menu
      ResetMenu();
      DrawStateScreen();
      //debugln("Home Btn pressed"); 
    }
    else {
      for (uint i = 0; i < subMenuButtonCount; i++){
        if (subMenuBtns[i].isPressed(x,y)){
          ExecuteSubMenuClickEvents({i % 4, i / 4}); // NOT COMMENT
          //debugv(i); debug(". Pressed: BTN_"); debugv(i/4+1); debug("_"); debugvln(i%4+1); // Debug
          break;
        }
      }
    }
    // debug("State= "); debugvln(state);
  }
  void SaveChanges(){
    SaveStyle(style);
    SaveMainSwitch(mainSwitch);
    SaveHumidity(humiditySensitivity);
    for (uint p = 0; p < PROFILE_COUNT; p++){
      SaveProfileData(profiles[p], p);
    }
    unsavedChanges = false;
  }
  Relay& CurrentRelay() { return profiles[currentProfile].relays[currentRelay]; }
};


// Create a sprinkle system controller object
SystemController Controller;