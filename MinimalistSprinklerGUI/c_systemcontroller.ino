// ******** SystemController.ino ********

struct SystemController
{
  // ==== Menu Variables ====
  // -- Save config vars --
  unsigned char relayCount;        // !EEPROM!
  bool mainSwitch;                 // !EEPROM! If true, then timing is processed, if false, then no automatic sprinkling
  uint humiditySensitivity;        // !EEPROM! Humidity sensitivity of the system
  Profile profiles[PROFILE_COUNT]; // !EEPROM! Time profiles when automatic sprinkling can happen

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

  // -- Constructor --
  SystemController() : relayCount(MAX_RELAY_COUNT), mainSwitch(false), humiditySensitivity(0)
  {
    // Load variables from EEPROM    
    LoadRelayCount(relayCount);
    LoadMainSwitch(mainSwitch);
    LoadHumidity(humiditySensitivity);
    for (uint p = 0; p < PROFILE_COUNT; p++)
    {
      LoadProfileData(profiles[p], p);
    }
    // Reaset running config
    ResetMenu();
  }
  // -- Functions --
  void StartMenu()
  {
    state = menuStates::mainMenu;
    ResetMenu();
    RunMenu();
  }

  void ResetMenu()
  {
    currentPage = 0;
    currentProfile = 0;
    currentRelay = 0;
    temporalSetter.start = Time(0, 0);
    temporalSetter.duration = 0;
    temporalFromRelay = 0;
    temporalToRelay = relayCount - 1;
  }
  /// Updates all relays. If current time is start, then activates, if end, then deactivates those relays.
  void UpdateRelays()
  {
    if (mainSwitch)
    { // If the main switch is on
      for (uint r = 0; r < relayCount; r++)
      {
        // === Update timed profiles ===
        for (uint p = 0; p < PROFILE_COUNT && profiles[p].isActive; p++)
        {
          // -- If the duration of the relay is greater than 0 --
          if (profiles[p].relays[r].duration() > 0)
          {
            // To activate
            if (now.hour() == profiles[p].relays[r].start.hours() && now.minute() == profiles[p].relays[r].start.minutes())
            {
              profiles[p].relays[r].SetRelayState(true);
              Serial.print(p);
              Serial.print(F("/"));
              Serial.print(r);
              Serial.println(F(" Relay Activated"));
            }
            // To deactivate
            if (now.hour() == profiles[p].relays[r].end().hours() && now.minute() == profiles[p].relays[r].end().minutes())
            {
              profiles[p].relays[r].SetRelayState(false);
              Serial.print(p);
              Serial.print(F("/"));
              Serial.print(r);
              Serial.println(F(" Relay Deactivated"));
            }
          }
        }
        // === Update temporal profile ===
        if (temporalProfile.isActive && temporalProfile.relays[r].duration() > 0)
        {
          // To activate
          if (now.hour() == temporalProfile.relays[r].start.hours() && now.minute() == temporalProfile.relays[r].start.minutes())
          {
            temporalProfile.relays[r].SetRelayState(true);
            Serial.print(F("Temp/"));
            Serial.print(r);
            Serial.println(F(" Relay Activated"));
          }
          // To deactivate
          if (now.hour() == temporalProfile.relays[r].end().hours() && now.minute() == temporalProfile.relays[r].end().minutes())
          {
            temporalProfile.relays[r].SetRelayState(false);
            Serial.print(F("Temp/"));
            Serial.print(r);
            Serial.println(F(" Relay Deactivated"));
            temporalProfile.relays[r].duration = 0;
          }
        }
      }
    }
  }
  void Touched(int x, int y)
  {
    // If the state is mainMenu
    if (state == mainMenu)
    {
      for (uint i = 0; i < mainScreenButtonCount; i++)
      {
        if (mainBtns[i].isPressed(x, y))
        {
          ExecuteMainMenuClickEvents(i);
          break;
        }
      }
    }
    // If the state is a subMenu
    else if (homeBtn.isPressed(x, y))
    {
      state = mainMenu; // Go back to main Menu
      ResetMenu();
      DrawMainMenu();
    }
    else
    {
      for (uint i = 0; i < subMenuButtonCount; i++)
      {
        if (subMenuBtns[i].isPressed(x, y))
        {
          ExecuteSubMenuClickEvents({i % 4, i / 4}); // NOT COMMENT
          break;
        }
      }
    }
  }
  void SaveChanges()
  {
    SaveRelayCount(relayCount);
    SaveMainSwitch(mainSwitch);
    SaveHumidity(humiditySensitivity);
    for (uint p = 0; p < PROFILE_COUNT; p++)
    {
      SaveProfileData(profiles[p], p);
    }
    unsavedChanges = false;
  }
  Relay &CurrentRelay() { return profiles[currentProfile].relays[currentRelay]; }
};

// Create a sprinkle system controller object
SystemController Controller;