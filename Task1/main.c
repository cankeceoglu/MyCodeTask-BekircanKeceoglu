#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "common.h"
#include "timer.h"
#include "input_parser.h"
#include "timer.h" 

void *timerThread(void *vargp)
{
    startTimerLoop();
}


void *userInputThread(void *vargp)
{
    startUserLoop();
}


int main()
{
    pthread_t thread_id1, thread_id2;
    pthread_create(&thread_id1, NULL, timerThread, NULL);
    pthread_create(&thread_id2, NULL, userInputThread, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}
