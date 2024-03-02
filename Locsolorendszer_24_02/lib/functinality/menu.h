// ---- menu.h ----

#ifndef MENU_H
#define MENU_H

enum menuStates
{
    mainMenu,
    timePeriods,
    realySettings,
    realTimeSettings,
    chainSprinkle,
    humiditySettings,
    settingsMenu
};

/* ---- Button Clickevents ----- */

/**
 * dw
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