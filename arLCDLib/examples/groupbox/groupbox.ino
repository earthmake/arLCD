// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.

#include <ezLCDLib.h>

//definitions to increase readablity 
#define GROUP_THEME 1
#define STRING_1 1
#define STRING_2 2
#define STRING_3 3
#define STRING_4 4
#define GROUP_FONT 1

ezLCD3 lcd;

int xPos = 35; // horizontal position
int yPos = 50; // vertical position
int width = 250;
int height = 120;
int option = 4; // 1=left,2=disabled,3=right,4=center.

void setup()
{
  lcd.begin( EZM_BAUD_RATE );

  lcd.string( STRING_1, "Left Align");
  lcd.string( STRING_2, "Disable");
  lcd.string( STRING_3, "Right Align");
  lcd.string( STRING_4, "Center Align");
  
  lcd.fontw( GROUP_FONT, "sans24" );
  lcd.theme( GROUP_THEME, DARKSLATEGRAY, LIGHTSLATEGRAY, WHITE, WHITE, GRAY, BLACK, GRAY, BLACK, BLACK, GROUP_FONT );
 
}

void loop()
{
  lcd.cls( 0 );
  lcd.groupBox(1, xPos, yPos, width, height, LEFTJUSTIFIED,  GROUP_THEME, STRING_1 );
  delay(1000);
  lcd.cls( 0 );
  lcd.groupBox(1, xPos, yPos, width, height, DISABLE, GROUP_THEME, STRING_2 );
  delay(1000);
  lcd.cls( 0 );
  lcd.groupBox(1, xPos, yPos, width, height, RIGHTJUSTIFIED,  GROUP_THEME, STRING_3 );
  delay(1000);
  lcd.cls( 0 );
  lcd.groupBox(1, xPos, yPos, width, height, CENTERJUSTIFIED,  GROUP_THEME, STRING_4 );
  delay(1000);
}

