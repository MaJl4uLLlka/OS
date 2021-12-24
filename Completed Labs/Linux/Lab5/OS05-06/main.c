#include <stdio.h>
#include <unistd.h>
#define COUNT 10000000

int main() {
    for(int i = 0; i < COUNT; i++)
    {
        printf("pid: %d priority: %d\n", getpid(), nice(0));
        sleep(1);
    }
    return 0;
}
