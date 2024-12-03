/**
 * @file LlvmIRGenerator.h
 */


#ifndef COMPILER_LLVMIRGENERATOR_H
#define COMPILER_LLVMIRGENERATOR_H


#include "../../symbolTable/SymbolItem.h"

class LlvmIRGenerator {
public:
    static void FuncDef(const SymbolItem &symbolItem);

    static void varDef(const SymbolItem& symbolItem);

    static void varInit(SymbolItem &symbolItem, std::vector<Value> &valueList, SymbolItem *context);

    static void varAssign(SymbolItem *symbolItem, Value &value, SymbolItem *context);

    static Value allocReg(std::string type, SymbolItem *context);

    static void Op(const std::string &op, const Value &result, const Value &value1, const Value &value2);

    static Value AddOrSubOp(std::string &op, Value &value1, Value &value2, SymbolItem *context);

    static Value MulOrDivOp(std::string &op, Value &value1, Value &value2, SymbolItem *context);

    static Value PerformOperation(std::string &op, Value &value1, Value &value2, SymbolItem *context);

    static std::string CalculateNumericOperation(const std::string &op, int val1, int val2);

    static void ConvertIfNeeded(Value &value, SymbolItem *context);

    static Value FuncCall(SymbolItem *funcSymbolItem, std::vector<Value> &valueList, SymbolItem *context);

    static Value LVal(SymbolItem *symbolItem, Value &value1, bool isLoal, SymbolItem *context);

    static Value LValArray(SymbolItem *symbolItem, Value &value, bool &isLoad, SymbolItem *context);

    static std::vector<Value> stringConst(const std::string &str);

    static void returnStmt(Value &value, SymbolItem *context);

    static void printStmt(const std::string &str, std::vector<Value> &valueList, SymbolItem *context);

    static Value UnaryOp(std::string &op, Value &value, SymbolItem *context);

    static void AddIOFunc();

    static void getRegType(SymbolItem &symbolItem, bool isFuncParam);

    static void getRegName(SymbolItem &symbolItem, SymbolItem *context);

    static void FuncFParam(SymbolItem &symbolItem);

    static void FuncFParamAssign(SymbolItem *funcSymbol, SymbolItem *context);

    static std::string DePtr(const std::string &type);

    static std::string AddPtr(const std::string &type);

    static Value readStmt(std::string &func, SymbolItem *context);

    static void addLlvmIRConde(const std::string &str);
};


#endif //COMPILER_LLVMIRGENERATOR_H
