# include <iostream>
# include <cmath>
using namespace std;

template <typename T>
class Stack {
    private:
        T* ptr;
        struct Node {
            T data;
            Node* next;
        };

        struct Node* stackTop = NULL;

        int isEmpty() {
            return stackTop == NULL;
        }

    public:
        void push (T item) {
            struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
            newNode -> data = item;
            newNode -> next = stackTop;
            stackTop = newNode;
        }

        T top () {
            return stackTop -> data;
        }

        void pop () {
            if (isEmpty()) {
                return;
            }
            stackTop = stackTop -> next;
        }
};

class Calculator {
    public:
        int calculate (string expression) {

        }

    private:
        int lastAnswer;

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

};

// Stack

# define SIZE 50

using namespace std;

int myStack[SIZE], stackTop, answer = 0;

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