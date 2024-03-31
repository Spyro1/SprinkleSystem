// --- menu.cpp ---

// #include "main.h"
#include "menu.h"
#include "display.h"

/* ---- Menu class definicions ---- */
Menu::Menu(MCUFRIEND_kbv &tft, SdFat &SD) : tft(tft), SD(SD)
{
  // Main menu button clickevents
  mainScreenButtons[0] = TouchButton(tft, SD, 8, 4, x64, x64, SprinkleButton_Clicked);
  mainScreenButtons[1] = TouchButton(tft, SD, 88, 4, x64, x64, ChainButton_Clicked);
  mainScreenButtons[2] = TouchButton(tft, SD, 168, 4, x64, x64, TestButton_Clicked);
  mainScreenButtons[3] = TouchButton(tft, SD, 248, 4, x64, x64, HumidityButton_Clicked);
  mainScreenButtons[4] = TouchButton(tft, SD, 48, 154, x64, x64, SprinkleButton_Clicked);
  mainScreenButtons[5] = TouchButton(tft, SD, 128, 154, x64, x64, MainToggleButton_Clicked);
  mainScreenButtons[6] = TouchButton(tft, SD, 208, 154, x64, x64, ClockButton_Clicked);
  // Submenu button clickevens
  subMenuButtons[0] = TouchButton(tft, SD, 8, 36, x64, x64, EventButton_Clicked_1_1);
  subMenuButtons[1] = TouchButton(tft, SD, 88, 36, x64, x64, EventButton_Clicked_1_2);
  subMenuButtons[2] = TouchButton(tft, SD, 168, 36, x64, x64, EventButton_Clicked_1_3);
  subMenuButtons[3] = TouchButton(tft, SD, 248, 36, x64, x64, EventButton_Clicked_1_4);
  subMenuButtons[4] = TouchButton(tft, SD, 8, 104, x64, x64, EventButton_Clicked_2_1);
  subMenuButtons[5] = TouchButton(tft, SD, 88, 104, x64, x64, EventButton_Clicked_2_2);
  subMenuButtons[6] = TouchButton(tft, SD, 168, 104, x64, x64, EventButton_Clicked_2_3);
  subMenuButtons[7] = TouchButton(tft, SD, 248, 104, x64, x64, EventButton_Clicked_2_4);
  subMenuButtons[8] = TouchButton(tft, SD, 8, 172, x64, x64, EventButton_Clicked_3_1);
  subMenuButtons[9] = TouchButton(tft, SD, 88, 172, x64, x64, EventButton_Clicked_3_2);
  subMenuButtons[10] = TouchButton(tft, SD, 168, 172, x64, x64, EventButton_Clicked_3_3);
  subMenuButtons[11] = TouchButton(tft, SD, 248, 172, x64, x64, EventButton_Clicked_3_4);
  subMenuButtons[12] = TouchButton(tft, SD, 284, 4, x32, x32, HomeIcon_Clicked); // Home icon
}
void Menu::RunMenu()
{
  // -- Start main screen --
  DrawMainScreen(tft, SD);
  // delay(10000);
  // DrawRTCSettingsSubMenu(tft, SD); // Test
  // delay(10000);
  // DrawPeriodSubMenu(tft, SD);
  // delay(10000);
  // DrawTimingSubMenu(tft, SD);
  // delay(10000);
  // DrawChainSprinkleSubMenu(tft, SD);
  // delay(10000);
  // DrawTestSubMenu(tft, SD);
}

void Menu::Touched(int x, int y)
{
  Serial.print("Menu: (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(") -  "); // Print actual coordinates
  Serial.println();
  if (State == mainMenu)
  {
    for (short i = 0; i < mainScreenButtonCount; i++)
    {
      mainScreenButtons[i].ifPressedThenActivate(x, y);
    }
  }
  else
  {
    for (short i = 0; i < subMenuButtonCount; i++)
    {
      subMenuButtons[i].ifPressedThenActivate(x, y);
    }
  }
}

/* ---- Button Clickevents ----- */
// --- Main Screen---

void SprinkleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("SprinkleButton_Clicked");
  if (State == mainMenu)
  {
    State = subPeriodsChoser;
    DrawPeriodSubMenu(tft, SD);
  }
}
void ChainButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("ChainButton_Clicked");
  if (State == mainMenu)
  {
    State = subChainSprinkle;
    DrawChainSprinkleSubMenu(tft, SD);
  }
}
void TestButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("TestButton_Clicked");
  if (State == mainMenu)
  {
    State = subTesting;
    DrawTestSubMenu(tft, SD);
  }
}
void HumidityButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("HumidityButton_Clicked");
  if (State == mainMenu)
  {
    State = subHumiditySetting;
    DrawHumiditySubMenu(tft, SD);
  }
}
void SettingsButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("SettingsButton_Clicked");
  if (State == mainMenu)
  {
    State = subSettingsMenu;
    DrawSettingsSubMenu(tft, SD);
  }
}
void MainToggleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("MainToggleButton_Clicked");
  if (State == mainMenu)
  {
    mainSwitch = !mainSwitch;
    if (mainSwitch)
    {
      PrintBmpOrRect(tft, SD, BTN_ON, CENTER_H, HEIGHT - FONT_2_V - M_V, x64, GREEN);
    }
    else
    {
      PrintBmpOrRect(tft, SD, BTN_OFF, CENTER_H, HEIGHT - FONT_2_V - M_V, x64, RED);
    }
  }
}
void ClockButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("ClockButton_Clicked");
  if (State == mainMenu)
  {
    State = subSettingsMenu;
    DrawRTCSettingsSubMenu(tft, SD);
  }
}

// --- Submenus ---

void HomeIcon_Clicked(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("HomeIcon_Clicked");
  if (State != mainMenu)
  {
    State = mainMenu;
    DrawMainScreen(tft, SD);
  }
}

void EventButton_Clicked_1_1(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("1"); // Button number
}
void EventButton_Clicked_1_2(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("2"); // Button number
}
void EventButton_Clicked_1_3(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("3"); // Button number
}
void EventButton_Clicked_1_4(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("4"); // Button number
}
void EventButton_Clicked_2_1(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("5"); // Button number
}
void EventButton_Clicked_2_2(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("6"); // Button number
}
void EventButton_Clicked_2_3(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("7"); // Button number
}
void EventButton_Clicked_2_4(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("8"); // Button number
}
void EventButton_Clicked_3_1(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("9"); // Button number
}
void EventButton_Clicked_3_2(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("10"); // Button number
}
void EventButton_Clicked_3_3(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("11"); // Button number
}
void EventButton_Clicked_3_4(MCUFRIEND_kbv &tft, SdFat &SD)
{
  Serial.println("12"); // Button number
}