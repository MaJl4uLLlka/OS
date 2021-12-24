#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 128
int main(){
    int n, f;
    char buff[10];
    f = open("../../OS09_05.txt", O_RDWR);
    read(f, buff, 5);
    write(1, buff, 5);
    lseek(f, 5, SEEK_CUR);
    read(f, buff, 5);
    write(1, buff, 5);
    printf("\n");
}