#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
    int currentProcess, currentExecutionTime, numOfProcess, numOfProcessLeft , time_quantum;
    int flag;
    double avgWaitingTime=0, avgTurnaroundTime=0;

    printf("Enter Number of Processes !! ");
    scanf("%d",&numOfProcess);
    printf("\n");
    if(numOfProcess<=0){
        printf("Number of process should be greater than 0 ");
        return -1;
    }

    int* processArrivalTime = malloc(numOfProcess * sizeof(int));
    int* processBurstTime = malloc(numOfProcess * sizeof(int));
    int* processWaitingTime = malloc(numOfProcess * sizeof(int));
    int* processTurnaroundTime = malloc(numOfProcess * sizeof(int));
    int* processEndTime = malloc(numOfProcess * sizeof(int));
    int* remainingBurstTime = malloc(numOfProcess * sizeof(int));

    numOfProcessLeft = numOfProcess;

    // storing process arrival time and burst time
    for(int i=0;i<numOfProcess;i++){
        printf("Enter Arrival time of Process %d :",i+1);
        scanf("%d",&processArrivalTime[i]);
        if(processArrivalTime[i]<0){
            printf("Arrival time cannot be negative ");
            return -1;
        }
        printf("Enter Burst time of Process %d : ",i+1);
        scanf("%d",&processBurstTime[i]);
        remainingBurstTime[i] = processBurstTime[i];

        if(processBurstTime[i]<0){
            printf("Burst time cannot be negative ");
            return -1;
        }
        printf("\n");  
    }


    printf("\n");
    printf("Enter time quantum : ");
    scanf("%d", &time_quantum);
    printf("\n");

    //currentProcess represents the current process which is executing by cpu
    currentProcess=0;


    //Initially current execution time is assigned the arrival time of 1st process as execution starts from there itself
    currentExecutionTime=processArrivalTime[0];

    //numOfProcessLeft represents the number of process which are not executed completely
    //Thus this loop will continuously work until all process executes completely
    while(numOfProcessLeft != 0)
    {
        
        /* CurrentExecutionTime actually stores the whole timeline along which program is running
        and if a process gets terminated, we store its termination time in the ProcessEndTime
        we calculate turnaround time by subtracting arrivalTime from ProcessEndTime 
        and we calculate waiting time by subtracting burstTime from turnaround Time */
        if(remainingBurstTime[currentProcess]>time_quantum){
            printf("Process %d executes from %d to %d \n",currentProcess+1,currentExecutionTime,currentExecutionTime+time_quantum);
            remainingBurstTime[currentProcess] -= time_quantum;
            currentExecutionTime += time_quantum;   
        }
        else if(remainingBurstTime[currentProcess]>0){
            printf("Process %d executes from %d to %d \n",currentProcess+1,currentExecutionTime,currentExecutionTime+remainingBurstTime[currentProcess]);
            currentExecutionTime += remainingBurstTime[currentProcess];
            remainingBurstTime[currentProcess] = 0;
            numOfProcessLeft--;
            processEndTime[currentProcess]=currentExecutionTime;
        }

        //below code is to switch our current process
        //if current Executing Process is last process then next current executing process will be the first process
        if(currentProcess == numOfProcess - 1)
        {
                currentProcess = 0;
        }

        /*if current Executing process is not last process then check whether
        the arrival time of next process is less then current execution time or not
        to make sure whether the next process is available at this point or not
        if available then let currentProcess point that process*/
        else if(processArrivalTime[currentProcess + 1] <= currentExecutionTime)
        {
                currentProcess++;
        }

        /*if our current process is not last process and next process is also not avialble
        then let currentProcess starts from 1st process
        but if all the process before it are already completed means CPU is idle currently
        then let just increase currentExecutionTime by 1 */
        else
        {   
            //flag check whether cpu is idle or not!!
            flag=1;
            for(int i=0;i<=currentProcess;i++){
                if(remainingBurstTime[i]!=0){
                    currentProcess = 0;
                    flag=0;
                    break;
                }
            }

            //Executed only when all the earlier process have remaining burst = 0
            if(flag==1){
                printf("CPU remain idle from %d to %d \n",currentExecutionTime,currentExecutionTime+1);
                currentExecutionTime+=1;
            }
        }
    }


    printf("\nProcess\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\n");
    for(int i =0;i<numOfProcess;i++){
        processTurnaroundTime[i]=processEndTime[i]-processArrivalTime[i];
        processWaitingTime[i]=processTurnaroundTime[i]-processBurstTime[i];

        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,processArrivalTime[i],processBurstTime[i],processWaitingTime[i],processTurnaroundTime[i]);
        
        avgTurnaroundTime+=processTurnaroundTime[i];
        avgWaitingTime+=processWaitingTime[i];
    }
    

    avgWaitingTime = (double)avgWaitingTime / numOfProcess;
    avgTurnaroundTime = (double)avgTurnaroundTime  / numOfProcess;

    printf("\n\nAverage Waiting Time:\t%f", avgWaitingTime);
    printf("\nAvg Turnaround Time:\t%f\n", avgTurnaroundTime);
    return 0;
}