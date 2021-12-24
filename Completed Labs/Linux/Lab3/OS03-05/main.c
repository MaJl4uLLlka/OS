#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void useless_load(int count, char const* name, pid_t pid){
    for(int i = 0; i < count; i++){
        printf("i: %d, name: %s, pid: %d\n", i, name, pid);
        sleep(1);
    }
}

int main() {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("error create child process\n"); exit(-1);
        case 0:
            printf("success create process child \n");
            printf("identifier of child process: %d\n\n", pid);
            printf("run cycle child\n");
            useless_load(50, "child", pid);
            printf("child exit\n");
            exit(0);
        default:
            printf("main process\n");
            printf("identifier of main process: %d\n\n", getpid()) ;
            printf("run cycle main\n");
            useless_load(100, "main",getpid());
            wait(NULL);
    }
    return 0;
}