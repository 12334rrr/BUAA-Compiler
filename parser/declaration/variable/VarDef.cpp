/**
 * File: VarDef.cpp
 * @brief 变量定义类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "VarDef.h"

#include <utility>
#include "../../Parser.h"
#include "../../expression/unaryexp/ConstExp.h"
#include "../../../util/Util.h"
#include "InitVal.h"
#include "../../../symbolTable/blockTree/BlockTree.h"
#include "../../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../../util/Constants.h"

void VarDef::varDefParser(std::vector<SymbolItem> &itemList,std::string type) {
    std::vector<Value> valueList;
    SymbolItem symbolItem = SymbolItem();
    symbolItem.scopeIndex = BlockTree::nowBlockIndex;
    symbolItem.type = std::move(type);
    bool isRepeat = false;
    tokenItem token = Token::getNowToken();
    if (token.type == "IDENFR") {
        if(BlockTree::nowBlockNode->symbolTable->isSymbolPresent(token.name) /*|| SymbolTable::isFunc(token.name)*/){
            Util::printSemanticErrorInfo(token.lineNum, "b");
            isRepeat = true;
        } else {
            symbolItem.name = token.name;
            itemList.emplace_back(token.name);
        }
        token = Token::getNextToken();
    }
    if (token.name == "[") {
        if(!isRepeat) {
            itemList.at(itemList.size() - 1).type = "Array";
            symbolItem.type += "Array";
        }
        token = Token::getNextToken();
        Value value = ConstExp::constExpParser();
        symbolItem.arraySize = std::stoi(value.name);
        token = Token::getNowToken();
        if (token.name == "]") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "k");
        }
    }

    //变量定义代码生成
    LlvmIRGenerator::getRegName(symbolItem, curFuncSymbol);
    LlvmIRGenerator::getRegType(symbolItem, false);
    LlvmIRGenerator::varDef(symbolItem);


    if(token.name == "="){
        token = Token::getNextToken();
        valueList = InitVal::initValParser(symbolItem.name, symbolItem.type);
    }
    //变量初始化
    LlvmIRGenerator::varInit(symbolItem, valueList, curFuncSymbol);

    Util::printParserInfo("<VarDef>");
    if(!isRepeat) {
        symbolItem.scopeIndex = BlockTree::nowBlockIndex;
        BlockTree::nowBlockNode->symbolTable->addSymbol(symbolItem);
    }
    for(auto &item : InitVal::arrayValue){
        printf("%s\n", item.c_str());
    }
}
