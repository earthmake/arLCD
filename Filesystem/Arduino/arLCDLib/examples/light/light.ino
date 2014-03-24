// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
 * light.ino displays backlight control
 */
 
#include <ezLCDLib.h>

ezLCD3 lcd;

void setup()
{
  lcd.begin( EZM_BAUD_RATE ); 
  lcd.cls(WHITE); // clear screen to white
  lcd.color(BLACK);
  lcd.font( "sans24" );
  lcd.xy("ct");
  lcd.print("Backlight variation\" \"ct");
  lcd.light(0);  // set the backlight level  
  lcd.xy( 10 ,100 );
  lcd.print("Backlight set to ");
}

void printInfo( void ) {
        lcd.color(WHITE);
        lcd.xy(180,100);
        lcd.box(70,30,FILL);
        lcd.xy(185,100);
        lcd.color(MAROON);
}

void loop()
{
  // set level in steps of 10%
  for(int i=0; i <= 100; i += 3)
  {
    lcd.light(i);  // set the backlight level  
    printInfo();
    lcd.print(i);
    delay(500); 
  }
}


