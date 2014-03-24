// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.

#include <ezLCDLib.h>  

#define led 13

ezLCD3 lcd;  // create lcd object from ezLCD3

volatile boolean ezLCDInt = false; // flag to indicate interrupt
char touch = 0;
void setup()
{
  lcd.begin( EZM_BAUD_RATE );    //baudrate is 115200 set in ezLCDLib.h
  lcd.light(100);                //backlight full bright
  lcd.cls();
  lcd.font(0);
  lcd.color(WHITE);
  lcd.xy(15,110);
  lcd.printString("What are you going to \\[6mMake\\[3m Today ?"); // the \\[6m will change draw color to yellow and \\[3m will chagne it back to white
  pinMode(led, OUTPUT);    
  attachInterrupt(0, ezLCDevent, LOW);   
 }

void loop()
{
  if(  ezLCDInt )                 //do nothing till ezLCDInt becomes true
  {

    detachInterrupt(0);           // disable touch interrupt just to be safe
    ezLCDInt = false;             //reset ezLCDInt flag
    touch = lcd.wstack(FIFO);
/* 
*  touch will equal the widget number that has changed, button press ect.
*  there are also 3 global vars that go along with the wstack command .
*  lcd.currentWidget  current widget number stame as touch above.
*  lcd.currentInfo  will have widget state info for buttons will be 4 for pressed 1 for released 2 for cancel.
*  lcd.currentData  this is used for widgets like sliders it will have the current slider value here .
*/
    switch(touch)
    {
      case 1:
      /*
      * Add your code here for widget 1 
      */
      if(lcd.currentInfo == PRESSED)  // if widget 1 was a button this would mean the button was pressed and released
      {
      
      }  
      if(lcd.currentInfo == RELEASED)  // if widget 1 was a button this would mean the button was pressed and not released yet
      {
        
      } 
      break;
  
      case 2:
      /*
      * Add your code here for widget 2 
      */
      break;  

      default:
      break;
    }
    attachInterrupt(0, ezLCDevent, LOW);   
  }
}

void ezLCDevent( void ) {
  ezLCDInt = true;
}
