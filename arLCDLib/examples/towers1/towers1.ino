// 
// Modified by Rich Obermeyer 1/14/2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/*
  Towers
  Towers of Hanoi demonstration.
  
  Author: Jim Mischel
  This program is in the public domain.
*/

#include <ezLCDLib.h>

ezLCD3 lcd;

#define ANIMATE_MOVES

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

// number of discs to play with.
// program supports values 1 through 8.
const int MAX_DISC = 8;

// time to wait between disc moves
const int DISC_DELAY = 1;

// time to wait between games
const int GAME_DELAY = 5000;

// discWidth is 1/2 the actual disc width.
// discs are centered on the pegs.
const int HALF_DISC_WIDTH = 5;
const int DISC_HEIGHT = 8;

// pegs at 40, 160, 280
const int LEFT_PEG = SCREEN_WIDTH/8;

const int BASE_Y = SCREEN_HEIGHT - DISC_HEIGHT;

const int PEG_WIDTH = 5;
const int PEG_HEIGHT = DISC_HEIGHT * (MAX_DISC +1);
const int PEG_TOP = BASE_Y - PEG_HEIGHT;

const int PEG_COLOR = 120;

int pegCenter(int peg)
{
  int c = LEFT_PEG + (LEFT_PEG * peg * 3);
  if (peg == 0) c += 5;
  if (peg == 2) c -= 5;
  return c;
}

void drawPeg(int peg)
{
  // lefPeg * ((x *2) + 1)
  int pegx = pegCenter(peg) - (PEG_WIDTH/2);
  lcd.xy(pegx, PEG_TOP);
  lcd.color(PEG_COLOR); // Sandy brown
  lcd.box(PEG_WIDTH, PEG_HEIGHT, 1);  
}

int discWidth(int disc)
{
  return (disc * HALF_DISC_WIDTH);
}

// ROYGBIV + Pink
int discColors[] = {4, 36, 6, 9, 12, 61, 51, 26};
int pegStates[] = {0, 0, 0};

void getDiscXY(int disc, int peg, int pos, int* discx, int* discy, int *discWidth)
{
  *discy = BASE_Y - (1+pos) * DISC_HEIGHT;
  *discWidth = 2*(disc+1)*HALF_DISC_WIDTH + PEG_WIDTH;
  *discx = pegCenter(peg) - *discWidth/2;
}

void drawDiscBox(int disc, int peg, int pos, int color)
{
  int discx, discy, discWidth;

  getDiscXY(disc, peg, pos, &discx, &discy, &discWidth);
  lcd.xy(discx, discy);
  lcd.color(color);
  lcd.box(discWidth, DISC_HEIGHT, 1);  
}

void drawDisc(int disc, int peg, int pos)
{
  drawDiscBox(disc, peg, pos, discColors[disc]);
}

void getPegXY(int peg, int pos, int *pegx, int *pegy)
{
  *pegx = pegCenter(peg) - (PEG_WIDTH/2);
  *pegy = BASE_Y - (pos+1)*DISC_HEIGHT;
}

void eraseDisc(int disc, int peg, int pos)
{
  drawDiscBox(disc, peg, pos, BLACK);
  // now draw the peg portion
  int pegx, pegy;
  getPegXY(peg, pos, &pegx, &pegy);
  lcd.xy(pegx, pegy);
  lcd.color(120); // Sandy brown
  lcd.box(PEG_WIDTH, DISC_HEIGHT, 1);  
}

void setup()
{
  lcd.begin(EZM_BAUD_RATE);
  lcd.cls(BLACK, WHITE);

  lcd.xy("ct");//middle top
  lcd.println("Towers of Hanoi\" \"ct");
  lcd.xy( 320/2, 20 );//middle one line down
  lcd.println("Written by: Jim Mischel\" \"ct");  
  // Draw the base
  lcd.xy(0, BASE_Y);
  lcd.color(PERU); // Peru (it's brown)
  lcd.box(320, 5, 1);
  
  // Draw the pegs
  drawPeg(0);
  drawPeg(1);
  drawPeg(2);

  int x;
  for (x = MAX_DISC-1; x >= 0; --x)
  {
    drawDisc(x, 0, MAX_DISC-x-1);
  }
  pegStates[0] = MAX_DISC;
}

void debugOut(int x, int y, String s)
{
  lcd.xy(x, y);
  lcd.color(WHITE);
  char buff[s.length()+1];
  s.toCharArray(buff, s.length()+1);
  lcd.printString(buff);
  
}

// If dir is negative, we're moving up.
// if dir is >= 0, we're moving down.
void animateOnPeg(int disc, int peg, int pos, int dir)
{
  int discx, discy, discWidth;
  int pegx, pegy;
  
  getDiscXY(disc, peg, pos, &discx, &discy, &discWidth);
  getPegXY(peg, pos, &pegx, &pegy);

  int inc = -1;
  int targety = PEG_TOP - DISC_HEIGHT - 1;
  int leadingOffset = 0;
  int trailingOffset = DISC_HEIGHT-1;
  if (dir >= 0)
  {
    inc = 1;
    int t = discy;
    discy = targety;
    targety = t;
    
    t = leadingOffset;
    leadingOffset = trailingOffset;
    trailingOffset = t;
//    debugOut(0, 0, String(targety));
  }

  do
  {
    // draw leading row of disc
    lcd.xy(discx, discy+leadingOffset+1);
    lcd.color(discColors[disc]);
    lcd.line(discx+discWidth, discy+leadingOffset+1);

    // erase trailing row of disc
    lcd.xy(discx, discy+trailingOffset);
    lcd.color(BLACK);
    lcd.line(discx+discWidth, discy+trailingOffset);
    
    // draw revealed peg portion
    if (discy+trailingOffset > PEG_TOP)
    {
      lcd.xy(pegx, discy+trailingOffset);
      lcd.color(PEG_COLOR);
      lcd.line(pegx+PEG_WIDTH, discy+trailingOffset);
    }

    discy += inc;
  } while (discy != targety);
}

void animateOver(int disc, int fp, int tp)
{
  int discx, discy, discWidth;
  int fpx, fpy;
  int tpx, tpy;
  
  getDiscXY(disc, fp, 0, &discx, &discy, &discWidth);
  discy = PEG_TOP - DISC_HEIGHT;
  int discBottom = discy + DISC_HEIGHT - 1;
  
  getPegXY(fp, 0, &fpx, &fpy);
  getPegXY(tp, 0, &tpx, &tpy);

  int inc = 1;
  int leadingOffset = discWidth;
  int trailingOffset = 0;
  if (fp > tp)
  {
    inc = -1;
    int t = leadingOffset;
    leadingOffset = trailingOffset;
    trailingOffset = t;
  }
  
  do
  {
    // draw leading edge of pixels
    lcd.xy(discx+leadingOffset+1, discy);
    lcd.color(discColors[disc]);
    lcd.line(discx+leadingOffset+1, discBottom);
    
    // erase trailing edge of pixels
    lcd.xy(discx+trailingOffset, discy);
    lcd.color(BLACK);
    lcd.line(discx+trailingOffset, discBottom);
    
    discx += inc;
    fpx += inc;
  } while (fpx != tpx);
}

void towers(int fp, int tp, int up, int ht)
{
  if (ht == 0)
    return;
  towers(fp, up, tp, ht-1);
  
  // move disc ht-1 from fp to tp
  // pegStates tells us how high each peg's stack is
#ifdef ANIMATE_MOVES
  animateOnPeg(ht-1, fp, pegStates[fp]-1, -1);
  animateOver(ht-1, fp, tp);
  animateOnPeg(ht-1, tp, pegStates[tp], 1);
#else
  // erase disc(ht-1) from peg(fp) at position (pegStates[fp]-1)
  eraseDisc(ht-1, fp, pegStates[fp]-1);
  
  // draw disc(ht-1) on peg(tp) at position (pegStates[tp])
  drawDisc(ht-1, tp, pegStates[tp]);
#endif

  // and then update the peg states
  --pegStates[fp];
  ++pegStates[tp];
  
  delay(DISC_DELAY);
  towers(up, tp, fp, ht-1);
}

int fromPeg = 0;
int toPeg = 1;
int usingPeg = 2;

void loop()
{
  delay(GAME_DELAY);
  
  // move stack
  towers(fromPeg, toPeg, usingPeg, MAX_DISC);
  
  // now adjust things so that it moves the stack
  // to the next peg.
  int temp = fromPeg;
  fromPeg = toPeg;
  toPeg = usingPeg;
  usingPeg = temp;
}
