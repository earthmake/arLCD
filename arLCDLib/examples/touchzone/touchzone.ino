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
  lcd.cls(BLACK, WHITE); // clear screen to white
  lcd.xy( 80, 0);
// shadow( int mode, int Scolor, int Slinetype, int Slinethickness )
  lcd.shadow( 1, RED, 0, 2 );//shadow ON
//  lcd.picture( 20, 20, "winter.gif" );
  lcd.picture( 20, 20, "keypad.gif" );
//touchZone [ID][x][y][width][height][options]
//first row
  lcd.touchZone( 1,  20, 20, 46, 46, 1 );
  lcd.touchZone( 2,  78, 20, 46, 46, 1 );
  lcd.touchZone( 3, 136, 20, 46, 46, 1 );
  lcd.touchZone( 4, 194, 20, 46, 46, 1 );
//second row
  lcd.touchZone( 5,  20, 75, 46, 46, 1 );
  lcd.touchZone( 6,  78, 75, 46, 46, 1 );
  lcd.touchZone( 7, 136, 75, 46, 46, 1 );
  lcd.touchZone( 8, 194, 75, 46, 46, 1 );
//third row
  lcd.touchZone( 9,  20, 128, 46, 46, 1 );
  lcd.touchZone( 10, 78, 128, 46, 46, 1 );
  lcd.touchZone( 11, 136, 128, 46, 46, 1 );
  lcd.touchZone( 12, 194, 128, 46, 46, 1 );
//fourth row
  lcd.touchZone( 13, 78, 180, 46, 46, 1 );
}

void loop()
{

}


