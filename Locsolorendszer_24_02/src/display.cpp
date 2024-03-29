// ---- display.cpp ----

#include "display.h"

/* ---- Drawing fucntions ---- */

void DrawMainScreen(Adafruit_TFTLCD& tft) { // Főképernyő
    tft.fillScreen(BLACK);

    // Draw top buttons
    if (!bmpDraw(tft, "on-sprk.bmp", M_H, M_V))
        tft.drawRoundRect(M_H, M_V, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Bal felső ikon
    if (!bmpDraw(tft, "chain.bmp", M_H * 3 + ICONSIZE, M_V))
        tft.drawRoundRect(M_H * 3 + ICONSIZE, M_V, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Bal fent közép ikon
    if (!bmpDraw(tft, "on-off.bmp", M_H * 5 + ICONSIZE * 2, M_V))
        tft.drawRoundRect(M_H * 5 + ICONSIZE * 2, M_V, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Jobb fent közép ikon
    if (!bmpDraw(tft, "humidity.bmp", M_H * 7 + ICONSIZE * 3, M_V))
        tft.drawRoundRect(M_H * 7 + ICONSIZE * 3, M_V, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Jobb fent ikon
    // Draw top button labels
    PrintLabel(tft, strBtnLeftTop, M_H + x32, M_V * 2 + ICONSIZE);
    PrintLabel(tft, strBtnLeftCenter, M_H * 3 + ICONSIZE * 3 / 2, M_V * 2 + ICONSIZE);
    PrintLabel(tft, strBtnRightCenter, M_H * 5 + ICONSIZE * 5 / 2, M_V * 2 + ICONSIZE);
    PrintLabel(tft, strBtnRightTop, M_H * 7 + ICONSIZE * 7 / 2, M_V * 2 + ICONSIZE);
    // Print Main Title
    PrintLabel(tft, strMainTitle, CENTER_H, M_V * 6 + ICONSIZE + FONT_1_V, 3); // Locsolórendzser
    // Draw Separating lines
    tft.drawFastHLine(20, M_V * 7 + ICONSIZE + FONT_1_V + FONT_3_V, 280, CYAN);
    tft.drawFastHLine(20, M_V * 7 + ICONSIZE + FONT_1_V + FONT_3_V + 1, 280, CYAN);
    // Print real time below line
    PrintRTCToMainScreen(tft, TimeSpan(1234)); // Valós idő
    // Draw bottom buttons 
    int bottomIconYCoord = HEIGHT - ICONSIZE - FONT_2_V - 2 * M_V;
    if (!bmpDraw(tft, "settings.bmp", CENTER_H - ICONSIZE * 3 / 2 - 2 * M_H, bottomIconYCoord))
        tft.drawRoundRect(CENTER_H - ICONSIZE * 3 / 2 - 2 * M_H, bottomIconYCoord, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Bal alsó ikon
    if (!bmpDraw(tft, "on-btn.bmp", CENTER_H - x32, bottomIconYCoord))
        tft.drawRoundRect(CENTER_H - x32, bottomIconYCoord, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Közép alsó ikon
    if (!bmpDraw(tft, "clock.bmp", CENTER_H + x32 + 2 * M_H, bottomIconYCoord))
        tft.drawRoundRect(CENTER_H + x32 + 2 * M_H, bottomIconYCoord, ICONSIZE, ICONSIZE, RADIUS, CYAN); // Jobb alsó ikon
    // Draw bottom button labels
    PrintLabel(tft, strBtnLeftBottom, CENTER_H - ICONSIZE - 2 * M_H, HEIGHT - FONT_2_V - M_V);
    PrintLabel(tft, strBtnCenterBottom2, CENTER_H, HEIGHT - FONT_2_V - M_V);
    PrintLabel(tft, strBtnRightBottom, CENTER_H + ICONSIZE + 2 * M_H, HEIGHT - FONT_2_V - M_V);
}

void DrawRTCSettingsSubMenu(Adafruit_TFTLCD &tft) {
    tft.fillScreen(BLACK);
    // Draw submenu title
    if (!bmpDraw(tft, "clock32.bmp", M_H, M_V / 2))
        tft.drawRoundRect(M_H, M_V/2, x32, x32, RADIUS, CYAN); // x32-es óra ikon
    if (!bmpDraw(tft, "home32.bmp", 320 - M_H - x32, M_V / 2))
        tft.drawRoundRect(WIDTH - M_H - x32, M_V/2, x32, x32, RADIUS, CYAN); // x32-es home ikon
    // Print title
    PrintLabel(tft, strRealTimeSettings, CENTER_H - GetTextWidth(strRealTimeSettings, 3)/2, M_V,3);
    // Draw double line below title
    PrintDoubleLine(tft, M_V + x32);
    // End of subtitle
    // Draw Settings
    PrintLabel(tft,":", CENTER_H, CENTER_V,3);
    // Draw Hour Up and Down buttons
    if (!bmpDraw(tft, "arrow-u.bmp", CENTER_H - M_H - ICONSIZE, SUBTITLE_H + M_V * 2 ))
        tft.drawRoundRect(CENTER_H - M_H - ICONSIZE, SUBTITLE_H + M_V * 2, ICONSIZE, ICONSIZE, RADIUS, CYAN); // x32-es óra ikon
    if (!bmpDraw(tft, "arrow-d.bmp", CENTER_H - M_H - ICONSIZE, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V*2 + x32))
        tft.drawRoundRect(CENTER_H - M_H - ICONSIZE, SUBTITLE_H + M_V * 2  + ICONSIZE + M_V*2 + x32, ICONSIZE, ICONSIZE, RADIUS, CYAN); // x32-es óra ikon
    if (!bmpDraw(tft, "arrow-u.bmp", CENTER_H + M_H , SUBTITLE_H + M_V * 2 ))
        tft.drawRoundRect(CENTER_H + M_H, SUBTITLE_H + M_V * 2, ICONSIZE, ICONSIZE, RADIUS, CYAN); // x32-es óra ikon
    if (!bmpDraw(tft, "arrow-d.bmp", CENTER_H + M_H, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V*2 + x32))
        tft.drawRoundRect(CENTER_H + M_H, SUBTITLE_H + M_V * 2  + ICONSIZE + M_V*2 + x32, ICONSIZE, ICONSIZE, RADIUS, CYAN); // x32-es óra ikon
    // Draw num Editor field
    tft.drawRoundRect(CENTER_H-x32-x16, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V, x32, x32, RADIUS, CYAN);   // Left hour field square
    tft.drawRoundRect(CENTER_H+x16, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V, x32, x32, RADIUS, CYAN);       // Right minute field 
    PrintLabel(tft,strHour, CENTER_H-x32*2, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V, 3);      // Óra label
    PrintLabel(tft,strMinute, CENTER_H+x16+x32, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V, 3);  // Perc label
    // Num fields
    PrintLabel(tft, "12", CENTER_H-x32, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V*2,3);
    PrintLabel(tft, "00", CENTER_H+x32, SUBTITLE_H + M_V * 2 + ICONSIZE + M_V*2,3);
    

}

void DrawPeriodSubMenu(Adafruit_TFTLCD& tft) {
    tft.fillScreen(BLACK);

    // tft.drawRoundRect(MARGIN_H, MARGIN_V / 2, x32, x32, 5, CYAN);                      // x32-es settings ikon
    // tft.drawRoundRect(320 - MARGIN_H - x32, MARGIN_V / 2, x32, x32, 5, CYAN); // x32-es home ikon
    bmpDraw(tft, "settings32.bmp", M_H, M_V / 2);                  // x32-es settings ikon
    bmpDraw(tft, "home32.bmp", 320 - M_H - x32, M_V / 2); // x32-es home ikon

    tft.setCursor(tft.width() - (10 * FONT_3_H + 9 * 3), M_V * 2);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Idozitesek");

    tft.drawFastHLine(10, M_V + x32, 300, CYAN);     // Dupla vonal
    tft.drawFastHLine(10, M_V + x32 + 1, 300, CYAN); // Dupla vonal

    tft.drawRoundRect(10, M_V * 7 + FONT_3_V, 300, OPTIONSIZE, 5, CYAN);                  // 1. időszak háttere
    tft.drawRoundRect(10, M_V * 8 + FONT_3_V + OPTIONSIZE, 300, OPTIONSIZE, 5, CYAN);     // 2. időszak háttere
    tft.drawRoundRect(10, M_V * 9 + FONT_3_V + OPTIONSIZE * 2, 300, OPTIONSIZE, 5, CYAN); // 3. időszak háttere
}
void DrawTimingSubMenu(Adafruit_TFTLCD& tft) {
    tft.fillScreen(BLACK);
}
void DrawChainSprinkleSubMenu(Adafruit_TFTLCD& tft) {
    tft.fillScreen(BLACK);
    // Top Icons
    if (!bmpDraw(tft, "chain.bmp", M_H, M_V / 2))
        tft.drawRoundRect(M_H, M_V / 2, x32, x32, RADIUS, CYAN); // x32-es chain ikon
    if (!bmpDraw(tft, "home.bmp", 320 - M_H - x32, M_V / 2))
        tft.drawRoundRect(320 - M_H - x32, M_V / 2, x32, x32, RADIUS, CYAN); // x32-es home ikon
    // Submenu Title
    PrintSubMenuTitle(tft, "Sorban locsolas", 3, WHITE);
    // Line
    tft.drawFastHLine(10, M_V + x32, 300, CYAN);     // Dupla vonal
    tft.drawFastHLine(10, M_V + x32 + 1, 300, CYAN); // Dupla vonal
    // First Relay setter column
    int lineheight = M_V + x32 + 1;
    if (!bmpDraw(tft, "up-arw.bmp", M_H, lineheight + M_V))
        tft.drawRoundRect(M_H, lineheight + M_V, ICONSIZE, ICONSIZE, RADIUS, CYAN);
    // tft.drawRoundRect()
    if (!bmpDraw(tft, "down-arw.bmp", M_H, lineheight + M_V * 3 + ICONSIZE))
        tft.drawRoundRect(M_H, lineheight + M_V * 3 + ICONSIZE, ICONSIZE, ICONSIZE, RADIUS, CYAN);
    // Last Relay setter column

    // Duration setter column

    // Start button
}
void DrawTestSubMenu(Adafruit_TFTLCD& tft) {
    tft.fillScreen(BGDARKCYAN);

    tft.drawRoundRect(M_H, M_V / 2, x32, x32, 5, CYAN);                      // x32-es settings ikon
    tft.drawRoundRect(320 - M_H - x32, M_V / 2, x32, x32, 5, CYAN); // x32-es home ikon

    PrintSubMenuTitle(tft, "Teszteles", 3, WHITE);

    PrintDoubleLine(tft, M_V + x32);   // Dupla vonal
}

void DrawSettingsSubMenu(Adafruit_TFTLCD &tft) {

}

void DrawHumiditySubMenu(Adafruit_TFTLCD &tft) {

}


/* ---- Common used drawing blocks ---- */

void PrintRTCToMainScreen(Adafruit_TFTLCD& tft, TimeSpan realTime) {
    char temp[20];
    sprintf(temp, "%2d:%02d:%02d", realTime.hours(), realTime.minutes(), realTime.seconds());
    PrintLabel(tft, temp, CENTER_H, M_V * 9 + ICONSIZE + FONT_1_V + FONT_3_V, 2);
}
void PrintSubMenuTitle(Adafruit_TFTLCD& tft, const char *title, int fontSize, uint16_t color) {
    tft.setCursor(CENTER_H - GetTextWidth(title, fontSize) / 2, M_V * 2);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(title);
}
void PrintLabel(Adafruit_TFTLCD& tft, const char *label, int x, int y, int fontSize, uint16_t color) {
    tft.setCursor(x - GetTextWidth(label, fontSize) / 2, y /* - (FONT_1_V * fontSize) */);
    tft.setTextColor(color);
    tft.setTextSize(fontSize);
    tft.print(label);
}
void PrintDoubleLine(Adafruit_TFTLCD& tft, int y, int width){
    tft.drawFastHLine((WIDTH - width) / 2, y, width, CYAN);     // Dupla vonal
    tft.drawFastHLine((WIDTH - width) / 2, y + 1, width, CYAN); // Dupla vonal
}
int GetTextWidth(const char *text, int fontSize) {
    return strlen(text) * (FONT_1_H * fontSize) + (strlen(text) - 1) * fontSize;
}

/* ---- Drawing helper function ---- */

#define BUFFPIXEL 20
bool bmpDraw(Adafruit_TFTLCD& tft, const char *filename, int x, int y)
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
