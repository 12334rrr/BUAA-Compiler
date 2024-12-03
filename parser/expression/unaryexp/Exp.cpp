/**
 * @file Exp.cpp
 * @brief Exp class
 * @version 1.0
 * @date 2024-10-03
 * @Author  王春博
 */
#include "Exp.h"
#include "../multiexp/AddExp.h"
#include "../../../util/Util.h"
#include "../../../codeGeneration/llvm/LlvmIRConstructor.h"
#include "../../../token/Token.h"

std::string Exp::expType;
std::string Exp::expString;
void printExpInfo() {
    printf("expType: %s expString: %s\n", Exp::expType.c_str(), Exp::expString.c_str());
}
void expInit() {
    Exp::expType = "";
    Exp::expString = "";
}
static int loopNum =0;
Value Exp::expParser() {
//    loopNum++;
//    expInit();
//    if(loopNum == 1){
//        for(int i = Token::tokenIndex; i < Token::tokenList.size(); i++) {
//            if(Token::tokenList[i].name == ";" || Token::tokenList[i].name == "," ||  Token::tokenList[i].name == "}"){
//                break;
//            }
//            Exp::expString += Token::tokenList[i].name;
//        }
//    }
    Value value = AddExp::addExpParser();
    Util::printParserInfo("<Exp>");
    return value;
}