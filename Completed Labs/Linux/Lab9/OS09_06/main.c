#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <locale.h>

int main(int argc, char* argv[]){
    int number;
    char c;
    int in = open("../../OS09_05.txt", O_RDONLY);
    int out;
    _Bool evenNumber = 0;
    if(argc != 2){
        printf("Second argument must be a number\n");
        exit(1);
    }
    number = atoi(argv[1]);
    printf("%d\n",number);
    if(number%2 ==0){
        evenNumber = 1;
        out = open("./OS09_05_02.txt", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
    }
    else
        out = open("./OS09_05_01.txt", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
    while(read(in, &c,1) == 1){
        if(!evenNumber){
            write(out, &c, 1);
        }
        if(c == '\n')
            evenNumber = !evenNumber;
    }
    printf("\n");
    close(in);
    close(out);
}
