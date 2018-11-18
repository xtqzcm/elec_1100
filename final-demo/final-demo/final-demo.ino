/*
 * ELEC1100 project 
 * GROUP 38
 */
#define pinLeftSensor A5      //pin A5
#define pinRightSensor A3     //pin A3
#define pinFrontSensor A0    //pin A0
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

int counter = 0;
int leftSensor = 1;
int rightSensor = 1;
int middleSensor = 1;
int frontSensor = 1;

/*
 * function lists
 * L_drive_motor(int LQ3,int LQ2,int LQ1,int LQ0,int Ldir)
 * R_drive_motor(int RQ3,int RQ2,int RQ1,int RQ0,int Rdir)
 * start_run(int frontSensor, int leftSensor,
               int rightSensor, int middleSensor, int* cnt)
 * stop_and_return(int frontSensor, int leftSensor,
               int rightSensor, int middleSensor, int* cnt)
 * adjust(int leftSensor, int rightSensor,
            int middleSensor, int* cnt)
 * split_turn(int leftSensor,int rightSensor,
                int middleSensor, int* cnt)
 */

 
void L_drive_motor(int LQ3,int LQ2,int LQ1,int LQ0,int Ldir)
{
  digitalWrite(pinLQ3, LQ3);
  digitalWrite(pinLQ2, LQ2);
  digitalWrite(pinLQ1, LQ1);
  digitalWrite(pinLQ0, LQ0);
  digitalWrite(pinLdir,Ldir);
}

void R_drive_motor(int RQ3,int RQ2,int RQ1,int RQ0,int Rdir)
{
  digitalWrite(pinLQ3, RQ3);
  digitalWrite(pinLQ2, RQ2);
  digitalWrite(pinLQ1, RQ1);
  digitalWrite(pinLQ0, RQ0);
  digitalWrite(pinLdir,Rdir);
}

void start_run(int frontSensor, int leftSensor,
               int rightSensor, int middleSensor, int* cnt)
{
  while(!frontSensor && !leftSensor && !rightSensor 
  && !middleSensor && *cnt == 0)
  {
    L_drive_motor(1,1,1,1,FORWARD);
    R_drive_motor(1,1,1,1,FORWARD);
  }
  *cnt += 1;
}

void adjust(int leftSensor, int rightSensor,
            int middleSensor, int* cnt)
{
  if(!middleSensor && *cnt <=3)  //faster
  {
    if(leftSensor && rightSensor)
    {
      L_drive_motor(1,1,1,1,FORWARD);
      R_drive_motor(1,1,1,1,FORWARD);        
    }
    else if (!leftSensor && rightSensor)//need go left
    {
      L_drive_motor(0,1,1,0,FORWARD);
      R_drive_motor(1,1,1,1,FORWARD);        
    }
    else if (leftSensor && !rightSensor)//need go right
    {
      L_drive_motor(1,1,1,1,FORWARD);
      R_drive_motor(0,1,1,0,FORWARD);        
    }
  }

  else if (!middleSensor && *cnt > 3) // slower
  {
     if(leftSensor && rightSensor)
    {
      L_drive_motor(0,1,1,0,FORWARD);
      R_drive_motor(0,1,1,0,FORWARD);        
    }
    else if (!leftSensor && rightSensor)//need go left
    {
      L_drive_motor(0,0,1,1,FORWARD);
      R_drive_motor(0,1,1,0,FORWARD);        
    }
    else if (leftSensor && !rightSensor)//need go right
    {
      L_drive_motor(0,1,1,0,FORWARD);
      R_drive_motor(0,0,1,1,FORWARD);        
    }
  }
}

void split_turn(int leftSensor,int rightSensor,
                int middleSensor, int* cnt)
{
  while(!leftSensor && !rightSensor
        && middleSensor && *cnt <= 3)
  {
    switch(*cnt)
    {
      case 1:
        L_drive_motor(0,1,0,1,FORWARD);
        R_drive_motor(1,1,1,1,FORWARD);
        break;
      case 2:
        L_drive_motor(0,1,0,1,FORWARD);
        R_drive_motor(1,1,1,1,FORWARD);
        break;      
      case 3:
        L_drive_motor(1,1,1,1,FORWARD);
        R_drive_motor(0,1,0,1,FORWARD);        
        break;        
    }
  }
  *cnt += 1;
}

void stop_and_return(int frontSensor, int leftSensor,
               int rightSensor, int middleSensor, int* cnt)
{
  while(!frontSensor && !leftSensor && !rightSensor
        && middleSensor && *cnt == 4)
  {
    L_drive_motor(0,0,0,0,BACKWARD);
    R_drive_motor(0,0,0,0,BACKWARD);
    delay(2000);//wait for two seconds
    L_drive_motor(1,1,1,1,BACKWARD);
    R_drive_motor(1,1,1,1,BACKWARD);
    delay(2000);//wait for two seconds
    while(true)
    {
       L_drive_motor(0,0,0,0,BACKWARD);
       R_drive_motor(0,0,0,0,BACKWARD);   
       digitalWrite(LED_BUILTIN, HIGH); 
    }
  }
}

void setup() {
  // put your setup code here, to run once:
    // define pins as input and output.
  pinMode(pinLeftSensor, INPUT);
  pinMode(pinRightSensor, INPUT);
  pinMode(pinFrontSensor, INPUT);
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
  digitalWrite(pinLQ2, LOW);
  digitalWrite(pinLQ1, LOW);
  digitalWrite(pinLQ0, LOW);
  digitalWrite(pinRQ3, LOW);
  digitalWrite(pinRQ2, LOW);
  digitalWrite(pinRQ1, LOW);
  digitalWrite(pinRQ0, LOW);
  digitalWrite(pinLdir, FORWARD);        //FORWARD as HIGH: move forward
  digitalWrite(pinRdir, FORWARD);        //BACKWARD as LOW:  move backward
}

void loop() {
  // put your main code here, to run repeatedly:
  leftSensor = digitalRead(pinLeftSensor);
  rightSensor = digitalRead(pinRightSensor);
  frontSensor = digitalRead(pinFrontSensor);
  middleSensor = digitalRead(pinMiddleSensor);

  start_run(frontSensor, leftSensor,
            rightSensor, middleSensor, &counter);
  adjust(leftSensor, rightSensor, middleSensor, &counter);
  split_turn(leftSensor, rightSensor, middleSensor,&counter);
  stop_and_return(frontSensor, leftSensor,
                  rightSensor, middleSensor, &counter);
  

}
