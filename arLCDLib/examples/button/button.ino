
#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;

int x1Pos = 10; // horizontal position for buttton 1 
int x2Pos = 210; // horizontal position for buttton 2 
int yPos = 70; // vertical position of both buttons
int width = 100;
int height = 100;
int radius = 20;
int alignment = 0; // 0=centered, 1=right, 2=left, 3=bottom, 4=top 
int option = 1; // 1=draw, 2=disabled, 3=toggle pressed, 4=toggle not pressed,
// 5=toggle pressed disabled, 6=toggle not pressed disabled.
int touch=0;
void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls( BLACK, WHITE );
  lcd.font("0");
//  lcd.printString("    Button Test To Turn On LED On D13");
  lcd.print("    Button Test To Turn On LED On D13");
  lcd.fontw( 1, "sans24" );
  lcd.theme( 1, 9, 3, 0, 0, 0, 8, 8, 8, 1, 1 );
  lcd.theme( 2, 5, 20, 3, 3, 3, 4, 4, 4, 2, 1 );
  lcd.string( 1, "ON" ); // stringId 1
  lcd.string( 2, "OFF" ); // stringId 2
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 1, 1 );
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 2, 2 );

  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
}

void loop()
{
  touch = lcd.wstack(0);
  if( touch ==1 ) {// if Button 1 is pressed:
    digitalWrite( LED_PIN, HIGH ); // turn LED on
    lcd.drawLed( 160, 50, 12, LIME, WHITE);
  }else if( touch ==2  ) { // if Button 2 was pressed:
    digitalWrite( LED_PIN, LOW ); // turn LED off
    lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  }
  delay(10);
}
