// ******** relay_profile.ino ********

// ==== Relay ====
struct Relay {
  static uint idCounter; // Max 256 relays available
  uint id;  // Relay identifier
  uint pin; // Connected pin on the arduino
  bool state; // Iondicates wheter the relay is activated or not
  // -- Timed Sprinkling --
  Time start; // Start time of sprinkling
  Range60 duration; // Duration in minutes of sprinkling

  /**
    * Constructor for instances
    * @param pin Pin of the relay on board
    * @param start Start time of automated sprinkling
    * @param duration Duration of the sprinkling in minutes
    * */
  Relay(uint8_t pin = 0, struct Time start = 0, uint duration = 0 ) : id(idCounter++), pin(pin), start(start), duration(duration)  { }
  // - Functions -
  Time end() { return start + duration(); } // Convert duration from minutes to seconds
  void SetRelayState(bool value) {
    state = value;
    if (!state) digitalWrite(pin, HIGH);
    else digitalWrite(pin, LOW);
  }
  void reset(){
    start = 0;
    duration = 0;
    // state = false;
  }
};

uint8_t Relay::idCounter = 0; // Set default value to id counter

// ==== Profile ====
struct Profile {
    bool isActive;             // !EEPROM!
    Relay relays[MAX_RELAY_COUNT]; // !EEPROM!

    Profile() : isActive(false) {
      for (uint i = 0; i < MAX_RELAY_COUNT; i++){
        relays[i].pin = RELAY_PINS[i]; // Set pins to relays
        relays[i].SetRelayState(relays[i].state); // set default state
      }
    }
};