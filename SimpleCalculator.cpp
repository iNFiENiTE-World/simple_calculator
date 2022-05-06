# include <iostream>
# include <cmath>
using namespace std;

// Math operators
int add (int x, int y) {
    return x + y;
}

int subtract (int x, int y) {
    return x - y;
}

int multiply (int x, int y) {
    return x * y;
}

int divide (int x, int y) {
    return x / y;
}

// Stack

# define SIZE 50

using namespace std;

int myStack[SIZE], stackTop, answer = 0;

void initStack () {
    stackTop = -1;
}

int isEmptyStack () {
    if (stackTop == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int isFullStack () {
    if (stackTop == SIZE - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

void push (int num) {
    if (isFullStack()) {
        return;
    }

    stackTop++;
    myStack[stackTop] = num;
}

int pop () {
    if (isEmptyStack()) {
        return NAN;
    }

    int temp = myStack[stackTop];
    stackTop--;
    return temp;
}

void display () {    
    if (isEmptyStack()) {
        cout << "Stack underflow" << endl;
        return;
    }

    int i;

    for (i = stackTop; i != -1; i--) {
        cout << myStack[i] << " ";
    }

    cout << endl;
}

// Calculator functions
// Expression Handler


int operate (char expression) {
    int x, y;
    switch (expression) {
        case '+':
            y = pop();
            x = pop();
            push(add(x, y));
            return 1;
        case '-':
            y = pop();
            x = pop();
            push(subtract(x, y));
            return 1;
        case 'x':
            y = pop();
            x = pop();
            push(multiply(x, y));
            return 1;
        case '/':
            y = pop();
            x = pop();
            push(divide(x, y));
            return 1;
        default:
            return 0;
    }
}

int stringToInt (string number) {
    int total = 0;

    int size = number.length();
    for (int i = size - 1; i != -1; i--) {
        int digit = int(number[i]) - 48;
        int value = digit * pow(10, size - i - 1);
        total += value;
    }

    return total;
}

int main () {
    string expression;
    initStack();

    // Handle infix expression
    while (1) {
        cout << "Input Number / Operator: ";
        cin >> expression;

        if (expression[0] == 'q') {
            exit(0);
            continue;
        }

        string subExpression = "";

        for (int i = 0; i < expression.length(); i++) {

            if (expression[i] != ' ') {
                subExpression += expression[i];
                continue;
            }

            int isOperator = operate(subExpression[0]);
                
            if (isOperator) {
                continue;
            }

            int num = stringToInt(subExpression);

            push(num);
        }

        cout << pop() << endl;
        initStack();
    }
}