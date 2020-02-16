#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *ReadLineFile(FILE *infile)
{
    int bufferSize = 1;
    char *buffer = (char *)malloc(sizeof(char) * bufferSize);
    buffer[bufferSize - 1] = '\0';
    char c;

    while ((c = fgetc(infile)) != EOF && c != '\n')
    {
        buffer[bufferSize - 1] = c;
        bufferSize++;
        buffer = (char *)realloc(buffer, bufferSize);
        buffer[bufferSize - 1] = '\0';
    }

    if (c == EOF)
    {

        free(buffer);
        return NULL;
    }
    return buffer;
}

char *ReadLine(void)
{
    return ReadLineFile(stdin);
}

static int count_words_in_line(char *line)
{
    int number_of_words = 0;
    char *delimeters = " \t\n\r", *word;
    word = strtok(line, delimeters);

    while (word != NULL)
    {
        number_of_words++;
        word = strtok(NULL, delimeters);
    }
    return number_of_words;
}

int count_words_in_file(char *filename)
{
    int number_of_words = 0;
    char *line;
    FILE *file = fopen(filename, "r");

    while ((line = ReadLineFile(file)))
    {
        number_of_words += count_words_in_line(line);
    }
    fclose(file);
    return number_of_words;
}

int count_words(char *str)
{
    int number_of_words = 0;
    char *rest = str, *line, *delimeters = "\n";

    while ((line = strtok_r(rest, delimeters, &rest)))
    {
        number_of_words += count_words_in_line(line);
    }

    return number_of_words;
}