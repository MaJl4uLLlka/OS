#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
    pid_t pid = getpid();
    pid_t tid = gettid();

    printf("pid: %d\n", pid);
    printf("tid: %d\n", tid);
    printf("current priority: %d\n", getpriority(PRIO_PROCESS,0));
    //nice(k)  return new_priority = old_priority + k;
    //or so getpriority(PRIO_PROCESS,0);

    cpu_set_t set;
    CPU_ZERO(&set);

    if(sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0)
    {
        bool is_set = 0;
        printf("using cpu: ");
        for (int i = 0; i < CPU_SETSIZE; i++) {
            is_set = CPU_ISSET(i, &set);
            if(is_set)
                printf("%d ", i);
        }
        printf("\n");
    }
    else printf("shed_getaffinity = ERROR");

    return 0;
}
