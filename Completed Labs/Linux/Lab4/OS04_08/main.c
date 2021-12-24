#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* OS04_07_T1(void* arg)
{
    pid_t pid = getpid();
    for (int i = 0; i < 75; ++i) {
        if( i == 50)
        {
            sleep(10);
        }
        printf("child %d - %d\n",i, pid);
        sleep(1);
    }
    pthread_exit("Child thread");
}

int main() {
    pthread_t a_thread;
    void* thread_result;
    pid_t pid = getpid();
    int res = pthread_create(&a_thread, NULL,OS04_07_T1, NULL);

    for (int i = 0; i < 100; ++i) {
        if( i == 30)
        {
            sleep(15);
        }
        printf("%d - %d\n",i, pid);
        sleep(1);
    }

    int status = pthread_join(a_thread, (void**)&thread_result);
    exit(0);
}
