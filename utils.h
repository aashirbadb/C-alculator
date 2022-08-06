#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Clearscreen for different platforms
#ifdef _WIN32
#define clrscr() ({if (clscr == 1) system("cls"); })
#else
#include <stdio.h>
#define clrscr() ({if (clscr == 1) printf("\e[1;1H\e[2J"); })
#endif

#define TRUE 1
#define FALSE 0

typedef char array[100];

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

    printf("fmt :%s", formatted);

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
    char *result = (char *)malloc(sizeof(char) * (strlen(str) - strlen(replace) + strlen(with)) * 2);

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

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

#define COLOR_INFO "\x1b[36m"
#define COLOR_ERROR "\x1b[31m"
#define COLOR_SUCCESS "\x1b[32m"
#define COLOR_INPUT "\x1b[33m"
// display text in different color
#define colorPrintf(color, format_string, ...) printf(color format_string "\x1b[0m"__VA_OPT__(, )__VA_ARGS__)
#define print_error(format, ...) colorPrintf(COLOR_ERROR, format COLOR_RESET __VA_OPT__(, ) __VA_ARGS__)
#define print_input(format, ...) colorPrintf(COLOR_INPUT, format COLOR_RESET __VA_OPT__(, ) __VA_ARGS__)
#define print_success(format, ...) colorPrintf(COLOR_SUCCESS, format COLOR_RESET __VA_OPT__(, ) __VA_ARGS__)