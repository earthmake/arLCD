// 
// Modified by Rich Obermeyer 1/14/2014.
// Modified by Jonathan Doerr  3/12/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
*  Robot demo 
* copy robot.gif to arLCD \ezusers\images
*/
#include <ezLCDLib.h>  

#define led 13

ezLCD3 lcd;  // create lcd object from ezLCD3

char touch = 0;
bool dir = 0;
int x = 0;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );    //baudrate is 230400 set in ezLCDLib.h
  lcd.light(10);               
  lcd.cls();
  lcd.font(0);
  
  pinMode(led, OUTPUT);    
  lcd.picture("robot.gif");
  drawLed(20, 120, 71, BLACK, GRAY); 
  drawLed(20, 200, 71, BLACK, WHITE);  
  lcd.light(100);                //backlight full bright
 }

void loop()
{
  delay(100);  
  unsigned char c = random(1,168);
  drawLed(20,200, 71, c, WHITE);  
  drawEye(10,190+x,71);
  drawLed(20,120, 71, c, WHITE);  
  drawEye(10,110+x,71);
  if((dir==0) && ((x+=5) > 20)) { dir=1;}
  if((dir==1) && ((x-=5) < 1)) { dir=0;}
}

void drawLed( char dim, int x, int y, char colorLed, char colorHigh) 
{
  lcd.xy(x,y);
  lcd.color(DIMGRAY);
  lcd.circle(dim,NOFILL);
  lcd.color(WHITE);
  lcd.arc(dim+1, 145,270,NOFILL); //circle(12,NOFILL);
 
  lcd.color(colorLed);
  lcd.circle(dim-2,FILL);
  lcd.color(colorHigh);
  lcd.arc(dim-4,180,270,NOFILL);
  lcd.arc(dim-5,180,270,NOFILL);
}

void drawEye( char dim, int x, int y )
{
  lcd.xy(x,y);
  lcd.color(BLACK);
  lcd.circle(10,FILL);
  lcd.color(WHITE);
  lcd.arc(8,180,270,NOFILL);
}
