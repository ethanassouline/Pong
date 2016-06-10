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
int Y =0;
int score =0; 
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
float r1x = 150.0/160.0 ;
float r1y = 64.0/128.0 ;
float joueur1;
char s = '0';

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
tft.drawRect(0,0,160,128,ST7735_WHITE);
tft.drawLine(159,0,159,127,ST7735_BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
 tft.drawChar(30, 15, s, ST7735_WHITE, ST7735_BLACK, 3);

  bx = bx + cos(alpha)/50;
  by = by + sin(alpha)/50;
  ballX = bx * 152 + 4 ;
  ballY = by * 120 + 4 ;
  if( ballX < 4 )ballX = 4 ;
  
 
  
  if ( ballY <4 ) ballY = 4;
  if ( ballY > 124) ballY = 124;
  
  
  
  drawBall(ballX,ballY);
  if(by<= 0  ){
    alpha = - alpha ;
  }
    if(by>=1){
    alpha = - alpha ;
  }
 
  if ( bx <= 0){
    alpha = pi - alpha ;

  }
  if ( bx >= r1x && bx<= r1x+ 3.0/160.0 && alpha >= -pi/2 && alpha <= pi/2){
    if(by >= r1y-15.0/128.0 && by <= r1y +15.0/128.0){
      alpha = pi - alpha + (r1y-by)*pi;
      s = s + 1;
      
    }
  }
  joueur1 = analogRead(A1);
  r1y = 16.0/128.0 + (joueur1/1023.0)*((112.0-16.0)/128); 
  
  drawRacket(r1x*160, r1y*128 );
  if(alpha >pi){
    alpha = alpha - 2*pi;
  }
  if ( alpha < -pi) {
    alpha = alpha + 2*pi;
  }
  delay(10);
  clearRacket(r1x*160,r1y*128);
  clearBall(ballX,ballY);
}
