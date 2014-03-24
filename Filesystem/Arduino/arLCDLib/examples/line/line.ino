// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.

#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object using pins 10 & 11

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls();
  lcd.string(10," LineType ");
  lcd.light(100);
}

void loop()
{  
  lcd.color(WHITE);
  lcd.lineType(0);
  lcd.groupBox(1, 0,160 ,319,79,4,1,10);
  lcd.font(1);
  lcd.print("\\[5x\\[175yLine Type 0");
  lcd.lineType(0);
  lcd.xy(80,183);
  lcd.line(300,183);
  lcd.print("\\[5x\\[185yLine Type 1");
  lcd.lineType(1);
  lcd.xy(80,193);
  lcd.line(300,193);

  lcd.print("\\[5x\\[195yLine Type 2");
  lcd.lineType(2);
  lcd.xy(80,203);
  lcd.line(300,203);

  lcd.print("\\[5x\\[205yLine Type 3");  
  lcd.lineType(3);
  lcd.xy(80,213);
  lcd.line(300,213);

  lcd.print("\\[5x\\[215yLine Type 4");  
  lcd.lineType(4);
  lcd.xy(80,223);
  lcd.line(300,223);
  lcd.xy(0,0);

  for(int i=0; i < 100; i++)
  {
     lcd.color(random(1,168));   
     int x = random(0,319); 
     int y = random(0,159);
     lcd.lineType(random(0,10));
     lcd.line(x,y);  //draw line from the previous xy location
     delay(100);
  }
   lcd.cls();  
}
