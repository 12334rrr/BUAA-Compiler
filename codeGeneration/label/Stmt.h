/**
 *
 */

#ifndef COMPILER_STMT_H
#define COMPILER_STMT_H


#include <string>

class Stmt {
public:
    int scopeIndex = 0;
    int andCount = 0;
    int orCount = 0;

    std::string getAnd(int count){
        return "If_" + std::to_string(scopeIndex) + std::to_string(count) + ;
    }
};


#endif //COMPILER_STMT_H
