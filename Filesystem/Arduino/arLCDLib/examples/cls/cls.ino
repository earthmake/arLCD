#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls();  // clear screen to black
}

void loop(){
  delay(500); 
  lcd.cls(random(0,150)); // clear screen to random color
}
