//
// Created by hp on 2024/11/25.
//

#ifndef COMPILER_CONSTVARINFO_H
#define COMPILER_CONSTVARINFO_H


#include <string>
#include <vector>

class constVarInfo {
public:
    std::string constVarName;
    std::string constVarType;
    std::string constVarValue;
    std::vector<std::string> constVarValueList;
    bool isArray;
    bool isGlobal;
    int arraySize;
public:
    constVarInfo(std::string constVarName, std::string constVarType, std::string constVarValue, std::vector<std::string> varValueList,bool isArray, bool isGlobal, int arraySize);
    void codeGeneration() const;
};


#endif //COMPILER_CONSTVARINFO_H
