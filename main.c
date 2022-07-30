// A program to solve math problems entered by the user
// Supports variable, input via file and put output to a file

// STEPS:
// 1. Check the input and format it.
//    1.1 Remove all spaces from the equation.
//    1.2 Check if there are proper bracket pairs.
//    1.3 Check the input for any illegal characters.
// 2. Go through the input and add all variables to an array.
// 3. Go through the input and get all the operators along with LHS and RHS and assign them points according to priority.
//    3.1 Start with the innermost bracket and move forward
// 4. Go through the array and start calculating from the highest to lowest priority order.

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "expression.h"

typedef char array[100];

double evaluate_expression(Expression);

int main()
{

    // array expression;
    array expression = "12+( .34-a/24+b)*(123*helo*12/21)";

    Expression expr = {(char *)malloc(sizeof(char) * 100), (variable *)malloc(sizeof(variable) * 100), 0};

    printf("Enter expression: ");
    scanf("%s", expr.expression);

    evaluate_expression(expr);

    // // printf("%d, %s\n", expr.var_length, expr.variables[0].name);

    // printf("\nThe result is: %lf\n", calculate(convert_postfix(expr.expression)));

    return 0;
}

double evaluate_expression(Expression expression)
{
    expression.expression = remove_spaces(expression.expression);

    expression.var_length = 0;

    if (is_expression_ok(expression.expression) == TRUE)
    {
        expression.var_length = getVariables(expression);
        printf("result: %g\n", calculate(convert_postfix(format_expression(replaceVariables(expression)))));
    }
    else
    {
        printf("Your expression is not correct.\n");
        exit(-1);
    };

    return 1.0;
}