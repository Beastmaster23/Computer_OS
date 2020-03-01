#ifndef PCB_FILE
#define PCB_FILE

#include <stdio.h>
#define NUM_OF_REGISTERS 8

typedef struct PCB_st
{
    int ProcId;
    int ProcPR;
    int CPUburst;
    int Reg[NUM_OF_REGISTERS];
    int queueEnterClock, waitingTime; /* other info */
    struct PCB_st *next;
} PCB_st;

typedef struct
{
    PCB_st *Head;
    PCB_st *Tail;
} Queue;

PCB_st *createPCB(int id, int priority, int cpuBurst);

void freePCB(PCB_st *pcb);

void addPCB(Queue *queue, PCB_st *pcb);

PCB_st *popPCB(Queue *queue);

Queue *createQueue();

void freeQueue(Queue *queue);

void printQueue(Queue *queue);

void printPCB(PCB_st *pcb);
PCB_st *findPCBMinCPU(Queue *queue);
PCB_st *popPCBMinCPU(Queue *queue);
PCB_st *popPCBMaxPr(Queue *queue);
/*
 * Function: ReadLineFile
 * Usage: line = ReadLineFile(File_pointer);
 * -------------------------------------------------
 * ReadLineFile Reads a line from a file. One character at time.
 */
char *ReadLineFile(FILE *infile);

#endif