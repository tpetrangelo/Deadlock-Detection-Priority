#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(){
    srand(time(0));

    const int numResources = 3;
    const int numProcesses = 5;
    int maxProc=0;;
    int maxPrio = 0;
    int maxNeed1 = 0;
    int maxNeed2 = 0;
    int maxNeed3 = 0;
    int resourceMax[3]; 
    int processNeed[5][3];
    int processPriority[5][5]; //was [5][3]
    int sortedProcessPriority[5][5];

    //Initialize the max allocation for each resource
    for(int i = 0; i < numResources; i++){
        resourceMax[i] = (rand() % (20 - 10 + 1)) + 10; 
    }

    //Initialize the need of each process for each resource
    for(int j = 0; j < numProcesses; j++){
        for(int k = 0; k < numResources; k++){
            processNeed[j][k] = (rand() % (9 - 1 + 1)) + 1;
        }
    }

    //Initialize array wil process, priority, and need
    for(int i = 0; i < numProcesses; i++){
        processPriority[i][0] = i;
        processPriority[i][1] = (rand() % (99 - 1 + 1)) + 1;
        processPriority[i][2] = processNeed[i][0];
        processPriority[i][3] = processNeed[i][1];
        processPriority[i][4] = processNeed[i][2];
    }

    //Print Max Resource Allocation
    printf("---------------------------\n");
    printf("Resource Max Allocation\n");
    for(int i = 0; i < numResources; i++){
        printf("[%d]", resourceMax[i]);
    }
    printf("\n\nProcess Needs\n");

    //Print out process need array
    for(int j = 0; j < numProcesses; j++){
        printf("P%d ",j);
        for(int k = 0; k < numResources; k++){
            printf("[%d]",processNeed[j][k]);
        }
        printf("\n");
    }

    printf("\nProcess Priorities\n");
    //Print out process priority
    for(int i = 0; i < numProcesses; i++){
        printf("P%d ",processPriority[i][0]);
        printf("(%d)\t",processPriority[i][1]);
        printf("[%d]",processPriority[i][2]);
        printf("[%d]",processPriority[i][3]);
        printf("[%d]\n",processPriority[i][4]);
    }
    
    //sort 2D array to have priority on top
    for (int i = 0; i < numProcesses; i++)
    {

        for (int j = 0; j < numProcesses; j++)
        {
            if(processPriority[j][1] > maxPrio){
                maxProc = processPriority[j][0];
                maxPrio = processPriority[j][1];
                maxNeed1 = processPriority[j][2];
                maxNeed2 = processPriority[j][3];
                maxNeed3 = processPriority[j][4];
            }
        }
    sortedProcessPriority[i][0] = maxProc;
    sortedProcessPriority[i][1] = maxPrio;
    sortedProcessPriority[i][2] = maxNeed1;
    sortedProcessPriority[i][3] = maxNeed2;
    sortedProcessPriority[i][4] = maxNeed3;
    
    processPriority[maxProc][0]=0;
    processPriority[maxProc][1]=0;
    processPriority[maxProc][2]=0;
    processPriority[maxProc][3]=0;
    processPriority[maxProc][4]=0;

    maxProc = 0;
    maxPrio = 0;
    maxNeed1 = 0;
    maxNeed2 = 0;
    maxNeed3 = 0;


    }

    //Print Sorted Priorities
    printf("\nSorted Priorities\n");
    for(int i = 0; i < numProcesses; i++){
        printf("P%d ",sortedProcessPriority[i][0]);
        printf("(%d)\t",sortedProcessPriority[i][1]);
        printf("[%d]",sortedProcessPriority[i][2]);
        printf("[%d]",sortedProcessPriority[i][3]);
        printf("[%d]\n",sortedProcessPriority[i][4]);
    }


    //Give each process a chance to obtain resources
    for (int i = 0; i < numProcesses;i++){
        printf("----------------------------------------------\n");
        for (int j = 0; j < numResources; j++){
            printf("[Process %d needs %d allocations of resource %d]\n", sortedProcessPriority[i][0], sortedProcessPriority[i][j + 2], j + 1);
            
            //If there are enough resources for the process, allow and take away from allocation
            if(sortedProcessPriority[i][j+2] <= resourceMax[j]){
                resourceMax[j] = resourceMax[j] - sortedProcessPriority[i][j + 2];
                sortedProcessPriority[i][j + 2] = 0;
            }else{
                printf("--[Not enough resources for this request!]--\n\n");
            }
        }
        printf("----------------------------------------------\n");

        //Update tables after every process
        printf("\nNew Max Allocation\n");
        printf("[%d][%d][%d]\n\n", resourceMax[0], resourceMax[1], resourceMax[2]);
        printf("New Process Need Table\n");
        for(int i = 0; i < numProcesses; i++){
            printf("P%d ",sortedProcessPriority[i][0]);
            printf("(%d)\t",sortedProcessPriority[i][1]);
            printf("[%d]",sortedProcessPriority[i][2]);
            printf("[%d]",sortedProcessPriority[i][3]);
            printf("[%d]\n",sortedProcessPriority[i][4]);
        }
        printf("\n");
    }

    //Print final left-over resource needs
    printf("Final Left-Over Process Needs\n");
    for(int i = 0; i < numProcesses; i++){
        printf("P%d ",sortedProcessPriority[i][0]);
        printf("(%d)\t",sortedProcessPriority[i][1]);
        printf("[%d]",sortedProcessPriority[i][2]);
        printf("[%d]",sortedProcessPriority[i][3]);
        printf("[%d]\n",sortedProcessPriority[i][4]);
    }
    printf("\n");
    return 0;
}