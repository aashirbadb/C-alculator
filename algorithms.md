# main.c

## main() [INCLUDE]

1. START
1. declare variable choice
1. DISPLAY "C-alculator"
1. DISPLAY Options
    1. Normal Mode
    1. Matrix Mode
    1. Equation Mode
    1. Show History
    1. Quit
1. DISPLAY "Enter choice"
1. READ choice
1. IF choice == 1
    1. Call the function "normal_mode"
1. ELSE IF choice == 2
    1. Call the function "matrix_mode"
1. ELSE IF choice == 3
    1. Call the function "equation_mode"
1. ELSE IF choice == 4
    1. DISPLAY history
1. ELSE IF choice == 5
    1. GOTO step 3
1. ELSE
    1. DISPLAY "Please enter a valid input"
    1. GOTO step 3
1. STOP

## normal_mode() [INCLUDE]

1. Open file "history" in append mode
1. DISPLAY "Normal"
1. LOOP
    1. Create variable expr
    1. DISPLAY "Enter expression"
    1. READ expr
    1. IF expression is incorrect
        1. goto step 3.1
    1. IF expression == "q"
        1. GOTO step 4
    1. evaluate expression and store it in result
    1. DISPLAY result
    1. WRITE expr and result in "history" file
    1. GOTO step 3.1
1. Close file "history"
1. STOP

## matrix_mode() [INCLUDE]

1. START
1. declare variable choice
1. DISPLAY "Matrix"
1. DISPLAY Options
    1. Addition
    1. Subtraction
    1. Multiplication
    1. Transpose
    1. Quit
1. DISPLAY "Enter choice"
1. READ choice
1. IF choice == 1
    1. Call the function "add"
1. ELSE IF choice == 2
    1. Call the function "subtract"
1. ELSE IF choice == 3
    1. Call the function "multiply"
1. ELSE IF choice == 4
    1. Call the function "Transpose"
1. ELSE IF choice == 5
    1. GOTO step 3
1. ELSE
    1. DISPLAY "Please enter a valid input"
    1. GOTO step 3
1. STOP

## equation_mode() [INCLUDE]

1. START
1. declare variable choice
1. DISPLAY "Equation"
1. DISPLAY Options
    1. ax^2+bx+c=0;
    1. anx+bnx=cn;
    1. anx+bnx+cnx=d;
    1. ax1+bx2+cx3+...=z;
    1. Quit
1. DISPLAY "Enter choice"
1. READ choice
1. IF choice == 1
    1. Call the function "quadratic"
1. ELSE IF choice == 2
    1. Call the function "gaussian_elimination" with argument 2
1. ELSE IF choice == 3
    1. Call the function "gaussian_elimination" with argument 3
1. ELSE IF choice == 4
    1. DISPLAY "Enter the number of unknowns"
    1. READ number, n
    1. Call the function "gaussian_elimination" with argument n
1. ELSE IF choice == 5
    1. GOTO step 3
1. ELSE
    1. DISPLAY "Please enter a valid input"
    1. GOTO step 3
1. STOP

# matrix.h

## add()

1. Declare variables r,c,i = 0,j = 0
1. Read r and c
1. Create matrix mat1, mat2, res of order r \* c
1. READ matrix mat1 and mat2
1. While i < r
    1. While j < c
        1. res[i][j] = mat1[i][j] + mat2[i][j]
        1. j = j + 1
    1. i = i + 1
1. DISPLAY res

1. ## subtract()
1. Declare variables r,c,i = 0,j = 0
1. Create matrix mat1, mat2, res of order r \* c
1. Read r and c
1. READ matrix mat1 and mat2
1. While i < r
    1. While j < c
        1. res[i][j] = mat1[i][j] - mat2[i][j]
        1. j = j + 1
    1. i = i + 1
1. DISPLAY res

## multiply

1. Start
1. Declare variables r1, r2, c1, c2, i = 0, j = 0, k = 0
1. Read rows and columns of 1st(r1,c1) and 2nd matrix(r2,c2)
1. Declare matrix mat1 of order r1 _ c1, matrix mat2 of order r2 _ c2 and res of order r1 \* c2
1. If c1 == r2
    1. Read mat1 and mat2
    1. While i < r1
        1. While j < c2
            1. sum = 0
            1. While k < c1
                1. sum= sum + A[i][k] \* B[k][j]
                1. k=k+1
            1. res[i][j] = sum
            1. j=j+1
        1. i=i+1
1. DISPLAY matrix res
1. Else
    1. DISPLAY "Cannot be multiplied"
1. Stop

## Transpose

1. Declare variables i,j,r,c
1. READ r and c
1. Create matrix mat(r*c) and res(c*r)
1. READ matrix mat
1. While i<c
    1. While j<r
        1. res[i][j] = res[j][i]
        1. j=j+1
    1. i = i + 1
1. DISPLAY matrix res
1. STOP

# equation.h

## quadratic()

1. START
1. DISPLAY "Enter a, b and c where a*x*x + b\*x + c = 0"
1. READ a,b,c
1. d = b _ b - 4 _ a \* c
1. IF d < 0
    1. real = -b/(2*a), imaginary = sqrt(-d)/(2*a)
    1. DISPLAY "The roots are:"
    1. DISPLAY "real + imaginary i"
    1. DISPLAY "real - imaginary i"
1. ELSE
    1. root1 = (-b + sqrt(d)) / (2 \* a);
    1. root2 = (-b - sqrt(d)) / (2 \* a);
    1. DISPLAY "The roots are:"
    1. DISPLAY "root1"
    1. DISPLAY "root2"
1. STOP

## gaussian_elimination(n)

1. READ n from function arguments
1. Create matrix A of order(n+1\*n)
1. Declare variable c, sum = 0, i=1,j=1,k
1. Create array x with n elements
1. WHILE i<=n
    1. WHILE j<=n
        1. DISPLAY "('A'+i-1)j: "
        1. READ expression exp
        1. IF expression is incorrect goto step 5.1
        1. A[i][j] = evaluate_expression(exp)
        1. j = j + 1
1. i = 1, j = 1, k = 1
1. WHILE j<=n
    1. WHILE i<=n
        1. if i>j
            1. c = A[i][j]/A[j][j]
            1. WHILE k<=n+1
                1. A[i][k] = A[i][k] - c \* A[j][k]
                1. k = k+1
        1. i = i + 1
    1. j = j + 1
1. x[n] = A[n][n + 1] / A[n][n]
1. i = n - 1
1. WHILE i >= 1
    1. sum = 0, j = i + 1
    1. WHILE j <= n
        1. sum = sum + A[i][j] \* x[j]
        1. j = j + 1
    1. x[i] = (A[i][n + 1] - sum) / A[i][i]
    1. i = i + 1
1. i = 1
1. WHILE i <= n
    1. DISPLAY "X(i) = (x[i])"
    1. i = i + 1
1. STOP

# expression.h

## convert_postfix()

1. Declare variables i = 0, decimals = 0, number = 0, formula_len = strlen(expression)
1. create string stack and buffer
1. WHILE i < formula_len
    1. IF expression[i] is a number
        1. IF decimals == 0
            1. number = number \* 10 + expression[i] - '0'
        1. ELSE IF decimals > 0
            1. number = number + (expression[i] - '0') / pow(10, decimals)
            1. decimals = decimals + 1
        1. Goto step 3
    1. IF expression[i] == '.'
        1. decimals = 1
        1. Goto step 3
    1. IF expression[i] == '\_'
        1. add number to buffer
        1. add '\_' to buffer
        1. number = 0, decimals = 0
        1. Goto step 3
    1. IF expression[i] is an operator [+,-,/,*,^]
        1. WHILE strlen(stack) > 0 and last element of stack is an operator
            1. Add last element of stack to buffer
            1. remove last element of stack
        1. Add expression[i] to stack
        1. Goto step 3
    1. IF expression[i] == '('
        1. Add '(' to stack
        1. Goto step 3
    1. IF expression[i] == ')'
        1. While strlen(stack) > 0 and last element of stack is not '('
            1. add last element of stack to buffer
            1. remove last element of stack
        1. remove last element of stack
        1. Goto step 3
    1. i = i + 1
1. i = strlen(stack) - 1
1. WHILE i>= 0
    1. add stack[i] to buffer
    1. i = i-1
1. STOP


## calculate()
1. Declare variable formula_len = strlen(formula), stack_count = 0, number = 0, decimals = 0, i=0
1. WHILE i < formula_len
    1. IF formula[i] is a number
        1. IF decimals == 0
            1. number = number \* 10 + formula[i] - '0'
        1. ELSE IF decimals > 0
            1. number = number + (formula[i] - '0') / pow(10, decimals)
            1. decimals = decimals + 1
        1. Goto step 2
    1. IF formula[i] == '.'
        1. decimals = 1
        1. Goto step 2
    1. IF formula[i] == '_'
        1. stack[stack_count] = number
        1. stack_count = stack_count + 1
        1. number = 0, decimals = 0
        1. Goto step 2
    1. IF formula[i] is an operator
        1. n1 = stack[stack_count - 1];
        1. n2 = stack[stack_count - 2];
        1. result = 0;
        1. IF formula[i] == '+'
            1. result = result + n2 + n1 
        1. ELSE IF formula[i] == '-'
            1. result = result + n2 - n1
        1. ELSE IF formula[i] == '*'
            1. result = result + n2 * n1
        1. ELSE IF formula[i] == '/'
            1. result = result + n2 / n1
        1. ELSE IF formula[i] == '^'
            1. result = result + n2 ^ n1
        1. stack[stack_count - 1] = 0
        1. stack[stack_count - 2] = 0
        1. stack_count -= 2
        1. stack[stack_count] = result
        1. stack_count = stack_count + 1
    i = i + 1
1. STOP