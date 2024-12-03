/**
 * @file cal.cpp
 */

#include "cal.h"

int getPropority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else {
        return 0;
    }
}
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
//            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
    }
    return 0;
}
void cal::calExp(const std::string& exp) {
    //计算表达式的值 例如1+2 3*4
}
