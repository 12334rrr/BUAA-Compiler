/**
 * LlvmIRConstructor.cpp
 * @brief The file that contains the definition of the class LlvmIRConstructor
 * @version 1.0
 * @date 2024-10-30
 * @Author  王春博
 */

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include "LlvmIRConstructor.h"
#include "Llvm.h"
#include "../../util/Util.h"

std::string LlvmIRConstructor::expString;
int LlvmIRConstructor::forNum = 0;
std::string LlvmIRConstructor::valName;

std::string llvmTypeConvert(const std::string &type) {
    if (type == "Int") {
        return "i32";
    } else if (type == "Char") {
        return "i8";
    } else if (type == "Void") {
        return "void";
    }
}

std::string llvmConstTypeConvert(const std::string &type) {
    if (type == "ConstInt" || type == "ConstIntArray") {
        return "i32";
    } else if (type == "ConstChar" || type == "ConstCharArray") {
        return "i8";
    } else if (type == "ConstVoid") {
        return "void";
    }
    return "";
}

void LlvmIRConstructor::valDeclGlobalConstructor(const std::string &varName, const std::string &varType,
                                                 const std::string &varValue) {
    if (varType == "Int") {
        Llvm::printLlvmCode("@" + varName + " = global i32 " + varValue);
    } else if (varType == "Char") {
        Llvm::printLlvmCode("@" + varName + " = global i8 " + varValue);
    } else {
        printf("全局变量类型错误\n");
    }
}

void LlvmIRConstructor::constValDeclGlobalConstructor(const std::string &constValName, const std::string &constValType,
                                                      const std::string &constValValue) {
    if (constValType == "ConstInt") {
        Llvm::printLlvmCode("@" + constValName + " = constant i32 " + constValValue);
    } else if (constValType == "ConstChar") {
        Llvm::printLlvmCode("@" + constValName + " = constant i8 " + constValValue);
    } else {
        printf("常量全局变量类型错误\n");
    }
}

void LlvmIRConstructor::varDeclLocalConstructor(const std::string &varName, const std::string &varType,
                                                const std::string &varValue) {
    if (varType == "Int") {
        Llvm::printLlvmCode("%" + varName + " = alloca i32, align 4");
        Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName);
    } else if (varType == "Char") {
        Llvm::printLlvmCode("%" + varName + " = alloca i8, align 1");
        Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName);
    } else {
        printf("局部变量类型错误\n");
    }
}

void LlvmIRConstructor::constVarDeclLocalConstructor(const std::string &constVarName, const std::string &constVarType,
                                                     const std::string &constVarValue) {
    if (constVarType == "ConstInt") {
        Llvm::printLlvmCode("%" + constVarName + " = alloca i32, align 4");
        Llvm::printLlvmCode("store i32 " + constVarValue + ", i32* %" + constVarName);
    } else if (constVarType == "ConstChar") {
        Llvm::printLlvmCode("%" + constVarName + " = alloca i8, align 1");
        Llvm::printLlvmCode("store i8 " + constVarValue + ", i8* %" + constVarName);
    } else {
        printf("常量局部变量类型错误\n");
    }
}

void
LlvmIRConstructor::constArrayDeclGlobalConstructor(const std::string &constValName, const std::string &constValType,
                                                   const std::vector<std::string> &constValValue, int arraySize) {
    Llvm::printLlvmCode("@" + constValName + " = constant [" + std::to_string(arraySize) + " x " +
                        llvmConstTypeConvert(constValType) + "] [");
    for (int i = 0; i < constValValue.size(); i++) {
        Llvm::printLlvmCode(llvmConstTypeConvert(constValType) + " " + constValValue[i]);
        if (i != constValValue.size() - 1) {
            Llvm::printLlvmCode(", ");
        }
    }
    Llvm::printLlvmCode("]");
}

void LlvmIRConstructor::constArrayDeclLocalConstructor(const std::string &constValName, const std::string &constValType,
                                                       const std::vector<std::string> &constValValue, int arraySize) {
    Llvm::printLlvmCode("%" + constValName + " = alloca [" + std::to_string(arraySize) + " x " +
                        llvmConstTypeConvert(constValType) + "], align 16");
//    Llvm::printLlvmCode("store [" + std::to_string(arraySize) + " x " + llvmConstTypeConvert(constValType) + "] [");
    for (int i = 0; i < constValValue.size(); i++) {
        Llvm::printLlvmCode("%" + constValName + "." + std::to_string(i) + " = getelementptr inbounds [" +
                            std::to_string(arraySize) + " x " + llvmConstTypeConvert(constValType) + "], [" +
                            std::to_string(arraySize) + " x " + llvmConstTypeConvert(constValType) + "]* %" + constValName +
                            ", "+llvmConstTypeConvert(constValType)+" 0," + llvmConstTypeConvert(constValType) + " " + std::to_string(i));
        Llvm::printLlvmCode("store " + llvmConstTypeConvert(constValType) + " " + constValValue[i] + ", " +
                            llvmConstTypeConvert(constValType) + "* %" + constValName + "." + std::to_string(i));
//        if (i != constValValue.size() - 1) {
//            Llvm::printLlvmCode(", ");
//        }
    }
//    Llvm::printLlvmCode("]");
//    Llvm::printLlvmCode("[" + std::to_string(arraySize) + " x " + llvmConstTypeConvert(constValType) + "] *%" +
//                        constValName);
}

void LlvmIRConstructor::arrayDeclGlobalConstructor(const std::string &arrayValName, std::string valType,
                                                   std::vector<std::string> valValue, int arraySize) {
    Llvm::printLlvmCode(
            "%" + arrayValName + " = alloca [" + std::to_string(arraySize) + " x " + llvmTypeConvert(valType) +
            "], align 16");
    Llvm::printLlvmCode("store [" + std::to_string(arraySize) + " x " + llvmConstTypeConvert(valType) + "] [");
    for (int i = 0; i < arraySize; i++) {
        Llvm::printLlvmCode(llvmConstTypeConvert(valType) + " " + valValue[i]);
        if (i != valValue.size() - 1) {
            Llvm::printLlvmCode(", ");
        }
    }
}

void LlvmIRConstructor::arrayDeclLocalConstructor(const std::string &arrayValueName, const std::string &arrayValueType,
                                                  std::vector<std::string> arrayValue, int arraySize) {
    Llvm::printLlvmCode(
            "%" + arrayValueName + " = alloca [" + std::to_string(arraySize) + " x " + llvmTypeConvert(arrayValueType) +
            "], align 16");
    Llvm::printLlvmCode("store [" + std::to_string(arraySize) + " x " + llvmTypeConvert(arrayValueType) + "] [");
    for (int i = 0; i < arraySize; i++) {
        Llvm::printLlvmCode(llvmTypeConvert(arrayValueType) + " " + arrayValue[i]);
        if (i != arrayValue.size() - 1) {
            Llvm::printLlvmCode(", ");
        }
    }
}

void LlvmIRConstructor::storeConstructor(const std::string &varName, const std::string &varValue,
                                         const std::string &varType) {
    printf("varType: %s\n", varType.c_str());
    Llvm::printLlvmCode("");
    Llvm::printLlvmCode(
            "store " + llvmConstTypeConvert(varType) + " " + varValue + " , " + llvmConstTypeConvert(varType) + "* %" +
            varName);
}

void LlvmIRConstructor::assignConstruct(const std::string &varName, const std::string &varType,
                                        const std::string &varValue) {
    if (varType == "Int") {
        Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName);
    } else if (varType == "Char") {
        Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName);
    }
}

void LlvmIRConstructor::addConstructor(const std::string &varName, const std::string &firstOperand,
                                       const std::string &secondOperand) {
    Llvm::printLlvmCode("%" + varName + " = add i32 " + firstOperand + ", " + secondOperand);
}

void LlvmIRConstructor::subConstructor(const std::string &varName, const std::string &firstOperand,
                                       const std::string &secondOperand) {
    Llvm::printLlvmCode("%" + varName + " = sub i32 " + firstOperand + ", " + secondOperand);
}

void LlvmIRConstructor::mulConstructor(const std::string &varName, const std::string &firstOperand,
                                       const std::string &secondOperand) {
    Llvm::printLlvmCode("%" + varName + " = mul i32 " + firstOperand + ", " + secondOperand);
}

void LlvmIRConstructor::divConstructor(const std::string &varName, const std::string &firstOperand,
                                       const std::string &secondOperand) {
    Llvm::printLlvmCode("%" + varName + " = sdiv i32 " + firstOperand + ", " + secondOperand);
}

void LlvmIRConstructor::modConstructor(const std::string &varName, const std::string &firstOperand,
                                       const std::string &secondOperand) {
    Llvm::printLlvmCode("%" + varName + " = srem i32 " + firstOperand + ", " + secondOperand);
}

int precedence(const std::string &op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/" || op == "%") return 2;
    return 0;
}

bool isOperator(const char &op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%';
}


void LlvmIRConstructor::expConstructor(const std::string &exp) {
    printf("LlvmIRConstructor::expConstructor exp: %s\n", exp.c_str());
    int tempNum = 0;
    std::stack<std::string> opStack = std::stack<std::string>();
    std::stack<std::string> numStack = std::stack<std::string>();
    printf("exp: %s\n", exp.c_str());
    for (int i = 0; i < exp.size(); i++) {
        if (isspace(exp[i])) {
            continue;
        } else if (isdigit(exp[i])) {
            int num = 0;
            while (isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            i--; // 调整索引
            numStack.push(std::to_string(num));
        } else if (Util::isIdentItem(exp[i])) {
            std::string varName;
            while (Util::isIdentItem(exp[i])) {
                varName += exp[i++];
            }
            i--; // 调整索引
            numStack.push(varName);
        } else if (exp[i] == '(') {
            opStack.emplace("(");
        } else if (exp[i] == ')') {
            while (!opStack.empty() && opStack.top() != "(") {
                processOperator(numStack, opStack.top(), tempNum++);
                opStack.pop();
            }
            if (!opStack.empty()) {
                opStack.pop(); // 弹出 '('
            }
        } else if (isOperator(exp[i])) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(std::string(1, exp[i]))) {
                processOperator(numStack, opStack.top(), tempNum++);
                opStack.pop();
            }
            opStack.emplace(1, exp[i]);
        }
    }
    while (!opStack.empty()) {
        processOperator(numStack, opStack.top(), tempNum++);
        opStack.pop();
    }
    expString = numStack.top();
}


void LlvmIRConstructor::processOperator(std::stack<std::string> &numStack, std::string &op, int tempNum) {
    std::string secondOperand = numStack.top();
    numStack.pop();
    std::string firstOperand = numStack.top();
    numStack.pop();
    std::string varName = "temp" + std::to_string(tempNum++);
    if (op == "+") {
        addConstructor(varName, firstOperand, secondOperand);
    } else if (op == "-") {
        subConstructor(varName, firstOperand, secondOperand);
    } else if (op == "*") {
        mulConstructor(varName, firstOperand, secondOperand);
    } else if (op == "/") {
        divConstructor(varName, firstOperand, secondOperand);
    } else if (op == "%") {
        modConstructor(varName, firstOperand, secondOperand);
    }
    numStack.push(varName);
}

void
LlvmIRConstructor::defArrayByIndex(const std::string &varName, const std::string &varType, const std::string &index,
                                   const std::string &varValue, int arraySize) {
    if (varType == "IntArray") {
        Llvm::printLlvmCode("%" + varName + "." + index + " = getelementptr inbounds [" + " x i32], [" + index +
                            " x i32]* %" + varName + ", i32 0, i32 " + index);
        Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName + "." + index);
    } else if (varType == "CharArray") {
        Llvm::printLlvmCode("%" + varName + "." + index + " = getelementptr inbounds [" + index + " x i8], [" + index +
                            " x i8]* %" + varName + ", i32 0, i32 " + index);
        Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName + "." + index);
    } else if (varType == "Int") {
        Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName);
    } else if (varType == "Char") {
        Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName);
    }
}

void LlvmIRConstructor::varDeclConstructor(const std::string &varName, const std::string &varType,
                                           const std::string &varValue, int arraySize, int index) {
    if (varType.find("Array") == std::string::npos) {
        if (varType == "Int") {
            Llvm::printLlvmCode("@" + varName + " = alloca i32, align 4");
            Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName);
        } else if (varType == "Char") {
            Llvm::printLlvmCode("@" + varName + " = alloca i8, align 1");
            Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName);
        }
    } else {
        if (varType == "IntArray") {
            Llvm::printLlvmCode("%" + varName + "." + std::to_string(index) + " = alloca i32, align 4");
            Llvm::printLlvmCode("store i32 0, i32* %" + varName + "." + std::to_string(index));
        } else if (varType == "CharArray") {
            Llvm::printLlvmCode("%" + varName + "." + std::to_string(index) + " = alloca i8, align 1");
            Llvm::printLlvmCode("store i8 0, i8* %" + varName + "." + std::to_string(index));
        }
    }
}

void
LlvmIRConstructor::defArrayByIndex(const std::string &varName, const std::string &varType, const std::string &index,
                                   const std::string &varValue) {
    if (varType == "IntArray") {
        Llvm::printLlvmCode("%" + varName + "." + index + " = getelementptr inbounds [" + " x i32], [" + index +
                            " x i32]* %" + varName + ", i32 0, i32 " + index);
        Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName + "." + index);
    } else if (varType == "CharArray") {
        Llvm::printLlvmCode("%" + varName + "." + index + " = getelementptr inbounds [" + index + " x i8], [" + index +
                            " x i8]* %" + varName + ", i32 0, i32 " + index);
        Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName + "." + index);
    } else if (varType == "Int") {
        Llvm::printLlvmCode("store i32 " + varValue + ", i32* %" + varName);
    } else if (varType == "Char") {
        Llvm::printLlvmCode("store i8 " + varValue + ", i8* %" + varName);
    }
}

std::string funcTypeCovert(const std::string &funcType) {
    if (funcType == "IntFunc") {
        return "i32";
    } else if (funcType == "CharFunc") {
        return "i8";
    } else if (funcType == "VoidFunc") {
        return "void";
    }
}

void LlvmIRConstructor::funcDeclConstructor(const std::string &funcName, const std::string &returnType,
                                            std::vector<std::string> paramsType, std::vector<std::string> paramsName) {
    printf("%s\n", funcName.c_str());
    std::string llvm_returnType = funcTypeCovert(SymbolTable::getSymbolItem(funcName).type);
    Llvm::printLlvmCode("define " + llvm_returnType + " @" + funcName + "(");
    for (int i = 0; i < paramsType.size(); i++) {
        Llvm::printLlvmCode(llvmTypeConvert(paramsType[i]) + " %" + paramsName[i]);
        if (i != paramsType.size() - 1) {
            Llvm::printLlvmCode(", ");
        }
    }
    Llvm::printLlvmCode(") {");
    Llvm::printLlvmCode("entry:");
}

void LlvmIRConstructor::retConstructor(const std::string &funcType) {
    std::cout << "funcType: " << funcType << std::endl;
    std::string llvm_returnType = funcTypeCovert(funcType);
    Llvm::printLlvmCode("ret " + llvm_returnType + " " + expString);
}

void LlvmIRConstructor::funcCallConstructor(const std::string &funcName, std::vector<std::string> paramsTypeList,
                                            std::vector<std::string> paramsNameList) {
    std::string llvm_returnType = funcTypeCovert(SymbolTable::getSymbolItem(funcName).type);
    Llvm::printLlvmCode("call " + llvm_returnType + " @" + funcName + "(");
    for (int i = 0; i < paramsTypeList.size(); i++) {
        Llvm::printLlvmCode(llvmTypeConvert(paramsTypeList[i]) + " %" + paramsNameList[i]);
        if (i != paramsTypeList.size() - 1) {
            Llvm::printLlvmCode(", ");
        }
    }
    Llvm::printLlvmCode(")");
}

void LlvmIRConstructor::mainConstructor() {
    Llvm::printLlvmCode("define i32 @main() {");
}
//void LlvmIRConstructor::un(std::string cond,std::string ){
//    Llvm::printLlvmCode("cond"+std::to_string(forNum)+":");
//}
//void LlvmIRConstructor::condConstructor(const std::string& condString){
//    for(int i= 0;i<condString.size();i++){
//
//    }
//}
//void LlvmIRConstructor::forConstructor(std::string cond,std::string ){
//    Llvm::printLlvmCode("cond"+std::to_string(forNum)+":");
//
//}
//void LlvmIRConstructor::ifConstructor(std::string cond){
//    Llvm::printLlvmCode("br i1 "+cond+", label %if"+std::to_string(forNum)+", label %if"+std::to_string(forNum+1));
//    Llvm::printLlvmCode("if"+std::to_string(forNum)+":");
//}