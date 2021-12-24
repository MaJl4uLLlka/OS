#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();
    for (int i = 0; i < 1000; ++i) {
        printf("%d - %d\n",i, pid);
        sleep(2);
    }
    return 0;
}
