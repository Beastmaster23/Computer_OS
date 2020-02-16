#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "words.h"
int main(int argc, char *argv[])
{
    char *fileName;
    int number_of_words = 0, number_of_files = argc - 1, i;

    for (i = 0; i < number_of_files; i++)
    {
        if (fork() == 0)
        {
            char *fileName = argv[i + 1];
            number_of_words = count_words_in_file(fileName);
            printf("Child process for %s: number of words is %3d\n", fileName, number_of_words);
            exit(0);
        }
    }

    for (i = 0; i < number_of_files; i++)
    {
        wait(NULL);
    }

    printf("All %d files have been counted!\n", number_of_files);
}