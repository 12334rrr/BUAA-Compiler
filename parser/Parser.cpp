/**
 * @file parser.cpp
 * @brief 语法分析器
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "Parser.h"
#include "compUnit/CompUnit.h"
#include "../codeGeneration/llvm/LlvmIRGenerator.h"

void Parser::parse() {
    LlvmIRGenerator::AddIOFunc();
    CompUnit::compUnitParser();
}

bool Parser::isBType(const tokenItem &token) {
    return token.name == "int" || token.name == "char";
}

bool Parser::isConst(const tokenItem &token) {
    return token.name == "const";
}

bool Parser::isFuncType(const tokenItem &token) {
//    Util::printParserInfo("<FuncType>");
    return token.name == "void" || isBType(token);
}

bool Parser::isUnaryExp(const tokenItem &token) {
    return token.type == "IDENFR" || token.type == "INTCON" || token.type == "CHRCON" || token.type == "LPARENT" || token.type == "PLUS" ||
           token.type == "MINU" || token.type == "NOT";
}

bool Parser::isUnaryOp(const tokenItem &token) {
    return token.name == "+" || token.name == "-" || token.name == "!";
}
