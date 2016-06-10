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

#define padThickness 6.0
#define padLength 15.0
int ballX;
int ballY;
int Y =0;
int score =0; 
float pi = 3.1415926;
float bx = 0.5;
float by = 0.5;
float alpha = -pi/3 ;
int sequence = 1 ;

void newBall(){
  bx = 0.5;
  by = 0.5;
  delay(500);
  switch(sequence){
    case 0 : 
      alpha = -pi/3;
    break ;
    case 1 :
      alpha = pi/3;
    break;
    case 2 :
      alpha = 2*pi/3;
    break ;
    case 3 :
      alpha = -2*pi/3;
    break ;
  }
  sequence = (sequence + 1) %4;
}
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
float r2x = 10.0/160.0;
float r2y = 64.0/128.0;
float joueur1;
float joueur2;
char s = '0';
char t = '0';

void drawRacket ( int rx, int ry ){
  tft.fillRect(rx-3,ry-15+1,6,30-1,ST7735_WHITE);
}
void clearRacket ( int rx, int ry) {
  tft.fillRect(rx-3,ry-15+1,6,30-1,ST7735_BLACK);
}
void player1won(){
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(100, 60);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setTextSize(1);
      tft.setTextWrap(true);
      tft.print("YOU WON");
      tft.setCursor(15,60);
      tft.print("YOU LOST");
      while (true) {
        delay(1);
      }
}
void player2won(){
      tft.fillScreen(ST7735_BLACK);
      tft.setCursor(15, 60);
      tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
      tft.setTextSize(1);
      tft.setTextWrap(true);
      tft.print("YOU WON");
      tft.setCursor(100,60);
      tft.print("YOU LOST");
      while (true) {
        delay(1);
      
}
}

void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
  delay(100);
tft.initR(INITR_BLACKTAB);
tft.fillScreen(ST7735_BLACK);
tft.setRotation(1);
tft.drawRect(0,0,160,128,ST7735_WHITE);
tft.drawLine(159,0,159,127,ST7735_BLACK);
tft.drawLine(0,0,0,127,ST7735_BLACK);
}

void loop() {

  
  // compute the new position of the ball
  bx = bx + cos(alpha)/33;
  by = by + sin(alpha)/33;

  // draw the ball
  clearBall(ballX,ballY);
  ballX = bx * 152 + 4 ;
  ballY = by * 120 + 4 ;
  if ( ballY <4 ) ballY = 4;
  if ( ballY > 124) ballY = 124;
  drawBall(ballX,ballY);


  // compute the position of the pads
  clearRacket(r1x*160,r1y*128);
  clearRacket(r2x*160,r2y*128);
  joueur1 = analogRead(A1);
  joueur1= joueur1-255;
  if(joueur1 <0) {
    joueur1 = 0;
  }
  if (joueur1 > 512) {
    joueur1 = 512;
  }
  joueur1 = 512- joueur1;
  r1y = padLength/128.0 + (joueur1/512.0)*((112.0-padLength)/128);
  joueur2 = analogRead(A0);
  
  if(joueur2 <0) {
    joueur2 = 0;
  }
  if (joueur2 > 512) {
    joueur2 = 512;
  }
  r2y = padLength/128.0 + (joueur2/512.0)*((112.0-padLength)/128); 
  drawRacket(r2x*160, r2y*128 );
  drawRacket(r1x*160, r1y*128 );

  // colisions on the top and bottom walls
  if(by <= 0){
    alpha = - alpha ;
    tone(3,220,20);
  }
  else if(by>=1){
    alpha = - alpha ;
    tone(3,220,20);
  }

  // scoring and reseting the ball 
  if ( bx <= 0){
    s = s+1;
    tone(3,220,400);
    newBall();

  }
  else if ( bx >= 1){
    t = t+1;
    tone(3,220,400);
    newBall();
  }

  // boucing off the player 1 pad
  if ( bx >= r1x && bx <= r1x+ padThickness/160.0) {
    Serial.print("r1x ");
    if (alpha >= -pi/2 && alpha <= pi/2){
      Serial.print("alpha1 ");  
      if(by >= r1y-padLength/128.0 && by <= r1y +padLength/128.0){
        Serial.print("r1y ");
        alpha = pi +( r1y - by )* 32.0*pi/padLength;
        tone(3,440,20);
      }  
    } 
    Serial.println();
  }
  // bouncing off player 2 pad
  else if ( bx <= r2x && bx>= r2x - padThickness /160.0) {
    Serial.print("r2x ");
    if ( alpha <= -pi/2 || alpha >= pi/2){
      Serial.print("alpha2 ");
      if(by >= r2y-padLength/128.0 && by <= r2y +padLength/128.0){
        Serial.print("r2y ");
        alpha = ( by - r2y)* 32.0*pi/padLength;
        tone(3,440,20);
      }
    }
    Serial.println();
 }

  // display the score
  tft.drawChar(85, 15, s, ST7735_WHITE, ST7735_BLACK, 3);
  tft.drawChar(50, 15, t, ST7735_WHITE, ST7735_BLACK, 3);

  // display the net 
  drawCenter();

  // Keep the angle between -pi and pi
  while(alpha > pi) alpha = alpha - 2*pi;
  while(alpha < -pi) alpha = alpha + 2*pi;

  // end of the game
  if(s>'9'){
    player1won();
  }
  if(t>'9'){
    player2won();
  }
  delay(2);
  }
