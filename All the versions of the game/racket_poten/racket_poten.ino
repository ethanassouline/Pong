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
int r1x = 150 ;
int r1y = 64 ;
int sens = 2 ;
int joueur1;

void drawRacket ( int rx, int ry ){
  tft.fillRect(rx-3,ry-15,6,30,ST7735_WHITE);
}
void clearRacket ( int rx, int ry) {
  tft.fillRect(rx-3,ry-15,6,30,ST7735_BLACK);
}




void setup() {
  // put your setup code here, to run once:
 tft.initR(INITR_BLACKTAB);
tft.fillScreen(ST7735_BLACK);
tft.setRotation(1);


tft.drawLine(0,0,160,0,ST7735_WHITE);
tft.drawLine(0,127,160,127,ST7735_WHITE);
}
void loop() {
  // put your main code here, to run repeatedly:
  joueur1 = analogRead(A1);
  r1y = map(joueur1,0,1023,16,112); 
  
  drawRacket(r1x, r1y );
  delay(30);
  clearRacket(r1x,r1y);

   
}
