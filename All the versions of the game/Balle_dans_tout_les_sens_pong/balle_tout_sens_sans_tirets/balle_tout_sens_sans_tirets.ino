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
float pi = 3.1415926;
float bx = 0.5;
float by = 0.5;
float alpha = -pi/3 ;
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
tft.drawRect(0,0,160,128,ST7735_WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:
 
  bx = bx + cos(alpha)/100;
  by = by + sin(alpha)/100;
  ballX = bx * 160 ;
  ballY = by * 128 ;
  drawBall(ballX,ballY);
  if(ballY<=4){
    alpha = - alpha ;
  }
    if(ballY>=123){
    alpha = - alpha ;
  }
  if(ballX>=156){
  alpha = pi - alpha ;
  }
  if ( ballX <= 4){
    alpha = pi - alpha ;

  }
  delay(15);
  clearBall(ballX,ballY);
}
