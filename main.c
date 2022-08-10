#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression.h"
#include "matrix.h"
#include "equation.h"
#include "utils.h"

enum main_modes
{
    m_normal = 1,
    m_matrix,
    m_equation,
    m_history,
    m_quit,
};

enum matrix_modes
{
    mat_addition = 1,
    mat_subtraction,
    mat_multiplication,
    mat_transpose,
    mat_exit
};

enum quadratic_modes
{
    quadratic_equation = 1,
    cubic_equation,
    linear_equation_2,
    linear_equation_3,
    linear_equation,
    q_quit
};

void normal_mode();
void history();
void matrix_mode();
void quadratic_mode();

int main(int argc, char *argv)
{
    int mode;
    char cont;

    while (cont != 'n')
    {
        clrscr();
        center(" ___________________________________________________________________ ");
        center("|    ___                _               _         _                 |");
        center("|   / __\\         __ _ | |  ___  _   _ | |  __ _ | |_   ___   _ __  |");
        center("|  / /    _____  / _` || | / __|| | | || | / _` || __| / _ \\ | '__| |");
        center("| / /___ |_____|| (_| || || (__ | |_| || || (_| || |_ | (_) || |    |");
        center("| \\____/         \\__,_||_| \\___| \\__,_||_| \\__,_| \\__| \\___/ |_|    |");
        center("|                                                                   |");
        center("|___________________________________________________________________|");
        print_options("\n\nMODES: \n1.Normal\n2.Matrix\n3.Equation\n4.History\n5.Exit\n");
        print_input("\nEnter mode: ");
        scanf("%d", &mode);

        switch (mode)
        {
        case m_normal:
            normal_mode();
            break;
        case m_history:
            history();
            break;
        case m_matrix:
            matrix_mode();
            break;
        case m_equation:
            quadratic_mode();
            break;
        case m_quit:
            cont = 'n';
            clrscr();
            break;
        default:
            print_error("Please enter a valid choice.\n\n");
            break;
        }
    }
    return 0;
}

void normal_mode()
{
    FILE *normal_history = fopen("normal_history.txt", "a+");
    Expression expr = createExpression();

    clrscr();
    center(" ____________________________________________ ");
    center("|      __                                 _  |");
    center("|   /\\ \\ \\  ___   _ __  _ __ ___    __ _ | | |");
    center("|  /  \\/ / / _ \\ | '__|| '_ ` _ \\  / _` || | |");
    center("| / /\\  / | (_) || |   | | | | | || (_| || | |");
    center("| \\_\\ \\/   \\___/ |_|   |_| |_| |_| \\__,_||_| |");
    center("|____________________________________________|");
    print_info("\nEnter \"q\" to quit\n\n");

    char cont;
    while (1)
    {
        int ok = -1;
        while (ok != 1)
        {
            printf("Enter expression: ");
            scanf("%s", expr.expression);
            ok = is_expression_ok(expr.expression);
        }
        if (strcmp(expr.expression, "q") == 0)
            break;
        double result = evaluate_expression(expr);
        print_result("%s = %g\n", expr.expression, result);
        fprintf(normal_history, "%s = %g\n", expr.expression, result);
    }

    free(expr.expression);
    free(expr.variables);
    fclose(normal_history);
}

void history()
{
    char cont;
    clrscr();
    center(" __________________________________________ ");
    center("|          _       _                       |");
    center("|   /\\  /\\(_) ___ | |_   ___   _ __  _   _ |");
    center("|  / /_/ /| |/ __|| __| / _ \\ | '__|| | | ||");
    center("| / __  / | |\\__ \\| |_ | (_) || |   | |_| ||");
    center("| \\/ /_/  |_||___/ \\__| \\___/ |_|    \\__, ||");
    center("|                                    |___/ |");
    center("|__________________________________________|");

    char file[] = "normal_history.txt";

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
                print_result("%c", ch);
            }
        }
    }

    getch();
}

void matrix_mode()
{

    char cont;
    int choice;
    while (cont != 'n')
    {
        clrscr();
        center(" _____________________________________ ");
        center("|                 _          _        |");
        center("|   /\\/\\    __ _ | |_  _ __ (_)__  __ |");
        center("|  /    \\  / _` || __|| '__|| |\\ \\/ / |");
        center("| / /\\/\\ \\| (_| || |_ | |   | | >  <  |");
        center("| \\/    \\/ \\__,_| \\__||_|   |_|/_/\\_\\ |");
        center("|_____________________________________|");
        print_options("\n\nOPERATIONS:\n");
        print_options("1. Addition\n");
        print_options("2. Subtraction\n");
        print_options("3. Multiplication\n");
        print_options("4. Transpose\n");
        print_options("5. Exit\n");
        print_info("Note: You can enter expressions like 2*(1+2) and a+b\n\n");
        print_input("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case mat_addition:
            add();
            break;
        case mat_subtraction:
            subtract();
            break;
        case mat_multiplication:
            multiply();
            break;
        case mat_transpose:
            transpose();
            break;
        case mat_exit:
            cont = 'n';
            clrscr();
            break;
        default:
            print_error("Invalid input.\n");
            print_error("Please enter the correct input.\n");
            break;
        }
    }
}

void quadratic_mode()
{
    int choice;
    while (choice != 'n')
    {
        clrscr();
        center(" ___________________________________________________ ");
        center("|    __                       _    _                |");
        center("|   /__\\  __ _  _   _   __ _ | |_ (_)  ___   _ __   |");
        center("|  /_\\   / _` || | | | / _` || __|| | / _ \\ | '_ \\  |");
        center("| //__  | (_| || |_| || (_| || |_ | || (_) || | | | |");
        center("| \\__/   \\__, | \\__,_| \\__,_| \\__||_| \\___/ |_| |_| |");
        center("|           |_|                                     |");
        center("|___________________________________________________|");
        print_options("\n\nOPERATIONS:\n");
        print_options("1.ax^2+bx+c=0\n");
        print_options("2.ax^3+bx^2+cx+d=0\n");
        print_options("3.anx+bnx=cn\n");
        print_options("4.anx+bnx+cnx=d\n");
        print_options("5.ax1+bx2+cx3+...=z\n");
        print_options("6.Exit\n");
        print_input("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case quadratic_equation:
            quadratic();
            break;
        case cubic_equation:
            break;
        case linear_equation_2:
            gaussian_elimination(2);
            break;
        case linear_equation_3:
            gaussian_elimination(3);
            break;
        case linear_equation:
            int n;
            print_input("Enter the number of unknowns: ");
            scanf("%d", &n);
            gaussian_elimination(n);
            break;
        case q_quit:
            choice = 'n';
            break;
        default:
            print_error("Invalid input.\nPlease enter the correct input.\n");
            break;
        }
    }
}