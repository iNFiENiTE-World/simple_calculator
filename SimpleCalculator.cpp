# include <iostream>
# include <cmath>
char DELIMITER = ',';
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
            if (isEmpty()) {
                return ' ';
            }
            return stackTop -> data;
        }

        T pop () {
            if (isEmpty()) {
                return ' ';
            }
            T data = top();
            stackTop = stackTop -> next;
            return data;
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
        Stack<int> numbers;

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
                        infixExpression += DELIMITER;
                        infixExpression += singleExpression;
                        currentState = number;
                    }
                    else {
                        infixExpression += singleExpression;
                    }

                    continue;
                }

                currentState = oper;

                if (isPrecedence(singleExpression)) {
                    opers.push(singleExpression);
                    continue;
                }

                char op;
                do {
                    op = opers.pop();
                    infixExpression += DELIMITER;
                    infixExpression += op;
                } while (isSimilarPrecedence(op));

                opers.push(singleExpression);
            }

            while (!opers.isEmpty()) {
                infixExpression += DELIMITER;
                infixExpression += opers.pop();
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
            if (opers.isEmpty()) {
                return 1;
            }
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

        int operate (char expression) {
            int x, y;
            switch (expression) {
                case '+':
                    y = numbers.pop();
                    x = numbers.pop();
                    numbers.push(add(x, y));
                    return 1;
                case '-':
                    y = numbers.pop();
                    x = numbers.pop();
                    numbers.push(subtract(x, y));
                    return 1;
                case 'x':
                    y = numbers.pop();
                    x = numbers.pop();
                    numbers.push(multiply(x, y));
                    return 1;
                case '/':
                    y = numbers.pop();
                    x = numbers.pop();
                    numbers.push(divide(x, y));
                    return 1;
                default:
                    return 0;
            }
        }

    public:
        int calculate (string expression) {
            string standardE = standardExpression(expression);
            string subE;
            for (int i = 0; i < standardE.length(); i++) {

                char atomE = standardE[i];

                if (atomE != ',') {
                    subE += atomE;
                    continue;
                }

                if (isOperator(subE[0])) {
                    operate(subE[0]);
                    subE = "";
                    continue;
                }

                int num = stringToInt(subE);

                numbers.push(num);

                subE = "";
            }

            operate(subE[0]);

            int numcout = numbers.pop();
            return numcout;
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

int main () {
    Calculator calculator;
    string expression;

    cout << "Input mathematical expression" << endl;
    while (1) {
        cin >> expression;

        cout << calculator.calculate(expression) << endl;
    }
}