#pragma once

#include <stdio.h>
#include <stdlib.h>

void read(double[100][100], int *, int *);
void add();
void subtract();
void multiply();
void transpose();
void display(double res[100][100], int r, int c);

enum choices
{
    m_addition = 1,
    m_subtraction,
    m_multiplication,
    m_transpose,
    m_exit
};

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

void read(double matrix[100][100], int *r, int *c)
{
    printf("Enter rows: ");
    scanf("%d", r);
    printf("Enter columns: ");
    scanf("%d", c);
    int i, j;
    for (i = 0; i < *r; i++)
    {
        for (j = 0; j < *c; j++)
        {
            Expression expr = {(char *)malloc(sizeof(char) * 100), (variable *)malloc(sizeof(variable) * 100), 0};

            printf("[%d][%d]: ", i + 1, j + 1);
            scanf("%f", expr.expression);
        }
    }
}

void add()
{
    int mat1[100][100], mat2[100][100], res[100][100], r1, r2, c1, c2, i, j;
    read(mat1, &r1, &c1);
    read(mat2, &r2, &c2);
    if (r1 == r2 && c1 == c2)
    {
        for (i = 0; i < r1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                res[i][j] = mat1[i][j] + mat2[i][j];
            }
        }
    }
    else
    {
        print_error("Error: Calculation cannot be performed.\n");
    }
}

void subtract()
{
    int mat1[100][100], mat2[100][100], res[100][100], r1, r2, c1, c2, i, j;
    read(mat1, &r1, &c1);
    read(mat2, &r2, &c2);
    if (r1 == r2 && c1 == c2)
    {
        for (i = 0; i < r1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                res[i][j] = mat1[i][j] - mat2[i][j];
            }
        }
    }
    else
    {
        print_error("Error: Calculation cannot be performed.\n");
    }
}
void multiply()
{
    int mat1[100][100], mat2[100][100], res[100][100], r1, r2, c1, c2, i, j, k;
    read(mat1, &r1, &c1);
    read(mat2, &r2, &c2);

    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
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
}

void transpose()
{
    double mat[100][100], res[100][100];
    int i, j, r, c;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            res[i][j] = mat[j][i];
        }
    }
}

void display(double res[100][100], int r, int c)
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
