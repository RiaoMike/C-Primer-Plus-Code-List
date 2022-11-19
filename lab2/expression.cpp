#include<iostream>
#include<string>
#define MAXSIZE 100
#define OVERFLOW -2
#define ERROR 0
using namespace std;

template<typename T>
class OpStack {
    private:
        T * base;
        T * top;
        int maxsize;
    public:
        OpStack();
        ~OpStack();
        void Push(T);
        T Pop();
        T GetTop();
};

template<typename T>
OpStack<T>::OpStack() {
    base = new T[MAXSIZE];
    if(!base) {
        exit(OVERFLOW);
    }
    top = base;
    maxsize = MAXSIZE;
}

template<typename T>
OpStack<T>::~OpStack() {
    delete [] base;
}

template<typename T>
void OpStack<T>::Push(T elem) {
    if(top - base == maxsize) {
        exit(ERROR);
    }
    else {
        *top = elem;
        top++;
    }
}

template<typename T>
T OpStack<T>::Pop() {
    if(top == base) {
        return ERROR;
    }
    else {
        top--;
        return *top;
    }
}

template<typename T>
T OpStack<T>::GetTop() {
    if(top != base) {
        return *(top - 1);
    }
    else exit(OVERFLOW);
}

int Operate(int a, char theta, int b) {
    if(theta == '-') {
        return a - b;
    }
    else if(theta == '+') {
        return a + b;
    }
    else if(theta == '*') {
        return a * b;
    }
    else {
        return a / b;
    }
}

bool In(char ch) {
    if(ch == '-' || ch == '+' || ch == '*' || ch == '/' || 
    ch == '(' || ch == ')' || ch == '#') {
        return true;
    }
    else {
        return false;
    }
}

int Precede(char a, char b) {
    if(!(In(a) && In(b))) {
        exit(ERROR);
    } 
    if(a == '+' || a == '-') {
        if(b == '*' || b == '/' || b == '(') {
            return -1;
        }
        else {
            return 1;
        }
    }
    else if(a == '*' || a == '/') {
        if(b == '(') {
            return -1;
        }
        else return 1;
    }
    else if(a == '(') {
        if(b == ')') {
            return 0;
        }
        else return -1;
    }
    else if(a == ')') {
        return 1;
    }
    else {
        return -1;
    }
}

int EvaluateExpression() {
    // Initialize the operation and number stacks
    OpStack<char> Operation;
    OpStack<int> Number;
    Operation.Push('#');

    char ch;
    cin >> ch;
    while(ch != '#' || Operation.GetTop() != '#') {
        // if ch is a number
        if(!In(ch)) {
            string str_num = "";
            str_num += ch;
            cin >> ch;
            while(!In(ch)) {
                str_num += ch;
                cin >> ch;
            }
            Number.Push(stoi(str_num));
        }
        else {
            switch(Precede(Operation.GetTop(), ch)) {
                case -1: {
                    Operation.Push(ch);
                    cin >> ch;
                    break;
                }
                case 1: {
                    char theta = Operation.Pop();
                    int right_n = Number.Pop();
                    int left_n = Number.Pop();
                    int result = Operate(left_n, theta, right_n);
                    Number.Push(result);
                    break;
                }
                case 0: {
                    Operation.Pop();
                    cin >> ch;
                    break;
                }
            }
        }
    }
    return Number.GetTop();
}

int main() {
    cout << "Please enter an expression: " << endl;
    int result = EvaluateExpression();
    cout << "The result is: " << result << endl;
    return 0;
}