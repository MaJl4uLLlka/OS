#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

int main() {
    time_t t = 0;
    t = time(&t);
    struct tm *tmptr;
    tmptr = localtime(&t);

    //  dd.mm.yyyy hh:min:sec
    char day[3];
    char month[3];
    char year[5];
    char hours[3];
    char minutes[3];
    char seconds[3];

    if(tmptr->tm_mday < 10)
    {
        sprintf(day, "0%d", tmptr->tm_mday);
    }
    else
    {
        sprintf(day,"%d", tmptr->tm_mday);
    }

    if(tmptr->tm_mon+1 < 10)
    {
        sprintf(month, "0%d", tmptr->tm_mon+1);
    }
    else
    {
        sprintf(month, "%d", tmptr->tm_mon+1);
    }

    sprintf(year, "%d", 1900 + tmptr->tm_year);

    if(tmptr->tm_hour < 10)
    {
        sprintf(hours, "0%d", tmptr->tm_hour);
    }
    else
    {
        sprintf(hours, "%d", tmptr->tm_hour);
    }

    if(tmptr->tm_min < 10)
    {
        sprintf(minutes, "0%d", tmptr->tm_min);
    }
    else
    {
        sprintf(minutes, "%d", tmptr->tm_min);
    }

    if(tmptr->tm_sec < 10)
    {
        sprintf(seconds, "0%d", tmptr->tm_sec);
    }
    else
    {
        sprintf(seconds, "%d", tmptr->tm_sec);
    }

    printf("%s.%s.%s %s:%s:%s\n", day, month, year, hours,minutes,seconds);
    return 0;
}