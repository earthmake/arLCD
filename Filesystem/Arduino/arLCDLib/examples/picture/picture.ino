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
  lcd.picture(0,0,"tulips.gif"); 
  delay(100);
  lcd.picture(0,0,"winter.gif"); 
  delay(100);
  lcd.picture(0,0,"Sunset.gif"); 
  delay(100);
}

