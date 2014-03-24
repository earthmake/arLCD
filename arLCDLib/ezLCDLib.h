// ---------------------------------------------------------------------------
// Created by Ken Segler 6/1/2013.
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
//
// @file ezLCDLib.h
// This file supports the ezLCD3xx interface to an Arduino serial port.
// 
// @author Ken Segler - kensegler@gmail.com
// ---------------------------------------------------------------------------

#ifndef _EZLCDLIB_H
#define _EZLCDLIB_H


#include <Arduino.h>
#include "Print.h"

#if 0
#define EZM_BAUD_RATE 115200  //default rate for coms link to GPU, this must match startup.ezm
#else
#define EZM_BAUD_RATE 230400  //default rate for coms link to GPU, this must match startup.ezm
#endif

#define FIFO    0
#define LIFO    1
#define CLEAR   2
#define PEEK    3

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define DELETE  0
#define ENABLE  1
#define DISABLE 2
#define REDRAW  3
#define FILL    1
#define NOFILL 0
#define PRESSED 4
#define RELEASED 1
#define CANCEL  2
#define ON 1
#define OFF 0
#define LEFTJUSTIFIED 1
#define RIGHTJUSTIFIED 3
#define CENTERJUSTIFIED 4
#define LEFTJUSTIFIEDF 5
#define RIGHTJUSTIFIEDF 7
#define CENTERJUSTIFIEDF 8


 /** Enum for standard colors */
enum { BLACK,GRAY,SILVER,WHITE,RED,MAROON,YELLOW,OLIVE,
		LIME,GREEN,AQUA,TEAL,BLUE,NAVY,FUCHSIA,PURPLE,
		INDIANRED,LIGHTCORAL,SALMON,DARKSALMON,LIGHTSALMON,RED2,CRIMSON,FIREBRICK,
		DARKRED,PINK,LIGHTPINK,HOTPINK,DEEPPINK,MEDIUMVIOLETRED,PALEVIOLETRED,LIGHTSALMON2,
		CORAL,TOMATO,ORANGERED,DARKORANGE,ORANGE,GOLD,YELLOW2,LIGHTYELLOW,
		LEMONCHIFFON,LIGHTGOLDENRODYELLOW,PAPAYAWHIP,MOCCASIN,PEACHPUFF,PALEGOLDENROD,KHAKI,DARKKHAKI,
		LAVENDER,THISTLE,PLUM,VIOLET,ORCHID,FUCHSIA2,MAGENTA,MEDIUMORCHID,
		MEDIUMPURPLE,BLUEVIOLET,DARKVIOLET,DARKORCHID,DARKMAGENTA,PURPLE2,INDIGO,SLATEBLUE,
		DARKSLATEBLUE,GREENYELLOW,CHARTREUSE,LAWNGREEN,LIME2,LIMEGREEN,PALEGREEN,LIGHTGREEN,
		MEDIUMSPRINGGREEN,SPRINGGREEN,MEDIUMSEAGREEN,SEAGREEN,FORESTGREEN,GREEN2,DARKGREEN,YELLOWGREEN,
		OLIVEDRAB,OLIVE2,DARKOLIVEGREEN,MEDIUMAQUAMARINE,DARKSEAGREEN,LIGHTSEAGREEN,DARKCYAN,TEAL2,
		AQUA2,CYAN2,LIGHTCYAN,PALETURQUOISE,AQUAMARINE,TURQUOISE,MEDIUMTURQUISE2,DARKTURQUOISE,
		CADETBLUE,STEELBLUE,LIGHTSTEELBLUE,POWDERBLUE,LIGHTBLUE,SKYBLUE,LIGHTSKYBLUE,DEEPSKYBLUE,
		DODGERBLUE,CORNFLOWERBLUE,MEDIUMSLATEBLUE,ROYALBLUE,BLUE2,MEDIUMBLUE,DARKBLUE,NAVY2,
		MIDNIGHTBLUE,CORNSILK,BLANCHEDALMOND,BISQUE,NAVAJOWHITE,WHEAT,BURLYWOOD,TAN,
		ROSYBROWN,SANDYBROWN,GOLDENROD,DARKGOLDENROD,PERU,CHOCOLATE,SADDLEBROWN,SIENNA,BROWN,MAROON2,
		WHITE2,SNOW,HONEYDEW,MINTCREAM,AZURE,ALICEBLUE,GHOSTWHITE,WHITESMOKE,
		SEASHELL,BEIGE,OLDLACE,FLORALWHITE,IVORY,ANTIQUEWHITE,LINEN,LAVENDERBLUSH,
		MISTYROSE,GAINSBORO,LIGHTGREY,SILVER2,DARKGRAY,GRAY2,DIMGRAY,LIGHTSLATEGRAY,
		SLATEGRAY,DARKSLATEGRAY,BLACK2};
        
class Stream;       /* Forward declaration of Stream to be used
                     * in the EzLCD3 abstract class */

/** Interface to the EarthLCD ezLCD3xx line of smart displays
* Derived class from Serial so that you
* can conveniently printf(), putc(), etc to the display.
*/
class ezLCD3: public Print
{
public:
    volatile unsigned int currentWidget;
    volatile unsigned int currentInfo;
    volatile unsigned int currentData;
    volatile bool timedOut;    
    volatile unsigned int error;        
    unsigned long timeOutMilliseconds;
    unsigned long timeOutBeginMillis;
    volatile unsigned int X;    
    volatile unsigned int Y; 
    volatile unsigned int hexmode; 
	char localbuffer[128];

    /** Create a new interface to a ezLCD3xx display
     */
    ezLCD3(void);

    /** Class destructor */
    virtual ~ezLCD3();

    /**
    * @param[in] baud baud rate defined here EZM_BAUD_RATE 115200
    *
    */
    void begin( long baud = EZM_BAUD_RATE );

/************************ Library Internal Functions *****************/
    /** required for classes derived from Print
    * This allows using build in arduino print functions 
    * like println(test,HEX);
    */
    virtual size_t write(uint8_t);
    
    /**
    *
    *
    */    
    void itoa(int value, char *sp, int radix);

    /**
    *
    *
    */
    void stripSpace(char *str);

    /**
    *
    *
    */
    bool sync( void );

    /** Send a integer to the display as command
    * @param[in] i integer to send
    */
    void sendInt( int i );

    /** Send a integer to the display as command
    * @param[in] i integer to send
    */
    void sendIntS( int i );

	/** Send a long to the display as command
    * @param[in] i long to send
    */
	void sendLong( long i );

    /** Send hex to the display as command
    * @param[in] i hex to send
    */
    void PrintHex( int value );

    /** Get a integer from the display
    * @param[out] str string to put the data in
    *
    */
    int getInt( char *str );

    /** Get a long from the display
    * @param[out] str string to put the data in
    *
    */
    long getLong( char *str );

    /** Get a string from the display
    * @param[out] str string to put the data in
    *
    */
    bool getString( char *str );

    /** Get a string from the display
    * @param[out] str string to put the data in
    *
    */
    bool getStringToSpace( char *str );

    /** Waits for a CR from display
    *
    */
    bool waitForCRNTO( void );
    bool waitForCR( void );

	void ClrSerial( void );


/************************ Library Internal Functions *****************/
    
    /**
     * 
     */ 
    void calibrate( void );

    /**
     * 
     */     
    unsigned char choice( char *str, unsigned char c  );
    
    /** clear the screen to black
    *
    */
    void cls(void);

    /** clear the screen with background color
    * @param[in] bcolor Background color
    */
    void cls(int bColor);

    /** clear the screen with background color and drawing color
    *
    * @param[in] bColor background color
    * @param[in] fColor drawing color
    */
    void cls(int bColor, int fColor);

    /** Set drawing color
    * @param[in] color color to draw with
    */
    void color( int color );

    /** Set drawing color
    * @param[in] color color to draw with
    */
    void colorID( unsigned char  ID, unsigned char r, unsigned char g, unsigned char b );

    /** set x y position for drawing and text
     *
     * @param[in] x is the x coordinate
     * @param[in] y is the y coordinate
     */
    void xy(int x, int y);
    
    void xy( void );

	void xy( char *str );
    
    unsigned int getX( void );

    unsigned int getY( void );
    
    /** set pixel at current x y
     *
     */
    void plot(void);
	void point(void);

    /** set pixel in current draw color at x y
     *
     * @param[in] x is the x coordinate
     * @param[in] y is the y coordinate
     */
    void plot(int x, int y);
    void point(int x, int y);

    /** get pixel from x y
     *
     * @param[in] x is the x coordinate
     * @param[in] y is the y coordinate
     */
	unsigned int getPixel( int x, int y );

    /** draw line from current x y to new x y
     *
     * @param[in] x is the x coordinate
     * @param[in] y is the y coordinate
     */
    void line(int x, int y);

    /** Set line drawing type
    * @param[in] type Options: 0 = solid, 1= dotted (1 pixel spacing between dots), 2 = dashed (2 pixel spacing between dashes)
    */
    void lineType( int type );

    /** Set line drawing width
    * @param[in] width in pixels
    */
    void lineWidth( int width );

    /** Draw circle in current color at current x y
     *
     * @param[in] x location of circle
     * @param[in] y location of circle
     * @param[in] radius diameter of circle
     * @param[in] filled  true for a filled box outline if false
     */
    void circle(int radius, bool filled );
	void circle(int x, int y, int radius, bool filled );

    /**
     * Draw a pie with the specified radius, start angle and end angle.
     * \param[in]  radius    pie radius in pixels.
     * \param[in]  start     Start angle in degrees.
     * \param[in]  end       End angle in degrees.
     */
    void pie( uint16_t radius, int16_t start, int16_t end );
    
    /**
     * Draw an arc with the specified radius, start angle and end angle.
     * \param[in]  radius    Arc radius in pixels.
     * \param[in]  start     Start angle in degrees.
     * \param[in]  end       End angle in degrees.
     */
    void arc( uint16_t radius, int16_t start, int16_t end , bool fill);
    
    /** draw a box from current x y of width and heigth
     *
     * @param[in] width
     * @param[in] heigth
     * @param[in] filled  true for a filled box outline if false
     */
    void box(int width, int height, bool filled);
	void rect(int x, int y, int width, int height, bool filled);

    /**
    * Return current brightness setting.
    * \return    Brightness in 0-100.
    */
    int light();

    /** set backlight brightness
     *
     * @param[in] level is brightness 0=off 100=full in steps of 32
     */
    void light(int level);

   /**
     * Set brightness & timeout
     * \param[in]  level Brightness in 0-100.
     * \param[in]  timeout    Timeout value in minutes before dimming
     * \param[in]  timeOutBrightness 
     */
     void light( int level, unsigned long timeout, int timeOutBrightness );
    
   /**
     * Set brightness & timeout
     * \param[in]  level Brightness in 0-100.
     * \param[in]  timeout    Timeout value in minutes before dimming
     * \param[in]  timeOutBrightness 
     * \param[in]  comm timeout disable 0=COMM enabled 
     */
     void light( int level, unsigned long timeout, int timeOutBrightness, int commdis );
    
    /** Send a command direct to display
    * @param str command string
    *
    * Example:\n
    * @code
    * lcd.sendCommand( "cls" ); // clear display
    * @endcode
    */
    void sendCommand( char *str );

    /** Return Xmax of display
    * @return int Xmax of display
    *
    */
    int getXmax( void );

    /** Return Ymax of display
    * @return int Ymax of display
    *
    */
    int getYmax( void );

    /** Return last touch x
    * @return int 
    *
    */
    int touchX( void );

    /** Return last touch y
    * @return int 
    *
    */
    int touchY( void );
    
    /** Return last touch status
    * @return int touch status
    *
    */
    int touchS( void );
    
    /** Send a string of data to display
    *
    */
    void sendString( char *str );

    /** Set stringID to display
    * @param ID string ID to write
    * @param str string to write
    *
    */
    void string( int ID, char *str );

    /** Get stringID from Display
    * @param ID string ID to read
    * @param str string to put data in
    *
    * Example:
    * @code
    * lcd.getStringID(66, ezVer);   // get ezLCD Firmware version
    * lcd.print(ezVer);             // print version
    * @endcode
    */
    void getStringID( int ID, char *str );

	void crlf(void);
	void print(int value, int mode);
	void print(long int value, int mode);
	void println(int value, int mode);
	void println(long int value, int mode);
    /** print string at current x y
    * @param str string prints directly to display
    */
    void printString( char *str );
    void print( char *str );
    void print( char str );
    void println( char *str );
    void println( char str );
    void println( void );
    
    /** print integer at current x y
    * @param int prints directly to display
    */
    void printInt( int value );
	void print(int value );
	void println(int value );
    
    /** print long at current x y
    * @param long prints directly to display
    */
    void printLong( long value );
	void print(long value);
	void println(long value);
	void print(double value);
	void println(double value);
	void print(double value, int digits);
	void println(double value, int digits);
    
    /** print stringID at current x y
    * @param str string prints directly to display
    */
    void printStringID( char ID );
	void printNumber(unsigned long n, int base);
    void printFloat(double number, int digits); 
   
    /** Set widget font
    * Fonts are located in the flash drive of the display\n
    * font 0 and font 1 are builtin fonts and are much faster to draw\n
    * in the /EZUSERS/FONTS and /EZSYS/FONTS directory\n
    * use the ezLCD3xx font convert utilty to convert true type fonts
    * @param str font name
    */
    void fontw( int id, char *str);
    /**
    *
    *
    *
    */
    
    void fontw( int ID, int font);
    /**
    *
    *
    *
    */

    void font(char *str);
    /**
    *
    *
    *
    */

    void font(int font);
    /**
    *
    *
    *
    */

    void fontO( bool dir );

    /**
    *
    *
    *
    */
    void clipArea( int l, int t, int r, int b);

    /**
    *
    *
    *
    */
    void clipEnable( bool enable );

    /** Sets color themes for widgets
    *
    *
    */
    void theme(int ID, int EmbossDkColor, int  EmbossLtColor, int TextColor0, int TextColor1, int TextColorDisabled, int Color0, int Color1, int ColorDisabled, int CommonBkColor, int Fontw);

    /** 
    * Draw an LED on display.
    * \param[in]	x		x location of LED center
    * \param[in]	y		y location of LED center
    * \param[in]	radius	radius of the LED
	* \param[in]	colorLed	color of the LED
	* \param[in]	colorHigh	color of the LED highlights
    */
    void drawLed( int x, int y, int radius, unsigned char colorLed, unsigned char colorHigh) ;

	/**
     * Draw/alter a groupBox.
     * \param[in]  id        Widget ID to assign.
     * \param[in]  x         Starting x-coordinate in pixels.
     * \param[in]  y         Starting y-coordinate in pixels.
     * \param[in]  width     Width in pixels.
     * \param[in]  height    Height in pixels.
     * \param[in]  options   Options 1=draw, 2=draw disabled, 3=draw right aligned, 4=draw center aligned    
     * \param[in]  theme     Theme ID to use.
     * \param[in]  stringID  String ID to use for text.
     */
    void groupBox( int id, int x, int y, int width, int height, int options, int theme, int stringID) ;

	/**
     * Draw/alter a checkBox.
     * \param[in]  id        Widget ID to assign.
     * \param[in]  x         Starting x-coordinate in pixels.
     * \param[in]  y         Starting y-coordinate in pixels.
     * \param[in]  width     Width in pixels.
     * \param[in]  height    Height in pixels.
     * \param[in]  option    Options 1=draw unchecked, 2=draw disabled, 3=draw checked, 4=redraw    
     * \param[in]  theme     Theme ID to use.
     * \param[in]  strid     String ID to use for text.
     */
    void checkBox( int id, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                 uint16_t option, int theme, int strid );

	/**
     * Draw/alter a radioButton.
     * \param[in]  id        Widget ID to assign.
     * \param[in]  x         Starting x-coordinate in pixels.
     * \param[in]  y         Starting y-coordinate in pixels.
     * \param[in]  width     Width in pixels.
     * \param[in]  height    Height in pixels.
     * \param[in]  option    Options 1=draw unchecked, 2=draw disabled, 3=draw checked, 4=redraw    
     * \param[in]  theme     Theme ID to use.
     * \param[in]  strid     String ID to use for text.
     */
    void radioButton( int id, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                 uint16_t option, int theme, int strid );

    /** Analog Meter Widget
    * Draw Analog Meter.
     * \param[in]  id        Widget ID to assign.
     * \param[in]  x         Starting x-coordinate in pixels.
     * \param[in]  y         Starting y-coordinate in pixels.
     * \param[in]  w		 Width in pixels.
     * \param[in]  h         Height in pixels.
     * \param[in]  options   Options 
	 * \param[in]  value	 Current Value
	 * \param[in]  min   	 Minimum Value
	 * \param[in]  max	     Maximum Value
     * \param[in]  theme     Theme ID to use.
     * \param[in]  strid     String ID to use for text.
	 * \param[in]  type		 Meter Value 0=360, 1=180, 2=90
    */
    void analogMeter( int ID, int x, int y, int w, int h, int options, int value, int min, int max, int theme, int stringID, int type);

    /** Analog Meter Color
    * Analog Meter Color.
     * \param[in]  ID        Widget ID to assign.
     * \param[in]  Sector1   Sector Color.
     * \param[in]  Sector2   Sector Color.
     * \param[in]  Sector3   Sector Color.
     * \param[in]  Sector4   Sector Color.
     * \param[in]  Sector5   Sector Color.
     * \param[in]  Sector6   Sector Color.
    */
    void analogMeterColor( int ID, int Sector1, int Sector2, int Sector3, int Sector4, int Sector5, int Sector6 );

    /** Touchzone Widget
    *
    *
    */
    void touchZone( int ID, int x, int y, int w, int h, bool option);

    /** Touchzone Shadow
     * \param[in]  mode				0=OFF, 1=ON.
     * \param[in]  Scolor			Shadow Color
     * \param[in]  Slinetype		Shadow Line Type
     * \param[in]  Slinethickness	Shadow Line Thickness
    */
    void shadow( int mode, int Scolor, int Slinetype, int Slinethickness );

    /** Button Widget
    *
    *
    */
    void button( int ID, int x, int y, int w, int h, int option, int align, int radius, int theme, int stringID );

    /**
     * Create/alter a dial widget.
     * \param[in]  id         Widget ID to assign.
     * \param[in]  theme      Theme ID to use.
     * \param[in]  x          Starting x-coordinate in pixels.
     * \param[in]  y          Starting y-coordinate in pixels.
     * \param[in]  radius     Radius of the dial in pixels.
     * \param[in]  resolution Resolution of the dial in degrees.
     * \param[in]  initial    Initial numeric position of the dial. 
     * \param[in]  max        Maximum numeric position of the dial. 
     * \param[in]  option     1=draw, 2=disabled, 3=ring, 4=accuracy
     */
    void dial( int id, uint16_t x, uint16_t y, uint16_t radius, uint16_t option,
             	int resolution, int initial, int max, int theme );

    /** Display Bitmap
    * Display Bitmap at current x y \n
    * supports GIF BMP JPG \n
    * images are located in the /EZUSERS/FONTS and /EZSYS/FONTS directory
    * @param str filename
    */
    bool picture( char *str );

    /** Display Bitmap
    * Display Bitmap at specfied x y \n
    * supports GIF BMP JPG \n
    * images are located in the /EZUSERS/FONTS and /EZSYS/FONTS directory
    * @param x x location to start bitmap
    * @param y y location to start bitmap
    * @param str filename
    */
    bool picture(  int x, int y ,char *str);
 
	/** Display Bitmap
    * Display Bitmap at specfied x y \n
    * supports GIF BMP JPG \n
    * images are located in the /EZUSERS/FONTS and /EZSYS/FONTS directory
    * @param x x location to start bitmap
    * @param y y location to start bitmap
	* @param options 1=align center 2=downscale 3= both
    * @param str filename
    */
    bool picture(  int x, int y, int options, char *str);

    /** StaticBox Widget
    * @param ID the Widget ID to create 
    * @param x
    * @param y
    * @param w
    * @param h
    * @param option
    * @param theme
    * @param stringID
    */
    void staticText( int ID, int x, int y, int w, int h, int option, int theme, int stringID);

    /** ProgressBar Widget
    * @param ID
    * @param x
    * @param y
    * @param w
    * @param h
    * @param option
    * @param value
    * @param max
    * @param theme
    * @param stringID
    */
   
    void progressBar(int ID, int x, int y, int w, int h, int option, int value, int max, int theme, int stringID);

    /** gauge Widget
    * @param ID
    * @param x
    * @param y
    * @param w
    * @param h
    * @param option
    * @param initial
    * @param min
    * @param max
    * @param theme
    * @param stringID
    *
    *
    */
    void gauge(int ID, int x, int y, int w, int h, int option, int initial, int min, int max, int theme, int stringID);
    
    /** Slider Widget
    * @param ID
    * @param x
    * @param y
    * @param w
    * @param h
    * @param option
    * @param range
    * @param res
    * @param value
    * @param theme
    *
    */
    void slider(int ID, int x, int y, int w, int h, int option, int range, int res, int value, int theme);
    
    void digitalMeter( int id, uint16_t x, uint16_t y, uint16_t width,
                      uint16_t height, uint16_t option, int initial,
                      int digits, int dotpos,int theme );
    /** wstate
    *
    *
    *
    */
    unsigned int wstate( int ID );

    /** wstate
    *
    *
    *
    */
    void wstate( int ID, int option );

    
    /** wquiet
    *   will disable the default data comming back from the GPU
    *   on widget events
    *
    */
    void wquiet( void );
    
    /** Wvalue set widget values
    * @param ID widget ID to update
    * @param value widget value to update
    */
    void wvalue( int ID, int value);

    /** Wvalue set widget values
    * @param ID widget ID to update
    * @param string to update
    */
	void wvalue( int ID, char *str );

    /** Wvalue set widget values
    * @param ID widget ID to update
    * @return widget value
    */
    unsigned int wvalue( int ID );
    
    /** Wstack is a 32 level stack of widget events
    * @param type LIFO  - Get the last widget event off the stack
    * @param type FIFO  - Get the first widget event off the stack
    * @param type CLEAR - Clear stack
    * @returns widget id and even touch, release
    */
    unsigned int wstack( int type );

	/** Send Debug data to IDE monitor
    * @param data  - data to display
    * @returns none
    */
    void Debug( unsigned long data, char *format = "%lu" );
    void Debug( long data, char *format = "%ld" );
    void Debug( unsigned int data, char *format = "%u" );
    void Debug( int data, char *format = "%i" );

    void Debug( char data );
    void Debug( char *str );

	/** Tx UART send character to GPU uart
    * @param type port  - Get the port number (pin)
    * @returns UART character or 0x8000 if none
    */
 	void TxUART( int port, char data );
	void TxUART( int port, char *str );

    /** Recv UART gets character from GPU uart
    * @param type port  - Get the port number (pin)
    * @returns UART character or 0x8000 if none
    */
 	int RecvUART( int port );
	int RxUART( int port );

	/** Available check to see if uart has character
    * @param type port  - Get the port number (pin)
    * @returns 1 has char, -1 no character -2 not configured
    */
 	int Available( int port );

	/** Available check to see if uart has character
    * @param type port  - Get the port number (pin)
    * @returns char, -1 no character -2 not configured
    */
 	int peek( int port );

	/** flush Initializes the UART (Rx and RX)
    * @param type port  - Get the port number (pin)
    * @returns 1 OK -1 not configured
    */
 	int flush( int port );

	/** FSopen is a file system open command for the flash drive on the arLCD
    * @param Filename - Defines the file to open
	* @param fileoption - defines the type open r=read, w=write, a=append, followed by h is binary mode
    */
    int FSopen( char *filename, char *mode );

	/** FSread is a file system read command for the flash drive on the arLCD
    * @param bytecount - Defines the number to read (upto 64 bytes)
    */
    int FSread( char * buffer, int bytecount );

	/** FSwrite is a file system write command for the flash drive on the arLCD
    * @param data - Defines the data to write.  Upto 64 bytes. in binary mode send hex (2 bytes)
    */
    int FSwrite( char *data, int count );

	/** FSclose is a file system close command for the flash drive on the arLCD
    */
    int FSclose( void );

	/** FSrewind is a file system rewind command for the flash drive on the arLCD
    */
    int FSrewind( void );

	/** FSseek is a file system seek command for the flash drive on the arLCD
    * @param offset - Defines the desired file location
 	* @param whence - Defines from where the offset applies. SEEK_SET=Begin, SEEK_CUR=Current, SEEK_END=END of file
    */
    int FSseek( long offset, int whence );

	/** FSerror is a file system FSerrno command for the flash drive on the arLCD
    * @returns FSerrno the latest file system error number
    */
    int FSerror( void );

	/** FStell is a file system tell command for the flash drive on the arLCD
    * @returns the current file location
    */
    long FStell( void );

	/** FSattrib is a file system attribute command for the flash drive on the arLCD
    * @param attrib - Defines the attributes of the currently open file
	* 1=ReadOnly, 2=Hidden, 4=System, 0x20=Archive
    */
    int FSattrib( int attribute );
    int GetFSattrib( void );

	/** FSeof is a file system end of file command for the flash drive on the arLCD
 	* @returns the current EOF status 0=No EOF, 1=EOF
    */
    int FSeof( void );

	/** FSgetcwd is a file system Get Current working directory command for the flash drive on the arLCD
 	* @returns the current directory
    */
    void FSgetcwd( void );

	/** FSchdir is a file system change directory command for the flash drive on the arLCD
 	* @param directory - the directory to change to
    */
    int FSchdir( char * directory );

	/** FSmkdir is a file system make directory command for the flash drive on the arLCD
 	* @param directory - the new directory to create
    */
    int FSmkdir( char * directory );

	/** FScopy is a file system copy file command for the flash drive on the arLCD
 	* @param source_filename - source file name
 	* @param dest_filename - new file name
    */
    int FScopy( char * source_filename, char * dest_filename );

	/** FSrename is a file system rename file command for the flash drive on the arLCD
 	* @param source_filename - existing file name
 	* @param dest_filename - new file name
    */
    int FSrename( char * source_filename, char * dest_filename );

	/** FSremove is a file system remove file command for the flash drive on the arLCD
 	* @param source_filename - existing file name
    */
    int FSremove( char * source_filename );

    /**
     * Numerical values for the EarthSEMPL commands.
     */

    enum Commands {
        Command=             0,     /**< Direct command. */
        Clr_Screen=          2,     /**< Clear to provided color. */
        Ping=                3,     /**< Return Pong */
        zBeep=               4,     /**< Beep provided duration
                                      *(frequency fixed) */
        Light=               5,     /**< \c 0 (off) to \c 100 (on) */
        Color=               6,
        eColor_ID=           7,
        Font=                10,    /**< Font number. */
        Fontw=               11,    /**< Font number widget. */
        Font_Orient=         12,    /**< Horizontal or vertical. */
        Line_Width=          13,    /**< 1 or 3. */
        Line_Type=           14,    /**< 1=dot dot 2=dash dash. */
        XY=                  15,    /**< X and Y. */
        StringID=            16,    /**< SID ASCII String or File Name that
                                      * ends with 0. */
        Plot=                17,    /**< Place Pixel at X and Y. */
        Line=                18,    /**< Draw a line to X and Y. */
        Box=                 19,    /**< Draws a Box to X and Y optional
                                      * fill. */
        Circle=              20,    /**< Draws a Circle with Radius optional
                                      * fill */
        Arc=                 21,    /**< Draws an Arc with Radius and Begin
                                      * Angle to End Angle. */
        Pie=                 22,    /**< Draws a Pie figure with Radius and
                                      * Begin Angle to End Angle and fills
                                      * it. */
        Picture=             24,    /**< Places a Picture on display. */
        Print=               25,    /**< Places the string on display which
                                      * ends with 0. */
        Beep_Freq=           26,    /**< Set the beeper frequency. */
		Get_Pixel=			 27,    /**< Get Pixel. */
		Calibrate=           28,    /**< Calibrate touch screen. */
        zReset=              29,    /**< Reset. */
        Rec_Macro=           30,    /**< Record Macro to flash drive. */
        Play_Macro=          31,    /**< Play Macro. */
        Stop_Macro=          32,    /**< Stop Macro. */
        Pause_Macro=         33,    /**< Pause n msec. */
        Loop_Macro=          34,    /**< Loop on Macro. */
        Speed_Macro=         35,    /**< Set the macro speed. */
        ConfigIO=            37,
        IO=                  38,	/**< Set/Get IO pin state */
        Bridge=              39,	/**< Set Bridge Command. */
        Security=            40,    /**< Set drive security string. */
        Location=            41,    /**< LID Location Value. */
        Upgrade=             43,
        Run_Macro=           44,
        Parameters=          45,
        ClipEnable=          46,    /**< Set clip Enable. */
        ClipArea=            47,    /**< Set clip area. */
		Snapshot=			 48,	/**< Snapshot the screen area. */
		Cmd=				 49,	/**< Sets the Command Port. */
        /* Filesystem operations */
		Comment=			 50,     /**< Comment */
		Fsgetcwd=			 51,     /**< Get current working directory */
		Fschdir=			 52,     /**< Change directory */
		Fsmkdir=			 53,     /**< Make directory */
		Fsrmdir=			 54,     /**< Remove directory */
		Fsdir=				 55,     /**< Display directory */
		Fscopy=				 56,     /**< File copy */
		Fsrename=			 57,     /**< File rename */
		Fsremove=			 58,     /**< File remove */
		Fsmore=				 59,     /**< File dump */
		Fsattrib=            60,     /**< File Attributes */
		Fsopen=              61,     /**< File Open */
		Fswrite=             62,     /**< File Write */
		Fsread=              63,     /**< File Close */
		Fsclose=             64,     /**< File Read */
		Fsrewind=            65,     /**< File Rewind */
		Fserror=             66,     /**< File Error */
		Fsseek=              67,     /**< File Seek */
		Fseof=               68,     /**< File EOF */
		Fstell=              69,     /**< File Tell */
		
        /* Widget commands */
        Set_Button=          70,    /**< Widget Button. */
        Set_CheckBox=        71,    /**< Widget Checkbox. */
        Set_Gbox=            72,    /**< Widget Group Box. */
        Set_RadioButton=     73,    /**< Widget Radio Button. */
        Set_DMeter=          74,    /**< Widget Digital Meter. */
        DMeter_Value=        75,    /**< Set DMeter value. */
        Set_AMeter=          76,    /**< Widget Analog Meter. */
        AMeter_Value=        77,    /**< Set AMeter value. */
        AMeter_Color=        78,    /**< Set AMeter color */
        Set_TouchZone=       79,    /**< touch zone       */
        Set_Dial=            80,    /**< Widget RoundDial. */
		Draw_LED=			 81,    /**< Draw LED. */
        Set_Slider=          82,    /**< Widget Slider. */
        Set_Progress=        85,    /**< Widget Progress bar. */
        Progress_Value=      86,    /**< Progress value. */
        Set_StaticText=      87,    /**< Widget Static text. */
        StaticText_Value=    88,    /**< Static text Value. */
        Choice=              89,    /**< Widget get choice. */
        Widget_Theme=        90,    /**< Widget Scheme. */
        Widget_Values=       91,    /**< Widget Values (Slider and Dial in this version).*/
        Widget_State=        92,    /**< Widget State (Button, checkbox, radiobutton in this version).*/
		Set_Gauge=			 93,	/**< Widget Gauge. */
		Gauge_Value=		 94,	/**< Set Gauge Value. */
		GetWidget_Values=    95,    /**< Get widget values. */        
        // no id returns the id of the last touched
        Xmax=                100,   /**< Return Xmax width. */
        Ymax=                101,   /**< Return Ymax height. */
        Wait=                102,   /**< Wait for touch. */
        Waitn=               103,   /**< Wait for no touch. */
        Waitt=               104,   /**< Wait for touch. */
        Threshold=           105,   /**< Touch threshold. */
        Verbose=             106,   /**< Controls the verbose mode. */
        Lecho=               107,   /**< Controls the echo mode. */
        Xtouch=              110,   /**< return touchX. */
        Ytouch=              111,   /**< return touchY. */
        Stouch=              112,   /**< return touchS. */
        Wquiet=              113,
        Wstack=              114,
		Avail=				 115,	/**< return UART available status */
		Peek=				 116,	/**< get character non-destructive */
		Flush=				 117,	/**< reset the UART and buffers */
		ReadUart=			 118,	/**< read UART on pin */
		WriteUart=			 119,	/**< write UART on pin */

		Shadow=				 252,	/**< used to turn on the shadow for hot spots. */
        Fshelp=              254
    };
protected:
private:
    void timeoutBegin( void );
    bool timeoutCheck( void );
};

#endif
