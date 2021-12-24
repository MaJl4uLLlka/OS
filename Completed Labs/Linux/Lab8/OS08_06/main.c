#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define SECOND_IN_NANOSECONDS 1000000000

int main() {
    int count = 0;
    struct timespec start, end, proc;
    clock_gettime(CLOCK_REALTIME, &start);
    for(;;)
    {
        count++;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);
        if(proc.tv_sec == 2) break;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    printf("2 sec: %d\n",count);
    long long time = (end.tv_sec * SECOND_IN_NANOSECONDS + end.tv_nsec ) - (start.tv_sec * SECOND_IN_NANOSECONDS + start.tv_nsec);
    long long nanoseconds = time % SECOND_IN_NANOSECONDS;
    long long seconds = (time - nanoseconds) / SECOND_IN_NANOSECONDS;
    printf("end: %ld sec %ld nanosec\n", end.tv_sec, end.tv_nsec);
    printf("start: %ld sec %ld nanosec\n", start.tv_sec, start.tv_nsec);
    printf("time: %lld sec %lld nanosec\n", seconds, nanoseconds);
    return 0;
}
