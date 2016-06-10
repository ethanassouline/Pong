#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

char A = '3' ;
char B = '1' ;
int Y = 0 ;
void setup() {
 
  // put your setup code here, to run once
tft.initR(INITR_BLACKTAB);
tft.fillScreen(ST7735_BLACK);
tft.setRotation(1);
tft.fillRect(5,50,6,40,ST7735_WHITE);
tft.drawRect(0,0,160,128,ST7735_WHITE);
tft.fillRect (30,100,6,6,ST7735_WHITE);
tft.drawChar(55, 15, A, ST7735_WHITE, ST7735_BLACK, 3);
tft.drawChar(95, 15, B, ST7735_WHITE, ST7735_BLACK, 3);
tft.fillRect(149,50,6,40,ST7735_WHITE);
while(Y<128){
  tft.fillRect(79,Y,2,5,ST7735_WHITE);
  Y = Y + 10;
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
