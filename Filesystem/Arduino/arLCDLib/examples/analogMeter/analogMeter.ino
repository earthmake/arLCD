// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
 * analogMeter.ino displays analog meter
 */
 
#include <ezLCDLib.h>

ezLCD3 lcd;

int xPos = 50;  // horizontal position
int yPos = 30;   // vertical position
int width = 200;
int height = 200;
int option = 1; // 1=draw, 2=disabled, 3=ring, 4=accuracy
int type = 0; //  0=full, 1=half, 2=quarter.

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls( WHITE );
  lcd.fontw( 1, "0" );
  lcd.string( 1, "ANALOG" ); // stringId 1
  lcd.theme( 1, DARKSLATEGRAY,DIMGRAY, WHITE, WHITE, WHITE, BLACK, RED, MAROON, BLACK, 16 );
  lcd.analogMeter( 1, xPos,yPos, width, height, option, 0, 0, 1023, 1, 1, type );
}

void loop()
{
   int value = analogRead(0);
   lcd.wvalue(1, value);
 }
