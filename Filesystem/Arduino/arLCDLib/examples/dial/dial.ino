// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
 
#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;

int xPos = 100;  // horizontal position
int yPos = 85;   // vertical position
int radius = 75;
int option = 1; // 1=draw, 2=disabled.
int resolution = 25;
int value = 250;
int max = 750;
int id = 1;


void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls(BLACK);
  lcd.color(WHITE);  
  lcd.dial( id, xPos, yPos, radius, option, resolution, value, max, 2 );

  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  lcd.drawLed( 240, 50, 12, BLACK, WHITE);
}


void loop()
{
  int value = lcd.wvalue(id);
  lcd.color(BLACK);
  lcd.xy(200,180);
  lcd.box(100,50,FILL);
  lcd.color(WHITE);
  lcd.println(value,DEC);
  blink(value);
}

void blink(int rate)
{  
  digitalWrite( LED_BUILTIN, HIGH ); // turn LED on
  lcd.drawLed( 240, 50, 12, LIME, WHITE);
  delay(rate);
  digitalWrite( LED_BUILTIN, LOW );  // turn LED off
  lcd.drawLed( 240, 50, 12, BLACK, WHITE);
  delay(rate);
}
