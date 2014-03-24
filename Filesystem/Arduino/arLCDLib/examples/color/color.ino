/*
 * color.ino displays pre-defined colors
 */
 
#include <ezLCDLib.h>

ezLCD3 lcd;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls();
  for(int i=0; i < 16; i++)
  {
    lcd.color(i);    
    lcd.xy(i*19,0);
    lcd.box(19,100,FILL);
  }
  for(int i=16; i < 168; i++)  
  {
    lcd.color(i);    
    int pos = (2*(i-12));
    lcd.xy(pos,110);
    lcd.box(2,100,FILL);
  }  
}

void loop(){}

