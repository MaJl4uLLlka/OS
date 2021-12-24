#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#define KB 1024
#define MB 1024 * KB

int main() {
    pid_t pid = getpid();
    printf("PID:  %d\n",pid);

    void* memory = malloc(256 * MB);
    printf("memory (256 MB) = %p\n", memory);

    int size = 256 * MB / sizeof(int);
    int *array = memory;

    for (int i = 0; i < size; ++i) {
        *(array + i) = i;
    }

    sleep(60 * 3);
    free(memory);

    return 0;
}
