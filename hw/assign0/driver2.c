#include <stdlib.h>
#include <stdio.h>
#include "myio.h"
int main(int argc, char *argv[])
{
    char *inputfileName, *outputfileName, *line;
    FILE *inputfile, *outputfile;
    if (argc < 3)
    {
        fprintf(stderr, "Not enough arguments!\n");
        return -1;
    }
    inputfileName = argv[1];
    outputfileName = argv[2];

    inputfile = fopen(inputfileName, "r");

    if (inputfile == NULL)
    {
        fprintf(stderr, "Input file name doesn't exist:(\n");
        return -1;
    }
    outputfile = fopen(outputfileName, "w");
    while ((line = ReadLineFile(inputfile)) != NULL)
    {
        int i = 0, spaces = 0;
        while (line[i] != '\0')
        {
            if (line[i] == ' ')
            {
                spaces++;
                if (spaces == 1)
                {
                    fprintf(outputfile, "%c", line[i]);
                }
            }
            else
            {
                spaces = 0;
                fprintf(outputfile, "%c", line[i]);
            }
            i++;
        }
        fprintf(outputfile, "\n");
        free(line);
    }
    fclose(outputfile);
    fclose(inputfile);
}