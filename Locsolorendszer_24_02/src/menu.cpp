// --- menu.cpp ---

#include "menu.h"
#include "display.h"

/* ---- Menu class definicions ---- */
Menu::Menu(MCUFRIEND_kbv &tft) : tft(tft)
{
  // btnMainOnOff() = TouchButton(0, 0, ICONSIZE, ICONSIZE, MainToggleButton_Clicked);
}

void Menu::RunMenu()
{

  // -- Start main screen --
  // DrawMainScreen(tft);
  // delay(5000);
  // DrawRTCSettingsSubMenu(tft); // Test
  // delay(10000);
  // delay(5000);
  // DrawPeriodSubMenu(tft);
  DrawTimingSubMenu(tft);
  delay(10000);
  DrawChainSprinkleSubMenu(tft);

  // btnMainOnOff().ifPressedThenActivate(0,0);
}

void Menu::Touched(int x, int y)
{
  Serial.print("Menu: (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.println(")"); // Print actual coordinates
}

/* ---- Button Clickevents ----- */
// --- Main Screen---

void SprinkleButton_Clicked() {}
void ChainButton_Clicked() {}
void TestButton_Clicked() {}
void HumidityButton_Clicked() {}
void SettingsButton_Clicked() {}
void MainToggleButton_Clicked()
{
  // autoSprinkle = !autoSprinkle;
  // if (autoSprinkle)
}
void ClockButton_Clicked() {}

// --- Submenus ---

void HomeIcon_Clicked() {}
/* ----  ---- */
