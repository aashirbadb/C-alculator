#pragma once

#include "expression.h"
#include <stdlib.h>

void rows_columns(int *rows, int *columns)
{
    print_input("Rows: ");
    scanf("%d", rows);
    print_input("Columns: ");
    scanf("%d", columns);
}

void display(double **res, int r, int c)
{
    int i, j;
    print_info("\nThe result is:\n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            print_result("%g\t", res[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    getch();
}

void read_matrix(double **matrix, int r, int c, char identifier)
{
    int i, j;
    print_info("\nMatrix %c\n", identifier);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            int ok = -1;
            while (ok != 1)
            {
                print_input("%c[%d][%d]: ", identifier, i + 1, j + 1);
                Expression expr = createExpression();
                scanf("%s", expr.expression);
                ok = is_expression_ok(expr.expression);
                matrix[i][j] = evaluate_expression(expr);
            }
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

    read_matrix(mat1, r, c, 'A');
    read_matrix(mat2, r, c, 'B');
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

    read_matrix(mat1, r, c, 'A');
    read_matrix(mat2, r, c, 'B');
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

    read_matrix(mat1, r1, c1, 'A');

    rows_columns(&r2, &c2);

    double **mat2 = create_matrix(r2, c2);
    read_matrix(mat2, r2, c2, 'B');

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

    read_matrix(mat, r, c, 'A');
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
