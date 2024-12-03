/**
 * @file MainFuncDef.cpp
 * @brief 主函数类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "MainFuncDef.h"
#include <iostream>
#include "../../token/Token.h"
#include "../statement/Block.h"
#include "../../util/Util.h"
#include "../../codeGeneration/llvm/Llvm.h"
#include "../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../util/Constants.h"

bool MainFuncDef::isMainReturn = false;
int MainFuncDef::mainNestingLevel = 0;
bool MainFuncDef::isInMainDef = false;

void MainFuncDef::mainFuncDefParser() {
//    SymbolItem *symbolItem;
    tokenItem token = Token::getNowToken();
    if (token.name == "int") {
        token = Token::getNextToken();
    }
    if(token.name == "main"){
//        symbolItem->name = "main";
        token = Token::getNextToken();
    }
    if (token.name == "(") {
        token = Token::getNextToken();
        if (token.name == ")") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "j");
        }
    }
    SymbolItem::initCurrentFuncSymbol(new SymbolItem("main", "IntFunc"));

    LlvmIRGenerator::addLlvmIRConde("define dso_local i32 @main() {\n");
    curFuncSymbol->llvmIRStoreReg++;
//    LlvmIRConstructor::mainConstructor();
    MainFuncDef::isInMainDef = true;


    Block::blockParser();
    Util::printParserInfo("<MainFuncDef>");
    MainFuncDef::isInMainDef = false;
    MainFuncDef::isMainReturn = false;
    MainFuncDef::mainNestingLevel = 0;
    LlvmIRGenerator::addLlvmIRConde("}");
//    Llvm::printLlvmCode("}");

}
