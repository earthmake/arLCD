// ---------------------------------------------------------------------------
// Created by Ken Segler 6/1/2013.
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
// @file ezLCDLib.cpp
// This file supports the ezLCD3xx interface to an Arduino serial port.
// 
// @author Ken Segler - kensegler@gmail.com
// ---------------------------------------------------------------------------

#include "ezLCDLib.h"
#include <math.h>

#if defined(__AVR_ATmega32U4__) || defined(CORE_TEENSY)
  // Arduino Leonardo and Teensy use "Serial" as USB virtual serial
  // The first hardware serial port on these boards is "Serial1".
  #define arSerial Serial1
#else
  // arLCD's Arduino-compatable processor, and most Arduino boards
  // use "Serial" as their first hardware serial port.
  #define arSerial Serial
#endif


ezLCD3::~ezLCD3()
{
}
 
ezLCD3::ezLCD3(void) //: Serial(void)
{
}

void ezLCD3::begin( long baud )
{
	timeOutMilliseconds = 500;  // .5 seconds
    arSerial.begin( baud );
    arSerial.setTimeout(0xf0000000);
    //while(!sync());
	sync();//just one ping please
}

/* itoa:  convert n to characters in s */
void ezLCD3::itoa(int value, char *sp, int radix)
{
    char tmp[16];// be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned v;
    int sign;

    sign = (radix == 10 && value < 0);
    if (sign)   v = -value;
    else    v = (unsigned)value;

    while (v || tp == tmp) {
        i = v % radix;
        v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
        if (i < 10)
            *tp++ = i+'0';
        else
            *tp++ = i + 'a' - 10;
    }

    if (sign)
        *sp++ = '-';
    while (tp > tmp)
        *sp++ = *--tp;
}

// Begin a timeout.  Sets timedOut to false and captures Arduino's
// millisecond clock, for later checking by timeoutCheck().
void ezLCD3::timeoutBegin( void )
{
    timedOut = false;
    timeOutBeginMillis = millis();
}

// Check if more than "timeOutMilliseconds" has elapsed since
// timeoutBegin() was called.  Returns true and sets timedOut
// if a timeout has occurred, or returns false if no timeout.
bool ezLCD3::timeoutCheck( void )
{
    if (millis() - timeOutBeginMillis > timeOutMilliseconds) {
        timedOut = true;
    }
    return timedOut;
}

//if any characters are in buffer they are junk left over
//clear them all out before starting new command.
void ezLCD3::ClrSerial( void )
{
	while(arSerial.available())
		arSerial.read();
}

bool ezLCD3::sync( void )
{
    char c = 0;
    //unsigned long timeOut=0;
    delay(1);
	timedOut = false;
    //remove any character in receive buffer
	//send out a null command to see if GPU is up yet
    //arSerial.flush();
	arSerial.write('\r');
//    delay(1);
//    c = arSerial.read();   
//	if ( c == '\r' ) arSerial.write('\0');
	ClrSerial();
    delay(1);
	arSerial.write('\r');
    timeoutBegin();
    while( c != '\r' && !timeoutCheck() ) // wait for char or timeout
        c = arSerial.read();   
    if( timedOut || c != '\r' ) {
        return false;
    }else
        return true;
}

bool ezLCD3::waitForCRNTO( void )
{
	ClrSerial();
    arSerial.write('\r');//always send CR to start command
    char c = 0;
    timedOut = false;
    error = false;
    while( c != '\r' ) {
        c = arSerial.read(); 
		if( c == 0x31 ) error = true;
	}
    return true;
}

bool ezLCD3::waitForCR( void )
{
	ClrSerial();
    arSerial.write('\r');//always send CR to start command
	char c=0;
    timedOut=false;
    error=false;
    timeoutBegin();
    while( c != '\r' && !timeoutCheck() ) {//wait for CR or timeout
        c = arSerial.read();
		if( c == 0x31 ) error = true;
	}
    if( timedOut ) {
		while(!sync());
    }
	return true;
}

void ezLCD3::sendInt( int i )
{
    char value[5]= {0, 0, 0, 0, 0};

    itoa(i, value, 10);
    if(value[0]) arSerial.write(value[0]);
    if(value[1]) arSerial.write(value[1]);
    if(value[2]) arSerial.write(value[2]);
    if(value[3]) arSerial.write(value[3]);
    if(value[4]) arSerial.write(value[4]);
}

void ezLCD3::sendIntS( int i )
{
    char value[5]= {0, 0, 0, 0, 0};

    itoa(i, value, 10);
    if(value[0]) arSerial.write(value[0]);
    if(value[1]) arSerial.write(value[1]);
    if(value[2]) arSerial.write(value[2]);
    if(value[3]) arSerial.write(value[3]);
    if(value[4]) arSerial.write(value[4]);
    arSerial.write(' ');
}

void ezLCD3::sendLong( long i )
{
    char value[9]= { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//    itoa(i, value, 10);
    sprintf( value, "%ld", i );
    if( value[0] ) arSerial.write( value[0] );
    if( value[1] ) arSerial.write( value[1] );
    if( value[2] ) arSerial.write( value[2] );
    if( value[3] ) arSerial.write( value[3] );
    if( value[4] ) arSerial.write( value[4] );
    if( value[5] ) arSerial.write( value[5] );
    if( value[6] ) arSerial.write( value[6] );
    if( value[7] ) arSerial.write( value[7] );
    if( value[8] ) arSerial.write( value[8] );
}

const unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void ezLCD3::PrintHex( int value )
{
    int printVar;

    printVar = value;
    value = (value>>4) & 0x0F;
    arSerial.write( ( char ) CharacterArray[ value ] );

    value = printVar & 0x0F;
    arSerial.write( ( char ) CharacterArray[ value ] );

    return;
}

void ezLCD3::stripSpace(char* str)
{
    char* i = str;
    char* j = str;
    while(*j != 0) {
        *i = *j++;
        if(*i != ' ')
            i++;
    }
    *i = 0;
}

int ezLCD3::getInt( char *str )
{
    stripSpace(str);
    return atoi(str );
}

long ezLCD3::getLong( char *str )
{
    stripSpace(str);
    return atol(str );
}

bool ezLCD3::getString( char *str )
{
    char c=0;
    *str = 0;
	timeoutBegin();
    do {
		if ( arSerial.available() ) {
			c = arSerial.read();
			*str++ = c;
            *str = 0;
        }
    } while( ( c != '\r' ) && !timeoutCheck() );
    if ( timedOut )  
		return false;
    if ( c == '\r' )
        return true;
    else
        return false;
}

bool ezLCD3::getStringToSpace( char *str )
{
    char c=0;
    *str = 0;
	timeoutBegin();
    do {
    	if(arSerial.available()) {
			c = arSerial.read();
			*str++ = c;
            *str = 0;
        }
    } while( c !='\r' && c !=' ' && !timeoutCheck() );
    if( timedOut )  
		return false;
    if( c=='\r' || c==' ' )
        return true;
    else
        return false;
}

void ezLCD3::calibrate( void ) {
    sendInt(Calibrate);
    waitForCRNTO();
}

void ezLCD3::cls()
{
    sendInt(Clr_Screen);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::cls(int bColor)
{
    sendInt(Clr_Screen);
    arSerial.write(' ');
    sendInt(bColor);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::cls(int bColor, int fColor)
{
    sendInt(Clr_Screen);
    arSerial.write(' ');
    sendInt(bColor);
    arSerial.write(' ');
    sendInt(fColor);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::color(int fColor)
{
    sendInt(Color);
    arSerial.write(' ');
    sendInt(fColor);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::colorID( unsigned char  ID, unsigned char r, unsigned char g, unsigned char b )
{
    sendInt(eColor_ID);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(r);
    arSerial.write(' ');
    sendInt(g);
    arSerial.write(' ');
    sendInt(b);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::xy(int x, int y)
{
    sendInt(XY);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::xy( void )
{
    sendInt(XY);
	ClrSerial();
    arSerial.write('\r');
    getStringToSpace( localbuffer );
    X = getInt( localbuffer );    
    getStringToSpace( localbuffer );
    Y = getInt( localbuffer );
}

void ezLCD3::xy( char *str )
{
    sendInt(XY);
    arSerial.write(' ');
    arSerial.write('\"');
    sendString(str);
    arSerial.write('\"');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

unsigned int ezLCD3::getX( void )
{
    sendInt(XY);
	ClrSerial();
    arSerial.write('\r');
    getStringToSpace( localbuffer );
    X = getInt( localbuffer );    
    getStringToSpace( localbuffer );
    Y = getInt( localbuffer );
    return X;
}

unsigned int ezLCD3::getY( void )
{
    sendInt(XY);
	ClrSerial();
    arSerial.write('\r');
    getStringToSpace( localbuffer );
    X = getInt( localbuffer );    
    getStringToSpace( localbuffer );
    Y = getInt( localbuffer );
    return Y;
}

void ezLCD3::plot( void )
{
    sendInt(Plot);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::point( void )
{
    plot( );
}

void ezLCD3::plot( int x, int y )
{
    sendInt(Plot);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::point( int x, int y )
{
    plot( x, y );
}

unsigned int ezLCD3::getPixel( int x, int y )
{
    sendInt( Get_Pixel );
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return strtoul(localbuffer, NULL, 16);
}

void ezLCD3::line(int x, int y )
{
    sendInt(Line);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::lineType( int type )
{
    sendInt(Line_Type);
    arSerial.write(' ');
    sendInt(type);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::lineWidth( int width )
{
    sendInt(Line_Width);
    arSerial.write(' ');
    sendInt(width);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::arc( uint16_t radius, int16_t start, int16_t end, bool fill ) 
{
    sendInt(Arc);
    arSerial.write(' ');
    sendInt(radius);
    arSerial.write(' ');
    sendInt(start);
    arSerial.write(' ');
    sendInt(end);
    arSerial.write(' ');
    sendInt(fill);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::circle(int radius, bool filled )
{
    sendInt(Circle);
    arSerial.write(' ');
    sendInt(radius);
    if(filled) {
        arSerial.write(' ');
        arSerial.write('f');
    }
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::circle(int x, int y, int radius, bool filled )
{
	xy( x, y );

    sendInt(Circle);
    arSerial.write(' ');
    sendInt(radius);
    if ( filled ) {
        arSerial.write(' ');
        arSerial.write('f');
    }
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::box(int width, int height, bool filled)
{
    sendInt(Box);
    arSerial.write(' ');
    sendInt(width);
    arSerial.write(' ');
    sendInt(height);
    if ( filled ) {
        arSerial.write(' ');
        arSerial.write('f');
    }
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::rect(int x, int y, int width, int height, bool filled)
{
	xy( x, y );

	sendInt(Box);
    arSerial.write(' ');
    sendInt(width);
    arSerial.write(' ');
    sendInt(height);
    if ( filled ) {
        arSerial.write(' ');
        arSerial.write('f');
    }
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::pie( uint16_t radius, int16_t start, int16_t end )
{
    sendInt(Pie);
    arSerial.write(' ');
    sendInt(radius);
    arSerial.write(' ');
    sendInt(start);
    arSerial.write(' ');
    sendInt(end);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::light(int level)
{
     sendInt( Light );
     arSerial.write(' ');
     sendInt( level );
     waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

int ezLCD3::light( void )
{
    sendInt( Light );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

void ezLCD3::light( int level, unsigned long timeOut, int timeOutBrightness )
{
     sendInt( Light );
     arSerial.write(' ');
     sendInt( level );
     arSerial.write(' ');
     sendInt( timeOut );
     arSerial.write(' ');
     sendInt( timeOutBrightness );
     waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::light( int level, unsigned long timeOut, int timeOutBrightness, int commdis )
{
     sendInt( Light );
     arSerial.write(' ');
     sendInt( level );
     arSerial.write(' ');
     sendInt( timeOut );
     arSerial.write(' ');
     sendInt( timeOutBrightness );
     arSerial.write(' ');
     sendInt( commdis );
     waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

int ezLCD3::getXmax( void )
{
    sendInt(Xmax);
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::getYmax( void )
{
    sendInt(Ymax);
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::touchX( void )
{
    sendInt(Xtouch);
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::touchY( void )
{
    sendInt(Ytouch);
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::touchS( void )
{
    sendInt(Stouch);
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

void ezLCD3::sendString( char *str )
{
    unsigned char c;
    while( (c = *str++) )
        arSerial.write(c);
}

void ezLCD3::string( int ID, char *str )
{
    sendInt(StringID);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    arSerial.write('\"');
    sendString(str);
    arSerial.write('\"');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::getStringID( int ID , char *str)
{
    sendInt(StringID);
    arSerial.write(' ');
    sendInt(ID);
	ClrSerial();
    arSerial.write('\r');
    getString(str);
}

void ezLCD3::printNumber(unsigned long n, int base) {
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);
  printString( str );
}

void ezLCD3::printFloat(double number, int digits) 
{ 
  
  if (isnan(number)) return;
  if (isinf(number)) return;
  if (number > 4294967040.0) return;
  if (number <-4294967040.0) return;
  
  // Handle negative numbers
  if (number < 0.0) {
     print('-');
     number = -number;
  }
  
  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (int i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;
  
  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print((long int)int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    print("."); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint; 
  } 
}

void writeit( char c)
{
    if(c =='\n') {
		arSerial.write(0x5c);
		arSerial.write(0x6e);
		}
	else if (c=='\r') {
		arSerial.write(0x5c);
		arSerial.write(0x72);
		}
	else {
		arSerial.write(c);
	}
}

void ezLCD3::printString( char *str )
{
	int i, tempptr, bcount, tempbcount;

	tempptr = 0;//start at beginning of buffer
	bcount = strlen( str );//get the number of bytes
	while( bcount ) {
		if ( bcount <= 62 )
			tempbcount = bcount;//send it all
		else
			tempbcount = 62;

		sendInt( Print );
		arSerial.write(' ');
		arSerial.write('\"');
		for ( i = 0; i < tempbcount; i++ ) {
				writeit( str[ tempptr + i ] );
		}
		arSerial.write('\"');

		bcount -= tempbcount;//adjust the count
		tempptr += tempbcount;//adjust the count
		waitForCR();//Clears buffer, send CR and then waits for answer or timeout
	}
}

void ezLCD3::crlf( void )
{
		sendInt( Print );
		arSerial.write(' ');
		arSerial.write('\"');
//		arSerial.write('\\');
//		arSerial.write('n');
		arSerial.write('\\');
		arSerial.write('r');
		arSerial.write('\"');
		waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::print( char *str )
{
	printString( str );
}

void ezLCD3::println( char *str )
{
	printString( str );
	crlf();
}

void ezLCD3::print( char str )
{
    sendInt(Print);
    arSerial.write(' ');
    arSerial.write('"');
    writeit(str);
    arSerial.write('"');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::println( char str )
{
	print( str );
	crlf();
}

void ezLCD3::println( void )
{
	crlf();
}

void ezLCD3::print( int value )
{
	printNumber((unsigned long) value, 10 );
}

void ezLCD3::println( int value )
{
	printNumber((unsigned long) value, 10 );
	crlf();
}

void ezLCD3::print( int value, int mode )
{
	printNumber((unsigned long) value, mode );
}

void ezLCD3::println( int value, int mode )
{
	printNumber((unsigned long) value, mode );
	crlf();
}

void ezLCD3::print( long value )
{
	printNumber((unsigned long) value, 10 );
}

void ezLCD3::print( long value, int mode )
{
	printNumber((unsigned long) value, mode );
}

void ezLCD3::println( long value, int mode )
{
	printNumber((unsigned long) value, mode );
	crlf();
}

void ezLCD3::print( double value, int digits )
{
	printFloat( value, digits);
}

void ezLCD3::println( double value, int digits )
{
	printFloat( value, digits);
	crlf();
}

void ezLCD3::print( double value )
{
	printFloat( value, 2 );
}

void ezLCD3::println( double value )
{
	printFloat( value, 2 );
	crlf();
}

void ezLCD3::printStringID( char ID )
{
    sendInt(Print);
    arSerial.write(' ');
    sendInt(ID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::fontw( int ID, char *str)
{
    sendInt(Fontw);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendString(str);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::fontw( int ID, int font)
{
    sendInt(Fontw);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(font);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::font( char *str)
{
    sendInt(Font);
    arSerial.write(' ');
    sendString(str);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::font( int font )
{
    sendInt(Font);
    arSerial.write(' ');
    sendInt(font);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::fontO( bool dir )
{
    sendInt(Font_Orient);
    arSerial.write(' ');
    if(dir)
        arSerial.write('1');
    else
        arSerial.write('0');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

unsigned char ezLCD3::choice( char *str, unsigned char c ) {
    sendInt(Choice);
    arSerial.write(' ');
    sendString(str);
    arSerial.write(' ');
    sendInt(c);
    arSerial.write(' ');    
	ClrSerial();
    arSerial.write('\r');
    timeOutMilliseconds = 3600000;  // 1 hour
    do {
		getString( localbuffer );
		currentData=strlen( localbuffer );
    }while( currentData == 0 );
	timeOutMilliseconds = 500;  // 0.5 seconds
    return getInt( localbuffer );
}

void ezLCD3::clipArea( int l, int t, int r, int b)
{
    sendInt(ClipArea);
    arSerial.write(' ');
    sendInt(l);
    arSerial.write(' ');
    sendInt(t);
    arSerial.write(' ');
    sendInt(r);
    arSerial.write(' ');
    sendInt(b);
    arSerial.write(' ');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::clipEnable( bool enable)
{
    sendInt(ClipEnable);
    arSerial.write(' ');
    if(enable)
        arSerial.write('1');
    else
        arSerial.write('0');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::drawLed( int x, int y, int radius, unsigned char colorLed, unsigned char colorHigh) 
{
    sendInt( Draw_LED );
    arSerial.write(' ');
    sendInt( x );
    arSerial.write(' ');
    sendInt( y );
    arSerial.write(' ');
    sendInt( radius );
    arSerial.write(' ');
    sendInt( colorLed );
    arSerial.write(' ');
    sendInt( colorHigh );
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::theme(int ID, int EmbossDkColor, int  EmbossLtColor, int TextColor0, int TextColor1, int TextColorDisabled, int Color0, int Color1, int ColorDisabled, int CommonBkColor, int Fontw)
{
    sendInt(Widget_Theme);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(EmbossDkColor);
    arSerial.write(' ');
    sendInt(EmbossLtColor);
    arSerial.write(' ');
    sendInt(TextColor0);
    arSerial.write(' ');
    sendInt(TextColor1);
    arSerial.write(' ');
    sendInt(TextColorDisabled);
    arSerial.write(' ');
    sendInt(Color0);
    arSerial.write(' ');
    sendInt(Color1);
    arSerial.write(' ');
    sendInt(ColorDisabled);
    arSerial.write(' ');
    sendInt(CommonBkColor);
    arSerial.write(' ');
    sendInt(Fontw);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::groupBox( int ID, int x, int y, int w, int h, int options, int theme, int stringID)
{
    sendInt(Set_Gbox);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(options);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::checkBox( int ID, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                 uint16_t options, int theme, int stringID )
{
    sendInt(Set_CheckBox);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(options);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout    
}

void ezLCD3::radioButton( int ID, uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                 uint16_t options, int theme, int stringID )
{
    sendInt(Set_RadioButton);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(options);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout    
}

void ezLCD3::analogMeter( int ID, int x, int y, int w, int h, int options, int value, int min, int max, int theme, int stringID, int type)
{
    sendInt(Set_AMeter);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(options);
    arSerial.write(' ');
    sendInt(value);
    arSerial.write(' ');
    sendInt(min);
    arSerial.write(' ');
    sendInt(max);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    arSerial.write(' ');
    sendInt(type);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::analogMeterColor( int ID, int Sector1, int Sector2, int Sector3, int Sector4, int Sector5, int Sector6 )
{
    sendInt( AMeter_Color );
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(Sector1);
    arSerial.write(' ');
    sendInt(Sector2);
    arSerial.write(' ');
    sendInt(Sector3);
    arSerial.write(' ');
    sendInt(Sector4);
    arSerial.write(' ');
    sendInt(Sector5);
    arSerial.write(' ');
    sendInt(Sector6);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}


void ezLCD3::touchZone( int ID, int x, int y, int w, int h, bool option)
{
    sendInt(Set_TouchZone);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    if(option)
        sendInt('1');
    else
        sendInt('0');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::shadow( int mode, int Scolor, int Slinetype, int Slinethickness )
{
    sendInt( Shadow );
    arSerial.write(' ');
    sendInt( mode );
    arSerial.write(' ');
    sendInt( Scolor );
    arSerial.write(' ');
    sendInt( Slinetype );
    arSerial.write(' ');
    sendInt( Slinethickness );
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::button( int ID, int x, int y, int w, int h, int option, int align, int radius, int theme, int stringID )
{
    sendInt(Set_Button);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(align);
    arSerial.write(' ');
    sendInt(radius);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::dial( int ID, uint16_t x, uint16_t y, uint16_t radius, uint16_t option, 
                    int resolution, int initial, int max, int theme )
{
    sendInt(Set_Dial);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(radius);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(resolution);
    arSerial.write(' ');
    sendInt(initial);
    arSerial.write(' ');
    sendInt(max);
    arSerial.write(' ');
    sendInt(theme);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

bool ezLCD3::picture( char *str )
{
    sendInt(Picture);
    arSerial.write(' ');
    arSerial.write('\"');
    sendString(str);
    arSerial.write('\"');
    timeOutMilliseconds = 11566;  // 11.566 seconds ... was timeOutCount = 2000000;
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
    timeOutMilliseconds = 376;    // 0.376 seconds  ... was timeOutCount = 65000;
    return timedOut;
}

bool ezLCD3::picture( int x, int y, char *str)
{
    sendInt(Picture);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendString(str);
    timeOutMilliseconds = 11566;  // 11.566 seconds ... was timeOutCount = 2000000;
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
    timeOutMilliseconds = 376;    // 0.376 seconds  ... was timeOutCount = 65000;
    return timedOut;
}

bool ezLCD3::picture( int x, int y, int options, char *str)
{
    sendInt(Picture);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(options);
    arSerial.write(' ');
    sendString(str);
    timeOutMilliseconds = 11566;  // 11.566 seconds ... was timeOutCount = 2000000;
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
    timeOutMilliseconds = 376;    // 0.376 seconds  ... was timeOutCount = 65000;
    return timedOut;
}

void ezLCD3::progressBar(int ID, int x, int y, int w, int h, int option, int value, int max, int theme, int stringID)
{
    sendInt(Set_Progress);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(value);
    arSerial.write(' ');
    sendInt(max);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::gauge(int ID, int x, int y, int w, int h, int option, int initial, int min, int max, int theme, int stringID)
{
    sendInt(Set_Gauge);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(initial);
    arSerial.write(' ');
    sendInt(min);
    arSerial.write(' ');
    sendInt(max);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::slider(int ID, int x, int y, int w, int h, int option, int range, int res, int value, int theme)
{
    sendInt(Set_Slider);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(range);
    arSerial.write(' ');
    sendInt(res);
    arSerial.write(' ');
    sendInt(value);
    arSerial.write(' ');
    sendInt(theme);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::staticText( int ID, int x, int y, int w, int h, int option, int theme, int stringID)
{
    sendInt(Set_StaticText);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(theme);
    arSerial.write(' ');
    sendInt(stringID);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::digitalMeter( int ID, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t option, int initial,int digits, int dotpos,int theme )
{    
	sendInt(Set_DMeter);
    arSerial.write(' ');
    sendInt(ID);
    arSerial.write(' ');
    sendInt(x);
    arSerial.write(' ');
    sendInt(y);
    arSerial.write(' ');
    sendInt(w);
    arSerial.write(' ');
    sendInt(h);
    arSerial.write(' ');
    sendInt(option);
    arSerial.write(' ');
    sendInt(initial);
    arSerial.write(' ');
    sendInt(digits);
    arSerial.write(' ');
    sendInt(dotpos);
    arSerial.write(' ');
    sendInt(theme);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

unsigned int ezLCD3::wstack( int type )
{
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
    sendInt( Wstack );
    arSerial.write(' ');
    sendInt( type );
	ClrSerial();
    arSerial.write('\r');
    timeOutMilliseconds = 1000;  // 1 second
    getStringToSpace( localbuffer );
    currentWidget = getInt( localbuffer );
    getStringToSpace( localbuffer );
    currentInfo = getInt( localbuffer );
    getStringToSpace( localbuffer );
//    getString( localbuffer );
    currentData = getInt( localbuffer );
    return currentWidget;
}

void ezLCD3::wquiet( void )
{
     sendInt( Wquiet);
     waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

unsigned int ezLCD3::wvalue( int ID )
{
    sendInt( GetWidget_Values );
    arSerial.write(' ');
    sendInt( ID );
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}
    
void ezLCD3::wvalue( int ID, int value )
{
    sendInt( Widget_Values );
    arSerial.write(' ');
    sendInt( ID );
    arSerial.write(' ');
    sendInt( value );
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

void ezLCD3::wvalue( int ID, char *str )
{
    sendInt( Widget_Values );
    arSerial.write(' ');
    sendInt( ID );
    arSerial.write(' ');
    arSerial.write('\"');
    sendString(str);
    arSerial.write('\"');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

unsigned int ezLCD3::wstate( int ID)
{
    sendInt( Widget_State );
    arSerial.write(' ');
    sendInt( ID );
    getString( localbuffer );
    return strtoul( localbuffer, NULL, 16 ); 
}

void ezLCD3::wstate( int ID, int option )
{
    sendInt( Widget_State );
    arSerial.write(' ');
    sendInt( ID );
    arSerial.write(' ');
    sendInt( option );
	waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

//file system access
int ezLCD3::FSchdir( char * directory )
{
    sendInt( Fschdir );
    arSerial.write(' ');
    arSerial.write('"');
    sendString( directory );
    arSerial.write('"');
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

void ezLCD3::FSgetcwd( void )
{
    sendInt( Fsgetcwd );
	ClrSerial();
	arSerial.write('\r');
    getString( localbuffer );
    return;
}

int ezLCD3::FSmkdir( char * directory )
{
    sendInt( Fsmkdir );
    arSerial.write(' ');
    arSerial.write('"');
    sendString( directory );
    arSerial.write('"');
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FScopy( char * source_filename, char * dest_filename )
{
    sendInt( Fscopy );
    arSerial.write(' ');
    arSerial.write('"');
    sendString( source_filename );
    arSerial.write('"');
    arSerial.write(' ');
    arSerial.write('"');
    sendString( dest_filename );
    arSerial.write('"');
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSrename( char * source_filename, char * dest_filename )
{
    sendInt( Fsrename );
    arSerial.write(' ');
    arSerial.write('"');
    sendString( source_filename );
    arSerial.write('"');
    arSerial.write(' ');
    arSerial.write('"');
    sendString( dest_filename );
    arSerial.write('"');
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSremove( char * filename )
{
    sendInt( Fsremove );
    arSerial.write(' ');
    arSerial.write('"');
    sendString( filename );
    arSerial.write('"');
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSopen( char * filename, char * mode )
{
	if (( mode[1] == 'H' ) || ( mode[1] == 'h' )) 
		hexmode = 1;
	else
		hexmode = 0;
	sendInt( Fsopen );
    arSerial.write(' ');
    arSerial.write('"');
    sendString( filename );
    arSerial.write('"');
    arSerial.write(' ');
    arSerial.write('"');
    sendString( mode );
    arSerial.write('"');
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSclose( void )
{
    sendInt( Fsclose );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSrewind( void )
{
    sendInt( Fsrewind );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSseek( long offset, int whence  )
{
	int temp;

    sendInt( Fsseek );
    arSerial.write(' ');
    sendInt( offset/65536 );
    arSerial.write(' ');
	temp = offset & 0xFFFF;
    sendInt( temp );
    arSerial.write(' ');
    sendInt( whence );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSerror( void )
{
    sendInt( Fserror );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

long ezLCD3::FStell( void )
{
    sendInt( Fstell );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getLong( localbuffer );
}

int ezLCD3::FSwrite( char * data, int count )
{
	int i, tempbcount;
	int bcount, tempptr, wcount;
	
	wcount = 0;//number of bytes written
	tempptr = 0;//start at beginning of buffer
	bcount = count;//get the number of bytes to store
	while( bcount ) {
		if ( bcount <= 62 ) 
			tempbcount = bcount;//send it all
		else
			tempbcount = 62;
		if (( hexmode == 1 ) && ( tempbcount > 31 ))
			tempbcount = 31;//max it fit our buffer size
		sendInt( Fswrite );
		arSerial.write(' ');
		arSerial.write('"');
		if ( hexmode == 1 ) { 
			for ( i = 0; i < tempbcount; i++ ) {
				PrintHex( data[ tempptr + i ] );
			}
		}else{
			for ( i = 0; i < tempbcount; i++ ) {
				if ( data[ tempptr + i ] >= 0x20 ) 
					arSerial.write( data[ tempptr + i ] );
				else//may want to exclude
					arSerial.write( 0x3f );//make illegal characters '?'
			}
		}
		arSerial.write('"');
		ClrSerial();
		arSerial.write('\r');

		tempptr += tempbcount;//adjust the count
		getString( localbuffer );
		bcount -= tempbcount;//adjust the count
		wcount += getInt( localbuffer );
	}
    return wcount;
}

int ezLCD3::FSread( char * buffer, int bcount )
{
	int tch, temp, i, tempbcount;
	char lbuffer[128];
	//int bpointer;

	buffer[0] = 0;//set end of string
	while( bcount ) {
		if ( bcount <= 62 )
			tempbcount = bcount;
		else
			tempbcount = 62;
	
		//read a buffer full
		sendInt( Fsread );
		arSerial.write(' ');
		sendInt( bcount );
		ClrSerial();
		arSerial.write('\r');
		getString( lbuffer );
		if ( hexmode == 1 ) {//check to see if its in hex format
			for ( i = 0; i < tempbcount * 2; i++) {
				tch = lbuffer[ i ];
				if ( tch <= 0x39 ) 
					tch = tch - 0x30;
				else
					tch = tch - 0x37;
				temp = tch * 16;
				i += 1;//move pointer
				tch = lbuffer[ i ];
				if ( tch <= 0x39 )
					tch = tch - 0x30;
				else
					tch = tch - 0x37;
				lbuffer[ i / 2 ] = temp + tch;//put in buffer
				lbuffer[ ( i / 2 ) + 1 ] = 0;//put in buffer
			}
		}
//transfer to local buffer
		strcat( buffer, lbuffer );
		bcount -= tempbcount;//subtract out the block from count
	}
    return strlen( buffer );
}

int ezLCD3::FSattrib( int attribute )
{
    sendInt( Fsattrib );
    arSerial.write(' ');
    sendInt( attribute );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::GetFSattrib( void )
{
    sendInt( Fsattrib );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

int ezLCD3::FSeof( void )
{
    sendInt( Fseof );
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
    return getInt( localbuffer );
}

//end file system

int ezLCD3::RecvUART( int port )
{
	int result;

	result = RxUART( port );
	return result;
}

int ezLCD3::RxUART( int port )
{
	int result;

    sendInt( ReadUart );
    arSerial.write(' ');
    switch( port ) {
		case 0:
			sendInt( 0 );
		break;
		case 10:
			sendInt( 4 );
		break;
		case 11:
			sendInt( 3 );
		break;
		case 12:
			sendInt( 5 );
		break;
		case 13:
			sendInt( 8 );
		break;
		default:
			sendInt( 3 );
		break;
	}
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
	result = getInt( localbuffer );
	if ( result == 0x8000 ) //no character
		return -1;
	else
		return result;
}

void ezLCD3::Debug( unsigned long data, char *format )
{
    char str[16];// be careful with the length of the buffer

	sprintf( str, format, data );
	Debug( str );
}

void ezLCD3::Debug( long data, char *format )
{
    char str[16];// be careful with the length of the buffer

	sprintf( str, format, data );
	Debug( str );
}

void ezLCD3::Debug( int data, char *format )
{
    char str[16];// be careful with the length of the buffer

	sprintf( str, format, data );
	Debug( str );
}

void ezLCD3::Debug( unsigned int data, char *format )
{
    char str[16];// be careful with the length of the buffer

	sprintf( str, format, data );
	Debug( str );
}

void ezLCD3::Debug( char data )
{
	TxUART( 0, data );
}

void ezLCD3::Debug( char *str )
{
    unsigned char c;

    while( (c = *str++) )
		TxUART( 0, c );
}

void ezLCD3::TxUART( int port,  char *str )
{
    unsigned char c;

    while( (c = *str++) )
        TxUART( port, c );
}

void ezLCD3::TxUART( int port, char data )
{
    sendInt( WriteUart );
    arSerial.write(' ');
    switch( port ) {
		case 0:
			sendInt( 0 );
		break;
		case 10:
			sendInt( 4 );
		break;
		case 11:
			sendInt( 3 );
		break;
		case 12:
			sendInt( 5 );
		break;
		case 13:
			sendInt( 8 );
		break;
		default:
			sendInt( 3 );
		break;
	}
    arSerial.write(' ');
    sendInt( data );
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

int ezLCD3::Available( int port )
{
	int result;

    sendInt( Avail );
    arSerial.write(' ');
    switch( port ) {
		case 0:
			sendInt( 0 );
		break;
		case 10:
			sendInt( 4 );
		break;
		case 11:
			sendInt( 3 );
		break;
		case 12:
			sendInt( 5 );
		break;
		case 13:
			sendInt( 8 );
		break;
		default:
			sendInt( 3 );
		break;
	}
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
	result = getInt( localbuffer );
	return result;
}

int ezLCD3::peek( int port )
{
	int result;

    sendInt( Peek );
    arSerial.write(' ');
    switch( port ) {
		case 0:
			sendInt( 0 );
		break;
		case 10:
			sendInt( 4 );
		break;
		case 11:
			sendInt( 3 );
		break;
		case 12:
			sendInt( 5 );
		break;
		case 13:
			sendInt( 8 );
		break;
		default:
			sendInt( 3 );
		break;
	}
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
	result = getInt( localbuffer );
	return result;
}

int ezLCD3::flush( int port )
{
	int result;

    sendInt( Flush );
    arSerial.write(' ');
    switch( port ) {
		case 0:
			sendInt( 0 );
		break;
		case 10:
			sendInt( 4 );
		break;
		case 11:
			sendInt( 3 );
		break;
		case 12:
			sendInt( 5 );
		break;
		case 13:
			sendInt( 8 );
		break;
		default:
			sendInt( 3 );
		break;
	}
	ClrSerial();
    arSerial.write('\r');
    getString( localbuffer );
	result = getInt( localbuffer );
	return result;
}

void ezLCD3::sendCommand(char *str)
{
    sendString(str);
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout
}

size_t ezLCD3::write( uint8_t c)
{
	sendInt(Print);
    arSerial.write(' ');
    arSerial.write('\"');
    if(c =='\n') {
		arSerial.write(0x5c);
		arSerial.write(0x6e);
		}
	else if (c=='\r') {
		arSerial.write(0x5c);
		arSerial.write(0x72);
		}
	else {
		arSerial.write(c);
	}
    arSerial.write('\"');
    waitForCR();//Clears buffer, send CR and then waits for answer or timeout    
    return(c);
}
