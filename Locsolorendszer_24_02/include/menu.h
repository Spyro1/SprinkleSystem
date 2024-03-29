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

class Menu
{
    TouchButton buttons[100];
    Adafruit_TFTLCD &tft;

    bool autoSprinkle = false; // If true, then timing is processed, if false, then no automatic sprinkleing

public:
    Menu(Adafruit_TFTLCD &tft);

    void RunMenu();
    void Touched(int x, int y);
    // -- Clickevents --
    // void MainToggleButton_Clicked();
    // -- Get Button counts --
    inline int getMainScreenButtonCount() const { return 7; }
    inline int getRTCScreenButtonCount() const { return 7; }
    inline int getPeriodButtonCount() const { return 6; }
    inline int getTimingButtonCount() const { return 8; }
    inline int getChainButtonCount() const { return 7; }
    inline int getTestButtonCount() const { return 10; }
    // -- Get Buttons --
    TouchButton *getMainScreenButtons() { return buttons; }
    TouchButton *getRTCScreenButtons() { return buttons + 7; }
    TouchButton *getPeriodButtons() { return buttons + 11; }
    TouchButton *getTimingButtons() { return buttons + 17; }
    TouchButton *getChainButtons() { return buttons + 25; }
    TouchButton *getTestButtons() { return buttons + 32; }

    // - MainScreen -
    inline TouchButton &btnMainOnOff() { return buttons[0]; }
    inline TouchButton &btnRealTime() { return buttons[1]; }
    inline TouchButton &btnSettings() { return buttons[2]; }
    inline TouchButton &btnTimingSprinkle() { return buttons[3]; }
    inline TouchButton &btnChainSprinkle() { return buttons[4]; }
    inline TouchButton &btnTestSprinkleButtoin() { return buttons[5]; }
    inline TouchButton &btnHumidity() { return buttons[6]; }
    // - RealTimeSetting -
    inline TouchButton &btnRTCHourUp() { return buttons[7]; }
    inline TouchButton &btnRTCHourDown() { return buttons[8]; }
    inline TouchButton &btnRTCMinuteUp() { return buttons[9]; }
    inline TouchButton &btnRTCMinuteDown() { return buttons[10]; }
    // - TimePeriods -
    inline TouchButton &btnPeriodEditor_1() { return buttons[11]; }
    inline TouchButton &btnPeriodSwitch_1() { return buttons[12]; }
    inline TouchButton &btnPeriodEditor_2() { return buttons[13]; }
    inline TouchButton &btnPeriodSwitch_2() { return buttons[14]; }
    inline TouchButton &btnPeriodEditor_3() { return buttons[15]; }
    inline TouchButton &btnPeriodSwitch_3() { return buttons[16]; }
    // - TimingRealys-
    inline TouchButton &btnTimingRelayUp() { return buttons[17]; }
    inline TouchButton &btnTimingRelayDown() { return buttons[18]; }
    inline TouchButton &btnTimingHourUp() { return buttons[19]; }
    inline TouchButton &btnTimingHourDown() { return buttons[20]; }
    inline TouchButton &btnTimingMinuteUp() { return buttons[21]; }
    inline TouchButton &btnTimingMinuteDown() { return buttons[22]; }
    inline TouchButton &btnTimingDurationUp() { return buttons[23]; }
    inline TouchButton &btnTimingDurationDown() { return buttons[24]; }
    // - ChainSprinkle -
    inline TouchButton &btnChainFromRelayUp() { return buttons[25]; }
    inline TouchButton &btnChainFromRelayDown() { return buttons[26]; }
    inline TouchButton &btnChainToRelayUp() { return buttons[27]; }
    inline TouchButton &btnChainToRelayDown() { return buttons[28]; }
    inline TouchButton &btnChainDurationUp() { return buttons[29]; }
    inline TouchButton &btnChainDurationDown() { return buttons[30]; }
    inline TouchButton &btnChainStart() { return buttons[31]; }
    // - Testing -
    inline TouchButton &btnTestSwitch_1_9() { return buttons[32]; }
    inline TouchButton &btnTestSwitch_2_10() { return buttons[33]; }
    inline TouchButton &btnTestSwitch_3_11() { return buttons[34]; }
    inline TouchButton &btnTestSwitch_4_12() { return buttons[35]; }
    inline TouchButton &btnTestSwitch_5_13() { return buttons[36]; }
    inline TouchButton &btnTestSwitch_6_14() { return buttons[37]; }
    inline TouchButton &btnTestSwitch_7_15() { return buttons[38]; }
    inline TouchButton &btnTestSwitch_8_16() { return buttons[39]; }
    inline TouchButton &btnTestPageLeft() { return buttons[40]; }
    inline TouchButton &btnTestPageRight() { return buttons[41]; }
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
void ClockButton_Clicked();

#endif