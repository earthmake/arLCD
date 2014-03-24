// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object 

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls(); 
}

void loop(){
  int x = random(0,319); 
  int y = random(0,239);
  lcd.xy(x,y);
  lcd.color(random(1,200));
  lcd.arc(random(1,100), random(1,360), random(1,360), NOFILL );
}
