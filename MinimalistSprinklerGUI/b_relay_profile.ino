// ******** relay_profile.ino ********

/**
 * @brief Represents a relay for controlling sprinklers. 
 * The Relay struct defines a relay with properties such as pin number, state, start time, and duration.
 */
struct Relay
{
  static uint idCounter; /**< Counter for generating unique relay IDs. Maximum of 256 relays available. */
  uint id;               /**< Unique identifier for the relay. */
  uint pin;              /**< Pin number on the Arduino to which the relay is connected. */
  bool state;            /**< Indicates whether the relay is activated or not. */
  Time start;            /**< Start time of the sprinkling. */
  Range60 duration;      /**< Duration of the sprinkling in minutes. */

  /**
   * @brief Constructor to initialize a Relay instance. 
   * @param pin The pin number to which the relay is connected. Defaults to 0.
   * @param start The start time of automated sprinkling. Defaults to 0.
   * @param duration The duration of the sprinkling in minutes. Defaults to 0.
   */
  Relay(uint8_t pin = 0, struct Time start = 0, uint duration = 0) : id(idCounter++), pin(pin), start(start), duration(duration) {}
  /**
   * @brief Calculates the end time of sprinkling. 
   * @return The end time of the sprinkling.
   */
  Time end() { return start + duration(); }
  /**
   * @brief Sets the state of the relay. 
   * @param value The desired state of the relay. True to activate, false to deactivate.
   */
  void SetRelayState(bool value) {
    state = value;
    if (!state) digitalWrite(pin, HIGH);
    else digitalWrite(pin, LOW);
  }
  /**
   * @brief Resets the relay's start time and duration.
   */
  void reset() {
    start = 0;
    duration = 0;
  }
};

uint8_t Relay::idCounter = 0; /**< Initialize the relay ID counter to 0. */

/**
 * @brief Represents a profile containing multiple relays.
 * The Profile struct defines a profile with an array of relays and an active state.
 */
struct Profile
{
  bool isActive;                 /**< Indicates whether the profile is active. */
  Relay relays[MAX_RELAY_COUNT]; /**< Array of relays in the profile. */

  /**
   * @brief Constructor to initialize a Profile instance.
   * The constructor sets the relays' pin numbers and their default states.
   */
  Profile() : isActive(false) {
    for (uint i = 0; i < MAX_RELAY_COUNT; i++) {
      relays[i].pin = RELAY_PINS[i];            // Set pins to relays
      relays[i].SetRelayState(relays[i].state); // Set default state
    }
  }
};