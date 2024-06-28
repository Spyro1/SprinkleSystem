// ******** SystemController.ino ********

/**
 * @brief Represents the main system controller for the sprinkler system. 
 * The SystemController struct manages the main configuration, profiles, and the current state of the system,
 * including methods to handle menu interactions and update relay states.
 */
struct SystemController
{
  // ==== Menu Variables ====
  unsigned char relayCount;        /**< Number of relays in use (saved in EEPROM). */
  bool mainSwitch;                 /**< Main switch to control automatic sprinkling (saved in EEPROM). If true, automatic sprinkling is enabled. */
  uint humiditySensitivity;        /**< Humidity sensitivity of the system (saved in EEPROM). */
  Profile profiles[PROFILE_COUNT]; /**< Array of time profiles for automatic sprinkling (saved in EEPROM). */

  // ==== Running Configuration Variables ====
  DateTime now;        /**< Current real-time. */
  menuStates state;    /**< Current state of the menu. */
  uint currentPage;    /**< Current page of the submenu. */
  uint currentProfile; /**< Index of the profile being edited. */
  uint currentRelay;   /**< Index of the relay being edited. */
  bool unsavedChanges; /**< Indicates if there are unsaved changes. */

  // ==== Temporal Settings for Chain Sprinkle and Testing ====
  Profile temporalProfile; /**< Temporary profile for testing purposes. */
  Relay temporalSetter;    /**< Temporary relay setter for testing. */
  uint temporalFromRelay;  /**< Starting relay for the temporary profile. */
  uint temporalToRelay;    /**< Ending relay for the temporary profile. */

  /**
   * @brief Constructor to initialize the SystemController instance.
   */
  SystemController() : relayCount(MAX_RELAY_COUNT), mainSwitch(false), humiditySensitivity(0){
    // Load variables from EEPROM    
    LoadRelayCount(relayCount);
    LoadMainSwitch(mainSwitch);
    LoadHumidity(humiditySensitivity);
    for (uint p = 0; p < PROFILE_COUNT; p++) {
      LoadProfileData(profiles[p], p);
    }
    // Reaset running config
    ResetMenu();
  }
  /**
   * @brief Starts the menu interface. Initializes the menu state and runs the menu.
   */
  void StartMenu() {
    state = menuStates::mainMenu;
    ResetMenu();
    RunMenu();
  }
  /**
   * @brief Resets the menu state and temporary settings.
   */
  void ResetMenu() {
    currentPage = 0;
    currentProfile = 0;
    currentRelay = 0;
    temporalSetter.start = Time(0, 0);
    temporalSetter.duration = 0;
    temporalFromRelay = 0;
    temporalToRelay = relayCount - 1;
  }
   /**
   * @brief Updates the states of all relays based on the current time.
   * Activates or deactivates relays according to their profiles and the main switch state.
   */
  void UpdateRelays() {
    // If the main switch is on then do anything
    if (mainSwitch) { 
      for (uint r = 0; r < relayCount; r++) {
        // -- Update timed profiles --
        for (uint p = 0; p < PROFILE_COUNT && profiles[p].isActive; p++) {
          // -- If the duration of the relay is greater than 0 --
          if (profiles[p].relays[r].duration() > 0) {
            // To activate
            if (now.hour() == profiles[p].relays[r].start.hours() && now.minute() == profiles[p].relays[r].start.minutes()) {
              profiles[p].relays[r].SetRelayState(true); // Turn on relay
              Serial.print(p); Serial.print(F("/")); Serial.print(r); Serial.println(F(" Relay Activated")); 
            }
            // To deactivate
            if (now.hour() == profiles[p].relays[r].end().hours() && now.minute() == profiles[p].relays[r].end().minutes()) {
              profiles[p].relays[r].SetRelayState(false); // Turn off relay
              Serial.print(p); Serial.print(F("/")); Serial.print(r); Serial.println(F(" Relay Deactivated"));
            }
          }
        }
        // === Update temporal profile ===
        if (temporalProfile.isActive && temporalProfile.relays[r].duration() > 0) {
          // To activate
          if (now.hour() == temporalProfile.relays[r].start.hours() && now.minute() == temporalProfile.relays[r].start.minutes()) {
            temporalProfile.relays[r].SetRelayState(true); // Turn on temporal relay
            Serial.print(F("Temp/")); Serial.print(r); Serial.println(F(" Relay Activated"));
          }
          // To deactivate
          if (now.hour() == temporalProfile.relays[r].end().hours() && now.minute() == temporalProfile.relays[r].end().minutes()) {
            temporalProfile.relays[r].SetRelayState(false); // Turn off temporal relay
            Serial.print(F("Temp/")); Serial.print(r); Serial.println(F(" Relay Deactivated")); temporalProfile.relays[r].duration = 0;
          }
        }
      }
    }
  }
  /**
   * @brief Handles touch events. 
   * @param x The x-coordinate of the touch.
   * @param y The y-coordinate of the touch.
   */
  void Touched(int x, int y) {
    // If the state is mainMenu then test mainmenu buttons
    if (state == mainMenu) {
      for (uint i = 0; i < mainScreenButtonCount; i++) {
        if (mainBtns[i].isPressed(x, y)) {
          ExecuteMainMenuClickEvents(i);
          break;
        }
      }
    }
    // If home button is pressed then reset menu to mainMenu
    else if (homeBtn.isPressed(x, y)) {
      state = mainMenu; // Go back to main Menu
      ResetMenu();
      DrawMainMenu();
    }
    // If the state is a subMenu then test submenu buttons in the grid
    else {
      for (uint i = 0; i < subMenuButtonCount; i++) {
        if (subMenuBtns[i].isPressed(x, y)) {
          ExecuteSubMenuClickEvents({i % 4, i / 4});
          break;
        }
      }
    }
  }
  /**
   * @brief Saves the current configuration to EEPROM.
   */
  void SaveChanges() {
    SaveRelayCount(relayCount);
    SaveMainSwitch(mainSwitch);
    SaveHumidity(humiditySensitivity);
    for (uint p = 0; p < PROFILE_COUNT; p++) {
      SaveProfileData(profiles[p], p);
    }
    unsavedChanges = false;
  }
   /**
   * @brief Gets the currently selected relay. 
   * @return Reference to the current relay.
   */
  Relay &CurrentRelay() { return profiles[currentProfile].relays[currentRelay]; }
};

// Create a sprinkle system controller object
SystemController Controller;