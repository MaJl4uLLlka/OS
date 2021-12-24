#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <errno.h>

void cycle(int count, char const* name, pid_t pid, int val_nice, int sleep_time)
{
    int new_nice = nice(val_nice);
    for (int i = 0; i < count; i++) {
        printf("*********%d*********\n" , i);
        printf("name: %s\n", name);
        printf("priority: %d\n", getpriority(PRIO_PROCESS, 0));
        sleep(sleep_time);
    }
}

int main() {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("error create child process"); exit(-1);
        case 0:
            printf("sucess create process child\n");
            printf("child pid: %d\n", pid);
            printf("run cicle child\n");
            cycle(100000, "child" , pid, 10, 1);
            printf("child exit\n");
            exit(0);
        default:
            printf("main process\n");
            printf("main pid: %d\n", getpid());
            printf("run cycle main\n");
            cycle(100000, "main" , getpid(), 0, 2);
            wait(NULL);
    }
    return 0;
}
