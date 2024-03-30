// ---- display.cpp ----

#include "display.h"

/* ---- Drawing fucntions ---- */

void DrawMainScreen(MCUFRIEND_kbv &tft)
{ // Főképernyő
    tft.fillScreen(BLACK);

    // Draw top buttons
    PrintBmpOrRect(tft, "on-sprk.bmp", M_H, M_V, x64);                // Bal felső ikon
    PrintBmpOrRect(tft, "chain.bmp", M_H * 3 + x64, M_V, x64);        // Bal fent közép ikon
    PrintBmpOrRect(tft, "on-off.bmp", M_H * 5 + x64 * 2, M_V, x64);   // Jobb fent közép ikon
    PrintBmpOrRect(tft, "humidity.bmp", M_H * 7 + x64 * 3, M_V, x64); // Jobb fent ikon
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
    PrintBmpOrRect(tft, "settings.bmp", CENTER_H - x64 * 3 / 2 - 2 * M_H, bottomIconYCoord, x64); // Bal alsó ikon
    PrintBmpOrRect(tft, "on-btn.bmp", CENTER_H - x32, bottomIconYCoord, x64);                     // Közép alsó ikon
    PrintBmpOrRect(tft, "clock.bmp", CENTER_H + x32 + 2 * M_H, bottomIconYCoord, x64);            // Jobb alsó ikon
    // Draw bottom button labels
    PrintLabel(tft, strBtnLeftBottom, CENTER_H - x64 - 2 * M_H, HEIGHT - FONT_2_V - M_V);
    PrintLabel(tft, strBtnCenterBottom2, CENTER_H, HEIGHT - FONT_2_V - M_V);
    PrintLabel(tft, strBtnRightBottom, CENTER_H + x64 + 2 * M_H, HEIGHT - FONT_2_V - M_V);
}

void DrawRTCSettingsSubMenu(MCUFRIEND_kbv &tft)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, "clock32.bmp", SUBMENUICON_POS, x32);
    PrintBmpOrRect(tft, "home32.bmp", SUBMENUHOME_POS, x32);
    // Print title
    PrintLabel(tft, strRealTimeSettings, CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Settings
    PrintLabel(tft, ":", COL_2_3_SEPERATOR, 3);
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_2);
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_3);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_2);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_3);
    // Draw Save and Exit buttons
    PrintBmpOrRect(tft, EXIT_ICON, SLOT_2_1, RED);
    PrintBmpOrRect(tft, OK_ICON, SLOT_2_4, GREEN);
    // Draw num Editor field
    PrintLabel(tft, strHour, COL_2_LABEL, 2);   // Óra label
    PrintLabel(tft, strMinute, COL_3_LABEL, 2); // Perc label
    // Num fields
    PrintLabel(tft, "12", COL_2_CENTER, 3);
    PrintLabel(tft, "00", COL_3_CENTER, 3);
}

void DrawPeriodSubMenu(MCUFRIEND_kbv &tft)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, "clock32.bmp", SUBMENUICON_POS, x32); // x32-es óra ikon
    PrintBmpOrRect(tft, "home32.bmp", SUBMENUHOME_POS, x32);  // x32-es home ikon
    // Print title
    PrintLabel(tft, strPreiodSettings, CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Period buttons
    tft.drawRoundRect(SLOT_1_1 + 160, x64, RADIUS, CYAN);                                           // 1. időszak háttere
    tft.drawRoundRect(SLOT_2_1 + 160, x64, RADIUS, CYAN);                                           // 2. időszak háttere
    tft.drawRoundRect(SLOT_3_1 + 160, x64, RADIUS, CYAN);                                           // 3. időszak háttere
    PrintLabel(tft, strFirstPeriod, CENTER_H - x64 - x16, SUBTITLE_H + M_V * 2 + x16, 2);           // 1. időszak szöveg
    PrintLabel(tft, strSecondPeriod, CENTER_H - x64 - x16, SUBTITLE_H + M_V * 3 + x64 + x16, 2);    // 2. időszak szöveg
    PrintLabel(tft, strThirdPeriod, CENTER_H - x64 - x16, SUBTITLE_H + M_V * 4 + x64 * 2 + x16, 2); // 3. időszak szöveg
    // On-off Switches
    PrintBmpOrRect(tft, ON_SWITCH_LABEL, SLOT_1_4, GREEN);
    PrintBmpOrRect(tft, OFF_SWITCH_LABEL, SLOT_2_4, RED);
    PrintBmpOrRect(tft, OFF_SWITCH_LABEL, SLOT_3_4, RED);
}
void DrawTimingSubMenu(MCUFRIEND_kbv &tft)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, "realy32.bmp", SUBMENUICON_POS, x32); // x32-es realy ikon
    PrintBmpOrRect(tft, "home32.bmp", SUBMENUHOME_POS, x32);  // x32-es home ikon
    // Print title
    PrintLabel(tft, "1/1. Rele", CENTER_H, M_V * 2, 3);
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_1);
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_2);
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_3);
    PrintBmpOrRect(tft, OK_ICON, SLOT_1_4, GREEN);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_1);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_2);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_3);
    PrintBmpOrRect(tft, EXIT_ICON, SLOT_3_4, RED);
    // Filed labels
    PrintLabel(tft, strHour, COL_1_LABEL, 1);     // Óra label
    PrintLabel(tft, strMinute, COL_2_LABEL, 1);   // Perc label
    PrintLabel(tft, strDuration, COL_3_LABEL, 1); // Időt. label
    PrintLabel(tft, "p", x32 + COL_3_CENTER, 3);  // "p" label
    PrintLabel(tft, ":", COL_1_2_SEPERATOR, 3);
    // Num Fileds
    PrintLabel(tft, "21", COL_1_CENTER, 3); // Óra szám
    PrintLabel(tft, "00", COL_2_CENTER, 3); // Perc szám
    PrintLabel(tft, "10", COL_3_CENTER, 3); // Időtartam
}
void DrawChainSprinkleSubMenu(MCUFRIEND_kbv &tft)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, "chain32.bmp", SUBMENUICON_POS, x32); // x32-es chain ikon
    PrintBmpOrRect(tft, "home32.bmp", SUBMENUHOME_POS, x32);  // x32-es home ikon
    // Print title
    PrintLabel(tft, strBtnLeftCenter, CENTER_H, M_V * 2, 3); // Sorban
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw Hour Up and Down buttons
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_1);
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_2);
    PrintBmpOrRect(tft, UP_ARROW, SLOT_1_3);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_1);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_2);
    PrintBmpOrRect(tft, DOWN_ARROW, SLOT_3_3);
    PrintBmpOrRect(tft, RUN_ICON, SLOT_2_4, GREEN);
    // Filed labels
    PrintLabel(tft, strFromRelay, COL_1_LABEL, 1); // Relétől label
    PrintLabel(tft, strToRelay, COL_2_LABEL, 1);   // Reléig label
    PrintLabel(tft, strDuration, COL_3_LABEL, 1);  // Időtartam label
    PrintLabel(tft, "p", x32 + COL_3_CENTER, 3);   // "p" label
    PrintLabel(tft, "->", COL_1_2_SEPERATOR, 3);
    // Num Fileds
    PrintLabel(tft, "21", COL_1_CENTER, 3); // Relétől szám
    PrintLabel(tft, "00", COL_2_CENTER, 3); // Reléig szám
    PrintLabel(tft, "10", COL_3_CENTER, 3); // Időtartam szám
}
void DrawTestSubMenu(MCUFRIEND_kbv &tft)
{
    tft.fillScreen(BLACK);
    // Draw submenu title
    PrintBmpOrRect(tft, "test32.bmp", SUBMENUICON_POS, x32); // x32-es chain ikon
    PrintBmpOrRect(tft, "home32.bmp", SUBMENUHOME_POS, x32); // x32-es home ikon
    // Print title
    PrintLabel(tft, strBtnRightCenter, CENTER_H, M_V * 2, 3); // Sorban
    // Draw double line below title
    PrintDoubleLine(tft, x32);
    // End of subtitle
    // Draw test switches
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_1_1, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_1_2, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_1_3, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_1_4, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_2_1, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_2_2, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_2_3, LIGHTGREY);
    PrintBmpOrRect(tft, OFF_SWITCH, SLOT_2_4, LIGHTGREY);
    // Bottom navigation buttons
    PrintBmpOrRect(tft, LEFT_ARROW, SLOT_3_1, BLUE);
    PrintBmpOrRect(tft, EXIT_ICON, SLOT_3_2, RED);
    PrintBmpOrRect(tft, RIGHT_ARROW, SLOT_3_4, BLUE);
}

void DrawSettingsSubMenu(MCUFRIEND_kbv &tft)
{
}

void DrawHumiditySubMenu(MCUFRIEND_kbv &tft)
{
}

/* ---- Common used drawing blocks ---- */

void PrintRTCToMainScreen(MCUFRIEND_kbv &tft, TimeSpan realTime)
{
    char temp[9];
    sprintf(temp, "%02d:%02d:%02d", realTime.hours(), realTime.minutes(), realTime.seconds());
    PrintLabel(tft, temp, CENTER_H, M_V * 9 + x64 + FONT_1_V + FONT_3_V, 2);
}
void PrintSubMenuTitle(MCUFRIEND_kbv &tft, const char *title, int fontSize, uint16_t color)
{
    tft.setCursor(CENTER_H - GetTextWidth(title, fontSize) / 2, M_V * 2);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(title);
}
void PrintLabel(MCUFRIEND_kbv &tft, const char *label, int x, int y, int fontSize, uint16_t color)
{
    tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y /* - (FONT_1_V * fontSize) */);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(label);
}
void PrintDoubleLine(MCUFRIEND_kbv &tft, int y, int width, uint16_t color)
{
    tft.drawFastHLine((WIDTH - width) / 2, y, width, color); // Dupla vonal
    // tft.drawFastHLine((WIDTH - width) / 2, y + 1, width, color); // Dupla vonal
}
int GetTextWidth(const char *text, int fontSize)
{
    return strlen(text) * (FONT_1_H * fontSize) + (strlen(text) - 1) * fontSize;
}
void PrintBmpOrRect(MCUFRIEND_kbv &tft, const char *bitmapname, int x, int y, int size, uint16_t color)
{
    if (!bmpDraw(tft, bitmapname, x, y))
        tft.drawRoundRect(x, y, size, size, RADIUS, color);
}

/* ---- Drawing helper function ---- */

#define BUFFPIXEL 20
bool bmpDraw(MCUFRIEND_kbv &tft, const char *filename, int x, int y)
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
    uint32_t pos = 0, startTime = millis();
    uint8_t lcdidx = 0;
    boolean first = true;

    if ((x >= tft.width()) || (y >= tft.height()))
        return false;

    Serial.println();
    Serial.print(F("Loading image '"));
    Serial.print(filename);
    Serial.println('\'');
    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) /* == NULL*/)
    {
        Serial.println(F("File not found"));
        return false;
    }

    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        Serial.println(F("File size: "));
        Serial.println(read32(bmpFile));
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        Serial.print(F("Image Offset: "));
        Serial.println(bmpImageoffset, DEC);
        // Read DIB header
        Serial.print(F("Header size: "));
        Serial.println(read32(bmpFile));
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);
        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            // Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            { // 0 = uncompressed

                goodBmp = true; // Supported BMP format -- proceed!
                // Serial.print(F("Image size: "));
                // Serial.print(bmpWidth);
                // Serial.print('x');
                // Serial.println(bmpHeight);

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
                Serial.print(F("Loaded in "));
                Serial.print(millis() - startTime);
                Serial.println(" ms");
            } // end goodBmp
        }
    }

    bmpFile.close();
    if (!goodBmp)
    {
        Serial.println(F("BMP format not recognized."));
        return false;
    }
    return true;
}

uint16_t read16(File f)
{
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t read32(File f)
{
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}
