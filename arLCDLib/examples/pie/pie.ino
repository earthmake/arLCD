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
  lcd.color(WHITE);
}
int angle = 10;

void loop()
{
  lcd.cls(BLACK, random( 1, 150 ));
  lcd.lineType( random( 0, 5 ));
  lcd.xy( 160, 120 );
  lcd.pie( 80, 0, angle ); 
  delay( 250 );  
  angle = angle + 10;
  if( angle > 359 )
    angle = 10;
}
