//print sum of 'n' user entered Numbers using threads 
//Each thread add one number
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int sum=0;


void* summation(void * num){
    sum+=*(int * )num;
}

int main(int argc,char* argv[])
{
    if (argc!=2){
        printf("PLease provide required number of command line arguments !! ");
        return -1;
    }
    else if (atoi(argv[1]) <= 0) {
        printf("Value of n must be greater than 0 !! ");
        return -1;
    }

    //creating an array of type pthread_t
    pthread_t* t=malloc(atoi(argv[1])*sizeof(pthread_t));
    int* number=malloc(atoi(argv[1])*sizeof(int));

    //storing all user entered number in the array number
    printf("Enter number : ");
    for(int i=0;i<atoi(argv[1]);i++){
        scanf("%d",&number[i]);
    }

    //creating n threads so that each add one integer in the sum
    for(int i=0;i<atoi(argv[1]);i++){
        if(pthread_create(&t[i],NULL,summation,&number[i])!=0){
            printf("Error in thread creation !! /n");
            return -1;       
        }
    }

    for(int i=0;i<atoi(argv[1]);i++){
        pthread_join(t[i],NULL);
    }

    printf("Summation of all the number is : %d\n",sum);

    return 0;
}