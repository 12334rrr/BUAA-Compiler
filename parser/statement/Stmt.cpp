/**
 * @file Stmt.cpp
 * @brief 语句类
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */

#include "Stmt.h"
#include "../../util/Util.h"
#include "Block.h"
#include "../expression/unaryexp/Cond.h"
#include "ForStmt.h"
#include "../Parser.h"
#include "../expression/unaryexp/Exp.h"
#include "../expression/unaryexp/Lval.h"
#include "../function/FuncDef.h"
#include "../function/MainFuncDef.h"
#include "../../codeGeneration/llvm/LlvmIRGenerator.h"
#include "../../util/Constants.h"

int Stmt::loopNum = 0;
int Stmt::isInIf = 0;
int Stmt::inInFor = 0;

void Stmt::stmtParser() {
    Value value;
    tokenItem token = Token::getNowToken();
    Token::lookAhead(1);
    if (token.name == "{") {
        Block::blockParser();
        token = Token::getNowToken();
    } else if (token.name == ";") {
        token = Token::getNextToken();
    } else if (token.type == "IFTK") {
        Stmt::isInIf++;
        token = Token::getNextToken();
        if (token.name == "(") {
            token = Token::getNextToken();
            Cond::condParser();
            token = Token::getNowToken();
            if (token.name == ")") {
                token = Token::getNextToken();
            } else {
                Util::printErrorInfo(token.lineNum, "j");
            }
            Stmt::stmtParser();
            token = Token::getNowToken();
            if (token.type == "ELSETK") {
                token = Token::getNextToken();
                Stmt::stmtParser();
                token = Token::getNowToken();
            }
        }
        Stmt::isInIf--;
    } else if (token.type == "FORTK") {
        Stmt::inInFor++;
        Stmt::loopNum++;
        token = Token::getNextToken();
        if (token.name == "(") {
            token = Token::getNextToken();
        }
        if (token.type == "IDENFR") {
            ForStmt::forStmtParser();
            token = Token::getNowToken();
        }
        if (token.name == ";") {
            token = Token::getNextToken();
        }
        if (Parser::isUnaryExp(token)) {
            Cond::condParser();
            token = Token::getNowToken();
        }
        if (token.name == ";") {
            token = Token::getNextToken();
        }
        if (token.type == "IDENFR") {
            ForStmt::forStmtParser();
            token = Token::getNowToken();
        }
        if (token.name == ")") {
            token = Token::getNextToken();
        }
        Stmt::stmtParser();
        Stmt::loopNum--;
        Stmt::inInFor--;
    } else if (token.type == "BREAKTK" || token.type == "CONTINUETK") {
        if(Stmt::loopNum == 0) {
            Util::printSemanticErrorInfo(token.lineNum, "m");
        }
        token = Token::getNextToken();
        if (token.name == ";") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "i");
        }
    } else if (token.name == "return") {
        int lineNum = token.lineNum;
        token = Token::getNextToken();
        if(FuncDef::isInFunc != 0 && SymbolTable::getSymbolItem(FuncDef::funcName).type == "VoidFunc" && token.name != ";"){
            Util::printSemanticErrorInfo(lineNum, "f");
        }
        std::string funcType = SymbolTable::getSymbolItem(FuncDef::funcName).type == ""? "IntFunc" : SymbolTable::getSymbolItem(FuncDef::funcName).type;
        if (Parser::isUnaryExp(token)) {
            value = Exp::expParser();
            std::string exp = Exp::expString;
            token = Token::getNowToken();
        }
        LlvmIRGenerator::returnStmt(value, curFuncSymbol);
        token = Token::getNowToken();
        if (token.name == ";") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "i");
        }
        if(FuncDef::isInFunc == 1 && token.name == "}" && Stmt::isInIf == 0 && Stmt::inInFor == 0){
            FuncDef::isReturn = true;
        }
        if(MainFuncDef::isInMainDef && token.name == "}" && MainFuncDef::mainNestingLevel == 1 && Stmt::isInIf == 0 && Stmt::inInFor == 0){
            MainFuncDef::isMainReturn = true;
        }
//        LlvmIRConstructor::retConstructor(funcType);
    } else if (token.name == "printf") {
        std::string  str;
        int formatSpecifierNum = 0,formatSpecifierParamNum = 0 ,lineNum = token.lineNum;
        token = Token::getNextToken();
        if (token.name == "(") {
            token = Token::getNextToken();
            if (token.type == "STRCON") {
                str = token.name;
                formatSpecifierNum = Stmt::calFormatSpecifierNum(token.name);
                token = Token::getNextToken();
            }
            std::vector<Value> valueList;
            while (token.name == ",") {
                formatSpecifierParamNum++;
                token = Token::getNextToken();
                value = Exp::expParser();
                token = Token::getNowToken();
                valueList.push_back(value);
            }
            if(formatSpecifierNum != formatSpecifierParamNum){
                Util::printSemanticErrorInfo(lineNum, "l");
            }

            LlvmIRGenerator::printStmt(str, valueList, curFuncSymbol);
            if (token.name == ")") {
                token = Token::getNextToken();
            } else {
                Util::printErrorInfo(token.lineNum, "j");
            }
        }
        if (token.name == ";") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "i");
        }
    } else if (token.type == "IDENFR" && Token::lookAheadList[0].name != "(" && Util::isExistEQL()) {
        tokenItem tokenTemp = Token::getNowToken();
        token = Token::getNowToken();
        SymbolItem symbolItem = SymbolTable::getSymbolItem(token.name);
//        SymbolTable::printAllSymbolInfo();
        SymbolItem *symbolItemPtr = SymbolTable::getSymbolItemPtr(token.name);
        Lval::lvalParser(false);
        token = Token::getNowToken();
        tokenTemp = Token::getNowToken();
        if (token.name == "=") {
            if(SymbolTable::getSymbolItem(tokenTemp.name).type.find("Const") != std::string::npos){
                Util::printSemanticErrorInfo(tokenTemp.lineNum, "h");
            }
            token = Token::getNextToken();
        }
        if (token.type == "GETINTTK" || token.type == "GETCHARTK") {
            value = LlvmIRGenerator::readStmt(token.name, curFuncSymbol);
            token = Token::getNextToken();
            if (token.name == "(") {
                token = Token::getNextToken();
            }
            if (token.name == ")") {
                token = Token::getNextToken();
            } else {
                Util::printErrorInfo(token.lineNum, "j");
            }
            LlvmIRGenerator::varAssign(symbolItemPtr, value, curFuncSymbol);
        }
        else if (Parser::isUnaryExp(Token::getNowToken())) {
            value = Exp::expParser();
            token = Token::getNowToken();
            LlvmIRGenerator::varAssign(symbolItemPtr, value, curFuncSymbol);
        }
        token = Token::getNowToken();
        if (token.name == ";") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "i");
        }
    } else {
        Exp::expParser();
        token = Token::getNowToken();
        if (token.name == ";") {
            token = Token::getNextToken();
        } else {
            Util::printErrorInfo(token.lineNum, "i");
        }
    }
    Util::printParserInfo("<Stmt>");
}

bool Stmt::isStmt(const tokenItem &token) {
    std::string type = token.type;
    return type == "IDENFR" || type == "IFTK" || type == "FORTK" || type == "BREAKTK" ||
           type == "CONTINUETK" || type == "RETURNTK" || type == "PRINTFTK"
           || token.name == "{" || token.name == ";" || Parser::isUnaryExp(token);
}

int Stmt::calFormatSpecifierNum(const std::string &string) {
    int count = 0;
    // 遍历字符串
    for (size_t i = 0; i < string.size(); ++i) {
        // 检查当前字符是否为 '%'
        if (string[i] == '%' && i + 1 < string.size()) {
            // 判断下一个字符是否是 'd' 或 'c'
            if (string[i + 1] == 'd' || string[i + 1] == 'c') {
                ++count;
                ++i; // 跳过已处理的 'd' 或 'c'
            }
        }
    }
    return count;
}
