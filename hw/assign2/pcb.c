#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>
PCB_st *createPCB(int id, int priority, int cpuBurst)
{
    PCB_st *pcb = malloc(sizeof(PCB_st));
    pcb->ProcId = id;
    pcb->ProcPR = priority;
    pcb->CPUburst = cpuBurst;
    pcb->queueEnterClock = 0;
    pcb->waitingTime = 0;
    int i = 0;
    pcb->next = NULL;
    for (i = 0; i < NUM_OF_REGISTERS; i++)
    {
        pcb->Reg[i] = id;
    }

    return pcb;
}

Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue *));
    queue->Head = NULL;
    queue->Tail = NULL;
    return queue;
}

void printQueue(Queue *queue)
{
    PCB_st *node = queue->Head;
    printf("%d\n", node->ProcId);
    while ((node = node->next) != NULL)
    {
        printf("%d\n", node->ProcId);
    }
}

void freeQueue(Queue *queue)
{
    PCB_st *node;
    while ((node = popPCB(queue)) != NULL)
    {
        freePCB(node);
    }

    free(queue);
}

void freePCB(PCB_st *pcb)
{
    free(pcb);
}

void addPCB(Queue *queue, PCB_st *pcb)
{
    if (queue->Head == NULL || queue->Tail == NULL)
    {
        queue->Head = pcb;
        queue->Tail = pcb;
        return;
    }

    queue->Tail->next = pcb;
    queue->Tail = pcb;
    queue->Tail->next = NULL;
}

PCB_st *popPCB(Queue *queue)
{
    if (queue->Head == NULL)
    {
        return NULL;
    }
    PCB_st *pcb = queue->Head;
    queue->Head = queue->Head->next;

    if (queue->Head == NULL || queue->Head->next == NULL)
    {
        queue->Tail = NULL;
    }

    return pcb;
}

PCB_st *findPCBMinCPU(Queue *queue)
{
    PCB_st *node = queue->Head;
    int min = node->CPUburst;
    PCB_st *minNode = node;
    while ((node = node->next) != NULL)
    {
        if (node->CPUburst >= min)
        {
            min = node->CPUburst;
            minNode = node;
        }
    }
    return minNode;
}

PCB_st *popPCBMinCPU(Queue *queue)
{
    PCB_st *node = queue->Head;
    if (node == NULL)
    {
        return NULL;
    }
    int min = node->CPUburst;
    PCB_st *minNode = node;

    PCB_st *prev_node = NULL, *save_prev;
    while (node != NULL)
    {
        if (node->CPUburst >= min)
        {
            min = node->CPUburst;
            minNode = node;
            save_prev = prev_node;
        }
        prev_node = node;
        node = node->next;
    }

    if (minNode == queue->Head)
    {
        if (queue->Head == NULL)
        {
            return NULL;
        }
        PCB_st *pcb = queue->Head;
        queue->Head = queue->Head->next;

        if (queue->Head == NULL || queue->Head->next == NULL)
        {
            queue->Tail = NULL;
        }
    }
    else if (minNode == queue->Tail)
    {

        queue->Tail = NULL;
    }
    else
    {
        save_prev->next = minNode->next;
        minNode->next = NULL;
    }

    return minNode;
}
PCB_st *popPCBMaxPr(Queue *queue)
{
    PCB_st *node = queue->Head;
    if (node == NULL)
    {
        return NULL;
    }
    int max = node->ProcPR;
    PCB_st *maxNode = node;

    PCB_st *prev_node = NULL, *save_prev;
    while (node != NULL)
    {
        if (node->ProcPR >= max)
        {
            max = node->ProcPR;
            maxNode = node;
            save_prev = prev_node;
        }
        prev_node = node;
        node = node->next;
    }

    if (maxNode == queue->Head)
    {
        if (queue->Head == NULL)
        {
            return NULL;
        }
        PCB_st *pcb = queue->Head;
        queue->Head = queue->Head->next;

        if (queue->Head == NULL || queue->Head->next == NULL)
        {
            queue->Tail = NULL;
        }
    }
    else if (maxNode == queue->Tail)
    {

        queue->Tail = NULL;
    }
    else
    {
        save_prev->next = maxNode->next;
        maxNode->next = NULL;
    }

    return maxNode;
}
char *ReadLineFile(FILE *infile)
{
    int index = 0;
    char *buffer = (char *)malloc(sizeof(char) * 1);
    buffer[index] = '\0';
    char c;

    while ((c = fgetc(infile)) != EOF && c != '\n')
    {
        buffer[index] = c;
        index++;
        buffer = (char *)realloc(buffer, index + 1);
        buffer[index + 1] = '\0';
    }
    if (buffer[0] == '\0')
    {
        free(buffer);
        return NULL;
    }
    return buffer;
}
void printPCB(PCB_st *pcb)
{
    printf("Id: %d, priority: %d, cpu: %d\n", pcb->ProcId, pcb->ProcPR, pcb->CPUburst);
    printf("Clock: %d, Wait: %d\n", pcb->queueEnterClock, pcb->waitingTime);
    int i;
    printf("Registers: \n");
    for (i = 0; i < NUM_OF_REGISTERS; i++)
    {
        printf("%d : %d\n", i, pcb->Reg[i]);
    }
    if (pcb->next != NULL)
    {
        printf("Next Id: %d\n", pcb->next->ProcId);
    }
}