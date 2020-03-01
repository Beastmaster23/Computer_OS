#ifndef PROG_FILE
#define PROG_FILE
#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CPUreg[NUM_OF_REGISTERS] = {0};

PCB_st *Head = NULL;
PCB_st *Tail = NULL;

int CLOCK = 0;
int Total_waiting_time = 0;
int Total_turnaround_time = 0;
int Total_job = 0;
Queue *mainQ;
void printPerformance();
void copyRegisters(int *reg1, int *reg2, int len);

int FIFO_Scheduling()
{
    PCB_st *pcb;

    while ((pcb = popPCB(mainQ)) != NULL)
    {
        copyRegisters(pcb->Reg, CPUreg, NUM_OF_REGISTERS);
        int i;
        for (i = 0; i < NUM_OF_REGISTERS; i++)
        {
            CPUreg[i] += 1;
        }
        copyRegisters(CPUreg, pcb->Reg, NUM_OF_REGISTERS);

        pcb->waitingTime = pcb->waitingTime + CLOCK - pcb->queueEnterClock;
        Total_waiting_time = Total_waiting_time + pcb->waitingTime;
        CLOCK = CLOCK + pcb->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        printf("Proces %d is completed at %d ms\n", pcb->ProcId, CLOCK);
        freePCB(pcb);
    }
    printf("\n");
    printPerformance();
    return 0;
}

int SJF_Scheduling()
{
    PCB_st *pcb;

    while ((pcb = popPCBMinCPU(mainQ)) != NULL)
    {
        copyRegisters(pcb->Reg, CPUreg, NUM_OF_REGISTERS);
        int i;
        for (i = 0; i < NUM_OF_REGISTERS; i++)
        {
            CPUreg[i] += 1;
        }
        copyRegisters(CPUreg, pcb->Reg, NUM_OF_REGISTERS);

        pcb->waitingTime = pcb->waitingTime + CLOCK - pcb->queueEnterClock;
        Total_waiting_time = Total_waiting_time + pcb->waitingTime;
        CLOCK = CLOCK + pcb->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        printf("Proces %d is completed at %d ms\n", pcb->ProcId, CLOCK);
        freePCB(pcb);
    }
    printf("\n");
    printPerformance();
    return 0;
}

int PR_Scheduling()
{
    PCB_st *pcb;

    while ((pcb = popPCBMaxPr(mainQ)) != NULL)
    {
        copyRegisters(CPUreg, pcb->Reg, NUM_OF_REGISTERS);
        int i;
        for (i = 0; i < NUM_OF_REGISTERS; i++)
        {
            CPUreg[i] += 1;
        }
        copyRegisters(pcb->Reg, CPUreg, NUM_OF_REGISTERS);

        pcb->waitingTime = pcb->waitingTime + CLOCK - pcb->queueEnterClock;
        Total_waiting_time = Total_waiting_time + pcb->waitingTime;
        CLOCK = CLOCK + pcb->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        printf("Proces %d is completed at %d ms\n", pcb->ProcId, CLOCK);
        freePCB(pcb);
    }
    printf("\n");
    printPerformance();
    return 0;
}

int RR_Scheduling(int quantum)
{
    PCB_st *pcb;

    while ((pcb = popPCB(mainQ)) != NULL)
    {
        copyRegisters(pcb->Reg, CPUreg, NUM_OF_REGISTERS);
        
        int i;
        for (i = 0; i < NUM_OF_REGISTERS; i++)
        {
            CPUreg[i] += 1;
        }
        copyRegisters(CPUreg, pcb->Reg, NUM_OF_REGISTERS);
        
        if (pcb->CPUburst <= quantum)
        {
            pcb->waitingTime = pcb->waitingTime + CLOCK - pcb->queueEnterClock;
            Total_waiting_time = Total_waiting_time + pcb->waitingTime;
            CLOCK = CLOCK + pcb->CPUburst;
            Total_turnaround_time = Total_turnaround_time + CLOCK;
            Total_job = Total_job + 1;
            printf("Proces %d is completed at %d ms\n", pcb->ProcId, CLOCK);
            freePCB(pcb);
        }
        else
        {
            pcb->waitingTime = pcb->waitingTime + CLOCK - pcb->queueEnterClock;
            CLOCK = CLOCK + quantum;
            pcb->CPUburst = pcb->CPUburst-quantum;
            pcb->queueEnterClock=CLOCK;
            addPCB(mainQ, pcb);
        }
    }
    printf("\n");
    printPerformance();
    return 0;
}

void copyRegisters(int *source, int *dest, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        dest[i] = source[i];
    }
}

void printPerformance()
{
    double awt = (double)Total_waiting_time / Total_job;
    double att = (double)Total_turnaround_time / Total_job;
    double thru = (double)Total_job / CLOCK;

    printf("Average Waiting time =  %.2f ms     (%d/%d)\n", awt, Total_waiting_time, Total_job);
    printf("Average Turnaround time =  %.2f ms     (%d/%d)\n", att, Total_turnaround_time, Total_job);
    printf("Throughput =  %.2f jobs per ms     (%d/%d)\n", thru, Total_job, CLOCK);
}

void loadQueue(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    char *line;
    mainQ = createQueue();

    while ((line = ReadLineFile(file)) != NULL)
    {
        int id = atoi(strtok(line, " "));
        int priority = atoi(strtok(NULL, " "));
        int cpuBurst = atoi(strtok(NULL, " "));
        PCB_st *pcb = createPCB(id, priority, cpuBurst);
        addPCB(mainQ, pcb);
        free(line);
    }
    fclose(file);
}

#endif