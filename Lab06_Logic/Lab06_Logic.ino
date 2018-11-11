/*
  ELEC1100 Lab06

  To program the car turning left at split

*/

// assign meaningful names to those pins that will be used
#define pinLeftSensor A5      //pin A5
#define pinRightSensor A3     //pin A3
#define pinMiddleSensor A0    //pin A0

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

//define variables to be used in script
int leftSensor = 1;
int rightSensor = 1;
int middleSensor = 1;

//the times of the turn
int turn_times = 1;                  
               

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

//adjust the position of the car
void adjust(int left_S, int right_S)
{
  //go too right, turn left
  if (!left_S && right_S)
  {
    L_drive_motor(0,1,0,0,FORWARD);
    R_drive_motor(1,1,1,1,FORWARD);    
  }

  //go too left, turn right
  else if (left_S && right_S)
  {
    L_drive_motor(1,1,1,1,FORWARD);
    R_drive_motor(0,1,0,0,FORWARD);
  }  
}

// decide and turn on the splits
void split_turn(int left_S,int right_S, int* turn_num)
{
  while(left_S && right_S)
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
}

// the setup function runs once when you press reset or power the board
void setup() {
  // define pins as input and output.
  pinMode(pinLeftSensor, INPUT);
  pinMode(pinRightSensor, INPUT);

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
  
  adjust(leftSensor,rightSensor);
  split_turn(leftSensor, rightSensor, &turn_times);  
}
