#include "drive.h"
#include "Arduino.h"

// assign meaningful names to those pins that will be used
#define pinLeftSensor A5      //pin A5
#define pinRightSensor A3     //pin A3
#define pinWallSensor A0    //pin A0
#define pinMiddleSensor A1  //pin A1

#define pinLQ3 3              //pin D3
#define pinLQ2 4              //pin D4
#define pinLQ1 5              //pin D5
#define pinLQ0 6              //pin D6

#define pinRQ3 7              //pin D7
#define pinRQ2 8              //pin D8
#define pinRQ1 9              //pin D9
#define pinRQ0 10             //pin D10

#define pinLdir 11            //pin D11
#define pinRdir 12            //pin D12

#define BACKWARD LOW          //back as LOW
#define FORWARD HIGH          //forward as HIGH



    

//easier way to set the left motor
void L_drive_motor(int LQ3,int LQ2,int LQ1,int LQ0,int Ldir)
{
  digitalWrite(pinLQ3, LQ3);
  digitalWrite(pinLQ2, LQ2);
  digitalWrite(pinLQ1, LQ1);
  digitalWrite(pinLQ0, LQ0);
  digitalWrite(pinLdir,Ldir);
}

//easier way to set the right motor
void R_drive_motor(int RQ3,int RQ2,int RQ1,int RQ0,int Rdir)
{
  digitalWrite(pinLQ3, RQ3);
  digitalWrite(pinLQ2, RQ2);
  digitalWrite(pinLQ1, RQ1);
  digitalWrite(pinLQ0, RQ0);
  digitalWrite(pinLdir,Rdir);
}

//start 
void start(int wall_S, int* state)
{
  while (*state == 1)
  {
    L_drive_motor(0,0,0,0,FORWARD);
    R_drive_motor(0,0,0,0,FORWARD);
    digitalWrite(LED_BUILTIN, HIGH);
    if(wall_S == 1) //release the white wall
    {
      *state += 1;
      digitalWrite(LED_BUILTIN, LOW);
      break;
    }
  }
}

void stop_and_back(int wall_S, int* state)
{
  if(*state == 2 && wall_S == 0)
  {
     L_drive_motor(0,0,0,0,BACKWARD);
     R_drive_motor(0,0,0,0,BACKWARD);
     delay(1500);
     *state += 1;
  }
  L_drive_motor(0,1,1,1,BACKWARD);
  R_drive_motor(0,1,1,1,BACKWARD);
  delay(4000);
  L_drive_motor(0,0,0,0,BACKWARD);
  R_drive_motor(0,0,0,0,BACKWARD);
  digitalWrite(LED_BUILTIN, HIGH);  
}

//adjust the position of the car
void adjust(int left_S, int right_S, int middle_S)
{
  if(!middle_S)
  {
    //go too right, turn left
    if (!left_S && right_S)
    {
      L_drive_motor(0,1,1,0,FORWARD);
      R_drive_motor(1,0,1,1,FORWARD);    
    }
  
    //go too left, turn right
    else if (left_S && !right_S)
    {
      L_drive_motor(1,0,1,1,FORWARD);
      R_drive_motor(0,1,1,0,FORWARD);
    } 
     
    //on the track haoHaoZou...
    else if (left_S && right_S)
    {
      L_drive_motor(0,1,1,1,FORWARD);
      R_drive_motor(0,1,1,1,FORWARD);
    }
  }
}

// decide and turn on the splits
void split_turn(int left_S,int right_S, 
                int middle_S, int* turn_num)
{
  while(!left_S && !right_S && middle_S)
  {
    switch(*turn_num)
    {
      case 1:   //first turn: left
          L_drive_motor(0,0,1,1,BACKWARD);
          R_drive_motor(1,1,1,1,FORWARD);
          break;
      case 2:   //second turn: left
          L_drive_motor(0,0,1,1,BACKWARD);
          R_drive_motor(1,1,1,1,FORWARD);
          break;
      case 3:   //third turn: right
          L_drive_motor(1,1,1,1,FORWARD);
          R_drive_motor(0,0,1,1,BACKWARD);
          break;
      case 5:   //alarm for error decision and pause
          digitalWrite(LED_BUILTIN, HIGH);
          delay(400);
          digitalWrite(LED_BUILTIN, LOW);
          delay(400);       
    }
  }
  *turn_num += 1;
  //delay(500)
}
