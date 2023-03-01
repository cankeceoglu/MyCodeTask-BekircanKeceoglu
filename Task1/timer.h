#ifndef TIMER_H_
#define TIMER_H_

#include "input_parser.h"

int initTimer(int hour, int min, int sec);
int runTimer();
int startTick(int timeFactor);
void printTime();
int activityControl(activity_t * acc);
int startTimerLoop();

int globalTime;
int activityStartTime;
int activityEndTime;

#endif
