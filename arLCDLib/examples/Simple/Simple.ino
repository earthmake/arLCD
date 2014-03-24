// 
// Modified by Jonathan Doerr March 12, 2014
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
 
#include <ezLCDLib.h>

#define led 13

ezLCD3 lcd;
volatile boolean ezLCDInt = false; // flag to indicate interrupt

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.light(100,1,25);
  lcd.cls();
  lcd.font("Sans24");
  lcd.color(WHITE);
  lcd.picture(275,0,"em.gif");
  lcd.xy(15,110);
  // the \\[6m will change draw color to yellow and \\[3m will chagne it back to white. "LC" puts text in Left Center of display.
  lcd.print("What are you going to\r   \\[6mMake\\[3m Today?\" \"LC");
 }

void loop()
{
  if(  ezLCDInt )                 //do nothing till ezLCDInt becomes true
  {
    detachInterrupt(0);
    ezLCDInt = false;             //reset ezLCDInt flag
/*


*/

    attachInterrupt(0, ezLCDevent, LOW);   
  }
}

void ezLCDevent( void ) {
  ezLCDInt = true;
}
