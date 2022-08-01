#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

int is_expression_ok(char *str)
{
    int isCorrect = 1, left = 0, right = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'Z' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              (str[i] == '.') ||
              (str[i] == '+') ||
              (str[i] == '-') ||
              (str[i] == '*') ||
              (str[i] == '/') ||
              (str[i] == '(') ||
              (str[i] == ')') ||
              (str[i] == '^')))
        {
            isCorrect = 0;
        }
    }

    for (int i = 0; i < strlen(str); i++)
    {

        if (str[i] == '(')
            left++;

        if (str[i] == ')')
            right++;
    }

    return (isCorrect && (left == right));
}

char *format_expression(char *expression)
{
    int explen = strlen(expression);
    char *new_exp = (char *)malloc(explen * sizeof(char) * 2);
    memset(new_exp, 0, explen * 2);

    for (int i = 0; i < explen; i++)
    {
        // MODIFICATIONS BEFORE CURRENT CHARACTER

        // replaces -123 or (-123) with 0-123
        if ((expression[i] == '-' && i == 0) || (expression[i] == '-' && expression[i - 1] == '('))
        {
            strcat(new_exp, "0_");
        }

        // replaces .1 with 0.1
        if ((expression[i] == '.' && i == 0) || (expression[i] == '.' && is_number(expression[i - 1]) == FALSE))
        {
            strcat(new_exp, "0");
        }

        // ADDS THE CURRENT CHARACTER TO THE NEW EXPRESSION
        new_exp[strlen(new_exp)] = expression[i];

        // MODIFICATINS AFTER CURRENT CHARACTER

        // replaces 2(4) or (2)4 with 2*(4)
        if (
            (is_number(expression[i]) == TRUE) && (expression[i + 1] == '(') ||
            ((expression[i] == ')') && is_number(expression[i + 1]) == TRUE))
        {
            strcat(new_exp, "*");
        }

        // Add _ to end of a number
        if ((is_number(expression[i]) || expression[i] == '.') && !(is_number(expression[i + 1]) || expression[i + 1] == '.'))
        {
            strcat(new_exp, "_");
        }
    }

    return new_exp;
}

char *convert_postfix(char *expression)
{
    int i;
    int formula_len = strlen(expression), decimals = 0;
    double number = 0;
    char *stack = (char *)malloc(sizeof(char) * formula_len);
    memset(stack, 0, formula_len);
    char *buf = (char *)malloc(sizeof(char) * formula_len);
    memset(buf, 0, formula_len);

    for (i = 0; i < formula_len; i++)
    {
        // handle number
        if (is_number(expression[i]))
        {
            if (decimals == 0)
            {
                number = number * 10 + expression[i] - '0';
            }
            else if (decimals > 0)
            {
                number = number + (expression[i] - '0') / pow(10, decimals);
                decimals++;
            }
            continue;
        }
        // handle decimal point
        if (expression[i] == '.')
        {
            decimals = 1;
            continue;
        }

        // Assign number to buf if meet the char of number end.
        if (expression[i] == '_')
        {
            sprintf(buf + strlen(buf), "%g", number);
            sprintf(buf + strlen(buf), "%c", expression[i]);
            number = 0;
            decimals = 0;
            continue;
        }
        // handle operator '+' and '-'
        if (expression[i] == '+' || expression[i] == '-')
        {
            while (strlen(stack) > 0 && is_operator(stack[strlen(stack) - 1]))
            {
                char stack_top = stack[strlen(stack) - 1];
                sprintf(buf + strlen(buf), "%c", stack_top);
                stack = remove_elements_by_index(stack, strlen(stack) - 1, 1);
            }
            sprintf(stack + strlen(stack), "%c", expression[i]);
            continue;
        }
        // handle operator '*' and '/'
        if (expression[i] == '*' || expression[i] == '/' || expression[i] == '^')
        {
            while (strlen(stack) > 0 &&
                   (stack[strlen(stack) - 1] == '*' || stack[strlen(stack) - 1] == '/' || stack[strlen(stack) - 1] == '^'))
            {
                char stack_top = stack[strlen(stack) - 1];
                sprintf(buf + strlen(buf), "%c", stack_top);
                stack = remove_elements_by_index(stack, strlen(stack) - 1, 1);
            }
            sprintf(stack + strlen(stack), "%c", expression[i]);
            continue;
        }
        // handle '('
        if (expression[i] == '(')
        {
            sprintf(stack + strlen(stack), "%c", expression[i]);
            continue;
        }
        // handle ')'
        if (expression[i] == ')')
        {
            while (strlen(stack) > 0 && stack[strlen(stack) - 1] != '(')
            {
                char stack_top = stack[strlen(stack) - 1];
                sprintf(buf + strlen(buf), "%c", stack_top);
                stack = remove_elements_by_index(stack, strlen(stack) - 1, 1);
            }
            stack = remove_elements_by_index(stack, strlen(stack) - 1, 1);
            continue;
        }
    }

    // Clear stack
    for (i = strlen(stack) - 1; i >= 0; i--)
    {
        sprintf(buf + strlen(buf), "%c", stack[i]);
    }

    return buf;
}

double calculate(char *formula)
{
    int formula_len = strlen(formula);
    double *stack = (double *)malloc(sizeof(double) * formula_len * 2);
    int stack_count = 0;
    double number = 0;
    int decimals = 0;
    int i;
    for (i = 0; i < formula_len; ++i)
    {
        if (is_number(formula[i]))
        {
            if (decimals == 0)
            {
                number = number * 10 + formula[i] - '0';
            }
            else if (decimals > 0)
            {
                number = number + (formula[i] - '0') / pow(10, decimals);
                decimals++;
            }
            continue;
        }
        if (formula[i] == '.')
        {
            decimals = 1;
            continue;
        }
        if (formula[i] == '_')
        {
            stack[stack_count++] = number;
            number = 0;
            decimals = 0;
            continue;
        }
        if (is_operator(formula[i]))
        {
            double n1 = stack[stack_count - 1];
            double n2 = stack[stack_count - 2];
            double result = 0;
            switch (formula[i])
            {
            case '+':
                result += n2 + n1;
                break;
            case '-':
                result += n2 - n1;
                break;
            case '*':
                result += n2 * n1;
                break;
            case '/':
                result += n2 / n1;
                break;
            case '^':
                result += pow(n2, n1);
            }
            stack[stack_count - 1] = 0;
            stack[stack_count - 2] = 0;
            stack_count -= 2;
            stack[stack_count++] = result;
        }
    }

    return stack[0];
}

int getVariables(Expression exp)
{
    int len = strlen(exp.expression);
    char *final = (char *)malloc(sizeof(char) * len * 2);

    for (int i = 0; i < len; i++)
    {
        char str[100] = "";
        int strl = 0;

        while ((exp.expression[i] >= 'a' && exp.expression[i] <= 'z') || (exp.expression[i] >= 'Z' && exp.expression[i] <= 'Z'))
        {
            str[strl] = exp.expression[i];
            str[strl + 1] = '\0';
            strl++;
            i++;
        }

        if (strlen(str) > 0)
        {
            double value;
            int isPresent = FALSE;
            for (int j = 0; j < exp.var_length; j++)
            {
                if (strcmp(str, exp.variables[j].name) == 0)
                {
                    isPresent = TRUE;
                    break;
                }
            }

            if (isPresent == FALSE && strcmp(exp.variables[i].name, str) != 0)
            {
                printf("Enter the value of %s: ", str);
                scanf("%lf", &value);
                strcpy(exp.variables[exp.var_length].name, str);
                exp.variables[exp.var_length].value = value;
                exp.var_length++;
            }

            strcpy(str, "");
            strl = 0;
        }
    }

    return exp.var_length;
}

char *replaceVariables(Expression exp)
{
    char *new_exp = (char *)malloc(sizeof(char) * strlen(exp.expression) * 2);
    strcpy(new_exp, exp.expression);
    char *with = (char *)malloc(strlen(exp.expression) * sizeof(char));

    for (int i = 0; i < exp.var_length; i++)
    {
        sprintf(with, "%g", exp.variables[i].value);
        strcpy(new_exp, replace_in_string(new_exp, exp.variables[i].name, with));
    }

    return new_exp;
}

char *handle_trigonometric_functions(Expression exp)
{
    char *new_exp = (char *)malloc(sizeof(char) * 1000);

    return new_exp;
}

double evaluate_expression(Expression expression)
{
    expression.expression = remove_spaces(expression.expression);


    if (is_expression_ok(expression.expression) == TRUE)
    {
        expression.var_length = getVariables(expression);
        return calculate(convert_postfix(format_expression(replaceVariables(expression))));
    }
    else
    {
        print_error("Your expression is not correct.\n");
        exit(-1);
    };
}