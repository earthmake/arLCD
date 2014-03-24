// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
#include <ezLCDLib.h>
ezLCD3 lcd; // create lcd object

int width;
int height;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
}

void loop(){
  lcd.cls();
  int x = 2;
  int y = 2; 
  width = lcd.getXmax();
  height = lcd.getYmax();

  for(int i=0; i < lcd.getYmax()/4; i++)
  {
     lcd.color(i);  
     lcd.xy(x, y);
     lcd.box( width, height, NOFILL );  //draw box from the previous xy location
     x = x + 2;
     y = y + 2;
     width  = width  - 4;
     height = height - 4;
     delay(100);
  } 

}

