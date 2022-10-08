#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int main(){
    pid_t pid=fork();
    if(pid==0){
        printf("This is the code executed by child process with pid : %d and with  parent id : %d \n",getpid(),getppid());
    }
    else if(pid>0){
        wait(NULL);
        printf("This is the code executed by parent process with pid : %d after waiting for child process  \n",getpid());
    }
    else{
        printf("fork command fail !!");
    }
}