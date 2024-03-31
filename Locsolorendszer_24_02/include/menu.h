// ---- menu.h ----

#ifndef MENU_H
#define MENU_H

#include <SdFat.h> // Use the SdFat library
#include <MCUFRIEND_kbv.h>
#include "button.h"
#include "display.h"

#define subMenuButtonCount 13
#define mainScreenButtonCount 7

enum menuStates
{
    mainMenu,
    subPeriodsChoser,
    subChoseRelay,
    subTimingRelay,
    subAutomaticTiming,
    subRealTimeSetting,
    subChainSprinkle,
    subTesting,
    subHumiditySetting,
    subSettingsMenu
};
// ---- Menu Variables ----
menuStates State = mainMenu;
bool mainSwitch = false; // If true, then timing is processed, if false, then no automatic sprinkleing
/* ---- Button Clickevents ----- */
/* --- MainScreen button events --- */
void SprinkleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void ChainButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void TestButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void HumidityButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void SettingsButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void MainToggleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void ClockButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
/* --- Table button evetns --- */
void HomeIcon_Clicked(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_1_1(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_1_2(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_1_3(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_1_4(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_2_1(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_2_2(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_2_3(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_2_4(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_3_1(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_3_2(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_3_3(MCUFRIEND_kbv &tft, SdFat &SD);
void EventButton_Clicked_3_4(MCUFRIEND_kbv &tft, SdFat &SD);

class Menu
{
    TouchButton mainScreenButtons[7]; // Main screen buttons
    TouchButton subMenuButtons[13];   // Table Buttons [12] hombe button
    MCUFRIEND_kbv &tft;               // Screen drawing reference
    SdFat &SD;                        // SD card reading obj

public:
    // friend void SprinkleButton_Clicked();
    // -- Constructor --
    Menu(MCUFRIEND_kbv &tft, SdFat &SD);
    // -- Functions --
    void RunMenu();
    void Touched(int x, int y);
};

#endif // MENU_H