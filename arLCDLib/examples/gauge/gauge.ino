// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
 
#include <ezLCDLib.h>

ezLCD3 lcd;

int xPos = 25;  // horizontal position
int yPos = 50;   // vertical position
int width = 250;
int height = 35;
int option = 1; // 1=draw horizontal, 2=horizontal disabled, 3=vertical,
                // 4=vertical disabled, 5=redraw horizontal,
                // 6=redraw horizontal disabled, 7=redraw vertical,
                // 8=redraw vertical disabled
int min = -40;
int max = 125;
int initial = random( 0, max );

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls( BLACK, WHITE );
  lcd.xy("ct");
  lcd.print("Gauge Test\" \"ct");
  lcd.string( 1,"%" );  //set string 1 to % for gauge
  lcd.gauge( 1, xPos, yPos, width, height, option, initial, min, max, 2, 1 );
  lcd.gauge( 2, xPos, yPos+75, width, height, option, initial, min+40, max+15, 6, 1 );
  min = initial;
}

void loop()
{
  min += 2;
  lcd.wvalue( 1, min );
  lcd.wvalue( 2, random( 0, max+15 ) );
  delay(100);
  if ( min >= max ) min = random( -42, max );
}

