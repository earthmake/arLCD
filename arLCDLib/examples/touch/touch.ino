// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
 * touch.ino example for touch functions
 */

#include <ezLCDLib.h>

ezLCD3 lcd;

void setup()
{
  lcd.begin( EZM_BAUD_RATE ); 
  lcd.font(0); 
  lcd.cls(WHITE, BLACK); // clear screen to white
  lcd.xy( 80, 0);
  lcd.print("Touch the Screen");
}

void loop()
{
  if(lcd.touchS() == 1) // if is touched
  {
  lcd.cls(WHITE, BLACK); // clear screen to white
  lcd.xy( 80, 0);
  lcd.print("Touch the Screen");
    int x = lcd.touchX();
    int y = lcd.touchY();
    if(x > 0){
      lcd.xy( 80, 220);
      lcd.print("Touch=");
      lcd.print(x);
      lcd.print(",");
      lcd.print(y);
    }
    lcd.xy(x,y);
    lcd.circle(25, NOFILL);
  }
}


