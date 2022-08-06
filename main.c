// A program to solve math problems entered by the user
// Supports variable, input via file and put output to a file

#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "expression.h"
#include "ui.h"
#include "matrix.h"

enum modes
{
    enormal = 1,
    ehistory = 2,
};

void normal_mode();
void history();

int clscr = 1;

int main(int argc, char *argv)
{
	
	int mode;
    char cont;

    // if (argc == 1)
    //     clscr = 0;

    main_matrix();

    // while (1)
    // {
    // mode:
    //     clrscr();
    //     home_screen();
    //     colorPrintf(COLOR_CYAN, "MODES: \n1.Normal\n2.History\n\n");
    //     print_input("Enter mode: ");
    //     scanf("%d", &mode);

    //     clrscr();
    //     switch (mode)
    //     {
    //     case (enum modes)enormal:
    //         normal_mode();
    //         break;
    //     case ehistory:
    //         history();
    //         break;
    //     default:
    //         goto quit;
    //         break;
    //     }
    // }
quit:
    return 0;
}

void normal_mode()
{
    FILE *normal_history = fopen("normal_history.txt", "a+");
    array expression = "12+( .34-a/24+b)*(123*helo*12/21)";
    Expression expr = {(char *)malloc(sizeof(char) * 100), (variable *)malloc(sizeof(variable) * 100), 0};
    char cont;
    while (1)
    {
        print_input("Enter expression: ");
        scanf("%s", expr.expression);
        clrscr();
        double result = evaluate_expression(expr);
        print_success("%s = %g\n", expr.expression, result);
        fprintf(normal_history, "%s = %g\n", expr.expression, result);
        if (expr.var_length > 0)
        {
            fprintf(normal_history, "WHERE:");
            for (int i = 0; i < expr.var_length; i++)
            {
                fprintf(normal_history, "\t%s = %g\n", expr.variables[i].name, expr.variables[i].value);
            }
        }

        fprintf(normal_history, "\n");
        print_input("Continue[Y/N]: ");
        scanf(" %c", &cont);
        clrscr();

        if (cont == 'n' || cont == 'N')
        {
            break;
        }
    }

    fclose(normal_history);
}

void history()
{
    char cont;

    while (1)
    {
        int mode;
        print_input("Enter mode of which you want to see history: ");
        scanf(" %d", &mode);
        char file[100];
        switch (mode)
        {
        case enormal:
            strcpy(file, "normal_history.txt");
            break;
        default:
            break;
        }

        if (strlen(file) > 0)
        {

            FILE *fp = fopen(file, "r");
            char ch;

            if (fp != NULL)
            {
                while (1)
                {
                    ch = fgetc(fp);
                    if (ch == EOF)
                        break;
                    print_success("%c", ch);
                }
            }
        }

        printf("Continue[Y/N]: ");
        scanf(" %c", &cont);
        if (cont == 'n' || cont == 'N')
        {
            break;
        }
    }
}
