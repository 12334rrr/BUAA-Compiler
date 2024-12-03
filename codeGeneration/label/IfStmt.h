//
// Created by hp on 2024/12/3.
//

#ifndef COMPILER_IFSTMT_H
#define COMPILER_IFSTMT_H


#include <string>

class IfStmt {
public:
    int scopeIndex = 0;
    int andCount = 0;
    int orCount = 0;
    std::string condStr;
    std::string elseStr;
    std::string endStr;

    std::string getAnd(int count){
        return "If.condAnd" + std::to_string(count) + ;
    }

    std::string getOr(int count){
        return "If.condOr" + std::to_string(count) + ;
    }
};


#endif //COMPILER_IFSTMT_H
