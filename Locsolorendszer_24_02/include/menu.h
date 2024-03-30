// ---- menu.h ----

#ifndef MENU_H
#define MENU_H

// #include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
#include "button.h"
#include "display.h"

#define subMenuButtonCount 13

enum menuStates
{
    mainMenu,
    timePeriods,
    timingRelaySetting,
    realTimeSetting,
    chainSprinkle,
    humiditySettings,
    settingsMenu
};

/* ---- Button Clickevents ----- */
/* --- MainScreen button events --- */
void HomeIcon_Clicked();
void SprinkleButton_Clicked();
void ChainButton_Clicked();
void TestButton_Clicked();
void HumidityButton_Clicked();
void SettingsButton_Clicked();
void MainToggleButton_Clicked();
void ClockButton_Clicked();
/* --- Table button evetns --- */
void EventButton_Clicked_1_1();
void EventButton_Clicked_1_2();
void EventButton_Clicked_1_3();
void EventButton_Clicked_1_4();
void EventButton_Clicked_2_1();
void EventButton_Clicked_2_2();
void EventButton_Clicked_2_3();
void EventButton_Clicked_2_4();
void EventButton_Clicked_3_1();
void EventButton_Clicked_3_2();
void EventButton_Clicked_3_3();
void EventButton_Clicked_3_4();

class Menu
{
    TouchButton mainScreenButtons[7]; // Main screen buttons
    TouchButton subMenuButtons[13];   // Table Buttons [12] hombe button
    MCUFRIEND_kbv &tft;               // Screen drawing reference
    bool mainSwitch = false;          // If true, then timing is processed, if false, then no automatic sprinkleing

public:
    // -- Constructor --
    Menu(MCUFRIEND_kbv &tft);
    // -- Functions --
    void RunMenu();
    void Touched(int x, int y);
};

#endif // MENU_H