#ifndef INPUT_PARSER_H_
#define INPUT_PARSER_H_

// default activity
static char* activity[8][4] = {
                        {"Bath", "8:30", "9:00", "undone"},
                        {"Breakfast", "9:10", "9:40", "undone"},
                        {"Lunch", "12:00", "12:30", "undone"},
                        {"Nap", "12:40", "13:40", "undone"},
                        {"Reading Book", "14:00", "14:30", "undone"},
                        {"Listening Music", "15:00", "15:30", "undone"},
                        {"Dinner", "18:00", "18:30", "undone"},
                        {"Wathcing TV", "19:00", "21:00", "undone"},
                       };

struct activity_s
{
   char * activityName;
   char * activityStart;
   char * activityEnd; 
   char * activityState;
   int activityStart_i;
   int activityEnd_i; 
   int activityNo;
   int isActivityFinished;
};

typedef struct activity_s activity_t;

typedef enum {
    COMMAND_YES,
    COMMAND_NO,
    COMMAND_NOW,
    COMMAND_TIME,

    COMMAND_MAX
} command_type_t;

int getActivityTimes(activity_t * acc);
int getActivityName(activity_t * acc);
int getActivityState(activity_t * acc);
int initActivityStruct(activity_t * acc);
int startUserLoop();

struct activity_s *acc;

#endif
