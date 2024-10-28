#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cmath>


bool isNumber(char c) {
    return c >= '0' && c <= '9';
}
double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

class Stack {
private:
    std::stack<char> items;
public:
    void push(char item) {
        items.push(item);
    }

    char pop() {
        if (!is_empty()) {
            char item = items.top();
            items.pop();
            return item;
        }
        return '\0';
    }

    char peek() {
        if (!is_empty()) {
            return items.top();
        }
        return '\0';
    }

    bool is_empty() {
        return items.empty();
    }
};
std::string stringCalculator(const std::string& expression) {
    Stack stack;
    std::string postfix;
    std::unordered_map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    for (char c : expression) {
        if (isNumber(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.is_empty() && stack.peek()!= '(') {
                postfix += stack.pop();
            }
            if (!stack.is_empty()) stack.pop();
        } else if (precedence.find(c)!= precedence.end()) {
            while (!stack.is_empty() && precedence[stack.peek()] >= precedence[c]) {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.is_empty()) {
        postfix += stack.pop();
    }

    return postfix;
}
double evaluateExpression(const std::string& postfixExpression) {
    std::stack<double> numStack;
    for (char c : postfixExpression) {
        if (isNumber(c)) {
            numStack.push(c - '0');
        } else {
            if (numStack.size() < 2) {
                std::cerr<< std::endl;
                return 0;
            }
            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();
            numStack.push(calculate(a, b, c));
        }
    }
    if (numStack.size()!= 1) {
        std::cerr << "Invalid expression. Too many or too few operands left." << std::endl;
        return 0;
    }
    return numStack.top();
}
std::string extendedStringCalculator(const std::string& expression) {
    Stack stack;
    std::string postfix;
    std::unordered_map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'s', 3}, {'c', 3}, {'l', 3}};

    for (char c : expression) {
        if (isNumber(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.is_empty() && stack.peek()!= '(') {
                postfix += stack.pop();
            }
            if (!stack.is_empty()) stack.pop();
        } else if (precedence.find(c)!= precedence.end()) {
            while (!stack.is_empty() && precedence[stack.peek()] >= precedence[c]) {
                postfix += stack.pop();
            }
            stack.push(c);
        } else if (c == 'i') {
            // 处理 sin
            if (stack.peek() == 's') {
                stack.pop();
                if (postfix.empty()) {
                    std::cerr << "Invalid expression for sin." << std::endl;
                    return "";
                }
                double value = evaluateExpression(postfix);
                postfix = std::to_string(sin(value));
            }
        } else if (c == 's') {
            // 处理 cos
            if (stack.peek() == 'c') {
                stack.pop();
                if (postfix.empty()) {
                    std::cerr << "Invalid expression for cos." << std::endl;
                    return "";
                }
                double value = evaluateExpression(postfix);
                postfix = std::to_string(cos(value));
            }
        } else if (c == 'o') {
            // 处理 log
            if (stack.peek() == 'l') {
                stack.pop();
                if (postfix.empty()) {
                    std::cerr << "Invalid expression for log." << std::endl;
                    return "";
                }
                double value = evaluateExpression(postfix);
                postfix = std::to_string(log(value));
            }
        }
    }

    while (!stack.is_empty()) {
        postfix += stack.pop();
    }

    return postfix;
}

double evaluateExtendedExpression(const std::string& postfixExpression) {
    std::stack<double> numStack;
    for (char c : postfixExpression) {
        if (isNumber(c)) {
            numStack.push(c - '0');
        } else if (c == 's') {
            if (numStack.empty()) {
                std::cerr << "Invalid expression for sin." << std::endl;
                return 0;
            }
            double value = numStack.top(); numStack.pop();
            numStack.push(sin(value));
        } else if (c == 'c') {
            if (numStack.empty()) {
                std::cerr << "Invalid expression for cos." << std::endl;
                return 0;
            }
            double value = numStack.top(); numStack.pop();
            numStack.push(cos(value));
        } else if (c == 'l') {
            if (numStack.empty()) {
                std::cerr << "Invalid expression for log." << std::endl;
                return 0;
            }
            double value = numStack.top(); numStack.pop();
            numStack.push(log(value));
        } else {
            if (numStack.size() < 2) {
                std::cerr << std::endl;
                return 0;
            }
            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();
            numStack.push(calculate(a, b, c));
        }
    }
    if (numStack.size()!= 1) {
        std::cerr << "Invalid expression. Too many or too few operands left." << std::endl;
        return 0;
    }
    return numStack.top();
}

int main() {
    std::string expr1 = "3+4*5";
    std::string postfix1 = stringCalculator(expr1);
    double result1 = evaluateExpression(postfix1);
    std::cout << "结果 " << expr1 << ": " << result1 << std::endl;

    std::string expr2 = "cos(5)+log(6)";
    std::string postfix2 = extendedStringCalculator(expr2);
    double result2 = evaluateExtendedExpression(postfix2);
    std::cout << "结果" << expr2 << ": " << result2 << std::endl;

    return 0;
}