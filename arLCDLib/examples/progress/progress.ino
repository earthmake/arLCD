// 
// Modified by Rich Obermeyer 1/14/2014.
// Modified by Jonathan Doerr 3/11/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
 
#include <ezLCDLib.h>
//definitions referencing the built in themes
#define THEME_RED 2
#define THEME_BLUE 6
//definition to improve readability
#define POSTFIX 1

ezLCD3 lcd;

int xPos = 25;  // horizontal position
int yPos = 50;   // vertical position
int width = 250;
int height = 35;
int option = 1; // 1=draw horizontal, 2=horizontal disabled, 3=vertical,
                // 4=vertical disabled, 5=redraw horizontal,
                // 6=redraw horizontal disabled, 7=redraw vertical,
                // 8=redraw vertical disabled
int value = 0;
int max= 128;
int newvalue = 0;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls( BLACK, WHITE );  
  lcd.font("0");
  lcd.xy("ct");
  lcd.print("Progress Bar Demo\" \"ct");
  lcd.string(POSTFIX,"%");  //set string 1 to % for progress bar
  lcd.progressBar( 1, xPos, yPos, width, height, option, value, max, THEME_RED ,POSTFIX);
  lcd.progressBar( 2, xPos, yPos+75, width, height, option, value, max, THEME_BLUE ,POSTFIX);
}

void loop()
{
   int value = random(0,128);
   if ( newvalue != value ) {
      lcd.wvalue(1, value);
      newvalue = value;
   }
   lcd.wvalue(2, random(0,128) );
   delay(100);
}

