#ifndef _DRIVE_H_
#define _DRIVE_H_

#include"Arduino.h"

void L_drive_motor(int LQ3,int LQ2,int LQ1,int LQ0,int Ldir);

void R_drive_motor(int RQ3,int RQ2,int RQ1,int RQ0,int Rdir);

void start(int wall_S, int* state);

void stop_and_back(int wall_S, int* state);

void adjust(int left_S, int right_S, int middle_S);

void split_turn(int left_S,int right_S, 
                int middle_S, int* turn_num);

#endif
