#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "input_parser.h"

static int timeParser(activity_t * acc);


int initActivityStruct(activity_t * acc)
{
    acc->activityNo = 0;
    acc->isActivityFinished = -1;
}

int getActivityTimes(activity_t * acc)
{
    acc->activityEnd = activity[acc->activityNo][2];
    acc->activityStart = activity[acc->activityNo][1];

    timeParser(acc);

    return 0;
}


int getActivityName(activity_t * acc)
{
    acc->activityName = activity[acc->activityNo][0];

    if(acc->activityName == NULL)
    {
        return -1;
    }

    return 0;
}

int getActivityState(activity_t * acc)
{
    acc->activityState = activity[acc->activityNo][3];

    return 0;
}


static int timeParser(activity_t * acc)
{
    int h, m, ret;
    ret = sscanf(acc->activityStart, "%d:%d", &h, &m);

	if (ret != 2)
		return -1;

    acc->activityStart_i = h*3600 + m*60;

    ret = sscanf(acc->activityEnd, "%d:%d", &h, &m);

	if (ret != 2)
		return -1;

    acc->activityEnd_i = h*3600 + m*60;

    return 0;
}

static int inputTimeParser(char * time)
{
    int h, m, ret, returnVal ;
    ret = sscanf(time, "%d:%d", &h, &m);

    returnVal = h*3600 + m*60;

    return returnVal;
}

int commandParser(char * userInput)
{
    int returnCmd;

    // TODO::control check for typo and time
    if(strcmp(userInput, "YES") == 0)
    {
        returnCmd = COMMAND_YES;
    }
    else if(strcmp(userInput, "NO") == 0)
    {
        returnCmd = COMMAND_NO;    
    }
    else if(strcmp(userInput, "NOW") == 0)
    {
        returnCmd = COMMAND_NOW;     
    }
    else
    {
        returnCmd = COMMAND_TIME;
    }

    return returnCmd;
}

int commandHandler(char * userInput)
{
    scanf("%s", userInput);
    printf("User Input: %s \n", userInput);

    switch(commandParser(userInput))
    {
        case COMMAND_YES:
            acc->activityState = "done"; 
            activity[acc->activityNo][3] = "done";
            break;

        case COMMAND_NO:
            acc->activityState = "undone"; 
            activity[acc->activityNo][3] = "undone";
            break;

        case COMMAND_NOW:
            if(strcmp(acc->activityState,"done") == 0)
            {
                printf("Chill you already have %s \n", acc->activityName);
            }
            else
            {
                acc->activityState = "done";
                activity[acc->activityNo][3] = "done";
            }
            break;

        case COMMAND_TIME:
            if(inputTimeParser(userInput) > acc->activityStart_i && inputTimeParser(userInput) < acc->activityEnd_i)
            {
                 if(strcmp(acc->activityState,"undone") == 0)
                 {
                    printf("Are you having %s \n", acc->activityName);
                 }
                 else
                 {
                    printf("Chill you already have %s \n", acc->activityName);
                 }
            }

            break;
    }
}

int startUserLoop()
{
    char  userInput[10];

    while (1) 
    {
        commandHandler(userInput);
    }

    return 0;
}