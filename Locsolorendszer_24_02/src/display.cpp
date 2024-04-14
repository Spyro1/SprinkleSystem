// ---- display.cpp ----

#include "display.h"

/* ---- Drawing fucntions ---- */

void DrawMainScreen(MCUFRIEND_kbv &tft, SdFat &SD)
{ // Főképernyő
    tft.fillScreen(BLACK);
    // Draw top buttons
    PrintBmpOrRect(tft, SD, SPRINKLER_ICON_ON, M_H, M_V, x64, GREEN);             // Bal felső ikon
    PrintBmpOrRect(tft, SD, CHAIN_ICON, M_H * 3 + x64, M_V, x64, PURPLE);         // Bal fent közép ikon
    PrintBmpOrRect(tft, SD, TEST_ICON, M_H * 5 + x64 * 2, M_V, x64, GREENYELLOW); // Jobb fent közép ikon
    PrintBmpOrRect(tft, SD, HUMIDITY_ICON, M_H * 7 + x64 * 3, M_V, x64, CYAN);    // Jobb fent ikon
    // Draw top button labels
    PrintLabel(tft, strBtnLeftTop, M_H + x32, M_V * 2 + x64);
    PrintLabel(tft, strBtnLeftCenter, M_H * 3 + x64 * 3 / 2, M_V * 2 + x64);
    PrintLabel(tft, strBtnRightCenter, M_H * 5 + x64 * 5 / 2, M_V * 2 + x64);
    PrintLabel(tft, strBtnRightTop, M_H * 7 + x64 * 7 / 2, M_V * 2 + x64);
    // Print Main Title
    PrintLabel(tft, strMainTitle, CENTER_H, M_V * 6 + x64 + FONT_1_V, 3); // Locsolórendzser
    // Draw Separating lines
    tft.drawFastHLine(20, M_V * 7 + x64 + FONT_1_V + FONT_3_V, 280, CYAN);
    tft.drawFastHLine(20, M_V * 7 + x64 + FONT_1_V + FONT_3_V + 1, 280, CYAN);
    // Print real time below line
    PrintRTCToMainScreen(tft, TimeSpan(1234)); // Valós idő
    // Draw bottom buttons
    const int bottomIconYCoord = HEIGHT - x64 - FONT_2_V - 2 * M_V;
    PrintBmpOrRect(tft, SD, SETTINGS_ICON, CENTER_H - x64 * 3 / 2 - 2 * M_H, bottomIconYCoord, x64, LIGHTGREY); // Bal alsó ikon
    PrintBmpOrRect(tft, SD, BTN_OFF, CENTER_H - x32, bottomIconYCoord, x64, RED);                               // Közép alsó ikon
    PrintBmpOrRect(tft, SD, CLOCK_ICON, CENTER_H + x32 + 2 * M_H, bottomIconYCoord, x64, NAVY);                 // Jobb alsó ikon
    // Draw bottom button labels
    PrintLabel(tft, strBtnLeftBottom, CENTER_H - x64 - 2 * M_H, HEIGHT - FONT_2_V - M_V);
    PrintLabel(tft, strBtnCenterBottom2, CENTER_H, HEIGHT - FONT_2_V - M_V, 2);
    PrintLabel(tft, strBtnRightBottom, CENTER_H + x64 + 2 * M_H, HEIGHT - FONT_2_V - M_V);
    debugln("MainScreen_Drawed");
}

void DrawRTCSettingsSubMenu(MCUFRIEND_kbv &tft, SdFat &SD)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, CLOCK_ICONx32, SUBMENUICON_POS, x32);
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);
    // Print title
    PrintLabel(tft, strRealTimeSettings, CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Settings
    PrintLabel(tft, ":", COL_2_3_SEPERATOR, 3);
    // Num fields
    PrintNumberField(tft, 2);
    PrintNumberField(tft, 3);
    // Draw num Editor field
    PrintLabel(tft, strHour, COL_2_LABEL, 2);         // Óra label
    PrintLabel(tft, strMinute, COL_3_LABEL, 2);       // Perc label
    PrintLabel(tft, strSave, COL_4_LABEL_B + x32, 2); // Mentés label
    PrintLabel(tft, strBack, COL_1_LABEL + x32, 2);   // Vissza label
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_2);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_3);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_2);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_3);
    // Draw Save and Exit buttons
    PrintBmpOrRect(tft, SD, EXIT_ICON, SLOT_2_1, RED);
    PrintBmpOrRect(tft, SD, OK_ICON, SLOT_2_4, GREEN);
    debugln("RTCScreen_Drawed");
}

void DrawPeriodSubMenu(MCUFRIEND_kbv &tft, SdFat &SD)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, SPRINKLER_ICONx32, SUBMENUICON_POS, x32); // x32-es óra ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);      // x32-es home ikon
    // Print title
    PrintLabel(tft, strPreiodSettings, CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Period buttons
    tft.drawRoundRect(SLOT_1_2, x64 + 80, x64, RADIUS, WHITE);                          // 1. időszak háttere
    tft.drawRoundRect(SLOT_2_2, x64 + 80, x64, RADIUS, WHITE);                          // 2. időszak háttere
    tft.drawRoundRect(SLOT_3_2, x64 + 80, x64, RADIUS, WHITE);                          // 3. időszak háttere
    PrintLabel(tft, strFirstPeriod, CENTER_H, SUBTITLE_H + M_V * 2 + x16, 2);           // 1. időszak szöveg
    PrintLabel(tft, strSecondPeriod, CENTER_H, SUBTITLE_H + M_V * 3 + x64 + x16, 2);    // 2. időszak szöveg
    PrintLabel(tft, strThirdPeriod, CENTER_H, SUBTITLE_H + M_V * 4 + x64 * 2 + x16, 2); // 3. időszak szöveg
    // On-off Switches
    PrintBmpOrRect(tft, SD, OFF_SWITCH_LABEL, SLOT_1_4, x64, RED);
    PrintBmpOrRect(tft, SD, OFF_SWITCH_LABEL, SLOT_2_4, x64, RED);
    PrintBmpOrRect(tft, SD, OFF_SWITCH_LABEL, SLOT_3_4, x64, RED);
    PrintBmpOrRect(tft, SD, AUTOMATIC_ICON, SLOT_1_1, x64, DARKCYAN);
    PrintBmpOrRect(tft, SD, AUTOMATIC_ICON, SLOT_2_1, x64, DARKCYAN);
    PrintBmpOrRect(tft, SD, AUTOMATIC_ICON, SLOT_3_1, x64, DARKCYAN);
    debugln("PeriodScreen_Drawed");
}
void DrawRelayChooserSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, int periodNumber)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, SPRINKLER_ICONx32, SUBMENUICON_POS, x32); // x32-es óra ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);      // x32-es home ikon
    // Print title
    if (periodNumber == 1)
        PrintLabel(tft, strFirstPeriod, CENTER_H, M_V * 2, 3);
    else if (periodNumber == 2)
        PrintLabel(tft, strSecondPeriod, CENTER_H, M_V * 2, 3);
    else if (periodNumber == 3)
        PrintLabel(tft, strThirdPeriod, CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Realy icons
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_1_1, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_1_2, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_1_3, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_1_4, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_2_1, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_2_2, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_2_3, x64, WHITE);
    PrintBmpOrRect(tft, SD, RELAY_ICON, SLOT_2_4, x64, WHITE);
    // Print Relay Numbers
    PrintRelayChoserNumbering(tft, SD, 1, BLACK);
    // Bottom navigation buttons
    PrintBmpOrRect(tft, SD, LEFT_ARROW, SLOT_3_1, x64, BLUE);
    PrintBmpOrRect(tft, SD, RIGHT_ARROW, SLOT_3_4, x64, BLUE);
    debugv(periodNumber);
    debugln(" - RelayChooserScreen_Drawed");
}
void DrawRelayTimingSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, RELAY_ICONx32, SUBMENUICON_POS, x32); // x32-es realy ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);  // x32-es home ikon
    // Print title
    String temp = String(MH.currentPeriod) + String("/") + String(MH.currentRelay) + String(strRelay);
    PrintLabel(tft, temp.c_str(), CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Filed labels
    PrintLabel(tft, strHour, COL_1_LABEL, 1);     // Óra label
    PrintLabel(tft, strMinute, COL_2_LABEL, 1);   // Perc label
    PrintLabel(tft, strDuration, COL_3_LABEL, 1); // Időt. label
    PrintLabel(tft, strSave, COL_4_LABEL_T, 1);   // Mentés label
    PrintLabel(tft, strBack, COL_4_LABEL_B, 1);   // vissza Label
    PrintLabel(tft, "p", x32 + COL_3_CENTER, 3);  // "p" label
    PrintLabel(tft, ":", COL_1_2_SEPERATOR, 3);
    // Num Fileds
    PrintNumberField(tft, 1, MH.getCurrentRelay().getStart().hours());   // Hour
    PrintNumberField(tft, 2, MH.getCurrentRelay().getStart().minutes()); // Minute
    PrintNumberField(tft, 3, MH.getCurrentRelay().getDuration());        // Duration
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_1, x64);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_2, x64);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_3, x64);
    PrintBmpOrRect(tft, SD, OK_ICON, SLOT_1_4, x64, GREEN);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_1, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_2, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_3, x64);
    PrintBmpOrRect(tft, SD, EXIT_ICON, SLOT_3_4, x64, RED);
    debugv(MH.currentPeriod);
    debug("/");
    debugv(MH.currentRelay);
    debugln(" - TimingScreen_Drawed");
}
void DrawChainSprinkleSubMenu(MCUFRIEND_kbv &tft, SdFat &SD)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, CHAIN_ICONx32, SUBMENUICON_POS, x32); // x32-es chain ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);  // x32-es home ikon
    // Print title
    PrintLabel(tft, strBtnLeftCenter, CENTER_H, M_V * 2, 3); // Sorban
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Num Fileds
    PrintNumberField(tft, 1, 0); // Relétől szám
    PrintNumberField(tft, 2, 0); // Reléig szám
    PrintNumberField(tft, 3, 0); // Időtartam szám
    // Filed labels
    PrintLabel(tft, strFromRelay, COL_1_LABEL, 1);     // Relétől label
    PrintLabel(tft, strToRelay, COL_2_LABEL, 1);       // Reléig label
    PrintLabel(tft, strDuration, COL_3_LABEL, 1);      // Időtartam label
    PrintLabel(tft, "p", x32 + COL_3_CENTER, 3);       // "p" label
    PrintLabel(tft, "->", COL_1_2_SEPERATOR, 3);       // Nyíl label
    PrintLabel(tft, strStart, COL_4_LABEL_B + x16, 2); // Indítás label
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_1, x64);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_2, x64);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_3, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_1, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_2, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_3, x64);
    PrintBmpOrRect(tft, SD, START_ICON, SLOT_2_4, x64, GREEN);
    debugln("ChainScreen_Drawed");
}
void DrawTestSubMenu(MCUFRIEND_kbv &tft, SdFat &SD)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, TEST_ICONx32, SUBMENUICON_POS, x32); // x32-es chain ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32); // x32-es home ikon
    // Print title
    PrintLabel(tft, strBtnRightCenter, CENTER_H, M_V * 2, 3); // Sorban
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw test switches
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_1_1, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_1_2, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_1_3, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_1_4, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_2_1, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_2_2, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_2_3, x64, LIGHTGREY);
    PrintBmpOrRect(tft, SD, OFF_SWITCH, SLOT_2_4, x64, LIGHTGREY);
    // Print Relay Numbers
    PrintRelayChoserNumbering(tft, SD, 1, BLACK);
    // Bottom navigation buttons
    PrintBmpOrRect(tft, SD, LEFT_ARROW, SLOT_3_1, x64, CYAN);
    PrintBmpOrRect(tft, SD, BTN_INACTIVE, SLOT_3_2, x64, RED);
    PrintBmpOrRect(tft, SD, RIGHT_ARROW, SLOT_3_4, x64, CYAN);
    PrintLabel(tft, strReset, COL_3_LABEL + x32, 1);
    debugln("TestScreen_Drawed");
}

void DrawSettingsSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, SETTINGS_ICONx32, SUBMENUICON_POS, x32); // x32-es chain ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);     // x32-es home ikon
    // Print title
    PrintLabel(tft, strBtnLeftBottom, CENTER_H, M_V * 2, 3); // Sorban
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    debugln("SettingsScreen_Drawed");
}

void DrawHumiditySubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, HUMIDITY_ICONx32, SUBMENUICON_POS, x32); // x32-es chain ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);     // x32-es home ikon
    // Print title
    PrintLabel(tft, strBtnRightTop, CENTER_H, M_V * 2, 3); // Sorban
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Humidity sensitivty button settings
    PrintLabel(tft, strSenitivity, COL_2_LABEL, 2);   // Erzekenyseg label
    PrintNumberField(tft, 2, MH.humiditySensitivity); // Érzékenység szám
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_2, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_2, x64);
    debugln("HumidityScreen_Drawed");
}

void DrawAutomaticTimingSubMenu(MCUFRIEND_kbv &tft, SdFat &SD, menuHandeler &MH)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, SD, AUTOMATIC_ICONx32, SUBMENUICON_POS, x32); // x32-es realy ikon
    PrintBmpOrRect(tft, SD, HOME_ICONx32, SUBMENUHOME_POS, x32);      // x32-es home ikon
    // Print title
    if (MH.currentPeriod == 1)
        PrintLabel(tft, strFirstPeriod, CENTER_H, M_V * 2, 3);
    if (MH.currentPeriod == 2)
        PrintLabel(tft, strSecondPeriod, CENTER_H, M_V * 2, 3);
    if (MH.currentPeriod == 3)
        PrintLabel(tft, strThirdPeriod, CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_1, x64);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_2, x64);
    PrintBmpOrRect(tft, SD, UP_ARROW, SLOT_1_3, x64);
    PrintBmpOrRect(tft, SD, OK_ICON, SLOT_1_4, x64, GREEN);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_1, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_2, x64);
    PrintBmpOrRect(tft, SD, DOWN_ARROW, SLOT_3_3, x64);
    PrintBmpOrRect(tft, SD, EXIT_ICON, SLOT_3_4, x64, RED);
    // Filed labels
    PrintLabel(tft, strHour, COL_1_LABEL, 1);     // Óra label
    PrintLabel(tft, strMinute, COL_2_LABEL, 1);   // Perc label
    PrintLabel(tft, strDuration, COL_3_LABEL, 1); // Időt. label
    PrintLabel(tft, strSave, COL_4_LABEL_T, 1);   // Mentés label
    PrintLabel(tft, strBack, COL_4_LABEL_B, 1);   // vissza Label
    PrintLabel(tft, "p", x32 + COL_3_CENTER, 3);  // "p" label
    PrintLabel(tft, ":", COL_1_2_SEPERATOR, 3);
    // Num Fileds
    PrintNumberField(tft, 1, MH.periods[MH.currentPeriod].realys[0].getStart().hours());   // Hour
    PrintNumberField(tft, 2, MH.periods[MH.currentPeriod].realys[0].getStart().minutes()); // Minute
    PrintNumberField(tft, 3, MH.periods[MH.currentPeriod].realys[0].getDuration());        // Duration
    debugln("TimingScreen_Drawed");
}

/* ---- Common used drawing blocks ---- */

void PrintRTCToMainScreen(MCUFRIEND_kbv &tft, const TimeSpan &realTime)
{
    char temp[9];
    sprintf(temp, "%02d:%02d:%02d", realTime.hours(), realTime.minutes(), realTime.seconds());
    tft.drawRect(CENTER_H - GetTextWidth(temp, 2) / 2, M_V * 9 + x64 + FONT_1_V + FONT_3_V, GetTextWidth(temp, 2), FONT_2_V, BLACK);
    PrintLabel(tft, temp, CENTER_H, M_V * 9 + x64 + FONT_1_V + FONT_3_V, 2);
}
void PrintSubMenuTitle(MCUFRIEND_kbv &tft, const char *title, const int fontSize, const uint16_t color)
{
    tft.setCursor(CENTER_H - GetTextWidth(title, fontSize) / 2, M_V * 2);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(title);
}
void PrintLabel(MCUFRIEND_kbv &tft, const char *label, const int x, const int y, const int fontSize, const uint16_t color)
{
    tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(label);
}
void PrintLabel(MCUFRIEND_kbv &tft, int labelValue, const int x, const int y, const int fontSize, const uint16_t color)
{
    // tft.fillRect(x - GetNumWidth(labelValue, fontSize) / 2, y, GetNumWidth(labelValue, fontSize), FONT_1_V * fontSize, BLACK); // Clear background
    tft.setCursor(x - GetNumWidth(labelValue, fontSize) / 2, y);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(labelValue);
}
void PrintDoubleLine(MCUFRIEND_kbv &tft, const int y, const int width, const uint16_t color)
{
    tft.drawFastHLine((WIDTH - width) / 2, y, width, color); // Dupla vonal
    // tft.drawFastHLine((WIDTH - width) / 2, y + 1, width, color); // Dupla vonal
}
void PrintRelayChoserNumbering(MCUFRIEND_kbv &tft, SdFat &SD, int pageNumber, const uint16_t color)
{
    int i = pageNumber == 1 ? 1 : 9;
    const int fontsize = 2;
    PrintLabel(tft, i++, x32 + SLOT_1_1 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_1_2 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_1_3 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_1_4 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_2_1 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_2_2 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_2_3 + x32, fontsize, color);
    PrintLabel(tft, i++, x32 + SLOT_2_4 + x32, fontsize, color);
}
void PrintNumberField(MCUFRIEND_kbv &tft, const int column, int value)
{
    if (column == 1)
    {
        tft.fillRect(-x32 + COL_1_CENTER, x64, x32, BLACK);
        PrintLabel(tft, value, COL_1_CENTER, 3);
    }
    else if (column == 2)
    {
        tft.fillRect(-x32 + COL_2_CENTER, x64, x32, BLACK);
        PrintLabel(tft, value, COL_2_CENTER, 3);
    }
    else if (column == 3)
    {
        tft.fillRect(-x32 + COL_3_CENTER, x64, x32, BLACK);
        PrintLabel(tft, value, COL_3_CENTER, 3);
    }
}
int GetTextWidth(const char *text, const int fontSize)
{
    return strlen(text) * FONT_1_H * fontSize + (strlen(text) - 1) * fontSize;
}
int GetNumWidth(const int number, const int fontSize)
{
    int lenght = floor(log10(number) + 1);
    return lenght * FONT_1_H * fontSize + (lenght - 1) * fontSize;
}
void PrintBmpOrRect(MCUFRIEND_kbv &tft, SdFat &SD, const char *bitmapname, const int x, const int y, const int size, const uint16_t color)
{
    // if (!bmpDraw(tft, bitmapname, x, y))
    //     tft.drawRoundRect(x, y, size, size, RADIUS, color);
    int ret = showBMP(tft, SD, bitmapname, x, y);
    debugv(bitmapname);
    switch (ret)
    {
    case 0:
        debugln(" found!");
        break;
    case 1:
        debugln(" bad position");
        break;
    case 2:
        debugln(" bad BMP ID");
        break;
    case 3:
        debugln(" wrong number of planes");
        break;
    case 4:
        debugln(" unsupported BMP format");
        break;
    case 5:
        debugln(" unsupported palette");
        break;
    default:
        debugln(" unknown");
        break;
    }
    if (ret != 0)
        tft.drawRoundRect(x, y, size, size, RADIUS, color);
}

/* ---- Drawing helper function ---- */

#define BUFFPIXEL 20
#define PALETTEDEPTH 8 // support 256-colour Palette
#define BMPIMAGEOFFSET 54
bool bmpDraw(MCUFRIEND_kbv &tft, SdFat &SD, const char *filename, int x, int y)
{

    File bmpFile;
    int bmpWidth, bmpHeight;            // W+H in pixels
    uint8_t bmpDepth;                   // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;            // Start of image data in file
    uint32_t rowSize;                   // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel in buffer (R+G+B per pixel)
    uint16_t lcdbuffer[BUFFPIXEL];      // pixel out buffer (16-bit per pixel)
    uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    boolean goodBmp = false;            // Set to true on valid header parse
    boolean flip = true;                // BMP is stored bottom-to-top
    int w, h, row, col;
    uint8_t r, g, b;
    uint32_t pos = 0;
    uint8_t lcdidx = 0;
    boolean first = true;

    if ((x >= tft.width()) || (y >= tft.height()))
        return false;

    // debugln();
    debug("\nLoading image '");
    debugv(filename);
    debugln("\'");
    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) /* == NULL*/)
    {
        debugln("File not found");
        return false;
    }

    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        debugln("File size: ");
        debugvln(read32(bmpFile));
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        debug("Image Offset: ");
        debugvln(bmpImageoffset);
        // Read DIB header
        debug("Header size: ");
        debugvln(read32(bmpFile));
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);
        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            // debug("Bit Depth: "); debugln(bmpDepth);
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            { // 0 = uncompressed

                goodBmp = true; // Supported BMP format -- proceed!
                // debug("Image size: ");
                // debug(bmpWidth);
                // debug('x');
                // debugln(bmpHeight);

                // BMP rows are padded (if needed) to 4-byte boundary
                rowSize = (bmpWidth * 3 + 3) & ~3;

                // If bmpHeight is negative, image is in top-down order.
                // This is not canon but has been observed in the wild.
                if (bmpHeight < 0)
                {
                    bmpHeight = -bmpHeight;
                    flip = false;
                }

                // Crop area to be loaded
                w = bmpWidth;
                h = bmpHeight;
                if ((x + w - 1) >= tft.width())
                    w = tft.width() - x;
                if ((y + h - 1) >= tft.height())
                    h = tft.height() - y;

                // Set TFT address window to clipped image bounds
                tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

                for (row = 0; row < h; row++)
                { // For each scanline...
                    // Seek to start of scan line.  It might seem labor-
                    // intensive to be doing this on every line, but this
                    // method covers a lot of gritty details like cropping
                    // and scanline padding.  Also, the seek only takes
                    // place if the file position actually needs to change
                    // (avoids a lot of cluster math in SD library).
                    if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    else // Bitmap is stored top-to-bottom
                        pos = bmpImageoffset + row * rowSize;
                    if (bmpFile.position() != pos)
                    { // Need seek?
                        bmpFile.seek(pos);
                        buffidx = sizeof(sdbuffer); // Force buffer reload
                    }

                    for (col = 0; col < w; col++)
                    { // For each column...
                        // Time to read more pixel data?
                        if (buffidx >= sizeof(sdbuffer))
                        { // Indeed
                            // Push LCD buffer to the display first
                            if (lcdidx > 0)
                            {
                                tft.pushColors(lcdbuffer, lcdidx, first);

                                lcdidx = 0;
                                first = false;
                            }
                            bmpFile.read(sdbuffer, sizeof(sdbuffer));
                            buffidx = 0; // Set index to beginning
                        }

                        // Convert pixel from BMP to TFT format
                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];
                        lcdbuffer[lcdidx++] = tft.color565(r, g, b);
                    } // end pixel
                }     // end scanline
                // Write any remaining data to LCD
                if (lcdidx > 0)
                {
                    tft.pushColors(lcdbuffer, lcdidx, first);
                    // tft.pushColor(lcdidx); // PROBA
                }
            } // end goodBmp
        }
    }

    bmpFile.close();
    if (!goodBmp)
    {
        debugln("BMP format not recognized.");
        return false;
    }
    return true;
}

// uint16_t read16(File f)
// {
//     uint16_t result;
//     ((uint8_t *)&result)[0] = f.read(); // LSB
//     ((uint8_t *)&result)[1] = f.read(); // MSB
//     return result;
// }

// uint32_t read32(File f)
// {
//     uint32_t result;
//     ((uint8_t *)&result)[0] = f.read(); // LSB
//     ((uint8_t *)&result)[1] = f.read();
//     ((uint8_t *)&result)[2] = f.read();
//     ((uint8_t *)&result)[3] = f.read(); // MSB
//     return result;
// }
uint16_t read16(File &f)
{
    uint16_t result; // read little-endian
    f.read(&result, sizeof(result));
    return result;
}

uint32_t read32(File &f)
{
    uint32_t result;
    f.read(&result, sizeof(result));
    return result;
}
uint8_t showBMP(MCUFRIEND_kbv &tft, SdFat &SD, const char *nm, int x, int y)
{
    File bmpFile;
    int bmpWidth, bmpHeight;         // W+H in pixels
    uint8_t bmpDepth;                // Bit depth (currently must be 24, 16, 8, 4, 1)
    uint32_t bmpImageoffset;         // Start of image data in file
    uint32_t rowSize;                // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
    uint16_t lcdbuffer[(1 << PALETTEDEPTH) + BUFFPIXEL], *palette = NULL;
    uint8_t bitmask, bitshift;
    boolean flip = true; // BMP is stored bottom-to-top
    int w, h, row, col, lcdbufsiz = (1 << PALETTEDEPTH) + BUFFPIXEL, buffidx;
    uint32_t pos;          // seek position
    boolean is565 = false; //

    uint16_t bmpID;
    uint16_t n; // blocks read
    uint8_t ret;

    if ((x >= tft.width()) || (y >= tft.height()))
        return 1; // off screen

    bmpFile = SD.open(nm);            // Parse BMP header
    bmpID = read16(bmpFile);          // BMP signature
    (void)read32(bmpFile);            // Read & ignore file size
    (void)read32(bmpFile);            // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    (void)read32(bmpFile);            // Read & ignore DIB header size
    bmpWidth = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    n = read16(bmpFile);        // # planes -- must be '1'
    bmpDepth = read16(bmpFile); // bits per pixel
    pos = read32(bmpFile);      // format
    if (bmpID != 0x4D42)
        ret = 2; // bad ID
    else if (n != 1)
        ret = 3; // too many planes
    else if (pos != 0 && pos != 3)
        ret = 4; // format: 0 = uncompressed, 3 = 565
    else if (bmpDepth < 16 && bmpDepth > PALETTEDEPTH)
        ret = 5; // palette
    else
    {
        bool first = true;
        is565 = (pos == 3); // ?already in 16-bit format
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * bmpDepth / 8 + 3) & ~3;
        if (bmpHeight < 0)
        { // If negative, image is in top-down order.
            bmpHeight = -bmpHeight;
            flip = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if ((x + w) >= tft.width()) // Crop area to be loaded
            w = tft.width() - x;
        if ((y + h) >= tft.height()) //
            h = tft.height() - y;

        if (bmpDepth <= PALETTEDEPTH)
        { // these modes have separate palette
            // bmpFile.seek(BMPIMAGEOFFSET); //palette is always @ 54
            bmpFile.seek(bmpImageoffset - (4 << bmpDepth)); // 54 for regular, diff for colorsimportant
            bitmask = 0xFF;
            if (bmpDepth < 8)
                bitmask >>= bmpDepth;
            bitshift = 8 - bmpDepth;
            n = 1 << bmpDepth;
            lcdbufsiz -= n;
            palette = lcdbuffer + lcdbufsiz;
            for (col = 0; col < (int)n; col++)
            {
                pos = read32(bmpFile); // map palette to 5-6-5
                palette[col] = ((pos & 0x0000F8) >> 3) | ((pos & 0x00FC00) >> 5) | ((pos & 0xF80000) >> 8);
            }
        }

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
        for (row = 0; row < h; row++)
        { // For each scanline...
            // Seek to start of scan line.  It might seem labor-
            // intensive to be doing this on every line, but this
            // method covers a lot of gritty details like cropping
            // and scanline padding.  Also, the seek only takes
            // place if the file position actually needs to change
            // (avoids a lot of cluster math in SD library).
            uint8_t r, g, b; //, *sdptr;
            int lcdidx, lcdleft;
            if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
                pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
            else // Bitmap is stored top-to-bottom
                pos = bmpImageoffset + row * rowSize;
            if (bmpFile.position() != pos)
            { // Need seek?
                bmpFile.seek(pos);
                buffidx = sizeof(sdbuffer); // Force buffer reload
            }

            for (col = 0; col < w;)
            { // pixels in row
                lcdleft = w - col;
                if (lcdleft > lcdbufsiz)
                    lcdleft = lcdbufsiz;
                for (lcdidx = 0; lcdidx < lcdleft; lcdidx++)
                { // buffer at a time
                    uint16_t color;
                    // Time to read more pixel data?
                    if (buffidx >= (int)sizeof(sdbuffer))
                    { // Indeed
                        bmpFile.read(sdbuffer, sizeof(sdbuffer));
                        buffidx = 0; // Set index to beginning
                        r = 0;
                    }
                    switch (bmpDepth)
                    { // Convert pixel from BMP to TFT format
                    case 32:
                    case 24:
                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];
                        if (bmpDepth == 32)
                            buffidx++; // ignore ALPHA
                        color = tft.color565(r, g, b);
                        break;
                    case 16:
                        b = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];
                        if (is565)
                            color = (r << 8) | (b);
                        else
                            color = (r << 9) | ((b & 0xE0) << 1) | (b & 0x1F);
                        break;
                    case 1:
                    case 4:
                    case 8:
                        if (r == 0)
                            b = sdbuffer[buffidx++], r = 8;
                        color = palette[(b >> bitshift) & bitmask];
                        r -= bmpDepth;
                        b <<= bmpDepth;
                        break;
                    }
                    lcdbuffer[lcdidx] = color;
                }
                tft.pushColors(lcdbuffer, lcdidx, first);
                first = false;
                col += lcdidx;
            }                                                       // end cols
        }                                                           // end rows
        tft.setAddrWindow(0, 0, tft.width() - 1, tft.height() - 1); // restore full screen
        ret = 0;                                                    // good render
    }
    bmpFile.close();
    return (ret);
}

void DrawIconRelay(MCUFRIEND_kbv &tft, const int x, const int y)
{
    tft.fillRoundRect(x + 13, y, 38, x64, x64, BLUE); // Háttér
    tft.fillRect(x + 24, y + 59, 16, 4, DARKGREY);    // Szürke Pin rész
    tft.fillRect(x + 27, y + 60, 2, 2, LIGHTGREY);    // 1. pin
    tft.fillRect(x + 31, y + 60, 2, 2, LIGHTGREY);    // 2. pin
    tft.fillRect(x + 35, y + 60, 2, 2, LIGHTGREY);    // 3. pin
    tft.fillRect(x + 20, y + 3, 24, 8, BLUE);         // Top pin holder
    tft.fillCircle(x + 22, y + 4, 6, LIGHTGREY);      // Top left pin
    tft.fillCircle(x + 29, y + 4, 6, LIGHTGREY);      // Top center pin
    tft.fillCircle(x + 36, y + 4, 6, LIGHTGREY);      // Top right pin
    tft.fillCircle(x + 14, y + 1, 4, BLACK);          // Hole 1
    tft.fillCircle(x + 14, y + 58, 4, BLACK);         // Hole 2
    tft.fillCircle(x + 46, y + 58, 4, BLACK);         // Hole 3
    tft.fillCircle(x + 46, y + 1, 4, BLACK);          // Hole 4
}
void DrawIconX(MCUFRIEND_kbv &tft, const int x, const int y)
{
}