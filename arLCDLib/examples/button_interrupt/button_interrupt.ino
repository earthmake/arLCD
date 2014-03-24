#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;
volatile boolean ezLCDInt = false; // flag to indicate interrupt

volatile int x1Pos = 10; // horizontal position for button 1 
volatile int x2Pos = 210; // horizontal position for button 2 
int yPos = 70; // vertical position of both buttons
int width = 100;
int height = 100;
int radius = 20;
int alignment = 0; // 0=centered, 1=right, 2=left, 3=bottom, 4=top 
int option = 1; // 1=draw, 2=disabled, 3=toggle pressed, 4=toggle not pressed,
// 5=toggle pressed disabled, 6=toggle not pressed disabled.

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.sendCommand("cfgio 9 touch_int low quiet");
  ezLCDInt = false;
  //lcd.sendCommand("bridge USBISPx");
  lcd.cls( BLACK, WHITE );
  lcd.font("0");
  lcd.xy("ct");      //move to center top of screen
  lcd.print("Button Test To Turn On LED On D13\" \"ct");//print centered text
  lcd.xy("ct");      //move to center top of screen
  lcd.print("\\[20y");//move down one row Note the two \\ characters
  lcd.print("Using Interrupts\" \"ct");//print centered text
  lcd.fontw( 1, "sans24" );
  lcd.theme( 1, 9, 3, 0, 0, 0, 8, 8, 8, 1, 1 );
  lcd.theme( 2, 5, 20, 3, 3, 3, 4, 4, 4, 2, 1 );
  lcd.string( 1, "ON" ); // stringId 1
  lcd.string( 2, "OFF" ); // stringId 2
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 1, 1 );
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 2, 2 );

  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  lcd.drawLed( 160, 80, 12, BLACK, WHITE);

  attachInterrupt(0, ezLCDevent, RISING );  
}

void loop()
{
  if(  ezLCDInt )
  {
    ezLCDInt = false;
	lcd.wstack(0);
    if( lcd.currentWidget == 1 ) {// if Button 1 is pressed:
      digitalWrite( LED_PIN, HIGH ); // turn LED on
      lcd.drawLed( 160, 80, 12, LIME, WHITE);
    }else if( lcd.currentWidget == 2 ) {// if Button 2 was pressed:
      digitalWrite( LED_PIN, LOW ); // turn LED off
      lcd.drawLed( 160, 80, 12, BLACK, WHITE);
    }
  }
}

void ezLCDevent( void ) {
  ezLCDInt = true;
}
