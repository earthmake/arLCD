// 
// Modified by Rich Obermeyer January 14, 2014.
// Modified by Jonathan Doerr March 24, 2014.
// Copyright 2013 - Under creative commons license 3.0:
//        Attribution-ShareAlike CC BY-SA
//
// This software is furnished "as is", without technical support, and with no 
// warranty, express or implied, as to its usefulness for any purpose.
/**
*  arLCD test code v1.0 4/16/2013
*  (c)2013 EarthLCD
*  ken@earthlcd.com
*  !!!!! copy em.gif o.gif and x.gif from this directory to you arlcd \ezusers\images
*
*  This test code uses touch interrupt of the GPU to Signal touch events
*  Using Interrupts offloads the arduino from having to poll for touch events
*  
*/
#include <ezLCDLib.h>

#define LED_PIN 13

ezLCD3 lcd;

volatile boolean ezLCDInt = false; // flag to indicate interrupt
unsigned int gridx[] ={98, 172, 246, 98, 172, 246, 98, 172, 246};
unsigned int gridy[] ={18, 18, 18, 92, 92, 92 , 166, 166, 166};

unsigned int linesx[]={166,166,  241, 241  ,92,  317  ,92,317 };
unsigned int linesy[]={10, 235,  10 , 235  ,86, 86   ,160,160 };

int temp =0;
bool turn =1 ;
bool x = 1;
bool o = 0;
char winner =false;
unsigned char gameBoard[9]={5,5,5,5,5,5,5,5,5};
unsigned long touch;
void setup()
{
  lcd.begin( EZM_BAUD_RATE );
  lcd.sendCommand("cfgio 9 touch_int low quiet");  // allows interupts to work properly
  showMainScreen();
  pinMode( LED_PIN, OUTPUT );
  digitalWrite( LED_PIN, LOW );
  
  attachInterrupt(0, ezLCDevent, LOW);  
  ezLCDInt = false;
}
void drawColoredBox(unsigned char n, unsigned char c) {
    lcd.color(c);
    lcd.xy(gridx[n],gridy[n]);
    lcd.box(64,64,1);
}

void drawTurn( unsigned char n ){
  if(gameBoard[n] ==5) {
  if(turn == x) {
  lcd.picture(gridx[n],gridy[n],"x.gif");
  gameBoard[n]=x;
  lcd.string(1,"ME");
  lcd.wstate(10,3);
  }
  else {
  lcd.picture(gridx[n],gridy[n],"o.gif");
  gameBoard[n]=o;
  lcd.string(1,"YOU");
  lcd.wstate(10,3);
  }
  turn ^=1;
}
}
char checkForMove( void ) {
      unsigned char n;
      // try to win
      if(gameBoard[0]+gameBoard[1]+gameBoard[2] == 5) {if(gameBoard[0]==5) return 0;if(gameBoard[1]==5) return 1;if(gameBoard[2]==5) return 2; }
      if(gameBoard[0]+gameBoard[4]+gameBoard[8] == 5) {if(gameBoard[0]==5) return 0;if(gameBoard[4]==5) return 4;if(gameBoard[8]==5) return 8; }
      if(gameBoard[0]+gameBoard[3]+gameBoard[6] == 5) {if(gameBoard[0]==5) return 0;if(gameBoard[3]==5) return 3;if(gameBoard[6]==5) return 6; }

      if(gameBoard[3]+gameBoard[4]+gameBoard[5] == 5) {if(gameBoard[3]==5) return 3;if(gameBoard[4]==5) return 4;if(gameBoard[5]==5) return 5; }     
      if(gameBoard[1]+gameBoard[4]+gameBoard[7] == 5) {if(gameBoard[1]==5) return 1;if(gameBoard[4]==5) return 4;if(gameBoard[7]==5) return 7; }    
      if(gameBoard[2]+gameBoard[5]+gameBoard[8] == 5) {if(gameBoard[2]==5) return 2;if(gameBoard[5]==5) return 5;if(gameBoard[8]==5) return 8; }    
      
      if(gameBoard[2]+gameBoard[4]+gameBoard[6] == 5) {if(gameBoard[2]==5) return 2;if(gameBoard[4]==5) return 4;if(gameBoard[6]==5) return 6; }    
      if(gameBoard[6]+gameBoard[7]+gameBoard[8] == 5) {if(gameBoard[6]==5) return 6;if(gameBoard[7]==5) return 7;if(gameBoard[8]==5) return 8; }   
      // block
      if(gameBoard[0]+gameBoard[1]+gameBoard[2] == 7) {if(gameBoard[0]==5) return 0;if(gameBoard[1]==5) return 1;if(gameBoard[2]==5) return 2; }
      if(gameBoard[0]+gameBoard[4]+gameBoard[8] == 7) {if(gameBoard[0]==5) return 0;if(gameBoard[4]==5) return 4;if(gameBoard[8]==5) return 8; }
      if(gameBoard[0]+gameBoard[3]+gameBoard[6] == 7) {if(gameBoard[0]==5) return 0;if(gameBoard[3]==5) return 3;if(gameBoard[6]==5) return 6; }

      if(gameBoard[3]+gameBoard[4]+gameBoard[5] == 7) {if(gameBoard[3]==5) return 3;if(gameBoard[4]==5) return 4;if(gameBoard[5]==5) return 5; }     
      if(gameBoard[1]+gameBoard[4]+gameBoard[7] == 7) {if(gameBoard[1]==5) return 1;if(gameBoard[4]==5) return 4;if(gameBoard[7]==5) return 7; }    
      if(gameBoard[2]+gameBoard[5]+gameBoard[8] == 7) {if(gameBoard[2]==5) return 2;if(gameBoard[5]==5) return 5;if(gameBoard[8]==5) return 8; }    
      
      if(gameBoard[2]+gameBoard[4]+gameBoard[6] == 7) {if(gameBoard[2]==5) return 2;if(gameBoard[4]==5) return 4;if(gameBoard[6]==5) return 6; }    
      if(gameBoard[6]+gameBoard[7]+gameBoard[8] == 7) {if(gameBoard[6]==5) return 6;if(gameBoard[7]==5) return 7;if(gameBoard[8]==5) return 8; }   
      if((gameBoard[2] == 1) && (gameBoard[6]==1) && (gameBoard[8]==5)) return 8; 
      if(gameBoard[4]==5) return 4;
      if(gameBoard[0]==5) return 0;
      if(gameBoard[2]==5) return 2;
      if(gameBoard[6]==5) return 6;
      if(gameBoard[8]==5) return 8;      
      for(n=0;n<9;n++) {if(gameBoard[n]==5) return n;}
}
char checkForWinner( unsigned char n ) {
  
      if(gameBoard[0]+gameBoard[1]+gameBoard[2] == 3) { lcd.string(1,"you won");  showWinningLine(1); return 1; }
      if(gameBoard[0]+gameBoard[4]+gameBoard[8] == 3) {  lcd.string(1,"you won");  showWinningLine(2);return 2;}
      if(gameBoard[0]+gameBoard[3]+gameBoard[6] == 3) {  lcd.string(1,"you won");  showWinningLine(3); return 3;}      
      if(gameBoard[3]+gameBoard[4]+gameBoard[5] == 3) {  lcd.string(1,"you won");  showWinningLine(4); return 4;}
      if(gameBoard[1]+gameBoard[4]+gameBoard[7] == 3) { lcd.string(1,"you won");  showWinningLine(5); return 5;}
      if(gameBoard[2]+gameBoard[5]+gameBoard[8] == 3) {  lcd.string(1,"you won");  showWinningLine(6); return 6;}    
      if(gameBoard[2]+gameBoard[4]+gameBoard[6] == 3) {  lcd.string(1,"you won");  showWinningLine(7); return 7;}          
      if(gameBoard[6]+gameBoard[7]+gameBoard[8] == 3) {  lcd.string(1,"you won");  showWinningLine(8); return 8;}        

      if(gameBoard[0]+gameBoard[1]+gameBoard[2] == 0) {  lcd.string(1," I WIN ");  showWinningLine(1); return 1;}
      if(gameBoard[0]+gameBoard[4]+gameBoard[8] == 0) {  lcd.string(1," I WIN ");  showWinningLine(2); return 2;}
      if(gameBoard[0]+gameBoard[3]+gameBoard[6] == 0) {  lcd.string(1," I WIN ");  showWinningLine(3); return 3;}      
      if(gameBoard[3]+gameBoard[4]+gameBoard[5] == 0) {  lcd.string(1," I WIN ");  showWinningLine(4); return 4;}
      if(gameBoard[1]+gameBoard[4]+gameBoard[7] == 0) {  lcd.string(1," I WIN ");  showWinningLine(5); return 5;}
      if(gameBoard[2]+gameBoard[5]+gameBoard[8] == 0) {  lcd.string(1," I WIN ");  showWinningLine(6); return 6;}    
      if(gameBoard[2]+gameBoard[4]+gameBoard[6] == 0) {  lcd.string(1," I WIN ");  showWinningLine(7); return 7;}          
      if(gameBoard[6]+gameBoard[7]+gameBoard[8] == 0) {  lcd.string(1," I WIN ");  showWinningLine(8); return 8;}          
      if(gameBoard[0] !=5 && gameBoard[1] !=5 && gameBoard[2] !=5 && gameBoard[3] !=5 && gameBoard[4] !=5 && gameBoard[5] !=5 && gameBoard[6] !=5 && gameBoard[7] !=5 && gameBoard[8] !=5 ) {  lcd.string(1,"DRAW"); return 9;}
      return false;
}

void showMainScreen( void ) {
  unsigned char x=0;
  unsigned char y=0;
  temp =0;
  turn =1 ;
  x = 1;
  o = 0;
  winner =false;
  gameBoard[0]=5;
  gameBoard[1]=5;
  gameBoard[2]=5;
  gameBoard[3]=5;
  gameBoard[4]=5;  
  gameBoard[5]=5;
  gameBoard[6]=5;
  gameBoard[7]=5;  
  gameBoard[8]=5;  
  lcd.cls( 0 );
  lcd.color(WHITE);
  lcd.light(100);
  for(temp=0;temp<9;temp++) {
    lcd.touchZone(temp+1,gridx[temp],gridy[temp],64,64,1);
  }
  lcd.xy(0,0);
  lcd.picture(0,0,"em.gif");
  lcd.string(1,"You");
  lcd.staticText(10, 38, 0, 80, 20, 1, 1, 1);
  lcd.color(WHITE);
  lcd.xy(35,200);
  lcd.printString("\\[1rWritten By Ken Segler\\[0r");
  lcd.xy(55,200);
  lcd.printString("\\[1r       For The arLCD\\[0r");

  lcd.color(RED);
  lcd.lineType(0);
  lcd.xy(linesx[0]-1,linesy[0]);
  lcd.line(linesx[1]-1,linesy[1]);

  lcd.xy(linesx[2]-1,linesy[2]);
  lcd.line(linesx[3]-1,linesy[3]);
  
  lcd.xy(linesx[4],linesy[4]-1);
  lcd.line(linesx[5],linesy[5]-1);

  lcd.xy(linesx[6],linesy[6]-1);
  lcd.line(linesx[7],linesy[7]-1);  


  lcd.xy(linesx[0]+1,linesy[0]);
  lcd.line(linesx[1]+1,linesy[1]);

  lcd.xy(linesx[2]+1,linesy[2]);
  lcd.line(linesx[3]+1,linesy[3]);
  
  lcd.xy(linesx[4],linesy[4]+1);
  lcd.line(linesx[5],linesy[5]+1);

  lcd.xy(linesx[6],linesy[6]+1);
  lcd.line(linesx[7],linesy[7]+1);  
  
  lcd.color(WHITE);
  lcd.lineType(2);
  lcd.xy(linesx[0],linesy[0]);
  lcd.line(linesx[1],linesy[1]);

  lcd.xy(linesx[2],linesy[2]);
  lcd.line(linesx[3],linesy[3]);
  
  lcd.xy(linesx[4],linesy[4]);
  lcd.line(linesx[5],linesy[5]);

  lcd.xy(linesx[6],linesy[6]);
  lcd.line(linesx[7],linesy[7]);  

  lcd.lineType(0);
}
void showWinningLine(char n ){
  lcd.lineWidth(3);
  lcd.color(YELLOW);
  if(n==1) { lcd.xy(92,48);lcd.line(317,48); }
  if(n==4) { lcd.xy(92,121);lcd.line(317,121); }  
  if(n==8) { lcd.xy(92,196);lcd.line(317,196); }  
 
  if(n==3) { lcd.xy(130,10);lcd.line(130,235); }
  if(n==5) { lcd.xy(205,10);lcd.line(205,235); }
  if(n==6) { lcd.xy(280,10);lcd.line(280,235); } 

  if(n==2) { lcd.xy(92,10);lcd.line(317,235); } 
  if(n==7) { lcd.xy(92,235);lcd.line(317,10); }   
  lcd.color(WHITE);
  lcd.lineWidth(1);
}

void loop()
{
  byte n;
   if(turn==0) 
       drawTurn(checkForMove());
      winner = checkForWinner(n);
  if(winner)
  {
  ezLCDInt = false;
  lcd.xy(97,88);
  lcd.color(BLACK);
  lcd.box(213,71,1);
  lcd.color(WHITE);
  lcd.xy(175,90);

  lcd.printStringID(1);
  lcd.xy(97,110);
  lcd.printString("          Touch Screen to");
  lcd.xy(97,128);
  lcd.printString("         Start A New Game");
  while(ezLCDInt == false);
  showMainScreen();
  ezLCDInt = false;
  winner=false;
  }

  if(ezLCDInt) {
  ezLCDInt = false;
  lcd.color(WHITE);
  touch = lcd.wstack(1);
  n=10;
      tone(3, 2000, 100); 
    switch(touch)
    {
      case 1:
      n =0;
      break;
      case 2:
      n =1;
      break;
      case 3:
      n =2;      
      break;

      case 4:
      n =3;      
      break;
      case 5:
      n =4;      
      break;
      case 6:
      n =5;      
      break;

      case 7:
      n =6;      
      break;
      case 8:
      n =7;
      break;
      case 9:
      n =8;      
      break;
      
    }
  if(n >= 0 && n<=8 ) {
     drawTurn(n);
     winner = checkForWinner(n);
      n=10;
  }
  }
}


void ezLCDevent( void ) {
  ezLCDInt = true;
}
