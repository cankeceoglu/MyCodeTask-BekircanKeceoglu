#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "timer.h"
#include "common.h"

#define ONE_SECOND 1000000

static int isActivityStarted(activity_t * acc);
static int isActivityEnded(activity_t * acc);

int initTimer(int hour, int min, int sec)
{
    globalTime = sec + min * 60 + hour * 60*60;
    activityStartTime = 0;
    activityEndTime = 0;
}

int runTimer(int timeFactor)
{
    startTick(timeFactor);
}

int startTick(int timeFactor)
{
    usleep(ONE_SECOND/timeFactor);
    globalTime++;
}

void printTime()
{
    int s, h, m;

    h = (globalTime/3600); 
	
	m = (globalTime -(3600*h))/60;
	
	s = (globalTime -(3600*h)-(m*60));

#ifdef DEBUG_VERBOSITY    
    printf("Time:%d:%d:%d \n", h, m, s);
#endif
}

int activityControl(activity_t * acc)
{
    int retVal;

    retVal = isActivityStarted(acc);
    retVal = isActivityEnded(acc);
    acc->isActivityFinished = retVal;

    if(retVal == 0)
    {   
       if(acc->activityNo < MAX_NUM_OF_ACTIVITY-1) 
       acc->activityNo = acc->activityNo + 1;     
    }

    return retVal;
}

static int isActivityStarted(activity_t * acc)
{
    if(acc->activityStart_i != globalTime)
    {
        return -1;
    }

    printf("Activity started: %s Start: %s End: %s \n", acc->activityName, acc->activityStart, acc->activityEnd);
    return 0;
}

static int isActivityEnded(activity_t * acc)
{
    if(acc->activityEnd_i-600 == globalTime)
    {
        if(strcmp(acc->activityState, "undone")==0)
            printf("10 minutes to activity end: %s \n", acc->activityName);

        return -1;
    }
    else if(acc->activityEnd_i != globalTime)
    {
        return -1;
    }

    printf("Activity ended: %s - Activity state: %s \n", acc->activityName, acc->activityState);
    return 0;
}
 
int startTimerLoop()
{
    initTimer(8, 29, 0);
    acc = malloc(sizeof (struct activity_s));
    while (1) 
    {
        runTimer(SPEED_FACTOR);
        printTime();

        if(getActivityName(acc) == SUCCESFULL)
        {
            getActivityTimes(acc);
            getActivityState(acc);
            activityControl(acc);           
        }
        else
        {
            printf("All activities are finished today!!");
        }
    }

    return 0;
}
