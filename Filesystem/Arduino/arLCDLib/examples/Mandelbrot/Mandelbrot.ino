// 
// Modified by Jonathan Doerr, March 11, 2014
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.

#include <stdint.h>
#include <ezLCDLib.h>

ezLCD3 lcd; // create lcd object

const int
  pixelWidth  = 320,  // LCD dimensions
  pixelHeight = 240,
  iterations  = 128;  // Fractal iteration limit or 'dwell'
const float
  leftReal    = -0.67058,  
  rightReal   = -0.67008,
  topImag     =  -0.45820,
  botImag     = -0.45770,
  
  centerReal  =  (rightReal-((rightReal - leftReal)/2)), // Image center point in complex plane
  centerImag  =  (botImag-((botImag - topImag)/2)),
  rangeReal   =  (rightReal - leftReal), // Image coverage in complex plane
  rangeImag   =  (botImag - topImag),

  startReal   = centerReal - rangeReal * 0.5,
  startImag   = centerImag + rangeImag * 0.5,
  incReal     = rangeReal / (float)pixelWidth,
  incImag     = rangeImag / (float)pixelHeight;

void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.cls();
}

void loop()
{
  int           x,y,n,i;
  float         a,b,a2,b2,posReal,posImag;
  unsigned int rgb[iterations];
  
  for(i = 0; i < iterations; i++) {
    rgb[i] = i                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          ;
  }
  
  posImag = startImag;
  for(y = 0; y < pixelHeight; y++) {
    posReal = startReal;
    for(x = 0; x < pixelWidth; x++) {
      a = posReal;
      b = posImag;
      for(n = iterations; n > 0 ; n--) {
        a2 = a * a;
        b2 = b * b;
        if((a2 + b2) >= 4.0) break;
        b  = posImag + a * b * 2.0;
        a  = posReal + a2 - b2;
      }
      lcd.color(rgb[n]);
      lcd.plot(x,y);
       posReal += incReal;
    }
    posImag -= incImag;
  }
}

