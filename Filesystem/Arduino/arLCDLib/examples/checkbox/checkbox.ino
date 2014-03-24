
#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object 

int xPos = 30;  // horizontal position for widget 
int yPos = 140;   // vertical position for widget
int width = 225;
int height = 40;
int option = 1; // 1=draw unchecked, 2=disabled, 3=draw checked, 4=redraw
int touch=0;

void setup()
{
  lcd.begin( 230400 );
  lcd.fontw( 1, "sans24" );
  lcd.cls(BLACK);
  lcd.color(WHITE);
  lcd.xy(70,0);
  lcd.print("Simple CheckBox Demo");
  lcd.xy(20,25);
  lcd.print("Will also flash LED on back of display");
  lcd.string( 1, "Flash LED Faster" );   // stringId 1
  lcd.checkBox( 1, xPos, yPos, width, height, option, 1, 1 );
  lcd.drawLed(160,85,20,GREEN,WHITE);  
  pinMode(LED_BUILTIN, OUTPUT );
  digitalWrite( LED_BUILTIN, LOW );
}

int rate = 500; // blink delay 
  
void loop()
{  
 if(lcd.wstack(0) ==1) {
  if( lcd.currentInfo ==4 )     // if checkbox 1 is checked
    rate = 200;  // reduce delay
 else  // if checkbox 1 is unchecked
    rate = 500;      
  }
  blink(rate);
}

void blink(int rate)
{
  digitalWrite( LED_BUILTIN, HIGH ); // turn LED on
  lcd.drawLed(160,85,20,LIME,WHITE);   
  delay(rate);
  digitalWrite( LED_BUILTIN, LOW );  // turn LED off
  lcd.drawLed(160,85,20,GREEN,GRAY);  
  delay(rate);
}
