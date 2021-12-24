#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    printf("Main pid: %d\n", pid);	
    printf("OS03-06\n");
    system("./OS03-05-1");
    for (int i = 0; i < 100; ++i) {
        printf("i: %d, pid: %d\n",i, pid);
        sleep(1);
    }
    return 0;
}
