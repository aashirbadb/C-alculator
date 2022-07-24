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

    array expression = "12+( .34-aashirbad/24+b)*(123*12/21)";
    array variables = {'\0'};

    char *exp;

    // printf("Enter an expression: ");
    // scanf("%[^\n]s", expression);

    variable vals[] = {{"a", 12.2}};

    Expression expr = {expression, vals, 0};
    evaluate_expression(expr);

    // printf("\nThe result is: %lf\n", calculate(convert_postfix(exp)));

    return 0;
}

double evaluate_expression(Expression expression)
{
    expression.expression = remove_spaces(expression.expression);

    char *new_expression_expression = (char *)malloc(sizeof(char) * strlen(expression.expression));

    char variables[100][100];
    int variables_index = 0;

    if (is_expression_ok(expression.expression) == TRUE)
    {
        for (int i = 0; i < strlen(expression.expression); i++)
        {
            int index = -1;
            char variable[100] = "\0";

            for (int j = i; j < strlen(expression.expression); j++)
            {
                if (j == i)
                    index = j;
                if ((expression.expression[j] >= 'a' && expression.expression[j] <= 'z') || (expression.expression[j] >= 'Z' && expression.expression[j] <= 'Z'))
                {
                    variable[strlen(variable)] = expression.expression[j];
                    i++;
                }
                else
                    break;
            }
            if (strlen(variable) > 0)
            {
                strcpy(variables[variables_index], variable);
                variables_index++;
            }
        }

        char notdefinedvars[100][100];
        int notdefinedvarsindex = 0;

        for (int i = 0; i < variables_index; i++)
        {
            int isPresent = FALSE;
            for (int j = 0; j < expression.var_length; j++)
            {
                if (strcmp(expression.variables[j].name, variables[i]) == 0)
                {
                    isPresent = TRUE;
                    break;
                }
            }
        }
    }
    else
    {
        printf("Your expression is not correct.\n");
        exit(-1);
    };

    return 1.0;
}