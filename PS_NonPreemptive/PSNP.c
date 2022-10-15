#include <stdio.h>
#include <unistd.h>

struct Process{
    int processNumber;
    int processArrivalTime; 
    int processBurstTime;
    int processPriority;
    int processWaitingTime;
    int processTurnaroundTime;
    int processExecutionStartTime;
    int processCompleted;
};

//provide the shortest arrival time among the processes which are not completed till now
int currentShortestArrivalTime(struct Process p[], int NumOfProcess){
    int ShortestArrivalTime=__INT_MAX__;
    for(int i=0;i<NumOfProcess;i++){
        if(p[i].processCompleted==0 && p[i].processArrivalTime<ShortestArrivalTime){
            
            ShortestArrivalTime=p[i].processArrivalTime;
        }
    }
    return ShortestArrivalTime;
}

//sort the array on the basis of Priority of processes
void prioritySort(struct Process p[], int NumOfProcess){
    struct Process temp;
    for(int i=0;i<NumOfProcess;i++){
        for(int j=0;j<NumOfProcess-i-1;j++){
            if(p[j].processPriority>p[j+1].processPriority){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    return;

}


//sort the array on the basis of process Number
void processNumberSort(struct Process p[], int NumOfProcess){
    struct Process temp;
    for(int i=0;i<NumOfProcess;i++){
        for(int j=0;j<NumOfProcess-i-1;j++){
            if(p[j].processNumber>p[j+1].processNumber){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    return;

}


int main(){
    int numOfProcess,numOfProcessLeft,currentExecutionTime;
    float avgTurnaroundTime=0,avgWaitingTime=0;

    printf("Enter Number of Process : ");
    scanf("%d",&numOfProcess);
    printf("\n");
    numOfProcessLeft=numOfProcess;
    if(numOfProcess<=0){
        printf("Number of process should be greater than 0 ");
        return -1;
    }

    //creating an array of object of structure 
    struct Process processArray[numOfProcess];

    for(int i=0;i<numOfProcess;i++){
        printf("Enter Arrival time of Process %d :",i+1);
        scanf("%d",&processArray[i].processArrivalTime);

        printf("Enter Burst time of Process %d : ",i+1);
        scanf("%d",&processArray[i].processBurstTime);
        
        printf("Enter Priority of Process %d : ",i+1);
        scanf("%d",&processArray[i].processPriority);

        processArray[i].processNumber=i+1;
        processArray[i].processCompleted=0;

        if(&processArray[i].processArrivalTime<0){
            printf("Arrival time cannot be negative ");
            return -1;
        }
        if(&processArray[i].processBurstTime<0){
            printf("Burst time cannot be negative ");
            return -1;
        }
        if(&processArray[i].processPriority<0){
            printf("Priority cannot be negative ");
            return -1;
        }
        printf("\n");  
    }

    //starting the program from shotest arrival Time
    currentExecutionTime=currentShortestArrivalTime(processArray,numOfProcess);

    //sorting the array on the basis of priority of process
    prioritySort(processArray,numOfProcess);
    
    int csat;
    while(numOfProcessLeft!=0){

        csat=currentShortestArrivalTime(processArray,numOfProcess);
        //checking whether the current execution time is smaller than shortest arrival time  which happen when cpu is idle
        if(currentExecutionTime<csat){
            printf("CPU remain idle from %d to %d \n ",currentExecutionTime,csat);
            currentExecutionTime=csat;
        }
        for(int i=0;i<numOfProcess;i++){
            if(processArray[i].processCompleted==0 && processArray[i].processArrivalTime<=currentExecutionTime){
                processArray[i].processExecutionStartTime=currentExecutionTime;
                printf("Process %d executes from %d to %d\n",processArray[i].processNumber,processArray[i].processExecutionStartTime,processArray[i].processExecutionStartTime+processArray[i].processBurstTime);
                currentExecutionTime+=processArray[i].processBurstTime;
                processArray[i].processCompleted=1;
                numOfProcessLeft--;
                break;
            }
        }

    }
    
    processNumberSort(processArray,numOfProcess);

    printf("\nProcess\tArrivalTime\tBurstTime\tPriority\tWaitingTime\tTurnAroundTime\n");
    for(int i =0;i<numOfProcess;i++){
        processArray[i].processWaitingTime=processArray[i].processExecutionStartTime-processArray[i].processArrivalTime;
        processArray[i].processTurnaroundTime=processArray[i].processWaitingTime+processArray[i].processBurstTime;

        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",processArray[i].processNumber,processArray[i].processArrivalTime,processArray[i].processBurstTime,processArray[i].processPriority,processArray[i].processWaitingTime,processArray[i].processTurnaroundTime);
        
        avgTurnaroundTime+=processArray[i].processTurnaroundTime;
        avgWaitingTime+=processArray[i].processWaitingTime;
    }

        

    avgWaitingTime = (double)avgWaitingTime / numOfProcess;
    avgTurnaroundTime = (double)avgTurnaroundTime  / numOfProcess;

    printf("\n\nAverage Waiting Time:\t%f", avgWaitingTime);
    printf("\nAvg Turnaround Time:\t%f\n", avgTurnaroundTime);

    return 0;
}