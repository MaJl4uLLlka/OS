//
// Created by greenboy on 21.10.21.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = getpid();
    for (int i = 0; i < 50; ++i) {
        printf("i: %d, pid: %d\n", i, pid);
        sleep(1);
    }
    return 0;
}