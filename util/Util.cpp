/**
 * 工具类
 * @Author: 王春博
 * @Date: 2024-10-05
 * @Version: 1.0
 * @Description: 工具类
 */

#include "Util.h"
#include "../token/Token.h"
#include "../symbolTable/blockTree/BlockTree.h"
#include "../parser/function/FuncDef.h"
#include "../semantic/Semantic.h"
#include<iostream>
#include<map>
#include <fstream>
#include <stack>

//token的map映射
std::map<std::string, std::string> tokenMap = {
        {"Ident",       "IDENFR"},
        {"else",        "ELSETK"},
        {"void",        "VOIDTK"},
        {";",           "SEMICN"},
        {"IntConst",    "INTCON"},
        {"!",           "NOT"},
        {"*",           "MULT"},
        {",",           "COMMA"},
        {"StringConst", "STRCON"},
        {"&&",          "AND"},
        {"/",           "DIV"},
        {"(",           "LPARENT"},
        {"CharConst",   "CHRCON"},
        {"||",          "OR"},
        {"%",           "MOD"},
        {")",           "RPARENT"},
        {"main",        "MAINTK"},
        {"for",         "FORTK"},
        {"<",           "LSS"},
        {"[",           "LBRACK"},
        {"const",       "CONSTTK"},
        {"getint",      "GETINTTK"},
        {"<=",          "LEQ"},
        {"]",           "RBRACK"},
        {"int",         "INTTK"},
        {"getchar",     "GETCHARTK"},
        {">",           "GRE"},
        {"{",           "LBRACE"},
        {"char",        "CHARTK"},
        {"printf",      "PRINTFTK"},
        {">=",          "GEQ"},
        {"}",           "RBRACE"},
        {"break",       "BREAKTK"},
        {"return",      "RETURNTK"},
        {"==",          "EQL"},
        {"continue",    "CONTINUETK"},
        {"+",           "PLUS"},
        {"!=",          "NEQ"},
        {"if",          "IFTK"},
        {"-",           "MINU"},
        {"=",           "ASSIGN"}
};

//是否属于token的组合部分
bool Util::isTokenItem(char c) {
    return isalpha(c) || isdigit(c) || c == '_';
}

//是否是标识符的组成部分
bool Util::isIdentItem(char c) {
    return isalpha(c) || c == '_';
}

// 是运算符
bool Util::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '%' || c == '|' || c == '&'
           || c == '<' || c == '>' || c == '!' || c == '=';
}

//是否是两个运算符的第一个
bool Util::isBinaryOperator(char c) {
    return c == '&' || c == '|' || c == '<' || c == '>' || c == '=';
}

//是否是界符
bool Util::isDelimiter(char c) {
    return c == ',' || c == ';' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}

//是否是单目运算符
bool Util::isUnaryOperator(const std::string &c) {
    return c == "+" || c == "-" || c == "!";
}

void Util::printParserInfo(const char *info) {
    std::ofstream parserFile("parser.txt", std::ios::app);
    parserFile << info << std::endl;
    parserFile.close();
}


void Util::printErrorInfo(int lineNum, const char *error) {
    std::ofstream errorFile("error.txt", std::ios::app);
    errorFile << Token::tokenList[Token::tokenIndex - 1].lineNum << " " << error << std::endl;
    errorFile.close();
}

void Util::printSemanticErrorInfo(int lineNum, const std::string &error) {
    std::ofstream errorFile("error.txt", std::ios::app);
    errorFile << lineNum << " " << error << std::endl;
    errorFile.close();
}

void Util::clearFile() {
    clearParserInfo();
}

void Util::clearParserInfo() {
    std::ofstream file("parser.txt");
    file.close();
}

void Util::initEnv() {
    createFile();
    clearFile();
    Token::tokenInit();
    BlockTree::init();
    FuncDef::funcDefInit();
}

void Util::createFile() {
    //创建输出文件
    std::ofstream lexerFile("lexer.txt");
    std::ofstream errorFile("error.txt");
    std::ofstream parserFile("parser.txt");
    std::ofstream symbolFile("symbol.txt");
    std::ofstream mipsFile("mips.txt");
    std::ofstream llvmFile("llvm_ir.txt");
}

bool Util::isExistEQL() {
    tokenItem token = Token::getNowToken();
    for (int i = Token::tokenIndex; i < Token::tokenList.size(); i++) {
        if (Token::tokenList[i].name == ";" || Token::tokenList[i].lineNum != token.lineNum) {
            break;
        }
        if (Token::tokenList[i].name == "=") {
            return true;
        }
    }
    return false;
}

void Util::printSemanticInfo(SymbolItem *item) {
    std::ofstream symbolFile("symbol.txt", std::ios::app);
    symbolFile << item->scopeIndex << " " << item->name << " " << item->type << std::endl;
    symbolFile.close();
}

void Util::printSemanticInfo(const std::vector<SymbolItem> *itemList) {
    std::ofstream symbolFile("symbol.txt", std::ios::app);
    for (auto &item: *itemList) {
        symbolFile << item.scopeIndex << " " << item.name << " " << item.type << std::endl;
    }
    symbolFile.close();
}

void Util::releaseEnv() {
    Semantic::clearRoot();
}

bool isCalOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int operatorPriority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/' || op == '%') {
        return 2;
    } else {
        return 0;
    }
}

int op(int firstOperand, int secondOperand, char op) {
    switch (op) {
        case '+':
            return firstOperand + secondOperand;
        case '-':
            return firstOperand - secondOperand;
        case '*':
            return firstOperand * secondOperand;
        case '/':
            return firstOperand / secondOperand;
        case '%':
            return firstOperand % secondOperand;
        default:
            return -1;
    }
}

//int Util::calConstExp(const std::string &exp) {
//    int flag = 0, index = 0;
//    if (exp[0] == '+' || exp[0] == '-') {
//        int num = 0;
//        while (exp[index] == '+' || exp[index] == '-') {
//            if (exp[index] == '-') {
//                flag++;
//            }
//            index++;
//        }
//    }
//    std::stack<int> numStack;
//    std::stack<char> opStack;
//    std::string varName;
//    int numTemp = 0;
//    for (int i = index; i < exp.size(); i++) {
//        numTemp = 0;
//        varName = "";
//        if (isdigit(exp[i])) {
//            while (isdigit(exp[i])) {
//                numTemp = numTemp * 10 + (exp[i] - '0');
//                i++;
//            }
//            i--;
//            numStack.push(numTemp);
//        } else if (isIdentItem(exp[i])) {
//            while (isIdentItem(exp[i])) {
//                varName += exp[i++];
//            }
//            i--;
//            int value = SymbolTable::getSymbolItem(varName).value;
//            numStack.push(value);
//        } else if (exp[i] == '(') {
//            opStack.push('(');
//        } else if (exp[i] == ')') {
//            while (!opStack.empty() && opStack.top() != '(') {
//                int secondOperand = numStack.top();
//                numStack.pop();
//                int firstOperand = numStack.top();
//                numStack.pop();
//                numStack.push(op(firstOperand, secondOperand, opStack.top()));
//                opStack.pop();
//            }
//            if (!opStack.empty()) {
//                opStack.pop();
//            }
//        } else if (isCalOperator(exp[i])) {
//            while (!opStack.empty() && operatorPriority(opStack.top()) >= operatorPriority(exp[i])) {
//                int secondOperand = numStack.top();
//                numStack.pop();
//                int firstOperand = numStack.top();
//                numStack.pop();
//                numStack.push(op(firstOperand, secondOperand, opStack.top()));
//                opStack.pop();
//            }
//            opStack.push(exp[i]);
//        }
//    }
//    while (!opStack.empty()) {
//        int secondOperand = numStack.top();
//        numStack.pop();
//        int firstOperand = numStack.top();
//        numStack.pop();
//        numStack.push(op(firstOperand, secondOperand, opStack.top()));
//        opStack.pop();
//    }
//    printf("numStack.top() = %d exp=%s\n", numStack.top(), exp.c_str());
//    return numStack.top() * (flag % 2 == 0 ? 1:-1);
//}

void Util::mvFileInfo(const std::string &sourcePath, const std::string &destinationPath) {
    printf("sourcePath = %s destinationPath = %s\n", sourcePath.c_str(), destinationPath.c_str());
    // 打开源文件
    std::ifstream sourceFile(sourcePath);
    if (!sourceFile) {
        std::cerr << "cant open: " << sourcePath << std::endl;
        return;
    }
    // 打开目标文件
    std::ofstream destinationFile(destinationPath);
    if (!destinationFile) {
        std::cerr << "cant create: " << destinationPath << std::endl;
        return;
    }
    // 逐行读取和写入
    std::string line;
    while (std::getline(sourceFile, line)) {
        destinationFile << line << "\n";
    }
    std::cout << "success: " << sourcePath << " -> " << destinationPath << std::endl;
}