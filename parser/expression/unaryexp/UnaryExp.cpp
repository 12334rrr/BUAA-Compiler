/**
 * @file UnaryExp.cpp
 * @brief UnaryExp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "UnaryExp.h"
#include "../../../token/Token.h"
#include "../../../util/Util.h"
#include "../multiexp/PrimaryExp.h"
#include "../../function/FuncRParams.h"
#include "../../Parser.h"
#include "../../../codeGeneration/llvm/LlvmIRConstructor.h"
#include "../../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "Exp.h"
#include "../../../util/Constants.h"
#include<fstream>

Value UnaryExp::unaryExpParser() {
    Token::lookAhead(1);
    Value value;
    tokenItem token = Token::getNowToken();
    tokenItem tmp = Token::getNowToken();
    if(Util::isUnaryOperator(token.name)){
        token = Token::getNextToken();
        Util::printParserInfo("<UnaryOp>");
        value = UnaryExp::unaryExpParser();
        token = Token::getNowToken();
        Exp::expType = "Int";
        value = LlvmIRGenerator::UnaryOp(tmp.name,value,curFuncSymbol);
    }
    else if(token.type == "IDENFR" && Token::lookAheadList[0].name == "("){
        std::string string = SymbolTable::getSymbolItem(token.name).type;
        SymbolItem symbolItem = SymbolItem();
        SymbolItem symbolItem1 = SymbolTable::getSymbolItem(token.name);
        SymbolItem *symbolItemPtr = SymbolTable::getSymbolItemPtr(token.name);
        std::string funcName = token.name;
        int lineNum = token.lineNum;
        std::vector<Value> valueList;
        if(!SymbolTable::isSymbolExist(token.name)){
            Util::printSemanticErrorInfo(token.lineNum, "c");
        }
        else{
            symbolItem = SymbolTable::getSymbolItem(token.name);
        }
        token = Token::getNextToken();
        if(token.name == "("){
            token = Token::getNextToken();
            if(Parser::isUnaryExp(token)){
                valueList = FuncRParams::funcRParamsParser(symbolItem,lineNum);
                token = Token::getNowToken();
            }
            else{
                if(symbolItem.paramNum != 0){
                    Util::printErrorInfo(token.lineNum, "d");
                }
            }
            if(token.name == ")"){
                token = Token::getNextToken();
            }
            else{
                Util::printErrorInfo(token.lineNum,"j");
            }
        }
        if(string == "CharFunc"){
            Exp::expType = "Char";
        }
        else if(string == "IntFunc"){
            Exp::expType = "Int";
        }
//        LlvmIRConstructor::funcCallConstructor(funcName,FuncRParams::funcRParamsTypeList,FuncRParams::funcRParamsNameList);
        if(symbolItemPtr){
            value = LlvmIRGenerator::FuncCall(symbolItemPtr,valueList,curFuncSymbol);
        }
    }
    else{
        value = PrimaryExp::primaryExpParser();
        token = Token::getNowToken();
    }
    Util::printParserInfo("<UnaryExp>");
    return value;
}
