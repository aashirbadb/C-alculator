#pragma once
#include <math.h>
void quadratic()
{
    Expression ea = createExpression(), eb = createExpression(), ec = createExpression();
    double a, b, c, d;
    double root1, root2;
    print_info("Enter a, b and c where a*x*x + b*x + c = 0\n");
    int ok = -1;
    while (ok != 1)
    {
        printf("Enter a: ");
        scanf("%s", ea.expression);

        ok = is_expression_ok(ea.expression);
    }
    ok = -1;
    while (ok != 1)
    {

        printf("Enter b: ");
        scanf("%s", eb.expression);
        ok = is_expression_ok(eb.expression);
    }
    ok = -1;
    while (ok != 1)
    {
        printf("Enter c: ");
        scanf("%s", ec.expression);
        ok = is_expression_ok(ec.expression);
    }

    a = evaluate_expression(ea);
    b = evaluate_expression(eb);
    c = evaluate_expression(ec);
    d = b * b - 4 * a * c;
    if (d < 0)
    {
        print_info("The roots are: \n");
        print_result("%g + %gi\n", -b / (double)(2 * a), sqrt(-d) / (2 * a));
        print_result("%g - %gi\n", -b / (double)(2 * a), sqrt(-d) / (2 * a));
    }
    else
    {
        root1 = (-b + sqrt(d)) / (2 * a);
        root2 = (-b - sqrt(d)) / (2 * a);
        print_info("The roots are: \n");
        print_result("%g\n", root1);
        print_result("%g\n", root2);
    }
    getch();

    freeExpression(ea);
    freeExpression(eb);
    freeExpression(ec);
}

void gaussian_elimination(int n)
{
    double **A = create_matrix(n + 1, n);
    double c, sum = 0.0;
    double *x = (double *)malloc(n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= (n + 1); j++)
        {
            Expression exp = createExpression();
            int ok = -1;
            while (ok != 1)
            {
                print_input("%c%d : ", 'A' + i - 1, j);
                scanf("%s", exp.expression);
                ok = is_expression_ok(exp.expression);
            }
            A[i][j] = evaluate_expression(exp);
        }
    }
    for (int j = 1; j <= n; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i > j)
            {
                c = A[i][j] / A[j][j];
                for (int k = 1; k <= n + 1; k++)
                {
                    A[i][k] = A[i][k] - c * A[j][k];
                }
            }
        }
    }
    x[n] = A[n][n + 1] / A[n][n];
    for (int i = n - 1; i >= 1; i--)
    {
        sum = 0;
        for (int j = i + 1; j <= n; j++)
        {
            sum = sum + A[i][j] * x[j];
        }
        x[i] = (A[i][n + 1] - sum) / A[i][i];
    }
    printf("\n");
    for (int i = 1; i <= n; i++)
    {
        print_result("%c = %g\n", 'A' + i - 1, x[i]);
    }
    getch();
}