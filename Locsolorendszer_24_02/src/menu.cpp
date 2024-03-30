// --- menu.cpp ---

#include "menu.h"
#include "display.h"

/* ---- Menu class definicions ---- */
Menu::Menu(MCUFRIEND_kbv &tft) : tft(tft)
{
  // Main menu button clickevents
  mainScreenButtons[0] = TouchButton(8, 4, x64, x64, SprinkleButton_Clicked);
  mainScreenButtons[1] = TouchButton(88, 4, x64, x64, ChainButton_Clicked);
  mainScreenButtons[2] = TouchButton(168, 4, x64, x64, TestButton_Clicked);
  mainScreenButtons[3] = TouchButton(248, 4, x64, x64, HumidityButton_Clicked);
  mainScreenButtons[4] = TouchButton(48, 154, x64, x64, SprinkleButton_Clicked);
  mainScreenButtons[5] = TouchButton(128, 154, x64, x64, MainToggleButton_Clicked);
  mainScreenButtons[6] = TouchButton(208, 154, x64, x64, ClockButton_Clicked);
  // Submenu button clickevens
  subMenuButtons[0] = TouchButton(8, 36, x64, x64, EventButton_Clicked_1_1);
  subMenuButtons[1] = TouchButton(88, 36, x64, x64, EventButton_Clicked_1_2);
  subMenuButtons[2] = TouchButton(168, 36, x64, x64, EventButton_Clicked_1_3);
  subMenuButtons[3] = TouchButton(248, 36, x64, x64, EventButton_Clicked_1_4);
  subMenuButtons[4] = TouchButton(8, 104, x64, x64, EventButton_Clicked_2_1);
  subMenuButtons[5] = TouchButton(88, 104, x64, x64, EventButton_Clicked_2_2);
  subMenuButtons[6] = TouchButton(168, 104, x64, x64, EventButton_Clicked_2_3);
  subMenuButtons[7] = TouchButton(248, 104, x64, x64, EventButton_Clicked_2_4);
  subMenuButtons[8] = TouchButton(8, 172, x64, x64, EventButton_Clicked_3_1);
  subMenuButtons[9] = TouchButton(88, 172, x64, x64, EventButton_Clicked_3_2);
  subMenuButtons[10] = TouchButton(168, 172, x64, x64, EventButton_Clicked_3_3);
  subMenuButtons[11] = TouchButton(248, 172, x64, x64, EventButton_Clicked_3_4);
  subMenuButtons[12] = TouchButton(284, 4, x32, x32, HomeIcon_Clicked); // Home icon
}
void Menu::RunMenu()
{
  // -- Start main screen --
  // DrawMainScreen(tft);
  // delay(10000);
  // DrawRTCSettingsSubMenu(tft); // Test
  // delay(10000);
  // DrawPeriodSubMenu(tft);
  // delay(10000);
  // DrawTimingSubMenu(tft);
  // delay(10000);
  // // DrawChainSprinkleSubMenu(tft);
  // delay(10000);
  DrawTestSubMenu(tft);
}

void Menu::Touched(int x, int y)
{
  Serial.println();
  Serial.print("Menu: (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(") ::  "); // Print actual coordinates
  for (size_t i = 0; i < subMenuButtonCount; i++)
  {
    subMenuButtons[i].ifPressedThenActivate(x, y);
  }
}

/* ---- Button Clickevents ----- */
// --- Main Screen---

void SprinkleButton_Clicked() { Serial.println("SprinkleButton_Clicked"); }
void ChainButton_Clicked() { Serial.println("ChainButton_Clicked"); }
void TestButton_Clicked() { Serial.println("TestButton_Clicked"); }
void HumidityButton_Clicked() { Serial.println("HumidityButton_Clicked"); }
void SettingsButton_Clicked() { Serial.println("SettingsButton_Clicked"); }
void MainToggleButton_Clicked() { Serial.println("MainToggleButton_Clicked"); }
void ClockButton_Clicked() { Serial.println("ClockButton_Clicked"); }

// --- Submenus ---

void HomeIcon_Clicked() { Serial.println("HomeIcon_Clicked"); }

void EventButton_Clicked_1_1() { Serial.print("1"); }
void EventButton_Clicked_1_2() { Serial.print("2"); }
void EventButton_Clicked_1_3() { Serial.print("3"); }
void EventButton_Clicked_1_4() { Serial.print("4"); }
void EventButton_Clicked_2_1() { Serial.print("5"); }
void EventButton_Clicked_2_2() { Serial.print("6"); }
void EventButton_Clicked_2_3() { Serial.print("7"); }
void EventButton_Clicked_2_4() { Serial.print("8"); }
void EventButton_Clicked_3_1() { Serial.print("9"); }
void EventButton_Clicked_3_2() { Serial.print("10"); }
void EventButton_Clicked_3_3() { Serial.print("11"); }
void EventButton_Clicked_3_4() { Serial.print("12"); }