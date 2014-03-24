// 
// Modified by Jonathan Doerr March 12, 2014
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
int touch = 0;
int result;

void setup()
{
  lcd.begin( );
  lcd.cls( BLACK, WHITE );
  lcd.font("0");
  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  digitalWrite( LED_PIN, HIGH );
  
//many examples of same thing for printing the banner
//  lcd.print("               Serial Monitor Test");
//using sendCommand
//  lcd.sendCommand( "XY CT");
//  lcd.print("Serial Monitor Test\" \"ct");
//using escape sequences
//  lcd.print("\\[60x\\[0ySerial Monitor Test");
//using newer library with XY string
  lcd.xy("ct");
  lcd.print("Serial Monitor Test\" \"ct");

  lcd.font("1");
  lcd.xy("cb");
  lcd.print("Press ON to send data to Serial Monitor\" \"cb");

  lcd.fontw( 1, "sans24" );
  lcd.theme( 1, GREEN, WHITE, BLACK, BLACK, BLACK, LIME, LIME, LIME, GRAY, 1 );
  lcd.theme( 2, MAROON, LIGHTSALMON, WHITE, WHITE, WHITE, RED, RED, RED, SILVER, 1 );
  lcd.string( 1, "ON" ); // stringId 1
  lcd.string( 2, "OFF" ); // stringId 2
  lcd.button( 1, x1Pos, yPos, width, height, option, alignment, radius, 1, 1 );
  lcd.button( 2, x2Pos, yPos, width, height, option, alignment, radius, 2, 2 );

  digitalWrite( LED_PIN, LOW );
  lcd.drawLed( 160, 50, 12, BLACK, WHITE );
  lcd.color(AQUA);
  lcd.font("0");
  lcd.xy(120,70);
  lcd.print("ID");
  printInfo(3,0);
  lcd.xy(120,110);
  lcd.print("Info");
  printInfo(4,0);
  lcd.xy(120,150);
  lcd.print("Data");
  printInfo(5,0);
  lcd.xy(110,210);
}

void loop()
{
  long ltemp;
  unsigned long ultemp;
  int inttemp;
  unsigned int uinttemp;
  char chartemp;
  float floattemp;
  double doubletemp;
  
    touch = lcd.wstack(0);
    if ( lcd.currentWidget != 0 ) {
      printInfo( 3, lcd.currentWidget );
      printInfo( 4, lcd.currentInfo );
      printInfo( 5, lcd.currentData );
    }
    if (( lcd.currentWidget == 1 ) && ( lcd.currentInfo == PRESSED )) {// if Button 1 is pressed:
      digitalWrite( LED_PIN, HIGH ); // turn LED on
      lcd.drawLed( 160, 50, 12, LIME, WHITE);

      ultemp = 0xa5dd;
      lcd.Debug( "Unsignedlong " );
      lcd.Debug( ultemp, "%X" );
      lcd.Debug( " " );
      lcd.Debug( ultemp );
      lcd.Debug( " " );
      lcd.Debug( ultemp, "%lu" );
      lcd.Debug( " " );
      lcd.Debug( ultemp, "%o" );
      lcd.Debug( "\r\n" );

      ltemp = 0xa5dd;
      lcd.Debug( "Long " );
      lcd.Debug( ltemp, "%X" );
      lcd.Debug( " " );
      lcd.Debug( ltemp );
      lcd.Debug( " " );
      lcd.Debug( ltemp, "%ld" );
      lcd.Debug( " " );
      lcd.Debug( ltemp, "%o" );
      lcd.Debug( "\r\n" );

      inttemp = 0xa5dd;
      lcd.Debug( "Integer " );
      lcd.Debug( inttemp, "%X" );
      lcd.Debug( " " );
      lcd.Debug( inttemp );
      lcd.Debug( " " );
      lcd.Debug( inttemp, "%i" );
      lcd.Debug( " " );
      lcd.Debug( inttemp, "%o" );
      lcd.Debug( "\r\n" );

      uinttemp = 0xa5dd;
      lcd.Debug( "Unsigned Integer " );
      lcd.Debug( uinttemp, "%X" );
      lcd.Debug( " " );
      lcd.Debug( uinttemp );
      lcd.Debug( " " );
      lcd.Debug( uinttemp, "%u" );
      lcd.Debug( " " );
      lcd.Debug( uinttemp, "%o" );
      lcd.Debug( "\r\n" );

      lcd.Debug( "Char " );
      lcd.Debug( 0x45 );
      lcd.Debug( "\r\n" );

      lcd.Debug( "String " );
      lcd.Debug( " Hello World" );
      lcd.Debug( "\r\n" );

    }else if (( lcd.currentWidget == 2  ) && ( lcd.currentInfo == PRESSED )) {// if Button 2 was pressed:
      digitalWrite( LED_PIN, LOW ); // turn LED off
      lcd.drawLed( 160, 50, 12, BLACK, WHITE);
    }
}

void printInfo( int location, int result ) {
      lcd.font("0");
      lcd.color(BLACK);
      switch(location) {
        case 1:
          lcd.xy(20,200);
          lcd.box(90,20,FILL);
          lcd.xy(20,200);
          break;
        case 2:
          lcd.xy(220,200);
          lcd.box(90,20,FILL);
          lcd.xy(220,200);
          break;
        case 3://ID
          lcd.xy(170,70);
          lcd.box(40,20,FILL);
          lcd.xy(170,70);
          break;
        case 4://Info
          lcd.xy(170,110);
          lcd.box(40,20,FILL);
          lcd.xy(170,110);
          break;
        case 5://Data
          lcd.xy(170,150);
          lcd.box(40,20,FILL);
          lcd.xy(170,150);
          break;
        default:
          lcd.xy(180,210);
          lcd.box(40,20,FILL);
          lcd.xy(180,210);
          break;
      }
      lcd.color(AQUA);
      if ( result < 256 ) 
        lcd.print( result );
}
