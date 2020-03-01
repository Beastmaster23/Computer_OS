#include "prog.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
bool str_matches(char *str, char *match)
{
    bool matches = false;
    int i = 0, len = strlen(match);
    if (strlen(str) != len)
    {
        return matches;
    }
    for (; i < len; i++)
    {
        if (tolower(str[i]) != tolower(match[i]))
        {
            return matches;
        }
    }
    matches = true;
    return matches;
}
typedef enum
{
    FIFO = 0,
    SJF = 1,
    PR = 2,
    RR = 3,
    NONE = -1
} Algorithm;

int main(int argc, char *argv[])
{

    bool fifo = false, sjf = false, pr = false, rr = false;
    Algorithm alg = NONE;
    int i = 0, quantum = 0;
    char *filename, *algorithoms[] = {
                        "FIFO", "SJF", "PR", "RR"};
    FILE *secrets = fopen("secrets.txt", "r");
    for (i = 0; i < argc; i++)
    {
        if (str_matches(argv[i], "-alg"))
        {
            if (i + 1 < argc)
            {

                if (str_matches(argv[i + 1], "fifo"))
                {
                    fifo = true;
                    alg = FIFO;
                }
                else if (str_matches(argv[i + 1], "sjf"))
                {
                    sjf = true;
                    alg = SJF;
                }
                if (str_matches(argv[i + 1], "pr"))
                {
                    pr = true;
                    alg = PR;
                }
                if (str_matches(argv[i + 1], "rr"))
                {
                    rr = true;
                    alg = RR;
                }
            }
            i += 1;
        }
        if (str_matches(argv[i], "-quantum") || str_matches(argv[i], "--quantum"))
        {
            if (i + 1 < argc)
            {
                quantum = atoi(argv[i + 1]);
            }
            i += 1;
        }

        if (str_matches(argv[i], "-input"))
        {
            if (i + 1 < argc)
            {
                filename = argv[i + 1];
            }
            i += 1;
        }
    }
    if (secrets == NULL)
        printf("Student Name: Nemo\n");
    else
    {
        char *prompt, *username;
        prompt=ReadLineFile(secrets);
        username=ReadLineFile(secrets);
        //Prompt : username
        printf("%s: %s\n", prompt, username);
        free(prompt);
        free(username);
        fclose(secrets);
    }
    printf("Input File Name : %s\n", filename);
    if (alg != NONE)
        printf("CPU Scheduling Alg : %s\n", algorithoms[alg]);
    else
    {
        printf("CPU Scheduling Alg : NONE\n");
    }

    loadQueue(filename);
    printf("\n");
    switch (alg)
    {
    case FIFO:
        FIFO_Scheduling();
        break;
    case PR:
        PR_Scheduling();
        break;
    case RR:
        RR_Scheduling(quantum);
        break;
    case SJF:
        SJF_Scheduling();
        break;
    }
}
