//print sum of all the natural number upto N using thread
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int sum = 0;  

void* summation(void* num)
{
    for(int i = 1; i<=atoi(num); i++)
    {
        sum+=i;
    }
}

int main(int argc, char* argv[])
{
    pthread_t tid;

    if (argc!=2){
        printf("PLease provide required number of command line arguments !! ");
        return -1;
    }
    else if (atoi(argv[1]) <= 0) {
        printf("Value of n must be greater than 0 !! ");
        return -1;
    }

    pthread_create(&tid,NULL,summation,argv[1]);
    pthread_join(tid,NULL);
    printf("Sum of all the natural Number upto %s is : %d\n",argv[1],sum);
}