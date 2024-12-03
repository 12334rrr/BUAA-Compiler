/**
 * @file FuncDef.cpp
 * @brief FuncDef class implementation file
 * @version 1.0
 * @date 2024-10-10
 * @Author  王春博
 */

#include <iostream>
#include "FuncDef.h"
#include "../../token/Token.h"
#include "../Parser.h"
#include "../statement/Block.h"
#include "../../util/Util.h"
#include "FuncFParams.h"
#include "../../symbolTable/blockTree/BlockTree.h"
#include "../../codeGeneration/llvm/LlvmIRConstructor.h"
#include "../../codeGeneration/llvm/Llvm.h"
#include "../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../util/Constants.h"

int FuncDef::isInFunc = 0;
std::string FuncDef::funcName;
bool FuncDef::isInParam = false;
bool FuncDef::isReturn = false;

void FuncDef::funcDefParser() {
    bool isRepeat = false;
    isInParam = true;
    FuncDef::isInFunc = 1;
    std::string type;
    SymbolItem item;
    tokenItem token = Token::getNowToken();
    if (Parser::isFuncType(token)) {
        if (token.name == "void") {
            item.type = "VoidFunc";
        } else if(token.name == "int"){
            item.type = "IntFunc";
        } else if(token.name == "char"){
            item.type = "CharFunc";
        }
        token = Token::getNextToken();
    }
    Util::printParserInfo("<FuncType>");
    if (token.type == "IDENFR"){
        item.name = token.name;
        if(BlockTree::nowBlockNode->symbolTable->isSymbolPresent(token.name) || SymbolTable::isFunc(token.name)){
            isRepeat = true;
            Util::printSemanticErrorInfo(token.lineNum, "b");
        } else {
            item.name = token.name;
            FuncDef::funcName = token.name;
        }
        token = Token::getNextToken();
    }
    item.scopeIndex = BlockTree::nowBlockIndex;

    //函数定义代码生成
    LlvmIRGenerator::getRegName(item, curFuncSymbol);
    LlvmIRGenerator::getRegType(item, false);
    LlvmIRGenerator::FuncDef(item);

    SymbolItem symbolItemTemp =  item;
    SymbolItem::initCurrentFuncSymbol(&symbolItemTemp);
    BlockTree::createBlockNode();

    token = Token::getNowToken();
    if (token.name == "(") {
        token = Token::getNextToken();
        Llvm::printLlvmCode("(");
        if (Parser::isBType(token)) {

            FuncFParams::funcFParamsParser(item);
//            for(int i = 0; i < item.paramNum; i++){
//                printf("%s %s\n", item.paramTypeList[i].c_str(), item.paramNameList[i].c_str());
//            }
//            LlvmIRConstructor::funcDeclConstructor(item.name, item.type, item.paramTypeList,item.paramNameList);
            BlockTree::nowBlockNode->parent->symbolTable->addSymbol(item);
            token = Token::getNowToken();
        }
        else{
            item.paramNum = 0;
            BlockTree::nowBlockNode->parent->symbolTable->addSymbol(item);
        }
        token = Token::getNowToken();
        if (token.name == ")") {
            Llvm::printLlvmCode(")");
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "j");
        }
    }
//    LlvmIRConstructor::funcDeclConstructor(item.name, item.type,item.paramTypeList,item.paramNameList);
    Llvm::printLlvmCode("{\n");
    curFuncSymbol->llvmIRStoreReg++;
    curFuncSymbol->paramTypeList = item.paramTypeList;
    curFuncSymbol->paramNameList = item.paramNameList;
    LlvmIRGenerator::FuncFParamAssign(curFuncSymbol,curFuncSymbol);

    Block::blockParser();

    if(curFuncSymbol->value.type == "void"){
        Llvm::printLlvmCode("return void");
    }

    token = Token::getNowToken();
    Util::printParserInfo("<FuncDef>");

    FuncDef::isInFunc = 0;
    FuncDef::funcName = "";
    FuncDef::isReturn = false;
    isInParam = false;
    if(isRepeat){
        BlockTree::nowBlockNode->symbolTable->deleteSymbol(item);
    }
    Llvm::printLlvmCode("}\n");
}

void FuncDef::funcDefInit() {
    FuncDef::isInFunc = false;
}
