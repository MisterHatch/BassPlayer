//Preprocessor Directives

//Include libraries
#include <Servo.h>


//Define 
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

//String and Pick ID's
#define String 20
#define Pick 30
//DC Motor Direction Control Pins
//  Names reflect fret numbering
#define Higher 10
#define Lower 14
#define Count 0

//Variables
//Command Variable
char i = 'r';
//Destination Fret
int Des = 2;
//Direction
int Dir = 0;
//Current Position Fret
int Pos = 2;
//String Strum variable
Strum = 0;
//State Variable
State = 3;

//Initial Dynamixwl Bus
Dynamixel Dxl(DXL_BUS_SERIAL1); 

////////////////////////////////////////////////////////////////
//Setup
//////////////////////////////////
void setup() {
 Dxl.begin(3);
 //Set Pinmodes to Output for DC motor Control
 pinMode(Higher,OUTPUT);
 pinMode(Lower,OUTPUT);
 digitalWrite(Higher,LOW);
 digitalWrite(Lower,LOW);
 
 
 //Attach Interrupt to SerialUSB
 SerialUSB.attachInterrupt(usbInterrupt);
 
 //Digital Input for Fret Counting
 pinMode(Count, INPUT_PULLUP);
 attachInterrupt(Count,FretPos,FALLING);
 
 
 //Initiate String and Pick in Jointmode
 Dxl.jointMode(String);
 Dxl.jointMode(Pick);
}
//////////////////////////////////////////////////////////////


///////////////////////////////////
//FUNCTIONS////////////////////////
///////////////////////////////////

///////////////////////////////////////////////////////////////
//Serial USB Interupts
///////////////////////////////////
void usbInterrupt(byte* buffer, byte nCount){
  
  i = (char)buffer[0];
  SerialUSB.println(i);
  
  //Switch Statement for actions 
  switch (i){
    case 'r':
      //Go to rest position
      MoveFret(Pos);
      Dxl.goalPosition(String,510);
      delay(20);
      Dxl.goalPosition(Pick,210);
      break;
    case 'a':
      MoveFret(7);
      Pluck(1);
      break;
    case 'b':
      MoveFret(2);
      Pluck(0);
      break;
     case 'c':
       MoveFret(3);
       Pluck(0);
      break;
    case 'C':
      MoveFret(4);
      Pluck(0);
      break;
    case 'd':
      MoveFret(5);
      Pluck(0);
      break;
    case 'D':
      MoveFret(6);
      Pluck(0);
      break;
    case 'E':
      MoveFret(7);
      Pluck(0);
      break;
    case 'e':
      MoveFret(2);
      Pluck(1);
      break;
    case 'f':
      MoveFret(3);
      Pluck(1);
      break;
    case 'F':
      MoveFret(4);
      Pluck(1);
      break;
    case 'g':
      MoveFret(5);
      Pluck(1);
      break;
    case 'G':
      MoveFret(6);
      Pluck(1);
      break;
    default:
      MoveFret(Pos);
      Dxl.goalPosition(String,510);
      delay(20);
      Dxl.goalPosition(Pick,210);
      break;  
  }
}
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Fret Postion: Determine Fretted Postion
void FretPos(){
  
  detachInterrupt(Count);
  if (Dir == 1){
    Pos++;
  }
  else if (Dir == 2){
    Pos--;
  }
  else{
    Pos = Pos;
  }
  
  SerialUSB.println(Pos);
  delay(1000);
  attachInterrupt(Count,FretPos,FALLING);
  
  
}
/////////////////////////////////////////////////////////

//////////////////////////////////////////////////////
//Move Fretter Function
// when 0 Stop
// when 1 Higher
// when 2 Lower
void MoveFret(int D){
  //Stopped
  Des = D;
}
////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//Pluck String Function
void Pluck(int s){
  Strum = s;
  //PLuck High or Low String
  SerialUSB.print("Plucks string : ");
  SerialUSB.println(s);
  SerialUSB.print("Position : ");
  SerialUSB.println(Pos);
  SerialUSB.print("Destination : ");
  SerialUSB.println(Des);
}

void Pick(){
   //Start Position
      Dxl.goalPosition(String,510);
      delay(20);
      Dxl.goalPosition(Pick,210);
      delay(20);
      
  if (Strum == 0){
     //Pluck Low
      Dxl.goalPosition(Pick,50);
      Dxl.goalPosition(String,800);
      delay(500);
      Dxl.goalPosition(Pick, 500);
      delay(500);
      Dxl.goalPosition(String,310);
      delay(500);
      Dxl.goalPosition(Pick,310);
      delay(500);
      Dxl.goalPosition(String,510);
      delay(500);
      Dxl.goalPosition(Pick,210);
      delay(20);}
   else if(Strum ==1){
      //Pluck High
      Dxl.goalPosition(String,510);
      delay(500);
      Dxl.goalPosition(Pick,210);
      delay(500);      
      Dxl.goalPosition(Pick,210);
      Dxl.goalPosition(String,220);
      delay(500);
      Dxl.goalPosition(Pick, 305);
      delay(500);//
      Dxl.goalPosition(String,510);
      delay(500);
      Dxl.goalPosition(Pick,210);
      delay(20);
   }
   else {
      Dxl.goalPosition(String,510);
      delay(20);
      Dxl.goalPosition(Pick,210);
      delay(20);
   }
  
}

////////////////////////////////////
//Main Loop
////////////////////////////////////
void loop() {
 
//Position Starts on 1st fret
  while(Pos != Des){
    //Higher Fret
    if(Pos < Des){
      Dir = 1;
      digitalWrite(Lower,LOW);
      digitalWrite(Higher,HIGH);
    }
    //Lower Fret
    else if(Pos > Des){
      Dir = 2;
      digitalWrite(Higher,LOW);
      digitalWrite(Lower,HIGH);
    }
  }
  if(Pos == Des){
    Dir = 0;
    digitalWrite(Higher,LOW);
    digitalWrite(Lower,LOW);
  }
 
 Pick();

 delay(20);
 
 
 
//     case 'a':
//      //DO THINGS HERE
//      Des = 10;
//      Dir = 1;
//      SerialUSB.println(Dir);
//      MoveFret(Dir);
//      break;
//    case 'd':
//      //DO THINGS HERE
//      Des = 10;
//      Dir = 0;
//      SerialUSB.println(Dir);
//      MoveFret(Dir);
//      break;
//    case 's':
//      Des = Pos;
//      SerialUSB.println(Des);
//      MoveFret(Dir);
//      break;
 
 
 
 
 
// 
// 
//  speed = 1200;
//  
//  Fret.writeMicroseconds(speed);
//  
//  delay(1000);
//  
//  speed = 0;
//  
//  Fret.writeMicroseconds(speed);
//  
//  delay(1000);
  //Center
  Dxl.goalPosition(String, 510); 
  Dxl.goalPosition(Pick, 210); 
//  // Wait for 1 second (1000 milliseconds)
//  delay(3000);
//  
//  Dxl.goalPosition(String, 420);
//  delay(20);
//
//  delay(1000);
//  Dxl.goalPosition(String, 600);
//  

//  //D string pluck  
//  /*Turn dynamixel ID 1 to position 300*/
//  Dxl.goalPosition(String, 480);
//  delay(20); 
//  Dxl.goalPosition(Pick, 100); 
//  delay(500); 
//  Dxl.goalPosition(Pick, 210); 
//  delay(500); 
//  Dxl.goalPosition(Pick, 100); 
//  // Wait for 1 second (1000 milliseconds)
}

