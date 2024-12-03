#include "constVarInfo.h"
#include "LlvmIRConstructor.h"
#include "../../parser/def/ConstDef.h"

#include <utility>
#include<string>
constVarInfo::constVarInfo(std::string constVarName, std::string constVarType, std::string constVarValue,
                           std::vector<std::string> varValueList, bool isArray, bool isGlobal, int arraySize) {
    this->constVarName = std::move(constVarName);
    this->constVarType = std::move(constVarType);
    this->constVarValue = std::move(constVarValue);
    this->isArray = isArray;
    this->isGlobal = isGlobal;
    this->arraySize = arraySize;
    this->constVarValueList = std::move(varValueList);
}
void constVarInfo::codeGeneration() const{
    if (isGlobal) {
        if (isArray) {
            LlvmIRConstructor::constArrayDeclGlobalConstructor(constVarName, constVarType, constVarValueList, ConstDef::constArraySize);
        } else {
            LlvmIRConstructor::constValDeclGlobalConstructor(constVarName, constVarType, constVarValue);
        }
    } else {
        if (isArray) {
            LlvmIRConstructor::constArrayDeclLocalConstructor(constVarName, constVarType, constVarValueList, ConstDef::constArraySize);
        } else {
            LlvmIRConstructor::constVarDeclLocalConstructor(constVarName, constVarType, constVarValue);
        }
    }
}