/**
 * File: ConstExp.cpp
 * @brief 常量表达式类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include <stack>
#include <iostream>
#include "ConstExp.h"
#include "../multiexp/AddExp.h"
#include "../../../util/Util.h"
#include "../../def/ConstInitVal.h"
#include "../../../parser/declaration/const/ConstDecl.h"
#include "../../../codeGeneration/llvm/Llvm.h"
#include "../../../codeGeneration/llvm/LlvmIRConstructor.h"
#include "../../../symbolTable/blockTree/BlockTree.h"

std::string ConstExp::constExpString;
int ConstExp::constExpValue = 0;
std::string ConstExp::constExpTypeString;

Value ConstExp::constExpParser() {
//    ConstExp::constExpString = "";
//    for (int i = Token::tokenIndex; i < Token::tokenList.size(); i++) {
//        if (Token::tokenList[i].name == "," || Token::tokenList[i].name == "]" || Token::tokenList[i].name == ";") {
//            break;
//        }
//        ConstExp::constExpString += Token::tokenList[i].name;
//    }
//    printf("ConstExp::constExpString: %s\n", LlvmIRConstructor::valName.c_str());
//    ConstExp::constExpValue = Util::calConstExp(ConstExp::constExpString);
    Value value = AddExp::addExpParser();
    Util::printParserInfo("<ConstExp>");
    return value;
}