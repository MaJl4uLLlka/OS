#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    for(int i=0; i < 1e7; i++)
    {
        printf("i: %d, pid : %d\n",i,pid);
    }
    return 0;
}
