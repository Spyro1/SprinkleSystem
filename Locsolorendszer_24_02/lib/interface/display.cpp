#include <Arduino.h>
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#include "display.h"

void DrawMainScreen() // Főképernyő
{
    tft.fillScreen(BLACK);

    // button1.initButton(&tft, 0,0,50,50, WHITE, YELLOW, WHITE, "Gomb", 2); // GOMB ?????
    // button1.drawButton();

    bmpDraw("on-sprk.bmp", MARGIN_H, MARGIN_V);
    bmpDraw("chain.bmp", MARGIN_H * 3 + ICONSIZE, MARGIN_V);
    bmpDraw("on-off.bmp", MARGIN_H * 5 + ICONSIZE * 2, MARGIN_V);
    bmpDraw("humidity.bmp", MARGIN_H * 7 + ICONSIZE * 3, MARGIN_V);
    // tft.drawRoundRect(MARGIN_H, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN);                    // Bal felső ikon
    // tft.drawRoundRect(MARGIN_H * 3 + ICONSIZE, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN);     // Bal fent közép ikon
    // tft.drawRoundRect(MARGIN_H * 5 + ICONSIZE * 2, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN); // Jobb fent közép ikon
    // tft.drawRoundRect(MARGIN_H * 7 + ICONSIZE * 3, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN); // Jobb fent ikon

    tft.setCursor(17, MARGIN_V * 2 + ICONSIZE);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    char temp[50];
    sprintf(temp, "%s      %s      %s    %s", strBtnLeftTop, strBtnLeftCenter, strBtnRightCenter, strBtnRightTop); // Locsolas      Sorban      Teszteles    Nedvesseg
    tft.print(temp);
    // tft.print("Locsolas      Sorban      Teszteles    Nedvesseg");

    tft.setCursor(26, MARGIN_V * 6 + ICONSIZE + FONT_1_V);
    tft.setTextColor(CYAN);
    tft.setTextSize(3);
    tft.print(strMainTitle); // Locsolórendzser

    tft.drawFastHLine(20, MARGIN_V * 9 + ICONSIZE + FONT_1_V + FONT_3_V, 280, WHITE);
    tft.drawFastHLine(20, MARGIN_V * 9 + ICONSIZE + FONT_1_V + FONT_3_V + 1, 280, WHITE);

    tft.setCursor(113, MARGIN_V * 11 + ICONSIZE + FONT_1_V + FONT_3_V);
    tft.setTextColor(CYAN);
    tft.setTextSize(2);
    tft.print("12:02:16"); // Valós óra

    // tft.drawRoundRect(48, 154, ICONSIZE, ICONSIZE, 5, CYAN);  // Bal alsó ikon
    // tft.drawRoundRect(128, 154, ICONSIZE, ICONSIZE, 5, CYAN); // Közép alsó ikon
    // tft.drawRoundRect(208, 154, ICONSIZE, ICONSIZE, 5, CYAN); // Jobb alsó ikon
    bmpDraw("settings.bmp", 48, 154);
    bmpDraw("on-btn.bmp", 128, 154);
    bmpDraw("clock.bmp", 208, 154);

    tft.setCursor(56, 222);
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
    sprintf(temp, "%s        %s           %s", strBtnLeftBottom, strBtnCenterBottom2, strBtnRightBottom);
    tft.print(temp);
    // tft.print("Idozites        Be           Ido");
}
void DrawPeriodsMenu()
{
    tft.fillScreen(BLACK);

    // tft.drawRoundRect(MARGIN_H, MARGIN_V / 2, ICONSIZE / 2, ICONSIZE / 2, 5, CYAN);                      // x32-es settings ikon
    // tft.drawRoundRect(320 - MARGIN_H - ICONSIZE / 2, MARGIN_V / 2, ICONSIZE / 2, ICONSIZE / 2, 5, CYAN); // x32-es home ikon
    bmpDraw("settings32.bmp", MARGIN_H, MARGIN_V / 2);                  // x32-es settings ikon
    bmpDraw("home32.bmp", 320 - MARGIN_H - ICONSIZE / 2, MARGIN_V / 2); // x32-es home ikon

    tft.setCursor(tft.width() - (10 * FONT_3_H + 9 * 3), MARGIN_V * 2);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Idozitesek");

    tft.drawFastHLine(10, MARGIN_V + ICONSIZE / 2, 300, CYAN);     // Dupla vonal
    tft.drawFastHLine(10, MARGIN_V + ICONSIZE / 2 + 1, 300, CYAN); // Dupla vonal

    tft.drawRoundRect(10, MARGIN_V * 7 + FONT_3_V, 300, OPTIONSIZE, 5, CYAN);                  // 1. időszak háttere
    tft.drawRoundRect(10, MARGIN_V * 8 + FONT_3_V + OPTIONSIZE, 300, OPTIONSIZE, 5, CYAN);     // 2. időszak háttere
    tft.drawRoundRect(10, MARGIN_V * 9 + FONT_3_V + OPTIONSIZE * 2, 300, OPTIONSIZE, 5, CYAN); // 3. időszak háttere
}
void DrawTestMenu()
{
    tft.fillScreen(DARKCYAN);

    tft.drawRoundRect(MARGIN_H, MARGIN_V / 2, ICONSIZE / 2, ICONSIZE / 2, 5, CYAN);                      // x32-es settings ikon
    tft.drawRoundRect(320 - MARGIN_H - ICONSIZE / 2, MARGIN_V / 2, ICONSIZE / 2, ICONSIZE / 2, 5, CYAN); // x32-es home ikon

    tft.setCursor(tft.width() - (9 * FONT_3_H + 8 * 3), MARGIN_V * 2);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Teszteles");

    tft.drawFastHLine(10, MARGIN_V + ICONSIZE / 2, 300, CYAN);     // Dupla vonal
    tft.drawFastHLine(10, MARGIN_V + ICONSIZE / 2 + 1, 300, CYAN); // Dupla vonal
}

// void listSD()
// {
//     File root;
//     root = SD.open("/");
//     printDirectory(root);
// }
void printDirectory(File dir)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            dir.rewindDirectory();
            break;
        }
        Serial.println(entry.name());
    }
    dir.rewindDirectory();
}

#define BUFFPIXEL 20
void bmpDraw(const char *filename, int x, int y)
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
        return;

    Serial.println();
    Serial.print(F("Loading image '"));
    Serial.print(filename);
    Serial.println('\'');
    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) /* == NULL*/)
    {
        Serial.println(F("File not found"));
        return;
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
                }
                Serial.print(F("Loaded in "));
                Serial.print(millis() - startTime);
                Serial.println(" ms");
            } // end goodBmp
        }
    }

    bmpFile.close();
    if (!goodBmp)
        Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

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
