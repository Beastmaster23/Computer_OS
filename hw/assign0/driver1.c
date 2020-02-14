#include <stdlib.h>
#include <stdio.h>
#include "myio.h"
#include <string.h>
int main(int argc, char*argv[])
{
    int numberOfIntergers, numberOfDoubles, numberOfStrings, i;
    int maxInt = 0;
    double maxDouble = 0;
    char *longestString = malloc(sizeof(char) * 1);
    longestString[0] = '\0';
    int n = 0;
    if (argc < 3 + 1)
    {
        return -1;
    }
    numberOfIntergers = atoi(argv[1]);
    numberOfDoubles = atoi(argv[2]);
    numberOfStrings = atoi(argv[3]);

    for (i = 0; i < numberOfIntergers; i++)
    {
        int temp = ReadInteger();
        if (temp > maxInt)
        {
            maxInt = temp;
        }
    }
    for (i = 0; i < numberOfDoubles; i++)
    {
        double temp = ReadDouble();
        if (temp > maxDouble)
        {
            maxDouble = temp;
        }
    }
    for (i = 0; i < numberOfStrings; i++)
    {
        char *temp = ReadLine();

        if (strlen(temp) > strlen(longestString))
        {
            free(longestString);
            longestString = temp;
        }
    }
    printf("Biggest integer=%d Biggest double=%f Longest string=%s\n", maxInt, maxDouble, longestString);

    free(longestString);
}