//
// Created by hp on 2024/11/26.
//

#ifndef COMPILER_VALUE_H
#define COMPILER_VALUE_H


#include <string>

class Value {
public:
    std::string type;
    std::string numValue;
    bool isNum = false;
    std::string name;
    Value(std::string name1, std::string type1, bool isNum1) : name(std::move(name1)), type(std::move(type1)),
    isNum(isNum1) {}
    Value() = default;
};


#endif //COMPILER_VALUE_H
