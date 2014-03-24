

/*
 * colorId.ino assigns a color to an id
 */
 
#include <ezLCDLib.h>
unsigned char r,g,b;
bool dir=false;
ezLCD3 lcd;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls();                      // clear the LCD  
  r=0;
  g=0;
  b=0;
}

void loop()
{
  lcd.colorID(168, r, 0, 0); 
  lcd.colorID(169, 0, g, 0); 
  lcd.colorID(170, 0, 0, b); 
  if(b==0 && g==0) {
  lcd.color(168);    // set color 168
  lcd.xy(10,10);
  lcd.box(50,50,FILL);
  lcd.xy(70,10);
  lcd.print("Fade in Red");
  }
  if(r==255 && b==0) {
  lcd.color(169);    // set color 168
  lcd.xy(60,60);
  lcd.box(50,50,FILL);
  lcd.xy(120,60);
  lcd.print("Fade in Green");
  }
  if(g==255 && r==255) {
  lcd.color(170);    // set color 168
  lcd.xy(110,110);
  lcd.box(50,50,FILL);
  lcd.xy(170,110);
  lcd.print("Fade in Blue");
  }
  if(r!=255) r++;
  if(r==255 && g!=255) g++;
  if(g==255 && b!=255) b++;
  if(r==255 && b==255 && g==255) { r=0;g=0;b=0;lcd.cls();}
  
}