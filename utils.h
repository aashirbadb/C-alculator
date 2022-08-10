#pragma once
#ifndef _WIN32
#include <sys/ioctl.h>
#endif
#include <stdlib.h>

// Clearscreen for different platforms
#ifdef _WIN32
#define clrscr() system("cls");
#else
#define clrscr() system("clear");
#endif

#define MAGENTA "\x1b[35m"
#define RESET "\x1b[0m"
// display text in different color
#define print_info(format_string, ...) printf("\x1b[34m" format_string RESET __VA_OPT__(, ) __VA_ARGS__)     // bule
#define print_input(format_string, ...) printf("\x1b[33m" format_string RESET __VA_OPT__(, ) __VA_ARGS__)    // yellow
#define print_error(format_string, ...) printf("\x1b[31m" format_string RESET __VA_OPT__(, ) __VA_ARGS__)    // red
#define print_options(format_string, ...) printf("\x1b[36m" format_string RESET __VA_OPT__(, ) __VA_ARGS__)  // cyan
#define print_result(format_string, ...) printf("\x1b[32m" format_string RESET __VA_OPT__(, ) __VA_ARGS__)   // green

#define getch() \
    getchar();  \
    getchar();

typedef struct variable {
    char name[100];
    double value;
} variable;

typedef struct Expression {
    char *expression;
    variable *variables;
    int var_length;
} Expression;

int is_number(char ch) {
    return (ch >= '0' && ch <= '9');
}

int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int is_letter(char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

char *remove_elements_by_index(char *str, int index, int number) {
    char *result = (char *)malloc(sizeof(char) * strlen(str));
    int res_len = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (!(i >= index && i < index + number)) {
            result[res_len] = str[i];
            res_len++;
        }
    }
    return result;
}

char *replace_in_string(char *str, char *replace, char *with) {
    char *result = (char *)malloc(sizeof(char) * (strlen(str) - strlen(replace) + strlen(with)) * 2);

    for (int i = 0; i < strlen(str); i++) {
        if (strncmp(str + i, replace, strlen(replace)) == 0) {
            str = remove_elements_by_index(str, i, strlen(replace) - 1);
            sprintf(result, "%s%s", result, with);
        } else {
            result[strlen(result)] = str[i];
        }
    }
    return result;
}

double **create_matrix(int rows, int columns) {
    double **arr = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
        arr[i] = (double *)malloc(columns * sizeof(double));

    return arr;
}

void destroy_matrix(double **matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++)
        free(matrix[i]);

    free(matrix);
}

Expression createExpression() {
    Expression expr = {(char *)malloc(sizeof(char) * 100), (variable *)malloc(sizeof(variable) * 100), 0};

    FILE *file = fopen("constants.txt", "r");
    if (file != NULL) {
        char name[100];
        double value;
        while (fscanf(file, "%s%lf", name, &value) != EOF) {
            strcpy(expr.variables[expr.var_length].name, name);
            expr.variables[expr.var_length].value = value;
            expr.var_length++;
        }
    }
    strcpy(expr.expression, "");
    return expr;
}

void freeExpression(Expression exp) {
    free(exp.expression);
    free(exp.variables);
}

void center(char *string) {  // Centers the text
#ifdef _SYS_IOCTL_H
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);  // gets no of rows and columns in terminal window
    int spaces = (w.ws_col - strlen(string)) / 2;
#else
    int spaces = 15;  // defaults to 15 if ioctl is not present
#endif
    printf(MAGENTA);
    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s\n" RESET, string);
}
