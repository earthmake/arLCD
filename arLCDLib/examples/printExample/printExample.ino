// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
#include <ezLCDLib.h>

ezLCD3 lcd;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls(BLACK);
  lcd.color(WHITE);
  lcd.font( 0 );
  lcd.xy("ct");
  lcd.print("Hello, World!\" \"ct");
  lcd.println();
  lcd.println(65);
  lcd.print("65 in Dec ");
  lcd.println(65,DEC);
  lcd.print("65 in Hex ");
  lcd.println(65,HEX);
  lcd.print("65 in Oct ");
  lcd.println(65,OCT);
  lcd.print("65 in BIN ");
  lcd.println(65,BIN);
  lcd.print("Pi ");
  lcd.print(3.14159);
  lcd.println();
  lcd.println(3.14159,4);
}

void loop() {}
