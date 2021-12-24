#include <stdio.h>
#include <unistd.h>

int main() {
    printf("OS03-04\n");
    pid_t pid = getpid();
    for (int i = 0; i < 1000; ++i) {
        printf("i: %d, pid: %d\n",i,pid);
        sleep(1);
    }
    return 0;
}
