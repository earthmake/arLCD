// 
// Modified by Rich Obermeyer 1/14/2014.
// Modified by Jonathan Doerr 3/12/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
 * radio.ino
 * radio buttons select the blink rate of an LED
 */

#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;
volatile boolean ezLCDInt = false;

int xPos = 90;  // horizontal position
int yPos = 80;   // vertical position
int width = 150;
int height = 35;
int option = 5; // 0=remove, 1=draw, 2=disabled, 3=checked,
// 4=draw first unchecked, 5=draw first checked

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls(BLACK,WHITE);
  lcd.font("0");
  lcd.xy("ct");
  lcd.print("Radio Button Demo\" \"ct");
  lcd.fontw( 1, "sans24" );
  //            t emb   b emb     text  -  disa  circle -  dcir  backg  font
  lcd.theme( 1, NAVY, POWDERBLUE, WHITE, BLACK, GRAY, BLACK, BLACK, LIME, BLACK, 1 );
  lcd.xy(20,30);
  lcd.string( 1, "Slow" );  // stringId 1
  lcd.string( 2, "Faster" );  // stringId 2
  lcd.string( 3, "Fastest" );  // stringId 3
  lcd.radioButton( 1, xPos, yPos,       width, height, 5, 1, 1 );//first
  lcd.radioButton( 2, xPos, yPos + 50,  width, height, 1, 1, 2 );
  lcd.radioButton( 3, xPos, yPos + 100, width, height, 1, 1, 3 );

  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  lcd.drawLed(  40, 50, 12, BLACK, WHITE);
  lcd.drawLed( 100, 50, 12, BLACK, WHITE);
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  lcd.drawLed( 220, 50, 12, BLACK, WHITE);
  lcd.drawLed( 280, 50, 12, BLACK, WHITE);
}

int rate = 1000; // blink delay 

void loop()
{
    if ( lcd.wvalue(1) == 1 )
      rate = 1000;
    if ( lcd.wvalue(2) == 1 )
      rate = 500;
    if ( lcd.wvalue(3) == 1 )
      rate = 200;
    blink();  
    delay(100);
}

void blink()
{  
  digitalWrite( LED_PIN, HIGH ); // turn LED on
  lcd.drawLed(  40, 50, 12, RED, WHITE);
  lcd.drawLed( 100, 50, 12, WHITE, WHITE);
  lcd.drawLed( 160, 50, 12, NAVY, WHITE);
  lcd.drawLed( 220, 50, 12, GREEN, WHITE);
  lcd.drawLed( 280, 50, 12, ORANGE, WHITE);
  delay(rate);
  digitalWrite( LED_PIN, LOW );  // turn LED off
  lcd.drawLed(  40, 50, 12, BLACK, WHITE);
  lcd.drawLed( 100, 50, 12, BLACK, WHITE);
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  lcd.drawLed( 220, 50, 12, BLACK, WHITE);
  lcd.drawLed( 280, 50, 12, BLACK, WHITE);
  delay(rate);
}



