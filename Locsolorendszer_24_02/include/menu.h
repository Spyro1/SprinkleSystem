// ---- menu.h ----

#ifndef MENU_H
#define MENU_H

#include <SdFat.h> // Use the SdFat library
#include <MCUFRIEND_kbv.h>
#include "button.h"
#include "display.h"
#include "types.h"

#define subMenuButtonCount 13
#define mainScreenButtonCount 7

#define BTN_1_1 Point(1, 1)
#define BTN_1_2 Point(2, 1)
#define BTN_1_3 Point(3, 1)
#define BTN_1_4 Point(4, 1)
#define BTN_2_1 Point(1, 2)
#define BTN_2_2 Point(2, 2)
#define BTN_2_3 Point(3, 2)
#define BTN_2_4 Point(4, 2)
#define BTN_3_1 Point(1, 3)
#define BTN_3_2 Point(2, 3)
#define BTN_3_3 Point(3, 3)
#define BTN_3_4 Point(4, 3)

/* ---- Button Clickevents ----- */
void ExecuteClickEvent(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH, Point clickPos);
/* --- MainScreen button clickevents --- */
void SprinkleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void ChainButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void TestButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void HumidityButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void SettingsButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void MainToggleButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void ClockButton_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
/* --- Table button clickevents --- */
void HomeIcon_Clicked(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_1_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_1_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_1_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_1_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_2_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_2_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_2_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_2_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_3_1(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_3_2(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_3_3(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);
void EventButton_Clicked_3_4(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH);

class Menu
{
    TouchButton mainScreenButtons[7]; // Main screen buttons
    TouchButton subMenuButtons[13];   // Table Buttons [12] hombe button

    MCUFRIEND_kbv &tft; // Screen drawing reference
    SdFat &SD;          // SD card reading obj
    menuHandeler MH;

public:
    // -- Constructor --
    Menu(MCUFRIEND_kbv &tft, SdFat &SD);
    // -- Functions --
    void RunMenu();
    void Touched(int x, int y);
    // -- Setters --
    void setState(menuStates state) { MH.State = state; }
};

#endif // MENU_H