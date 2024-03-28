// ---- menu.h ----

#ifndef MENU_H
#define MENU_H

#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "button.h"
#include "display.h"

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

class Menu{
    TouchButton buttons[100];
    Adafruit_TFTLCD& tft;
public:
    Menu(Adafruit_TFTLCD& tft);

    void RunMenu();
    void Touched(int x, int y);
    
};





/* ---- Button Clickevents ----- */

/**
 *
 */
void HomeIcon_Clicked();
void SprinkleButton_Clicked();
void ChainButton_Clicked();
void TestButton_Clicked();
void HumidityButton_Clicked();
void SettingsButton_Clicked();
void MainToggleButton_Clicked();
void ClockButton_Clicked();

#endif