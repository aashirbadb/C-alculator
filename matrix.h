#pragma once

#include "expression.h"
#include <stdio.h>
#include <stdlib.h>

void read_matrix(double **, int, int);
void add();
void subtract();
void multiply();
void transpose();
void display(double **, int, int);

enum choices
{
    m_addition = 1,
    m_subtraction,
    m_multiplication,
    m_transpose,
    m_exit
};

void rows_columns(int *rows, int *columns)
{
    printf("Rows: ");
    scanf("%d", rows);
    printf("Columns: ");
    scanf("%d", columns);
}

double **create_matrix(int rows, int columns)
{
    double **arr = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
        arr[i] = (double *)malloc(columns * sizeof(double));

    return arr;
}

void destroy_matrix(double **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

void main_matrix()
{

    int choice;
    printf("Choose Matrix Operation\n");
    printf("----------------------------\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Transpose\n");
    printf("5. Exit\n");
    printf("----------------------------\n");
    printf("Note: You can enter expressions like 2*(1+2) and a+b\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case m_addition:
        add();
        break;
    case m_subtraction:
        subtract();
        break;
    case m_multiplication:
        multiply();
        break;
    case m_transpose:
        transpose();
        break;
    case m_exit:
        printf("Thank You.\n");
        break;
    default:
        printf("Invalid input.\n");
        printf("Please enter the correct input.\n");
        break;
    }
}

void read_matrix(double **matrix, int r, int c)
{
    int i, j;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            Expression expr = {(char *)malloc(sizeof(char) * 100), (variable *)malloc(sizeof(variable) * 100), 0};
            printf("[%d][%d]: ", i + 1, j + 1);
            scanf("%s", expr.expression);
            matrix[i][j] = evaluate_expression(expr);
        }
    }
}

void add()
{
    int r, c, i, j;
    rows_columns(&r, &c);
    double **mat1 = create_matrix(r, c);
    double **mat2 = create_matrix(r, c);
    double **res = create_matrix(r, c);

    read_matrix(mat1, r, c);
    read_matrix(mat2, r, c);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            res[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    display(res, r, c);

    destroy_matrix(mat1, r, c);
    destroy_matrix(mat2, r, c);
    destroy_matrix(res, r, c);
}

void subtract()
{
    int r, c, i, j;
    rows_columns(&r, &c);

    double **mat1 = create_matrix(r, c);
    double **mat2 = create_matrix(r, c);
    double **res = create_matrix(r, c);

    read_matrix(mat1, r, c);
    read_matrix(mat2, r, c);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            res[i][j] = mat1[i][j] - mat2[i][j];
        }
    }

    display(res, r, c);

    destroy_matrix(mat1, r, c);
    destroy_matrix(mat2, r, c);
    destroy_matrix(res, r, c);
}

void multiply()
{
    int r1, r2, c1, c2, i, j, k;
    rows_columns(&r1, &c1);

    double **mat1 = create_matrix(r1, c1);
    read_matrix(mat1, r1, c1);

    rows_columns(&r2, &c2);

    double **mat2 = create_matrix(r2, c2);
    read_matrix(mat2, r2, c2);

    double **res = create_matrix(r1, c2);

    for (i = 0; i < c1; i++)
    {
        for (j = 0; j < r2; j++)
        {
            res[i][j] = 0;
        }
    }

    if (c1 == r2)
    {
        for (i = 0; i < r1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                for (k = 0; k < c1; k++)
                {
                    res[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        display(res, r1, c2);
    }
    else
    {
        print_error("Error: The matrices cannot be multiplied\n");
    }

    destroy_matrix(mat1, r1, c1);
    destroy_matrix(mat2, r2, c2);
    destroy_matrix(res, r1, c2);
}

void transpose()
{
    int i, j, r, c;

    rows_columns(&r, &c);

    double **mat = create_matrix(r, c);
    double **res = create_matrix(c, r);

    read_matrix(mat, r, c);
    for (i = 0; i < c; i++)
    {
        for (j = 0; j < r; j++)
        {
            res[i][j] = mat[j][i];
        }
    }
    display(res, c, r);
    destroy_matrix(mat, r, c);
    destroy_matrix(res, c, r);
}

void display(double **res, int r, int c)
{
    int i, j;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%g\t", res[i][j]);
        }
        printf("\n");
    }
}
