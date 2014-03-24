// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/**
*  !!!!! make sure you have the line below in your startup.ezm !!!!!
*  cfgio 9 touch_int low quiet
*
*  This test code uses touch interrupt of the GPU to Signal touch events
*  Using Interrupts offloads the arduino from having to poll for touch events
*  
*/
#include <ezLCDLib.h>

#define LED_PIN 13
ezLCD3 lcd;
volatile boolean ezLCDInt = false; // flag to indicate interrupt
int result;
int x1Pos = 0; // horizontal position for buttton 1 
int x2Pos = 270; // horizontal position for buttton 2 
int yPos = 0; // vertical position of both buttons
int width = 50;
int height = 50;
int radius = 10;
int alignment = 0; // 0=centered, 1=right, 2=left, 3=bottom, 4=top 
int option = 1; // 1=draw, 2=disabled, 3=toggle pressed, 4=toggle not pressed,
// 5=toggle pressed disabled, 6=toggle not pressed disabled.
int L =50;
unsigned int temp =0;
unsigned long valueAD;
unsigned long valueAD2;
void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  showMainScreen();
  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  attachInterrupt(0, ezLCDevent, LOW);  
}
void showMainScreen( void ) {
  lcd.cls( BLACK, WHITE );
  lcd.font("0");
  lcd.light(50);
//note the use of escape sequences for color change
//  lcd.xy(55,0);
  lcd.printString("\\[55x\\[0yar\\[4mL\\[9mC\\[12mD\\[3m Hardware Test V1.0");
//  lcd.color(RED);
//  lcd.printString("L");
//  lcd.color(GREEN);
//  lcd.printString("C");
//  lcd.color(BLUE);
//  lcd.printString("D");
//  lcd.color(WHITE);  
//  lcd.printString(" Hardware Test V1.0");
  lcd.xy(65,225);
  lcd.font("1");
  lcd.printString("arLCD Firmware Version - ");
  lcd.xy(70,70);
  lcd.font("0");
  lcd.printString("Slider Adjust Brightness");
  lcd.fontw( 2, 0);
  lcd.fontw( 7, 1);
  lcd.fontw( 6, 0);
//  Theme [ID][EmbossDkColor][EmbossLtColor][TextColor0][TextColor1][TextColorDisabled][Color0][Color1][ColorDisabled][CommonBkColor][Fontw].
//           A    B    C  D  E  F   G   H    I  J  K
  lcd.theme( 0,   1,   2, 0, 0, 0,  3,  3,   1, 0, 2);
  lcd.theme( 1, 155, 152, 3, 3, 3,  4,  24,   5, 0, 2);
  lcd.theme( 2,   5,  20, 3, 3, 3,  4,  24,   5, 0, 2);
  lcd.theme( 3,   9,   3, 0, 0, 0,  8,  68,   9, 0, 2);
  lcd.theme( 4,   7,   3, 0, 0, 0,  6,  40,   6, 6, 2);
  lcd.theme( 5, 126, 118, 3, 3, 3, 35, 35,  36, 0, 2);
  lcd.theme( 6, 111, 106, 3, 3, 3, 104, 107, 101, 0, 6);
  lcd.theme( 7,  58,  48, 3, 3, 3, 14, 14,  54, 0, 7);
 
  lcd.string( 1, "UL" ); // stringId 1
  lcd.string( 2, "UR" ); // stringId 2
  lcd.string( 3, "LL" ); // stringId 1
  lcd.string( 4, "LR" ); // stringId 2
  lcd.string( 5, "%" );
  lcd.string( 7,"Calibrate Touch");
  lcd.string( 8,"Continue");
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 2, 1 );//UL
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 2, 2 );//UR
  lcd.button( 3, x1Pos, yPos+190, width, height, option, alignment, radius, 2, 3 );//LL
  lcd.button( 4, x2Pos, yPos+190, width, height, option, alignment, radius, 2, 4 );//LR
  lcd.slider( 5, 20, 100, 280, 30, 5, 100, 5, 50, 0 );//brightness
  lcd.staticText(7, 200, 225, 60, 15, 1, 7, 66);//Text area
  lcd.button( 9, 60, 140, 200, 35, option, alignment, radius, 2, 7 );//Calibrate   
}
void printInfo( void ) {
        lcd.font("0");
        lcd.color(BLACK);
        lcd.xy(115,200);
        lcd.box(120,20,FILL);
        lcd.xy(115,200);
        lcd.color(AQUA);
}
void loop()
{
  if(  ezLCDInt ) {                //do nothing till ezLCDInt becomes true
    detachInterrupt(0);
    ezLCDInt = false;             //reset ezLCDInt flag
    lcd.wstack(FIFO);
    switch ( lcd.currentWidget ) {  //switch based on last widget pressed
      case 1:                 //widget #1 pressed
        printInfo();
        if(lcd.currentInfo==PRESSED)
          lcd.printString("UL Pressed");
        if(lcd.currentInfo==RELEASED)
          lcd.printString("UL Released");
        if(lcd.currentInfo==CANCEL)
          lcd.printString("UL Cancel");
        break;
      case 2:
        printInfo();
        if(lcd.currentInfo==PRESSED)
          lcd.printString("UR Pressed");
        if(lcd.currentInfo==RELEASED)
          lcd.printString("UR Released");
        if(lcd.currentInfo==CANCEL)
          lcd.printString("UR Cancel");
          break;
      case 3:                 
        printInfo();
        if(lcd.currentInfo==PRESSED)
          lcd.printString("LL Pressed");
        if(lcd.currentInfo==RELEASED)
          lcd.printString("LL Released");
        if(lcd.currentInfo==CANCEL)
          lcd.printString("LL Cancel");
          break;
      case 4:
        printInfo();
        if(lcd.currentInfo==PRESSED)
          lcd.printString("LR Pressed");
        if(lcd.currentInfo==RELEASED)
          lcd.printString("LR Released");
        if(lcd.currentInfo==CANCEL)
          lcd.printString("LR Cancel");   
          break;

      case 9:
        lcd.calibrate();
        showMainScreen(); 
        break;

      case 5:                         //slider touched 
        lcd.light(lcd.currentData);   //set light to slider value
        break;
   
      default:
        printInfo();
        lcd.printString("Default Pressed");
        lcd.wstack(CLEAR); 
        break;
    }     
    lcd.wstack(CLEAR);
    attachInterrupt(0, ezLCDevent, LOW);  
  }
}

/**
*  ezLCDevent we get here from a touch press event and all we do is set 
*  ezLCDInt flag true
*/

void ezLCDevent( void ) {
  ezLCDInt = true;
}
