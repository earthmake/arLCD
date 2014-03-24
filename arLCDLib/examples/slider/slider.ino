// 
// Modified by Rich Obermeyer 1/14/2014.
// Modified by Jonathan Doerr 3/12/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
 
#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;

int xPos = 30;  // horizontal position
int yPos = 100;   // vertical position
int width = 250;
int height = 60;
int option = 5; // 1=draw horizontal, 2=horizontal disabled, 3=vertical,
                // 4=vertical disabled, 5=horizontal slider,
                // 6=horizontal slider disabled, 7=vertical slider,
                //  8=vertical slider disabled
int max= 500;
int resolution = 5;
int value = 200;


void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls(BLACK);
  lcd.color(WHITE);  
  lcd.font("0");
  lcd.xy("ct");
  lcd.print("Slider Demo\" \"ct");
  lcd.fontw( 1, "Blip72" );
//             t emb   b emb      text            disa     slider handle  dslider  backg  font
  lcd.theme( 1, NAVY, POWDERBLUE,  BLACK,  BLACK,  BLACK,   NAVY, BLACK,   GRAY,   BLACK, 1 );
  lcd.slider( 1, xPos, yPos, width, height, option, max, resolution, value, 1 );
  lcd.font("1");
  lcd.xy(xPos,70);
  lcd.print("Fastest\" \"ct");
  lcd.xy(xPos+width,70);
  lcd.print("Slowest\" \"ct");

  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  lcd.drawLed(  40, 50, 12, BLACK, WHITE);
  lcd.drawLed( 100, 50, 12, BLACK, WHITE);
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  lcd.drawLed( 220, 50, 12, BLACK, WHITE);
  lcd.drawLed( 280, 50, 12, BLACK, WHITE);
}

void loop()
{
  int rate = lcd.wvalue(1); 
  blink(rate);
}

void blink(int rate)
{  
  digitalWrite( LED_BUILTIN, HIGH ); // turn LED on
  lcd.drawLed(  40, 50, 12, RED, WHITE);
  lcd.drawLed( 100, 50, 12, WHITE, WHITE);
  lcd.drawLed( 160, 50, 12, NAVY, WHITE);
  lcd.drawLed( 220, 50, 12, GREEN, WHITE);
  lcd.drawLed( 280, 50, 12, ORANGE, WHITE);
  delay(rate);
  digitalWrite( LED_BUILTIN, LOW );  // turn LED off
  lcd.drawLed(  40, 50, 12, BLACK, WHITE);
  lcd.drawLed( 100, 50, 12, BLACK, WHITE);
  lcd.drawLed( 160, 50, 12, BLACK, WHITE);
  lcd.drawLed( 220, 50, 12, BLACK, WHITE);
  lcd.drawLed( 280, 50, 12, BLACK, WHITE);
  delay(rate);
}
