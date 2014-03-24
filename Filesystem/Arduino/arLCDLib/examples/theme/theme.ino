// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
 * theme.ino example showing the use of themes
 * TODO this example is not complete
 */
 
#include <ezLCDLib.h>

ezLCD3 lcd;

// theme parameters
int embossDkColor     = GREEN;
int embossLtColor     = WHITE;
int textColor0        = BLACK;
int textColor1        = BLACK;
int textColorDisabled = BLACK; 
int color0            = LIME;
int color1            = LIME;
int colorDisabled     = LIME;
int commonBkColor     = GRAY;    

int x1Pos = 10; // horizontal position for buttton 1 
int x2Pos = 150; // horizontal position for buttton 2 
int yPos = 40; // vertical position of both buttons
int width = 100;
int height = 100;
int radius = 0;
int alignment = 0; // 0=centered, 1=right, 2=left, 3=bottom, 4=top 
int option = 1; // 1=draw, 2=disabled, 3=toggle pressed, 4=toggle not pressed,
// 5=toggle pressed disabled, 6=toggle not pressed disabled. 

  
void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.fontw( 1, "sans24" );
  lcd.theme( 1, 9, 3, 0, 0, 0, 8, 8, 8, 1, 1 );
  lcd.cls( 0 );
  lcd.string( 1, "ON" );   // stringId 1
  lcd.string( 2, "OFF" );  // stringId 2
  
  lcd.theme( 1, AQUA, BLUE, BLACK, BLUE, BLACK, LIME, LIME, LIME, GRAY, GRAY ); // text to blue  
  lcd.theme( 2, RED, MAROON, BLACK, RED, BLACK, SALMON, DARKSALMON, LIME, GRAY, GRAY ); // text to red
  
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 1, 1 );
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 2, 2 );
}

void loop()
{
}

