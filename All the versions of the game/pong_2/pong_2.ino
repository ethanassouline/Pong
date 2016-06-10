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
int ballX;
int ballY;
int sens = 2;
int Y =0;

void drawBall(int x, int y){
  tft.fillRect(x-3,y-3,6,6,ST7735_WHITE);
} 
void clearBall(int x, int y){
  tft.fillRect(x-3,y-3,6,6,ST7735_BLACK);

  
}
void drawCenter(){ 
   Y = 0 ;
 while(Y<128){
  tft.fillRect(79,Y,2,5,ST7735_WHITE);
  Y = Y + 10;
}
}

void setup() {
  // put your setup code here, to run once:
tft.initR(INITR_BLACKTAB);
tft.fillScreen(ST7735_BLACK);
tft.setRotation(1);
ballX = 3;
ballY = 64;
drawBall(ballX,ballY);

}

void loop() {
  // put your main code here, to run repeatedly:

 clearBall(ballX,ballY);
  if(ballX>=76 || ballX<=84){     
    drawCenter();
  }
  ballX= ballX + sens;
  drawBall(ballX,ballY);
  if(ballX>=157){
    sens = -2; 
  }
  if ( ballX <= 3){
    sens= 2 ;
  }
  delay(30);

}
