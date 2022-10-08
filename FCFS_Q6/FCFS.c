#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Process should be provided in ascending order of arrival time!!

int main(){
    int numOfProcesses;
    printf("Enter Number of Processes !! ");
    scanf("%d",&numOfProcesses);
    printf("\n");
    if(numOfProcesses<=0){
        printf("Number of process should be greater than 0 ");
        return -1;
    }

    int* processArrivalTime = malloc(numOfProcesses * sizeof(int));
    int* processBurstTime = malloc(numOfProcesses * sizeof(int));
    int* processWaitingTime = malloc(numOfProcesses * sizeof(int));
    int* processTurnAroundTime = malloc(numOfProcesses * sizeof(int));

    //this array will store the time at which process starts its execution
    int* processExecutionStartTime = malloc(numOfProcesses * sizeof(int));

    double avgWaitingTime=0;
    double avgTurnaroundTime=0;

    // storing process arrival time and burst time
    for(int i=0;i<numOfProcesses;i++){
        printf("Enter Arrival time of Process %d : ",i+1);
        scanf("%d",&processArrivalTime[i]);
        if(processArrivalTime[i]<0){
            printf("Arrival time cannot be negative ");
            return -1;
        }
        printf("Enter Burst time of Process %d : ",i+1);
        scanf("%d",&processBurstTime[i]);
        if(processBurstTime[i]<0){
            printf("Burst time cannot be negative ");
            return -1;
        }
        printf("\n");
    }
    printf("\n");

    // FCFS is non-preemptive sheduling. Thus when a process starts its execution, 
    // it should be executed completely and after that another process can start executing.
    // Thus waiting time = (time at which process starts its execution) - (arrival time of that process)
    
    //hence we are calculation the process execution start time of each process!!
    processExecutionStartTime[0]=processArrivalTime[0];
    //first process executes at its arrival time
    printf("Process 1 executes from %d to %d \n",processExecutionStartTime[0],processBurstTime[0]);


    for(int i=1;i<numOfProcesses;i++){
        //adding burst time of all the process till that process!!
        processExecutionStartTime[i]=processExecutionStartTime[i-1]+processBurstTime[i-1];
        
        //this will executes if cpu is idle!!
        if (processExecutionStartTime[i] < processArrivalTime[i]) {
            printf("CPU remain idle from %d to %d \n",processExecutionStartTime[i],processArrivalTime[i]);
            processExecutionStartTime[i] = processArrivalTime[i];
        }
        printf("Process %d executes from %d to %d \n",i+1,processExecutionStartTime[i],processExecutionStartTime[i]+processBurstTime[i]);
    }

    printf("\n Process\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\n");
    for(int i=0;i<numOfProcesses;i++){

        processWaitingTime[i]=processExecutionStartTime[i]-processArrivalTime[i];
        processTurnAroundTime[i]=processWaitingTime[i]+processBurstTime[i];

        avgWaitingTime+=processWaitingTime[i];
        avgTurnaroundTime+=processTurnAroundTime[i];

        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,processArrivalTime[i],processBurstTime[i],processWaitingTime[i],processTurnAroundTime[i]);
    }

    avgWaitingTime=(double)avgWaitingTime/numOfProcesses;
    avgTurnaroundTime=(double)avgTurnaroundTime/numOfProcesses;

    printf("\n");
    printf("Average Waiting Time : %f \n",avgWaitingTime);
    printf("Average Turnaround Time : %f \n",avgTurnaroundTime);

    return 0;
}