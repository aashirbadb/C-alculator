#pragma once
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

double evaluate_expression(Expression expression);

int priority(char x) {
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    if (x == '^')
        return 3;
    return 0;
}

// Check expression for errors
// Returns 0 if there are errors along with error messages
int is_expression_ok(char *str, int allow_chars) {
    int isCorrect = 1, left = 0, right = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (!((allow_chars && is_letter(str[i])) || is_number(str[i]) || is_operator(str[i]) ||
              str[i] == '.' || str[i] == ' ' || str[i] == '(' ||
              str[i] == ')')) {
            isCorrect = 0;
            print_error("Your expression contains invalid characters.\n");
            print_error("You can only enter %snumbers, operators, brackets[\'(\' and \')\'] and spaces.\n", allow_chars ? "letters, " : "");
            break;
        }
        if ((is_number(str[i]) && is_letter(str[i + 1])) ||
            (is_letter(str[i]) && is_number(str[i + 1]))) {
            print_error("You enter a letter immediately before or after a number. Please use * to separate them.\n");
            isCorrect = 0;
            break;
        }
        if ((str[i] == '.' && is_letter(str[i + 1])) ||
            (is_letter(str[i]) && str[i + 1] == '.')) {
            print_error("You enter a decimal point(.) immediately before or after a variable. Please use * to separate them.\n");
            isCorrect = 0;
            break;
        }
        if (str[i] == '(') left++;
        if (str[i] == ')') right++;
    }
    return (isCorrect && (left == right));
}

// Applies modifications to the expression before converting it to postfix
char *format_expression(char *expression) {
    int explen = strlen(expression);
    char *new_exp = (char *)malloc(explen * sizeof(char) * 2);
    memset(new_exp, 0, explen * sizeof(char) * 2);
    for (int i = 0; i < explen; i++) {
        if (expression[i] == ' ')
            continue;

        if ((expression[i] == '-' && i == 0) || (expression[i] == '-' && expression[i - 1] == '('))
            strcat(new_exp, "0_");  // replaces -123 or (-123) with 0-123

        if ((expression[i] == '.' && i == 0) || (expression[i] == '.' && is_number(expression[i - 1]) == 0))
            strcat(new_exp, "0");  // replaces .1 with 0.1

        new_exp[strlen(new_exp)] = expression[i];  // add current character to the expression

        if ((is_number(expression[i]) == 1) && (expression[i + 1] == '(') || ((expression[i] == ')') && is_number(expression[i + 1]) == 1))
            strcat(new_exp, "*");  // replaces 2(4) or (2)4 with 2*(4)

        if ((is_number(expression[i]) || expression[i] == '.') &&
            !(is_number(expression[i + 1]) || expression[i + 1] == '.'))
            strcat(new_exp, "_");  // Add _ to end of a number
    }
    return new_exp;
}

// Converts expression to postfix (eg: 2*2+1 => 2_2_*1_+)
char *convert_postfix(char *expression) {
    int formula_len = strlen(expression), decimals = 0;
    double number = 0;
    char *stack = (char *)malloc(sizeof(char) * formula_len);
    char *buf = (char *)malloc(sizeof(char) * formula_len);
    memset(stack, 0, sizeof(char) * formula_len);
    memset(buf, 0, sizeof(char) * formula_len);

    for (int i = 0; i < formula_len; i++) {
        if (is_number(expression[i])) {
            if (decimals == 0) {
                number = number * 10 + expression[i] - '0';
            } else if (decimals > 0) {
                number = number + (expression[i] - '0') / pow(10, decimals);
                decimals++;
            }
            continue;
        }
        if (expression[i] == '.') {
            decimals = 1;
            continue;
        }
        if (expression[i] == '_') {
            sprintf(buf + strlen(buf), "%g%c", number, expression[i]);
            number = 0;
            decimals = 0;
            continue;
        }
        if (expression[i] == '(') {
            sprintf(stack + strlen(stack) + 1, "%c", expression[i]);
            continue;
        }
        if (expression[i] == ')') {
            while (strlen(stack) > 0 && stack[strlen(stack)] != '(') {
                sprintf(buf + strlen(buf), "%c", stack[strlen(stack) - 1]);
                stack = remove_elements_by_index(stack, strlen(stack) - 1, 1);
            }
            continue;
        }
        if (is_operator(expression[i])) {
            while (strlen(stack) > 0 && priority(stack[strlen(stack) - 1] >= priority(expression[i]))) {
                sprintf(buf + strlen(buf), "%c", stack[strlen(stack) - 1]);
                stack = remove_elements_by_index(stack, strlen(stack) - 1, 1);
            }
            sprintf(stack + strlen(stack), "%c", expression[i]);
            continue;
        }
    }
    for (int i = strlen(stack) - 1; i >= 0; i--) {
        sprintf(buf + strlen(buf), "%c ", stack[i]);
    }
    return buf;
}

// Calculates the value of the postfix formula provided
// The numbers are stored in an array and if there is an operator then the last two numbers are taken
// from the array and the operation is done. The last two numbers of the array are removed and the result is added
// At the end, the first value of the array is the result
double calculate(char *formula) {
    int formula_len = strlen(formula);
    double *stack = (double *)malloc(sizeof(double) * formula_len * 2);
    memset(stack, 0, formula_len);
    int stack_count = 0;
    double number = 0;
    int decimals = 0;
    int i;
    for (i = 0; i < formula_len; ++i) {
        if (is_number(formula[i])) {
            if (decimals == 0) {
                number = number * 10 + formula[i] - '0';
            } else if (decimals > 0) {
                number = number + (formula[i] - '0') / pow(10, decimals);
                decimals++;
            }
            continue;
        }
        if (formula[i] == '.') {
            decimals = 1;
            continue;
        }
        if (formula[i] == '_') {
            stack[stack_count++] = number;
            number = 0;
            decimals = 0;
            continue;
        }
        if (is_operator(formula[i])) {
            double n1 = stack[stack_count - 1];
            double n2 = stack[stack_count - 2];
            double result = 0;
            switch (formula[i]) {
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

// reads the expression and if there are any variables, it asks the user to enter it.
// The variables are stored in expression struct
// Variables also supports expression but it cannot contain any variables(2+2 is ok but 2*a is not)
int getVariables(Expression exp) {
    int len = strlen(exp.expression);
    for (int i = 0; i < len; i++) {
        char str[100] = "";
        int strl = 0;
        while ((exp.expression[i] >= 'a' && exp.expression[i] <= 'z') ||
               (exp.expression[i] >= 'A' && exp.expression[i] <= 'Z')) {
            str[strl] = exp.expression[i];
            str[strl + 1] = '\0';
            strl++;
            i++;
        }
        if (strlen(str) > 0) {
            double value = 0.0;
            int isPresent = 0;
            for (int j = 0; j < exp.var_length; j++) {
                if (strcmp(str, exp.variables[j].name) == 0) {
                    isPresent = 1;
                    break;
                }
            }
            if (isPresent == 0 && strcmp(exp.variables[i].name, str) != 0) {
                int ok = -1;
                while (ok != 1) {
                    Expression expr = createExpression();
                    print_input("\tEnter the value of %s: ", str);

                    scanf("%s", expr.expression);
                    ok = is_expression_ok(expr.expression, 0);
                    if (ok == 1)
                        value = evaluate_expression(expr);
                    free(expr.expression);
                    free(expr.variables);
                }
                strcpy(exp.variables[exp.var_length].name, str);
                exp.variables[exp.var_length].value = value;
                exp.var_length++;
            }
            strcpy(str, "");
            strl = 0;
        }
    }

    // Sort the variables array from longest to shortest
    for (int i = 0; i < exp.var_length; i++) {
        for (int j = 0; j < exp.var_length - 1 - i; j++)
            if (strlen(exp.variables[j].name) < strlen(exp.variables[j + 1].name)) {
                variable temp = exp.variables[j];
                exp.variables[j] = exp.variables[j + 1];
                exp.variables[j + 1] = temp;
            }
    }
    return exp.var_length;
}

// Replace the variables int the equation with the variable's value
char *replaceVariables(Expression exp) {
    char *new_exp = (char *)malloc(sizeof(char) * strlen(exp.expression) * 2);
    memset(new_exp, 0, strlen(exp.expression) * 2);
    strcpy(new_exp, exp.expression);
    char *with = (char *)malloc(strlen(exp.expression) * sizeof(char));
    memset(with, 0, strlen(exp.expression));
    for (int i = 0; i < exp.var_length; i++) {  // sort the variables from longest length to shortest
        for (int j = 0; j < exp.var_length - 1 - i; j++)
            if (strlen(exp.variables[j].name) < strlen(exp.variables[j + 1].name)) {
                variable temp = exp.variables[j];
                exp.variables[j] = exp.variables[j + 1];
                exp.variables[j + 1] = temp;
            }
    }

    for (int i = 0; i < exp.var_length; i++) {
        sprintf(with, "%g", exp.variables[i].value);
        strcpy(new_exp, replace_in_string(new_exp, exp.variables[i].name, with));
    }
    return new_exp;
}

// takes an Expression struct as the argument and returns the result
// prints error message and returns 0 if the any errors are found.
double evaluate_expression(Expression expression) {
    if (is_expression_ok(expression.expression, 1) == 1) {
        expression.var_length = getVariables(expression);
        char *replaced_vars = replaceVariables(expression);
        char *formatted_expression = format_expression(replaced_vars);
        char *postfix_expression = convert_postfix(formatted_expression);
        return calculate(postfix_expression);
    } else {
        print_error("Your expression is not correct.\n");
        return 0;
    };
}