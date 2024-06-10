// ******** relay_profile.ino ********

// ==== Relay ====
struct Relay {
  static uint8_t idCounter; // Max 256 relays available
  uint8_t id;  // Relay identifier
  uint8_t pin; // Connected pin on the arduino
  bool state; // Iondicates wheter the relay is activated or not
  // -- Timed Sprinkling --
  TimeSpan start; // Start time of sprinkling
  TimeSpan duration; // Duration in minutes of sprinkling

  // -- Constructors --
  /**
    * Constructor for instances
    * @param pin Pin of the relay on board
    * @param start Start time of automated sprinkling
    * @param duration Duration of the sprinkling in minutes
    * */
  Relay::Relay(uint8_t pin = 0, TimeSpan start = 0, uint8_t duration = 0 ) : id(idCounter++), pin(pin), start(start), duration(duration)  { }
  // - Functions -
  TimeSpan end() { return start + duration; } // Convert duration from minutes to seconds
  void Relay::SetRelayState(bool value) {
    state = value;
    if (state) digitalWrite(pin, HIGH);
    else digitalWrite(pin, LOW);
  }
  void Relay::ChangeStartHour(uint8_t byValue) { start = start + TimeSpan(byValue * 3600); }
  void Relay::ChangeStartMinute(uint8_t byValue) { start = start + TimeSpan(byValue * 60); }
  void Relay::ChangeDuration(uint8_t byValue) { duration = duration + TimeSpan(byValue * 60); }
};

uint8_t Relay::idCounter = 0; // Set default value to id counter

// ==== Profile ====
struct Profile {
    bool isActive;             // !EEPROM!
    Relay relays[RELAY_COUNT]; // !EEPROM!
};