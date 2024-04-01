// --- menu.cpp ---

// #include "main.h"
#include "menu.h"
#include "display.h"

/* ---- Menu class definicions ---- */
Menu::Menu(MCUFRIEND_kbv &tft, SdFat &SD) : tft(tft), SD(SD)
{
  // Main menu button clickevents
  mainScreenButtons[0] = TouchButton(8, 4, x64, x64, SprinkleButton_Clicked);
  mainScreenButtons[1] = TouchButton(88, 4, x64, x64, ChainButton_Clicked);
  mainScreenButtons[2] = TouchButton(168, 4, x64, x64, TestButton_Clicked);
  mainScreenButtons[3] = TouchButton(248, 4, x64, x64, HumidityButton_Clicked);
  mainScreenButtons[4] = TouchButton(48, 154, x64, x64, SettingsButton_Clicked);
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
  DrawMainScreen(tft, SD);
  MH.State = mainMenu;
  MH.mainSwitch = false;
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
    for (size_t i = 0; i < mainScreenButtonCount; i++)
    {
      mainScreenButtons[i].ifPressedThenActivate(x, y, tft, SD, MH);
    }
  }
  else
  {
    for (size_t i = 0; i < subMenuButtonCount; i++)
    {
      subMenuButtons[i].ifPressedThenActivate(x, y, tft, SD, MH);
    }
  }
}

/* ---- Button Clickevents ----- */
// --- Main Screen---
void SprinkleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("SprinkleButton_Clicked");
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
  debug("MainToggleButton_Clicked - ");
  if (MH.State == mainMenu)
  {
    MH.mainSwitch = !MH.mainSwitch;
    if (MH.mainSwitch)
    {
      PrintLabel(tft, strBtnCenterBottom2, CENTER_H, HEIGHT - FONT_2_V - M_V, 2, BLACK);
      PrintLabel(tft, strBtnCenterBottom1, CENTER_H, HEIGHT - FONT_2_V - M_V, 2);
      PrintBmpOrRect(tft, SD, BTN_ON, CENTER_H - x32, HEIGHT - x64 - FONT_2_V - 2 * M_V, x64, GREEN);
      debugln("mainSwitch set to ON");
    }
    else
    {

      PrintLabel(tft, strBtnCenterBottom1, CENTER_H, HEIGHT - FONT_2_V - M_V, 2, BLACK);
      PrintLabel(tft, strBtnCenterBottom2, CENTER_H, HEIGHT - FONT_2_V - M_V, 2);
      PrintBmpOrRect(tft, SD, BTN_OFF, CENTER_H - x32, HEIGHT - x64 - FONT_2_V - 2 * M_V, x64, RED);
      debugln("mainSwitch set to OFF");
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
void ExecuteClickEvent(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH, Point clickPos)
{
  switch (MH.State)
  {
  case subPeriodsChoser:
    if (clickPos == BTN_1_4)
    {
      if (MH.periods[0].isActive)
      {
        PrintBmpOrRect(tft, SD, OFF_SWITCH_LABEL, SLOT_1_4, RED);
        MH.periods[0].isActive = false;
      }
      else
      {
        PrintBmpOrRect(tft, SD, ON_SWITCH_LABEL, SLOT_1_4, GREEN);
        MH.periods[0].isActive = true;
      }
    }
    if (clickPos == BTN_2_4)
    {
      if (MH.periods[1].isActive)
      {
        PrintBmpOrRect(tft, SD, OFF_SWITCH_LABEL, SLOT_2_4, RED);
        MH.periods[1].isActive = false;
      }
      else
      {
        PrintBmpOrRect(tft, SD, ON_SWITCH_LABEL, SLOT_2_4, GREEN);
        MH.periods[1].isActive = true;
      }
    }
    if (clickPos == BTN_3_4)
    {
      if (MH.periods[2].isActive)
      {
        PrintBmpOrRect(tft, SD, OFF_SWITCH_LABEL, SLOT_3_4, RED);
        MH.periods[2].isActive = false;
      }
      else
      {
        PrintBmpOrRect(tft, SD, ON_SWITCH_LABEL, SLOT_3_4, GREEN);
        MH.periods[2].isActive = true;
      }
    }
    break;
  case subChoseRelay:
    if (MH.page == 0)
    {
    }
    else if (MH.page == 1)
    {
    }
    break;
  case subTimingRelay:
    break;
  case subAutomaticTiming:
    break;
  case subChainSprinkle:
    break;
  case subTesting:
    if (MH.page == 0)
    {
    }
    else if (MH.page == 1)
    {
    }
    break;
  case subHumiditySetting:
    break;
  case subSettingsMenu:
    break;
  case subRealTimeSetting:
    break;
  default:
    break;
  }
}

void HomeIcon_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("HomeIcon_Clicked");
  if (MH.State != mainMenu)
  {
    MH.Reset();
    DrawMainScreen(tft, SD);
  }
}

void EventButton_Clicked_1_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("1"); // Button number
  ExecuteClickEvent(tft, SD, MH, {1, 1});
}
void EventButton_Clicked_1_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("2"); // Button number
  ExecuteClickEvent(tft, SD, MH, {2, 1});
}
void EventButton_Clicked_1_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("3"); // Button number
  ExecuteClickEvent(tft, SD, MH, {3, 1});
}
void EventButton_Clicked_1_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("4"); // Button number
  ExecuteClickEvent(tft, SD, MH, {4, 1});
}
void EventButton_Clicked_2_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("5"); // Button number
  ExecuteClickEvent(tft, SD, MH, {1, 2});
}
void EventButton_Clicked_2_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("6"); // Button number
  ExecuteClickEvent(tft, SD, MH, {2, 2});
}
void EventButton_Clicked_2_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("7"); // Button number
  ExecuteClickEvent(tft, SD, MH, {3, 2});
}
void EventButton_Clicked_2_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("8"); // Button number
  ExecuteClickEvent(tft, SD, MH, {4, 2});
}
void EventButton_Clicked_3_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("9"); // Button number
  ExecuteClickEvent(tft, SD, MH, {1, 3});
}
void EventButton_Clicked_3_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("10"); // Button number
  ExecuteClickEvent(tft, SD, MH, {2, 3});
}
void EventButton_Clicked_3_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("11"); // Button number
  ExecuteClickEvent(tft, SD, MH, {3, 3});
}
void EventButton_Clicked_3_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
  debugln("12"); // Button number
  ExecuteClickEvent(tft, SD, MH, {4, 3});
}
