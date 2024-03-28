// --- menu.cpp ---

#include "menu.h"

/* ---- Menu class definicions ---- */
Menu::Menu(Adafruit_TFTLCD& tft) : tft(tft) { }

void Menu::RunMenu() {
    
  // -- Start main screen -- 
  DrawMainScreen(tft);
}

void Menu::Touched(int x, int y) {
    Serial.print("Menu: ("); Serial.print(x); Serial.print(", "); Serial.print(y); Serial.println(")"); // Print actual coordinates
}

/* ---- Button Clickevents ----- */
// --- Main Screen---

void SprinkleButton_Clicked() {}
void ChainButton_Clicked() {}
void TestButton_Clicked() {}
void HumidityButton_Clicked() {}
void SettingsButton_Clicked() {}
void MainToggleButton_Clicked() {}
void ClockButton_Clicked() {}

// --- Submenus ---

void HomeIcon_Clicked() {}
/* ----  ---- */

