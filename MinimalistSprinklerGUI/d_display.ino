// ******** display.ino ********

// ======================== DECLARATIONS ========================
void PrintLabel(const char* label, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE);

// ======================== DRAW FUNCTIONS ========================

void DrawMainMenu(){
  // === Main title ===
  PrintLabel(strMainTitle, CENTER_H, CENTER_V - x16, 3);
  // === Real time ===
  PrintRTCToMainScreen();
  // === Sprinkle Btn ===
  tft.fillRoundRect(MAIN_1.x, MAIN_1.y, x64, x64, RADIUS, CYAN);
  PrintLabel(strSprinkle, MAIN_1.x + x32, MAIN_1.y + x32, 1, BLACK);
  // === Chain Btn ===
  tft.fillRoundRect(MAIN_2.x, MAIN_2.y, x64, x64, RADIUS, DARKCYAN);
  PrintLabel(strChain, MAIN_2.x + x32, MAIN_2.y + x32, 1, BLACK);
  // === Test Btn ===
  tft.fillRoundRect(MAIN_3.x, MAIN_3.y, x64, x64, RADIUS, GREEN);
  PrintLabel(strTest, MAIN_3.x + x32, MAIN_3.y + x32, 1, BLACK);
  // === Humidity Btn ===
  tft.fillRoundRect(MAIN_4.x, MAIN_4.y, x64, x64, RADIUS, BLUE);
  PrintLabel(strHumidity, MAIN_4.x + x32, MAIN_4.y + x32, 1, WHITE);
  // === Settings Btn ===
  tft.fillRoundRect(MAIN_5.x, MAIN_5.y, x64, x64, RADIUS, DARKGREY);
  PrintLabel(strSettings, MAIN_5.x + x32, MAIN_5.y + x32);
  // === Main Switch ===
  tft.fillRoundRect(MAIN_6.x, MAIN_6.y, x64, x64, RADIUS, RED);
  PrintLabel(strOFF, MAIN_6.x + x32, MAIN_6.y + x32, 3);
  // === Clock Btn ===
  tft.fillRoundRect(MAIN_7.x, MAIN_7.y, x64, x64, RADIUS, LIGHTGREY);
  PrintLabel(strClock, MAIN_7.x + x32, MAIN_7.y + x32, 1, BLACK);

}
void DrawSprinkleProfilesMenu(){

}
void DrawSprinkleRelayChooser(){

}
void DrawSprinkleSetter(){

}
void DrawSprinkleAutomatic(){
  
}
void DrawChainSprinkleMenu(){

}
void DrawTestMenu(){

}
void DrawHumidityMenu(){

}
void DrawSettingsMenu(){

}
void DrawClockMenu(){

}

// ---- Display helper functions ----
void PrintRTCToMainScreen()
{
    char temp[9];
    sprintf(temp, "%02d:%02d:%02d", Controller.now.hour(), Controller.now.minute(), Controller.now.second());
    tft.fillRect(CENTER_H - GetTextWidth(temp, 2) / 2 - 1, CENTER_V + x16 - GetTextHeight(2) / 2 - 1, GetTextWidth(temp, 2) + 2, GetTextHeight(2) + 2, BLACK);
    PrintLabel(temp, CENTER_H, CENTER_V + x16, 2);
}

void PrintLabel(const char* label, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE)
{
    tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y - GetTextHeight(fontSize) / 2);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(label);
}
void PrintLabel(const int labelValue, const int x, const int y, const int fontSize = 1, const uint16_t color = WHITE)
{
    // tft.fillRect(x - GetNumWidth(labelValue, fontSize) / 2, y, GetNumWidth(labelValue, fontSize), FONT_1_V * fontSize, BLACK); // Clear background
    tft.setCursor(x - GetNumWidth(labelValue, fontSize) / 2, y);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(labelValue);
}
void PrintDoubleLine(const int y, const int width, const uint16_t color)
{
    tft.drawFastHLine((WIDTH - width) / 2, y, width, color); // Dupla vonal
    // tft.drawFastHLine((WIDTH - width) / 2, y + 1, width, color); // Dupla vonal
}
void PrintRelayChoserNumbering(int pageNumber, const uint16_t color)
{
    int i = pageNumber == 1 ? 1 : 9;
    const int fontsize = 2;
    // PrintLabel(tft, i++, x32 + SLOT_1_1 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_1_2 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_1_3 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_1_4 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_1 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_2 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_3 + x32, fontsize, color);
    // PrintLabel(tft, i++, x32 + SLOT_2_4 + x32, fontsize, color);
}
void PrintNumberField(const int column, int value)
{
    if (column == 1)
    {
        tft.fillRect(-x32 + COL_1_CENTER, x64, x32, BLACK);
        PrintLabel(value, COL_1_CENTER, 3, WHITE);
    }
    else if (column == 2)
    {
        tft.fillRect(-x32 + COL_2_CENTER, x64, x32, BLACK);
        PrintLabel(value, COL_2_CENTER, 3);
    }
    else if (column == 3)
    {
        tft.fillRect(-x32 + COL_3_CENTER, x64, x32, BLACK);
        PrintLabel(value, COL_3_CENTER, 3);
    }
}
int GetTextWidth(const char *text, const int fontSize)
{
    return strlen(text) * FONT_1_H * fontSize + (strlen(text) - 1) * fontSize;
}
int GetTextHeight(const int fontSize){
  return FONT_1_V * fontSize;
}
int GetNumWidth(const int number, const int fontSize)
{
    int lenght = floor(log10(number) + 1);
    return lenght * FONT_1_H * fontSize + (lenght - 1) * fontSize;
}
