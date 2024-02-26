/*#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_ImageReader.h>*/
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

#define TS_MINX 920
#define TS_MINY 80
#define TS_MAXX 135
#define TS_MAXY 915

// For better pressure precision, we need to know the resistance between X+ and X- Use any multimeter to read it For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define SD_CS 10
#define LCD_RESET A4 // optional

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// 16 bites szinek
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define DARKCYAN 0x032D //0472

// Menü makrók
#define MARGIN_V 4  // Vertical margin
#define MARGIN_H 8  // Horizonatal margin
#define ICONSIZE 64 // Base Iconsize for buttons
#define OPTIONSIZE 61
#define FONT_1_H 7
#define FONT_2_H FONT_1_H * 2
#define FONT_3_H FONT_1_H * 3
#define FONT_1_V 5
#define FONT_2_V FONT_1_V * 2
#define FONT_3_V FONT_1_V * 3

// Make TFT Display 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// == Objects and global variables ==
/*class MyButton 
{
  uint16_t backColor;
  uint16_t borderColor;
  uint16_t fontColor;

  uint16_t activebackColor;
  uint16_t activeborderColor;
  uint16_t activeFontColor;

  char text[50];
  short fontSize;
  short x, y, width, height;
  short radius = 0;

  Mybutton(char text[], short fontSize, short x, short y, short width, short height){
    
    this->fontSize = fontSize;
  }

  Mybutton(char text[], short fontSize, short x, short y, short width, short height, short radius)
  {
  }

};*/

class ImageButton {
  char *filename;
  
  public:
  ImageButton(char *filename, int x, int y, int boxwidth, int boxheight) {

  }
};

Adafruit_GFX_Button button1;

/*SdFat                SD;         // SD card filesystem
Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys
*/
// == Functions ==

void DrawMainScreen() // Főképernyő
{
  tft.fillScreen(BLACK);

  //button1.initButton(&tft, 0,0,50,50, WHITE, YELLOW, WHITE, "Gomb", 2); // GOMB ?????
  //button1.drawButton();

  bmpDraw("on-sprk.bmp", MARGIN_H, MARGIN_V);
  bmpDraw("chain.bmp", MARGIN_H * 3 + ICONSIZE, MARGIN_V);
  bmpDraw("on-off.bmp", MARGIN_H * 5 + ICONSIZE * 2, MARGIN_V);
  bmpDraw("humidity.bmp", MARGIN_H * 7 + ICONSIZE * 3, MARGIN_V);
  //tft.drawRoundRect(MARGIN_H, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN);                    // Bal felső ikon
  //tft.drawRoundRect(MARGIN_H * 3 + ICONSIZE, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN);     // Bal fent közép ikon
  //tft.drawRoundRect(MARGIN_H * 5 + ICONSIZE * 2, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN); // Jobb fent közép ikon
  //tft.drawRoundRect(MARGIN_H * 7 + ICONSIZE * 3, MARGIN_V, ICONSIZE, ICONSIZE, 5, CYAN); // Jobb fent ikon

  tft.setCursor(17, MARGIN_V * 2 + ICONSIZE);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Locsolas      Sorban      Teszteles    Nedvesseg");

  tft.setCursor(26, MARGIN_V * 6 + ICONSIZE + FONT_1_V);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.print("Locsolorendszer");

  tft.drawFastHLine(20, MARGIN_V * 9 + ICONSIZE + FONT_1_V + FONT_3_V, 280, WHITE);
  tft.drawFastHLine(20, MARGIN_V * 9 + ICONSIZE + FONT_1_V + FONT_3_V + 1, 280, WHITE);

  tft.setCursor(113, MARGIN_V * 11 + ICONSIZE + FONT_1_V + FONT_3_V);
  tft.setTextColor(CYAN);
  tft.setTextSize(2);
  tft.print("12:02:16"); // Valós óra

  
  bmpDraw("settings.bmp", 48, 154);  //tft.drawRoundRect(48, 154, ICONSIZE, ICONSIZE, 5, CYAN);  // Bal alsó ikon
  bmpDraw("on-btn.bmp", 128, 154);  //tft.drawRoundRect(128, 154, ICONSIZE, ICONSIZE, 5, CYAN); // Közép alsó ikon
  bmpDraw("clock.bmp", 208, 154);  //tft.drawRoundRect(208, 154, ICONSIZE, ICONSIZE, 5, CYAN); // Jobb alsó ikon
  
  
  

  tft.setCursor(56, 222);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Idozites        Be           Ido");
}
void DrawPeriodsMenu()
{
  tft.fillScreen(DARKCYAN);

  tft.drawRoundRect(MARGIN_H, MARGIN_V / 2, ICONSIZE / 2, ICONSIZE / 2, 5, CYAN);                      // x32-es settings ikon
  tft.drawRoundRect(320 - MARGIN_H - ICONSIZE / 2, MARGIN_V / 2, ICONSIZE / 2, ICONSIZE / 2, 5, CYAN); // x32-es home ikon

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

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Paint!"));

  tft.reset();
  uint16_t identifier = tft.readID();

  // Set tft panel
  tft.begin(identifier);
  pinMode(13, OUTPUT);
  tft.setRotation(3);
  tft.fillScreen(BLACK);


  // Setup SD card
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS)) {
    Serial.println(F("Failed!"));
    //return;
  }
  Serial.println(F("OK!"));

  //listSD();

  DrawMainScreen();
  // DrawPeriodsMenu();
  delay(2000);
  digitalWrite(5, LOW);
  delay(2000);
  digitalWrite(5, HIGH);
  
}



void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  // pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    /*
    Serial.print("\tPressure = "); Serial.println(p.z);
    */

    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
    Serial.print(" (");
    Serial.print(p.x);
    Serial.print(", ");
    Serial.print(p.y);
    Serial.println(")");
  }
}




// Helper functions

File root;
void listSD()  {
    root = SD.open("/");
    printDirectory(root);
}
void printDirectory(File dir) {
    while(true) {
        File entry =  dir.openNextFile();
        if (! entry) {
            dir.rewindDirectory();
            break;
        }
        Serial.println(entry.name());
   }
   dir.rewindDirectory();
}



#define BUFFPIXEL 20
void bmpDraw(char *filename, int x, int y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      //Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        //Serial.print(F("Image size: "));
        //Serial.print(bmpWidth);
        //Serial.print('x');
        //Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        } 
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

