# include <iostream>
# include <cmath>
# define DELIMITER ','
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

        int isEmpty() {
            return stackTop == NULL;
        }
};

class Calculator {
    private: 
        enum state {
            oper = 1,
            number = 2
        };

        Stack<char> opers;

        string standardExpression (string postfixExpression) {
            string infixExpression;
            state currentState = number;

            for (int i = 0; i < postfixExpression.length(); i++) {
                char singleExpression = postfixExpression[i];

                if (singleExpression == ' ') {
                    continue;
                }

                if (!isOperator(singleExpression)) {
                    if (currentState != number) {
                        infixExpression += DELIMITER + singleExpression;
                        currentState = number;
                    }
                    infixExpression += singleExpression;
                    continue;
                }

                if (isPrecedence(singleExpression)) {
                    opers.push(singleExpression);
                    continue;
                }

                do {
                    singleExpression = opers.top();
                    infixExpression += DELIMITER + singleExpression;
                    opers.pop();
                } while (isSimilarPrecedence(singleExpression));

                currentState = oper;
            }

            while (!opers.isEmpty()) {
                infixExpression += opers.top();
                opers.pop();
            }

            return infixExpression;
        }

        int isOperator (char subexpression) {
            switch (subexpression) {
                case '+': return 1;
                case '-': return 1;
                case 'x': return 1;
                case '/': return 1;
                default: return 0;
            }
        }

        int isPrecedence (char oper) {
            return getPriority(oper) >= getPriority(opers.top());
        }

        int isSimilarPrecedence (char oper) {
            return getPriority(oper) == getPriority(opers.top());
        }

        int getPriority (char oper) {
            int priority;
            switch (oper) {
                case '+': priority = 1; break;
                case '-': priority = 1; break;
                case 'x': priority = 2; break;
                case '/': priority = 2; break;
                default: return 0;
            }
            return priority;
        }

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