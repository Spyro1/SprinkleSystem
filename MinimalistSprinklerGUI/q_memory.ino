// ******** memory.ino ********
#include <EEPROM.h>

// EEPROM system:
#define styleAdress 0
#define switchAdress 1
#define humidityAdress 2
#define profileStartAdress 3 
#define relayDataSize 3 // Start hour, start minute, duration in minutes
#define profileDataSize relayDataSize * RELAY_COUNT 

// -- Style --
void SaveStyle(const unsigned char style) { EEPROM.update(styleAdress, style); }
void LoadStyle(unsigned char& style) { style = EEPROM.read(styleAdress); }
// -- mainSwitch --
void SaveMainSwitch(const bool mainSwitch) { EEPROM.update(switchAdress, mainSwitch ? 1 : 0); }
void LoadMainSwitch(bool& mainSwitch) { mainSwitch = EEPROM.read(switchAdress) != 0 ? true : false; }
// -- humiditySensitivity --
void SaveHumidity(const unsigned char& humidity) { EEPROM.update(humidityAdress, humidity); }
void LoadHumidity(unsigned char& humidity) { humidity = EEPROM.read(humidityAdress); }
// -- Profile --
void SaveProfileData(const struct Profile& profile, int profileNumber){
  EEPROM.update(profileStartAdress + profileNumber * (profileDataSize+1), profile.isActive ? 1 : 0);
  debug("SaveProfile: "); debugv(profileNumber); debug(". IsActive: "); debugvln(profileStartAdress + profileNumber * (profileDataSize+1));
  for (int r = 0; r < RELAY_COUNT; r++){
    SaveRelayData(profile.relays[r], profileNumber, r);
  }
}
void LoadProfileData(struct Profile& profile, int profileNumber){
  profile.isActive = EEPROM.read(profileStartAdress + profileNumber * (profileDataSize+1)) != 0 ? true : false;
  
  for (int r = 0; r < RELAY_COUNT; r++){
    LoadRelayData(profile.relays[r], profileNumber, r);
  } 
}
// -- Relay --
void SaveRelayData(const struct Relay& rel, int profileNumber, int relayNumber) {
  EEPROM.update(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber, (uint)rel.start.hours());
  EEPROM.update(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 1, (uint)rel.start.minutes());
  EEPROM.update(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 2, rel.duration());
  debug("Save: "); debugv(profileNumber); debug("/"); debugv(relayNumber); debug(":: H: "); debugv(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber);
  debug(" M: "); debugv(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 1); debug(" D: "); debugvln(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 2);
}
void LoadRelayData(struct Relay& rel, int profileNumber, int relayNumber) {
  int hour, min, dur;
  hour = EEPROM.read(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber);
  min = EEPROM.read(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 1);
  dur = EEPROM.read(profileStartAdress + profileNumber * (profileDataSize+1) + 1 + relayDataSize * relayNumber + 2);
  rel.start = Time(hour, min);
  rel.duration = dur;
}
