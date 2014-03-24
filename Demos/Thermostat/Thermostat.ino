/**
*  arLCD Thermostat Demo
*  Written by Ken Segler for the arLCD
*  ken@earthlcd.com
*
*  copy *.gif files from this file to arLCD \EZUSERS\IMAGES
*
*  !!!!! make sure you have the line below in your startup.ezm !!!!!
*  cfgio 9 touch_int low quiet
*
*  This test code uses touch interrupt of the GPU to Signal touch events
*  Using Interrupts offloads the arduino from having to poll for touch events
*  
*/
#include <ezLCDLib.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LM75.h>
#define LED_PIN 13


LM75 sensor(LM75_ADDRESS | 0b111);  // initialize an LM75 object
//ezLCD3 lcd( 10, 11 );
ezLCD3 lcd;
SoftwareSerial xBee(8, 9);

volatile boolean ezLCDInt = false; // flag to indicate interrupt

unsigned long light;
unsigned int lightOld=0;
unsigned int lightCount = 0;
int touch;
bool onOFF =0;
bool heatCool =0;
char bitmapNames[13][12]= { "b0.gif","b1.gif","b2.gif","b3.gif","b4.gif","b5.gif","b6.gif","b7.gif","b8.gif","b9.gif","bb.gif","bs.gif","decf.gif"};
unsigned char temp = 0;
unsigned char currentTemp =0;
unsigned char setTemp = 0;
const unsigned char shadeRGB[]={128,128,128};
unsigned long xBeeUpdate =0;
unsigned long tempDelay = 0;
#define shade  155
#define bright 3

int displayFont = 0;

char buffer[32];
char xBeeString[64];

void turnOn(void) {
  lcd.font(displayFont);

  lcd.color(shade);
  lcd.xy(185,10);
  lcd.printString("RUN");

  lcd.color(bright);
  lcd.xy(185,30);
  lcd.printString("ON");

  lcd.color(shade);
  lcd.xy(185,50);
  lcd.printString("AUTO");

  lcd.color(shade);
  lcd.xy(185,70);
  lcd.printString("OFF");

  displaySetTemp(setTemp);
  onOFF =1;
}

void turnOff(void) {
  lcd.font(displayFont);
  lcd.color(shade);
  lcd.xy(185,10);
  lcd.printString("RUN");

  lcd.color(shade);
  lcd.xy(185,30);
  lcd.printString("ON");

  lcd.color(shade);
  lcd.xy(185,50);
  lcd.printString("AUTO");

  lcd.color(bright);
  lcd.xy(185,70);
  lcd.printString("OFF");

  lcd.color(shade);
  lcd.xy(10,30);
  lcd.printString("HEAT");

  lcd.color(shade);
  lcd.xy(10,50);
  lcd.printString("COOL");

  lcd.color(shade);
  lcd.xy(10,70);
  lcd.printString("FAN");

  lcd.color(0);
  lcd.xy(70,70);
  lcd.box(110,20,FILL);
   
  onOFF =0;
}
void tempSet( void ) {
  lcd.font(displayFont);
  lcd.color(8);
  lcd.xy(185,10);
  lcd.printString("RUN");
}

void tempUnSet( void ) {
  lcd.font(displayFont);
  lcd.color(shade);
  lcd.xy(185,10);
  lcd.printString("RUN");
}

void heatOn( void ) {
  lcd.font(displayFont);
  lcd.color(4);
  lcd.xy(10,30);
  lcd.printString("HEAT");

  lcd.color(shade);
  lcd.xy(10,50);
  lcd.printString("COOL");

  lcd.color(shade);
  lcd.xy(10,70);
  lcd.printString("FAN");
}

void coolOn( void ) {
  lcd.font(displayFont);
  lcd.color(shade);
  lcd.xy(10,30);
  lcd.printString("HEAT");

  lcd.color(104);
  lcd.xy(10,50);
  lcd.printString("COOL");
  
  lcd.color(shade);
  lcd.xy(10,70);
  lcd.printString("FAN");  
}

void fanOn( void ) {
  lcd.font(displayFont);
  lcd.color(shade);
  lcd.xy(10,30);
  lcd.printString("HEAT");

  lcd.color(shade);
  lcd.xy(10,50);
  lcd.printString("COOL");

  lcd.color(bright);
  lcd.xy(10,70);
  lcd.printString("FAN");  

}
void displaySetTemp( char t ) {
  lcd.color(0);
  lcd.xy(70,70);
  lcd.box(110,20,FILL);
  lcd.font(displayFont);
  lcd.color(10);
  lcd.xy(80,70);
  lcd.printString("Set To - ");
  itoa(setTemp,buffer,10);
  lcd.printString(buffer);
}

/** displayTemp( char t ) will display current temp using bitmap chars listed in bitmapNames[]
*  @param t Temp to display
*
*/
void displayTemp( char t ) {
  unsigned char ones;
  unsigned char tens;
  unsigned char hund;
  unsigned int tempX;
  ones = t % 10;
  hund = t /100;
  tens = (t / 10) % 10 ;
  tempX = 70;

  if(hund) {
  lcd.picture(tempX,10,bitmapNames[hund]);
  }
  else {
  tempX=54;
  lcd.picture(tempX,10,bitmapNames[10]);
  }
  lcd.picture(tempX+32,10,bitmapNames[tens]);
  lcd.picture(tempX+64,10,bitmapNames[ones]);
  lcd.picture(tempX+96,10,"degf.gif");  
}

void getString( char *str ) {
   char c=0;
    unsigned long timeOut=0;
    *str++ ='a';
    *str++ ='b';
    *str++ ='c';
    *str++ =0;    
  /*
     do {
    if(xBee.available()) {
        c = xBee.read();
        *str++ = c;
        }
        timeOut++;
    } while(c!='\r' && timeOut!=0x2fefe);
    *str = 0;
   */
}

void setup()
{

  xBee.begin(9600);
  xBee.println("xBee is up");
  Wire.begin();
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls( 0 );
  lcd.font("0");
  lcd.color(WHITE);
  lcd.picture("therm.gif");
  lcd.touchZone(1, 250, 6 ,65,65,1);
  lcd.touchZone(2, 250, 80 ,65,65,1);
  lcd.touchZone(3, 250, 151 ,65,65,1);  
  lcd.touchZone(4, 20, 98 ,60,40,1);
  lcd.touchZone(5, 90, 104 ,60,40,1);
  lcd.touchZone(6,180 , 104 ,60,40,1);  
  turnOff();

  sensor.shutdown(false);
  temp=sensor.temp();
  temp = (temp * 9.0)/ 5.0 + 32.0;
  sensor.shutdown(true);
  displayTemp(temp);
  setTemp = temp;
  turnOff();

  lcd.font("1");
  lcd.color(3);
  lcd.xy(20,140);
  lcd.printString("Weather For Huntington Beach");
  lcd.xy(20,155);
  lcd.printString("65 deg F");
  lcd.xy(20,170);
  lcd.printString("Precipitation: 0%");

  lcd.xy(20,185);
  lcd.printString("Humidity: 83%");
  lcd.xy(20,200);
  lcd.printString("Wind: 3mph");

  lcd.xy(20,215);
  lcd.printString("HI: 77 LOW:59");
  lcd.picture(165,165,"clearday.gif");

  pinMode( LED_PIN, OUTPUT );
//  pinMode(3,OUTPUT);
  digitalWrite( LED_PIN, LOW );
  attachInterrupt(0, ezLCDevent, LOW);  
}

void loop()
{
  
  light += analogRead(0)/2;    //read a/d 0 add it to light and we will average this 1000 times
  lightCount +=1;

  // once we read the a/d 1000 times we will update the backlight level 
  if (lightCount > 1000 ) {
    lightOld = light;
    light /=1000;
    if(light >=5)
    lcd.light(light);
    lightCount =0;  
    lightOld = light;
    light =0;
  }

    tempDelay++;
    if(tempDelay == 5000) {
    if(onOFF && (setTemp != currentTemp)) tempSet();
    sensor.shutdown(false);
    currentTemp=sensor.temp();
    currentTemp = (currentTemp * 9.0)/ 5.0 + 32.0;
    displayTemp(currentTemp);
    sensor.shutdown(true);
//    tempDelay=0;

    }
    if(tempDelay == 10000) {
    if(onOFF && (setTemp != currentTemp)) tempUnSet();
    tempDelay=0;
    }

/*
  if(xBeeUpdate ==1000000 || xBeeUpdate==0 ) {
    xBee.println("update me");

    lcd.font("1");
    lcd.color(0);
    lcd.xy(20,140);
    lcd.box(210,87,1);

    lcd.color(3);

    lcd.xy(20,140);
    getString(xBeeString);
    lcd.printString(xBeeString);

    lcd.xy(20,155);
    xBee.println("\r");
    getString(xBeeString);
    lcd.printString(xBeeString);

    lcd.xy(20,170);
    xBee.println("\r");
    getString(xBeeString);
    lcd.printString(xBeeString);

    lcd.xy(20,185);
    xBee.println("\r");
    getString(xBeeString);
    lcd.printString(xBeeString);

    lcd.xy(20,200);
    xBee.println("\r");    
    getString(xBeeString);
    lcd.printString(xBeeString);

    lcd.xy(20,215);
    xBee.println("\r");
    getString(xBeeString);
    lcd.printString(xBeeString);
    xBee.println("\r");
    lcd.picture(165,165,"clearday.gif");

    xBeeUpdate =0;  
    }
    xBeeUpdate ++;  
*/
  // if ezLCDInt is true we have a widget interrupt
  if(  ezLCDInt )
  {
    detachInterrupt(0);
    ezLCDInt = false;
    touch = 0;
    touch = lcd.wstack(FIFO);    
    switch(touch){

      case 1:
      if(lcd.currentData == 4) {
      tone(3,1000,100);
      if(onOFF) {
      displaySetTemp(++setTemp);
      if(setTemp >81) {
      }
      if(setTemp > currentTemp)
       heatOn();
      }
      }
      break;

      case 2:
      if(lcd.currentData == 4) {
      tone(3,1000,100);      
      if(onOFF) {
      displaySetTemp(--setTemp);
      if(setTemp < currentTemp)
       coolOn();
      }
      }
      break;

      case 3:
      if(lcd.currentData == 4) {      
      tone(3,1000,100);      
      if(onOFF==1) 
      turnOff();
      else
      turnOn();    
      }
      break;

      case 4:
      if(lcd.currentData == 4) {      
      tone(3,1000,100);      
      if(onOFF) heatOn();
      }
      break;

      case 5:
      if(lcd.currentData == 4) {      
      tone(3,1000,100);
      if(onOFF) coolOn();
      }
      break;

      case 6:
      if(lcd.currentData == 4) {      
      tone(3,1000,100);
      if(onOFF)   fanOn();
      }
      break;

      default:
      break;

    }
    lcd.wstack(CLEAR);
    attachInterrupt(0, ezLCDevent, LOW);  
  }
}

void ezLCDevent( void ) {
  ezLCDInt = true;
}

