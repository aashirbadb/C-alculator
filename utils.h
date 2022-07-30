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
    char name[100];
    double value;
} variable;

typedef struct Expression
{
    char *expression;
    variable *variables;
    int var_length;
} Expression;

char *remove_spaces(char *);
char *remove_elements_by_index(char *, int, int);
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

    formatted = (char *)realloc(formatted, sizeof(char) * strlen(string));

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
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return TRUE;
    else
        return FALSE;
}

char *remove_elements_by_index(char *str, int index, int number)
{
    char *result = (char *)malloc(sizeof(char) * strlen(str));
    int res_len = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (!(i >= index && i < index + number))
        {
            result[res_len] = str[i];
            res_len++;
        }
    }

    return result;
}

char *replace_in_string(char *str, char *replace, char *with)
{
    char *result = malloc(sizeof(char) * (strlen(str) - strlen(replace) + strlen(with)) * 2);

    for (int i = 0; i < strlen(str); i++)
    {
        if (strncmp(str + i, replace, strlen(replace)) == 0)
        {
            str = remove_elements_by_index(str, i, strlen(replace) - 1);
            sprintf(result, "%s%s", result, with);
        }
        else
        {

            result[strlen(result)] = str[i];
        }
    }
    return result;
}