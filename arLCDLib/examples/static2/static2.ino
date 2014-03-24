// 
// Modified by Rich Obermeyer 1/14/2014.
// Modified by Jonathan doerr 3/12/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
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
  lcd.xy("ct");
  lcd.printString("Button Test To Modify Static Text\" \"ct");
  lcd.fontw( 1, "sans24" );
//            t emb b emb text0 text1  disa  Frame  -  dcir  backg  font
  lcd.theme( 4,  0,     0, WHITE,  0,   RED, BLACK, 0,  0,   BLACK, 1 );
  lcd.string( 1, "ON" ); // stringId 1
  lcd.string( 2, "OFF" ); // stringId 2
  lcd.string( 3, "Hello World" ); // stringId 3
  lcd.string( 4, "Welcome World" ); // stringId 4
  lcd.string( 5, "Goodbye World");
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 2, 1 );
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 3, 2 );

  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  lcd.drawLed(  40, 50, 12, BLACK, WHITE);
  lcd.drawLed( 100, 50, 12, BLACK, WHITE);
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  lcd.drawLed( 220, 50, 12, BLACK, WHITE);
  lcd.drawLed( 280, 50, 12, BLACK, WHITE);
  lcd.staticText( 3, 40, 175, 250, 50, CENTERJUSTIFIED, 4, 3 );
}

void loop()
{
  touch = lcd.wstack(0);
  if (( lcd.currentWidget == 1 ) && ( lcd.currentInfo == PRESSED )) {// if Button 1 is pressed:
    digitalWrite( LED_PIN, HIGH ); // turn LED on
  lcd.drawLed(  40, 50, 12, RED, WHITE);
  lcd.drawLed( 100, 50, 12, WHITE, WHITE);
  lcd.drawLed( 160, 50, 12, NAVY, WHITE);
  lcd.drawLed( 220, 50, 12, GREEN, WHITE);
  lcd.drawLed( 280, 50, 12, ORANGE, WHITE);
    lcd.wvalue( 3, 4 );  
  }else 
  if(( lcd.currentWidget == 2 ) && ( lcd.currentInfo == PRESSED )) { // if Button 2 was pressed:
    digitalWrite( LED_PIN, LOW ); // turn LED off
  lcd.drawLed(  40, 50, 12, BLACK, WHITE);
  lcd.drawLed( 100, 50, 12, BLACK, WHITE);
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  lcd.drawLed( 220, 50, 12, BLACK, WHITE);
  lcd.drawLed( 280, 50, 12, BLACK, WHITE);
    lcd.wvalue( 3, 5 );  
  }
}
