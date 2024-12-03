/**
 * ConstDef.cpp -- Parse const definition
 * @Author  王春博
 */

#include "ConstDef.h"
#include "../../token/Token.h"
#include "../expression/unaryexp/ConstExp.h"
#include "../../util/Util.h"
#include "ConstInitVal.h"
#include "../../symbolTable/blockTree/BlockTree.h"
#include "../../codeGeneration/llvm/LlvmIRConstructor.h"
#include "../../codeGeneration/llvm/constVarInfo.h"
#include "../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../util/Constants.h"

//extern SymbolItem* currentFuncSymbol;
int ConstDef::constVal = 0;
int ConstDef::constArraySize = 0;

void ConstDef::constDefParser(std::vector<SymbolItem>& itemList, const std::string& type) {
    std::vector<Value> valueList;
    ConstDef::constArraySize = 1;
    bool isRepeat = false;
    SymbolItem symbolItem = SymbolItem();
    symbolItem.type = type;
    SymbolTable *symbolTable = BlockTree::nowBlockNode->symbolTable;
    tokenItem token = Token::getNowToken();
    if(token.type == "IDENFR"){
        if(symbolTable->isSymbolPresent(token.name)|| SymbolTable::isFunc(token.name)){
            Util::printSemanticErrorInfo(token.lineNum,"b");
            isRepeat = true;
        }
        else{
            symbolItem.name = token.name;
            LlvmIRConstructor::valName = token.name;
            itemList.emplace_back(token.name);
        }
        token = Token::getNextToken();
    }
    if(token.name == "["){
        itemList.at(itemList.size()-1).type = "Array";
        symbolItem.type += "Array";
        token = Token::getNextToken();
        Value value = ConstExp::constExpParser();
//        itemList.at(itemList.size()-1).arraySize = ConstExp::constExpValue;
          itemList.at(itemList.size()-1).arraySize = std::stoi(value.name);
        ConstDef::constArraySize = ConstExp::constExpValue;
//        printf("%d\n",ConstExp::constExpValue);
        token = Token::getNowToken();
        if(token.name == "]"){
            token = Token::getNextToken();
        }
        else{
            Util::printErrorInfo(token.lineNum,"k");
        }
    }
    symbolItem.scopeIndex = BlockTree::nowBlockIndex;
    //常量定义代码生成
    LlvmIRGenerator::getRegName(symbolItem,curFuncSymbol);
    LlvmIRGenerator::getRegType(symbolItem,false);
    LlvmIRGenerator::varDef(symbolItem);

    ConstExp::constExpTypeString = symbolItem.type;
    token = Token::getNowToken();
    if(token.name == "="){
        token = Token::getNextToken();
    }
    std::vector<std::string> varValueList;
    valueList = ConstInitVal::constInitValParser();

    LlvmIRGenerator::varInit(symbolItem,valueList,curFuncSymbol);

    Util::printParserInfo("<ConstDef>");
    if(!isRepeat){
        symbolItem.scopeIndex = BlockTree::nowBlockIndex;
        if(symbolItem.type.find("Array") != std::string::npos){
            for(int i : ConstInitVal::constInitValValueList){
                symbolItem.arrayValueList.push_back(i);
                varValueList.push_back(std::to_string(i));
            }
        }
        BlockTree::nowBlockNode->symbolTable->addSymbol(symbolItem);
    }
    bool isGlobal = BlockTree::nowBlockNode->blockIndex == 1;
    bool isArray = symbolItem.type.find("Array") != std::string::npos;
//    constVarInfo constVarInfo1 = constVarInfo(symbolItem.name + "_" + std::to_string(symbolItem.scopeIndex),symbolItem.type,std::to_string(symbolItem.value),varValueList,isArray,isGlobal,symbolItem.arraySize);
//    constVarInfo1.codeGeneration();
}