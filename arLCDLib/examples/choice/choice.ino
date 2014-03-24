
#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;

int x1Pos = 20; // horizontal position for buttton 1 
int x2Pos = 120; // horizontal position for buttton 2 
int x3Pos = 220; // horizontal position for buttton 3 
int yPos = 90; // vertical position of both buttons
int width = 70;
int height = 60;
int radius = 5;
int alignment = 0; // 0=centered, 1=right, 2=left, 3=bottom, 4=top 
int option = 1; // 1=draw, 2=disabled, 3=toggle pressed, 4=toggle not pressed,
// 5=toggle pressed disabled, 6=toggle not pressed disabled.
int result= 0;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls( BLACK, MAROON );
  lcd.font("0");
  lcd.xy("ct");
  lcd.printString("Choice Example\" \"ct");
  lcd.fontw( 1, "sans24" );
  lcd.theme( 1, 9, 3, 0, 0, 0, 8, 8, 8, 1, 1 );
  lcd.string( 1, "YES" ); // stringId 1
  lcd.string( 2, "NO" ); // stringId 2
  lcd.string( 3, "CANCEL" ); // stringId 3
  lcd.string( 4, "NONE" ); // stringId 3
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 1, 1 );
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 1, 2 );
  lcd.button( 3, x3Pos, yPos, width, height, option, alignment, radius, 1, 3 );
  lcd.color( WHITE );
  lcd.xy( 120, 55 );
  lcd.printString("Got Milk?");
//void staticText( int ID, int x, int y, int width, int height, int option, int theme, int stringID);
  lcd.staticText( 4, 30, 175, 250, 30, CENTERJUSTIFIED, 1, 4 );
}

void loop()
{
  lcd.wstack(0);//this will update currentWidget, currentInfo, currentData
  if (( lcd.currentWidget == 1 ) && ( lcd.currentInfo==PRESSED )) {// if Button 1 is pressed:
    result = 1; // choice is YES
    lcd.wvalue( 4, "You have chosen YES" );  
    delay(500);
  }else
  if (( lcd.currentWidget == 2 ) && ( lcd.currentInfo==PRESSED )) {// if Button 2 is pressed:
    result = 0; // choice is NO
    lcd.wvalue( 4, "You have chosen NO" );  
    delay(500);
  }else
  if (( lcd.currentWidget == 3 ) && ( lcd.currentInfo==PRESSED )) {// if Button 3 is pressed:
    result = -1; // choice is CANCEL
    lcd.wvalue( 4, "You have chosen CANCEL" );  
    delay(500);
  }
}
