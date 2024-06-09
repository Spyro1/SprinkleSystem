// ******** menu.ino ********

enum menuStates {
  mainMenu, 
  sprinkleProfiles, 
  sprinkleRelays, 
  sprinkleAuto,
  sprinkleSetter,
  chainSprinkler,
  test,
  humidity,
  settings,
  clock
};
enum menuStyle {
  easy,
  medium,
  quality
};

// ==== Declaration ====

// ==== Menu functions ====

void RunMenu(){
  DrawMainMenu();
}

