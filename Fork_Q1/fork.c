#include <unistd.h>
#include <stdio.h>

int main(){
    fork();
    printf("This is the same code executed by both child process and parent process!!\n");
}