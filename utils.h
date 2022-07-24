#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Clearscreen for different platforms
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#define TRUE 1
#define FALSE 0

typedef struct variable
{
    char *name;
    double value;
} variable;

typedef struct Expression
{
    char *expression;
    variable *variables;
    int var_length;
} Expression;

char *remove_spaces(char *);
char *remove_element_by_index(char *, int);
int isNumber(char);
int isOperator(char);

char *remove_spaces(char *string)
{
    char *formatted = (char *)malloc(strlen(string) * sizeof(char));
    memset(formatted, 0, strlen(string) * sizeof(char));
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] != ' ')
        {
            formatted[strlen(formatted)] = string[i];
        }
    }

    formatted = realloc(formatted, sizeof(char) * strlen(string));

    return formatted;
}

int is_number(char ch)
{
    if (ch >= '0' && ch <= '9')
        return TRUE;
    else
        return FALSE;
}

int is_operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return TRUE;
    else
        return FALSE;
}

char *remove_element_by_index(char *formula, int index)
{
    int i, idex = 0, len = strlen(formula);
    char *result = (char *)malloc(sizeof(char) * len);
    memset(result, 0, len);
    for (i = 0; i < len; i++)
    {
        if (i != index)
        {
            result[idex] = formula[i];
            idex++;
        }
    }
    return result;
}