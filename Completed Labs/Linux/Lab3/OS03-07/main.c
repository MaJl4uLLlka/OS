#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char* argv[]) {
    pid_t pid = getpid();
    printf("Main pid: %d\n", pid);
    execv("./OS03-05-1", argv);
    for (int i = 0; i < 100; ++i) {
        printf("i: %d, pid: %d", i, pid);
        sleep(1);
    }
    
    printf("Finish main process");
    return 0;
}
