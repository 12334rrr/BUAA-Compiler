/**
 * @file LlvmIRConstructor.h
 * @brief The file that contains the declaration of the class LlvmIRConstructor
 * @version 1.0
 * @date 2024-10-30
 * @Author  王春博
 */
#ifndef COMPILER_LLVMIRCONSTRUCTOR_H
#define COMPILER_LLVMIRCONSTRUCTOR_H
#include <vector>
#include <stack>
#include <string>

class LlvmIRConstructor {
public:
    static int forNum;
    static std::string uniqueString;
    static std::string valName;
public:
    static void varDeclConstructor(const std::string &varName, const std::string &varType, const std::string &varValue,
                            int arraySize);
    static std::string expString;

    static void assignConstruct(const std::string &varName, const std::string &varType, const std::string &varValue);

    static void addConstructor(const std::string &varName, const std::string &firstAddend, const std::string &secondAddend);

    static void subConstructor(const std::string &varName, const std::string &firstAddend, const std::string &secondAddend);

    static void mulConstructor(const std::string &varName, const std::string &firstAddend, const std::string &secondAddend);

    static void divConstructor(const std::string &varName, const std::string &firstAddend, const std::string &secondAddend);

    static void modConstructor(const std::string &varName, const std::string &firstOperand, const std::string &secondOperand);

    static void expConstructor(const std::string &exp);

    static void processOperator(std::stack<std::string> &numStack, std::string &op, int tempNum);

    static void defArrayByIndex(const std::string &varName, const std::string &varType, const std::string &index,
                         const std::string &varValue);

    static void varDeclConstructor(const std::string &varName, const std::string &varType, const std::string &varValue,
                       int arraySize,int index);

    static void defArrayByIndex(const std::string &varName, const std::string &varType, const std::string &index,
                         const std::string &varValue, int arraySize);

    static void funcDeclConstructor(const std::string& funcName, const std::string& returnType, std::vector<std::string> paramsType,
                             std::vector<std::string> paramsName);

    static void retConstructor(const std::string& exp);

    static void retConstructor(const std::string &exp, const std::string &funcType);

    static void funcCallConstructor(const std::string &funcName, std::vector<std::string> paramsTypeList,
                             std::vector<std::string> paramsNameList);

    static void mainConstructor();

    static void storeConstructor(const std::string& varName, const std::string& varValue);

    static void storeConstructor(const std::string &varName, const std::string &varValue, const std::string& varType);

    static void constValDeclGlobalConstructor(const std::string& constValName, const std::string& constValType, const std::string& constValValue);

    static void valDeclGlobalConstructor(const std::string& varName, const std::string& varType, const std::string& varValue);

    static void varDeclLocalConstructor(const std::string &varName, const std::string &varType, const std::string &varValue);

    static void constVarDeclLocalConstructor(const std::string &constVarName, const std::string &constVarType,
                                      const std::string &constVarValue);

    static void constArrayDeclGlobalConstructor(const std::string &constValName, const std::string &constValType,
                                         const std::vector<std::string> &constValValue, int arraySize);

    static void constArrayDeclLocalConstructor(const std::string &constValName, const std::string &constValType,
                                        const std::vector<std::string> &constValValue, int arraySize);

    static void
    arrayDeclGlobalConstructor(const std::string& valName, std::string valType, std::vector<std::string> valValue,
                               int arraySize);

    static void
    arrayDeclLocalConstructor(const std::string& arrayValueName, const std::string& arrayValueType,
                              std::vector<std::string> arrayValue,
                              int arraySize);
};


#endif //COMPILER_LLVMIRCONSTRUCTOR_H
