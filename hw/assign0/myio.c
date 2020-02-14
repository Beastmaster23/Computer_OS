#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "myio.h"

/*
 * Function: convertCharToInteger
 * Usage: integer = convertCharToInteger(character);
 * -------------------------------------------------
 * convertCharToInteger converts Ascii code to Integer.
 */
static int convertCharToInteger(char c)
{
    switch (c)
    {
    case 48:
        return 0;
        break;
    case 49:
        return 1;
        break;
    case 50:
        return 2;
        break;
    case 51:
        return 3;
        break;
    case 52:
        return 4;
        break;
    case 53:
        return 5;
        break;
    case 54:
        return 6;
        break;
    case 55:
        return 7;
        break;
    case 56:
        return 8;
        break;
    case 57:
        return 9;
        break;
    }
    return -1;
}

/*
 * Function: isInteger
 * Usage: check = isInteger(integerString);
 * -------------------------------------------------
 * isInteger Checks if a string is an integer. 
 */
static bool isInteger(char *str)
{
    bool check = false;
    int decimalIndex = 0, decimalCount = 0;

    while (str[decimalIndex] != '\0')
    {
        if (isdigit(str[decimalIndex]) == 0)
        {
            return false;
        }
        check = true;
        decimalIndex++;
    }
    return check;
}
/*
 * Function: getDecimalIndex
 * Usage: index = getDecimalIndex(decimalString);
 * -------------------------------------------------
 * getDecimalIndex searches for the decimal point. Returns the index of the decimal point.
 */
static int getDecimalIndex(char *str)
{
    int decimalIndex = 0, length=strlen(str);

    while (str[decimalIndex] != '\0' && str[decimalIndex] != '.')
    {
        decimalIndex++;
    }
    if (decimalIndex == 0 || decimalIndex == length)
    {
        decimalIndex = -1;
    }
    return decimalIndex;
}
/*
 * Function: isDouble
 * Usage: check = isDouble(doubleString);
 * -------------------------------------------------
 * isDouble Checks if a string is an double. 
 */
static bool isDouble(char *str)
{
    bool check = false;
    int decimalIndex = 0, decimalCount = 0;
    
    while (str[decimalIndex] != '\0')
    {
        if (str[decimalIndex] == '.')
            decimalCount++;
        if (isdigit(str[decimalIndex]) == 0 && str[decimalIndex] != '.')
        {
            if (decimalCount > 1)
                return false;
            return false;
        }
        check = true;
        decimalIndex++;
    }
    return check;
}
int ReadInteger(void)
{
    int num = 0, i = 0, length, sign = 1;

    char *line = ReadLine();

    while (isInteger(line) == false)
    {
        free(line);
        fprintf(stderr, "Please Have a valid Integer.\n");
        line = ReadLine();
    }
    length = strlen(line);
    if (line[i] == '-')
    {
        i++;
        sign = -1;
    }
    else if (line[i] == '+')
    {
        i++;
    }
    while (line[i] != '\0')
    {
        num += convertCharToInteger(line[i]) * pow(10, length - 1 - i);
        i++;
    }

    free(line);
    return num * sign;
}

double ReadDouble(void)
{
    int i = 0, length, sign = 1, numIndex = 0, extraChar = 0, decimalIndex = 0;
    double num = 0;
    bool decimal = false;
    char *line = ReadLine();
    while (isDouble(line) == false)
    {
        free(line);
        fprintf(stderr, "Please Have a valid Double.\n");
        line = ReadLine();
    }
    length = strlen(line);
    if (line[i] == '-')
    {
        i++;
        sign = -1;
        extraChar++;
    }
    else if (line[i] == '+')
    {
        i++;
        extraChar++;
    }
    decimalIndex = getDecimalIndex(line);
    if (decimalIndex == -1)
        decimalIndex = length;
    numIndex = decimalIndex - 1;

    while (line[i] != '\0')
    {
        if (line[i] == '.')
        {
            decimal = true;
            i++;
            break;
        }
        num += convertCharToInteger(line[i]) * pow(10, numIndex - i);
        i++;
    }

    while (decimal == true && line[i] != '\0')
    {
        num += convertCharToInteger(line[i]) * pow(10, -(i - decimalIndex));
        i++;
    }

    free(line);
    return num * sign;
}

char *ReadLineFile(FILE *infile){
    int bufferSize = 1;
    char *buffer = (char *)malloc(sizeof(char) * bufferSize);
    buffer[bufferSize-1]= '\0';
    char c;
    
    while ((c = fgetc(infile)) != EOF && c != '\n')
    {
        buffer[bufferSize-1] = c;
        bufferSize++;
        buffer = (char *)realloc(buffer, bufferSize);
        buffer[bufferSize-1]= '\0';
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

