/*
  ELEC1100 project
  Group38
*/
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


//the times of the turn
int turn_times = 1;  

//the state of start or stop or return
int state = 1;

//define variables to be used in script
int leftSensor = 1;
int rightSensor = 1;
int middleSensor = 1;
int wallSensor = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // define pins as input and output.
  pinMode(pinLeftSensor, INPUT);
  pinMode(pinRightSensor, INPUT);
  pinMode(pinWallSensor, INPUT);
  pinMode(pinMiddleSensor, INPUT);

  pinMode(pinLQ3, OUTPUT);
  pinMode(pinLQ2, OUTPUT);
  pinMode(pinLQ1, OUTPUT);
  pinMode(pinLQ0, OUTPUT);

  pinMode(pinRQ3, OUTPUT);
  pinMode(pinRQ2, OUTPUT);
  pinMode(pinRQ1, OUTPUT);
  pinMode(pinRQ0, OUTPUT);

  pinMode(pinLdir, OUTPUT);
  pinMode(pinRdir, OUTPUT);

  // initialize output pins.
  digitalWrite(pinLQ3, LOW);
  digitalWrite(pinLQ2, HIGH);
  digitalWrite(pinLQ1, HIGH);
  digitalWrite(pinLQ0, HIGH);
  digitalWrite(pinRQ3, LOW);
  digitalWrite(pinRQ2, HIGH);
  digitalWrite(pinRQ1, HIGH);
  digitalWrite(pinRQ0, HIGH);
  digitalWrite(pinLdir, FORWARD);        //FORWARD as HIGH: move forward
  digitalWrite(pinRdir, FORWARD);        //BACKWARD as LOW:  move backward

}

// the loop function runs over and over again forever
void loop() {
  leftSensor = digitalRead(pinLeftSensor);
  rightSensor = digitalRead(pinRightSensor);
  wallSensor = digitalRead(pinWallSensor);
  middleSensor = digitalRead(pinMiddleSensor);
  
  start(wallSensor, &state);
  stop_and_back(wallSensor, &state);
  adjust(leftSensor,rightSensor,middleSensor);
  split_turn(leftSensor, rightSensor,
             middleSensor , &turn_times);  
}
