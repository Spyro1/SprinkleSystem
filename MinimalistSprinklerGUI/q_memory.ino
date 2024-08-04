// ******** memory.ino ********
#include <EEPROM.h>

// EEPROM system:
// #define styleAddress 0
#define relayCountAddress 200
#define switchAddress 1
#define humidityAddress 2
#define profileStartAddress 3
#define relayDataSize 3 // Start hour, start minute, duration in minutes
#define profileDataSize relayDataSize * MAX_RELAY_COUNT

// -- Relay count --
/**
 * @brief Saves the relay count to EEPROM.
 * @param relayCount The number of relays to be saved.
 */
void SaveRelayCount(const unsigned char& relayCount) { EEPROM.update(relayCountAddress, relayCount); }
/**
 * @brief Loads the relay count from EEPROM.
 * @param relayCount The variable to store the loaded relay count.
 */
void LoadRelayCount(unsigned char& relayCount) { relayCount = EEPROM.read(relayCountAddress); }
// -- mainSwitch --
/**
 * @brief Saves the main switch state to EEPROM.
 * @param mainSwitch The state of the main switch to be saved.
 */
void SaveMainSwitch(const bool mainSwitch) { EEPROM.update(switchAddress, mainSwitch ? 1 : 0); }
/**
* @brief Loads the main switch state from EEPROM.
* @param mainSwitch The variable to store the loaded main switch state.
*/
void LoadMainSwitch(bool &mainSwitch) { mainSwitch = EEPROM.read(switchAddress) != 0 ? true : false; }
// -- humiditySensitivity --
/**
 * @brief Saves the humidity sensitivity to EEPROM.
 * @param humidity The humidity sensitivity value to be saved.
 */
void SaveHumidity(const unsigned char &humidity) { EEPROM.update(humidityAddress, humidity); }
/**
 * @brief Loads the humidity sensitivity from EEPROM.
 * @param humidity The variable to store the loaded humidity sensitivity.
 */
void LoadHumidity(unsigned char &humidity) { humidity = EEPROM.read(humidityAddress); }

// -- Profile --
/**
* @brief Saves a profile to EEPROM.
* @param profile The profile data to be saved.
* @param profileNumber The index of the profile.
*/
void SaveProfileData(const struct Profile &profile, int profileNumber) {
  EEPROM.update(profileStartAddress + profileNumber * (profileDataSize + 1), profile.isActive ? 1 : 0);
  // debug("SaveProfile: "); debugv(profileNumber); debug(". IsActive: "); debugvln(profileStartAddress + profileNumber * (profileDataSize+1));
  for (int r = 0; r < Controller.relayCount; r++) {
    SaveRelayData(profile.relays[r], profileNumber, r);
  }
}
/**
 * @brief Loads a profile from EEPROM.
 * @param profile The variable to store the loaded profile.
 * @param profileNumber The index of the profile.
 */
void LoadProfileData(struct Profile &profile, int profileNumber) {
  profile.isActive = EEPROM.read(profileStartAddress + profileNumber * (profileDataSize + 1)) != 0 ? true : false;
  for (int r = 0; r < Controller.relayCount; r++) {
    LoadRelayData(profile.relays[r], profileNumber, r);
  }
}

// -- Relay --
/**
 * @brief Saves relay data to EEPROM.
 * @param rel The relay data to be saved.
 * @param profileNumber The index of the profile.
 * @param relayNumber The index of the relay.
 */
void SaveRelayData(const struct Relay &rel, int profileNumber, int relayNumber) {
  EEPROM.update(profileStartAddress + profileNumber * (profileDataSize + 1) + 1 + relayDataSize * relayNumber, (uint)rel.start.hours());
  EEPROM.update(profileStartAddress + profileNumber * (profileDataSize + 1) + 1 + relayDataSize * relayNumber + 1, (uint)rel.start.minutes());
  EEPROM.update(profileStartAddress + profileNumber * (profileDataSize + 1) + 1 + relayDataSize * relayNumber + 2, rel.duration());
  // debug("Save: "); debugv(profileNumber); debug("/"); debugv(relayNumber); debug(":: H: "); debugv(profileStartAddress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber);
  // debug(" M: "); debugv(profileStartAddress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 1); debug(" D: "); debugvln(profileStartAddress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 2);
}
/**
 * @brief Loads relay data from EEPROM.
 * @param rel The variable to store the loaded relay data.
 * @param profileNumber The index of the profile.
 * @param relayNumber The index of the relay.
 */
void LoadRelayData(struct Relay &rel, int profileNumber, int relayNumber) {
  int hour, min, dur;
  hour = EEPROM.read(profileStartAddress + profileNumber * (profileDataSize + 1) + 1 + relayDataSize * relayNumber);
  min = EEPROM.read(profileStartAddress + profileNumber * (profileDataSize + 1) + 1 + relayDataSize * relayNumber + 1);
  dur = EEPROM.read(profileStartAddress + profileNumber * (profileDataSize + 1) + 1 + relayDataSize * relayNumber + 2);
  rel.start = Time(hour, min);
  rel.duration = dur;
}
