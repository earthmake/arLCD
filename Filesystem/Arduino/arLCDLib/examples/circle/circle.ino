#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
}

void loop()
{
  lcd.cls(); 
  int x = 160;
  int y = 120; 
  int size = 20;
  for(int i=0; i < 100; i++)
  {
     lcd.color(i);  
     lcd.circle( x, y, size, NOFILL );  
     size += 4; 
     delay(100);
  } 
}

