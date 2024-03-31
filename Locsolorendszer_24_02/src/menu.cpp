// --- menu.cpp ---

// #include "main.h"
#include "menu.h"
#include "display.h"

/* ---- Menu class definicions ---- */
Menu::Menu(MCUFRIEND_kbv &tft, SdFat &SD) : tft(tft), SD(SD)
{
  // Main menu button clickevents
  btnSprinkle = TouchButton(tft, SD, MH, 8, 4, x64, x64, SprinkleButton_Clicked);
  btnChain = TouchButton(tft, SD, MH, 88, 4, x64, x64, ChainButton_Clicked);
  btnTest = TouchButton(tft, SD, MH, 168, 4, x64, x64, TestButton_Clicked);
  btnHumidity = TouchButton(tft, SD, MH, 248, 4, x64, x64, HumidityButton_Clicked);
  btnSettings = TouchButton(tft, SD, MH, 48, 154, x64, x64, SettingsButton_Clicked);
  btnMainToggle = TouchButton(tft, SD, MH, 128, 154, x64, x64, MainToggleButton_Clicked);
  btnClock = TouchButton(tft, SD, MH, 208, 154, x64, x64, ClockButton_Clicked);
  // Table button definitions
  // TouchButton btn
  //     TouchButton btn
  //         TouchButton btn
  //             TouchButton btn
  //                 TouchButton btn
  //                     TouchButton btn
  // TouchButton temp[] = {btnSprinkle, btnChain, btnTest, btnHumidity, btnSettings, btnMainToggle, btnClock};
  // mainScreenButtons = temp;
  // mainScreenButtons[0] = btnSprinkle;
  // mainScreenButtons[1] = btnChain;
  // mainScreenButtons[2] = btnTest;
  // mainScreenButtons[3] = btnHumidity;
  // mainScreenButtons[4] = btnSettings;
  // mainScreenButtons[5] = btnMainToggle;
  // mainScreenButtons[6] = btnClock;
  // // Submenu button clickevens
  // subMenuButtons[0] = TouchButton(tft, SD, MH, 8, 36, x64, x64, EventButton_Clicked_1_1);
  // subMenuButtons[1] = TouchButton(tft, SD, MH, 88, 36, x64, x64, EventButton_Clicked_1_2);
  // subMenuButtons[2] = TouchButton(tft, SD, MH, 168, 36, x64, x64, EventButton_Clicked_1_3);
  // subMenuButtons[3] = TouchButton(tft, SD, MH, 248, 36, x64, x64, EventButton_Clicked_1_4);
  // subMenuButtons[4] = TouchButton(tft, SD, MH, 8, 104, x64, x64, EventButton_Clicked_2_1);
  // subMenuButtons[5] = TouchButton(tft, SD, MH, 88, 104, x64, x64, EventButton_Clicked_2_2);
  // subMenuButtons[6] = TouchButton(tft, SD, MH, 168, 104, x64, x64, EventButton_Clicked_2_3);
  // subMenuButtons[7] = TouchButton(tft, SD, MH, 248, 104, x64, x64, EventButton_Clicked_2_4);
  // subMenuButtons[8] = TouchButton(tft, SD, MH, 8, 172, x64, x64, EventButton_Clicked_3_1);
  // subMenuButtons[9] = TouchButton(tft, SD, MH, 88, 172, x64, x64, EventButton_Clicked_3_2);
  // subMenuButtons[10] = TouchButton(tft, SD, MH, 168, 172, x64, x64, EventButton_Clicked_3_3);
  // subMenuButtons[11] = TouchButton(tft, SD, MH, 248, 172, x64, x64, EventButton_Clicked_3_4);
  // subMenuButtons[12] = TouchButton(tft, SD, MH, 284, 4, x32, x32, HomeIcon_Clicked); // Home icon
}
void Menu::RunMenu()
{
  // -- Start main screen --
  DrawMainScreen(tft, SD);
  // DrawTimingSubMenu(tft, SD);
  MH.State = mainMenu;
  MH.mainSwitch = false;
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
  debug("\nMenu: (");
  debugv(x);
  debug(", ");
  debugv(y);
  debug(") -  "); // Print actual coordinates
  if (MH.State == mainMenu)
  {
    btnSprinkle.ifPressedThenActivate(x, y);
    btnChain.ifPressedThenActivate(x, y);
    btnTest.ifPressedThenActivate(x, y);
    btnHumidity.ifPressedThenActivate(x, y);
    btnSettings.ifPressedThenActivate(x, y);
    btnMainToggle.ifPressedThenActivate(x, y);
    btnClock.ifPressedThenActivate(x, y);
    // for (size_t i = 0; i < mainScreenButtonCount; i++)
    // {
    //   mainScreenButtons[i].ifPressedThenActivate(x, y);
    // }
    debug("mainButtonsTested");
  }
  else
  {
    // for (size_t i = 0; i < subMenuButtonCount; i++)
    // {
    //   subMenuButtons[i].ifPressedThenActivate(x, y);
    // }
    debug("tableButtonsTested");
  }
}

/* ---- Button Clickevents ----- */
// --- Main Screen---

void SprinkleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("SprinkleButton_Clicked");
  // debug("MH.State=");
  // debugv(MH.State);
  if (MH.State == mainMenu)
  {
    MH.State = subPeriodsChoser;
    DrawPeriodSubMenu(tft, SD);
  }
}
void ChainButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("ChainButton_Clicked");
  if (MH.State == mainMenu)
  {
    MH.State = subChainSprinkle;
    DrawChainSprinkleSubMenu(tft, SD);
  }
}
void TestButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("TestButton_Clicked");
  if (MH.State == mainMenu)
  {
    MH.State = subTesting;
    DrawTestSubMenu(tft, SD);
  }
}
void HumidityButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("HumidityButton_Clicked");
  if (MH.State == mainMenu)
  {
    MH.State = subHumiditySetting;
    DrawHumiditySubMenu(tft, SD);
  }
}
void SettingsButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("SettingsButton_Clicked");
  if (MH.State == mainMenu)
  {
    MH.State = subSettingsMenu;
    DrawSettingsSubMenu(tft, SD);
  }
}
void MainToggleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("MainToggleButton_Clicked");
  if (MH.State == mainMenu)
  {
    MH.mainSwitch = !MH.mainSwitch;
    if (MH.mainSwitch)
    {
      PrintBmpOrRect(tft, SD, BTN_ON, CENTER_H, HEIGHT - FONT_2_V - M_V, x64, GREEN);
    }
    else
    {
      PrintBmpOrRect(tft, SD, BTN_OFF, CENTER_H, HEIGHT - FONT_2_V - M_V, x64, RED);
    }
  }
}
void ClockButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("ClockButton_Clicked");
  if (MH.State == mainMenu)
  {
    MH.State = subSettingsMenu;
    DrawRTCSettingsSubMenu(tft, SD);
  }
}

// --- Submenus ---

void HomeIcon_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("HomeIcon_Clicked");
  if (MH.State != mainMenu)
  {
    MH.State = mainMenu;
    DrawMainScreen(tft, SD);
  }
}

void EventButton_Clicked_1_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("1"); // Button number
}
void EventButton_Clicked_1_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("2"); // Button number
}
void EventButton_Clicked_1_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("3"); // Button number
}
void EventButton_Clicked_1_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("4"); // Button number
}
void EventButton_Clicked_2_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("5"); // Button number
}
void EventButton_Clicked_2_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("6"); // Button number
}
void EventButton_Clicked_2_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("7"); // Button number
}
void EventButton_Clicked_2_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("8"); // Button number
}
void EventButton_Clicked_3_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("9"); // Button number
}
void EventButton_Clicked_3_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("10"); // Button number
}
void EventButton_Clicked_3_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("11"); // Button number
}
void EventButton_Clicked_3_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("12"); // Button number
}