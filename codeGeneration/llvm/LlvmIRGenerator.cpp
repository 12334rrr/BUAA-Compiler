

#include <fstream>
#include <map>
#include <utility>
#include "LlvmIRGenerator.h"
#include "Llvm.h"
#include "../../symbolTable/SymbolTable.h"

std::ofstream file("llvm_ir.txt", std::ios::app); // 追加模式

void LlvmIRGenerator::addLlvmIRConde(const std::string &str) {
    file << str;
}

std::string typeConvert(SymbolItem symbolItem) {
    if (symbolItem.type == "Int" || symbolItem.type == "ConstInt" || symbolItem.type == "IntFunc") {
        symbolItem.type = "i32";
        symbolItem.value.type = "i32";
        return "i32";
    } else if (symbolItem.type == "Char" || symbolItem.type == "ConstChar" || symbolItem.type == "CharFunc") {
        symbolItem.value.type = "i8";
        symbolItem.type = "i8";
        return "i8";
    }
    printf("typeConvert: %s\n", symbolItem.type.c_str());
    return symbolItem.value.type;
}

std::string typeConvert(std::string type) {
    if (type == "Int" || type == "ConstInt" || type == "IntFunc") {
        type = "i32";
    } else if (type == "Char" || type == "ConstChar" || type == "CharFunc") {
        type = "i8";
    }
    printf("typeConvert: %s\n", type.c_str());
    return type;
}

void LlvmIRGenerator::AddIOFunc() {
    Llvm::printLlvmCode("declare i32 @getint()\n");
    Llvm::printLlvmCode("declare i32 @getchar()\n");
    Llvm::printLlvmCode("declare void @putint(i32)\n");
    Llvm::printLlvmCode("declare void @putch(i32)\n");
    Llvm::printLlvmCode("declare void @putstr(i8*)\n");
}

std::string LlvmIRGenerator::DePtr(const std::string &type) {
    if(type.find('*') == std::string::npos){
        return type;
    }
    return type.substr(0, type.size() - 1);
}

std::string LlvmIRGenerator::AddPtr(const std::string &type) {
    if(type.find('*') != std::string::npos){
        return type;
    }
    return type + "*";
}

// 转义字符
std::map<char, int> escapeChar = {
        {'\0', 0},
        {'\\', 92},
        {'\'', 39},
        {'\"', 34},
        {'a',  7},
        {'b',  8},
        {'f',  12},
        {'n',  10},
        {'r',  13},
        {'t',  9},
        {'v',  11}
};

Value LlvmIRGenerator::allocReg(std::string type, SymbolItem *context) {
    Value value;
    value.type = std::move(type);
    value.name = "%" + std::to_string(context->llvmIRStoreReg);
    context->llvmIRStoreReg++;
    return value;
}

void LlvmIRGenerator::getRegName(SymbolItem &symbolItem, SymbolItem *context) {
    if (symbolItem.scopeIndex == 1) {
        symbolItem.value.name = "@" + symbolItem.name;
    } else {
        symbolItem.llvmIRStoreReg = context->llvmIRStoreReg;
        symbolItem.value.name = "%" + std::to_string(symbolItem.llvmIRStoreReg);
        context->llvmIRStoreReg++;
    }
}

void LlvmIRGenerator::getRegType(SymbolItem &symbolItem, bool isFuncParam) {
    if (symbolItem.type == "void") {
        symbolItem.value.type = "void";
        return;
    }
    if (!isFuncParam) {
        if (symbolItem.type == "Int") {
            symbolItem.value.type = "i32*";
        } else if (symbolItem.type == "Char") {
            symbolItem.value.type = "i8*";
        }
        else{
            symbolItem.value.type = symbolItem.type;
        }
    } else {
        if (symbolItem.type == "Int" || symbolItem.type == "ConstInt") {
            symbolItem.value.type = "i32";
        } else if (symbolItem.type == "Char" || symbolItem.type == "ConstChar") {
            symbolItem.value.type = "i8";
        } else if (symbolItem.type == "ConstIntArray" || symbolItem.type == "IntArray") {
            symbolItem.value.type = "i32*";
        } else if (symbolItem.type == "ConstCharArray" || symbolItem.type == "CharArray") {
            symbolItem.value.type = "i8*";
        }else{
            symbolItem.value.type = symbolItem.type;
        }
    }
}

Value i8Toi32(const Value &value, SymbolItem *context) {
    Value value1 = LlvmIRGenerator::allocReg("i32", context);
    file << value1.name << " = zext i8 " << value.name << " to i32" << std::endl;
    return value1;
}

Value i32Toi8(const Value &value, SymbolItem *context) {
    Value value1 = LlvmIRGenerator::allocReg("i8", context);
    file << value1.name << " = trunc i32 " << value.name << " to i8" << std::endl;
    return value1;
}

bool isArray(const SymbolItem &symbolItem) {
    return symbolItem.type.find("Array") != std::string::npos;
}

void LlvmIRGenerator::Op(const std::string &op, const Value &result, const Value &value1, const Value &value2) {
    std::string opStr;
    if (op == "+") opStr = "add";
    else if (op == "-") opStr = "sub";
    else if (op == "*") opStr = "mul";
    else if (op == "/") opStr = "sdiv";
    else if (op == "%") opStr = "srem";
    else if (op == "<") opStr = "icmp slt";
    else if (op == ">") opStr = "icmp sgt";
    else if (op == "<=") opStr = "icmp sle";
    else if (op == ">=") opStr = "icmp sge";
    else if (op == "==") opStr = "icmp eq";
    else if (op == "!=") opStr = "icmp ne";
    file << result.name << " = " << opStr << " " << typeConvert(value1.type) << " " << value1.name << ", " << value2.name
         << "\n";
}

std::string LlvmIRGenerator::CalculateNumericOperation(const std::string &op, int val1, int val2) {
    if (op == "+") return std::to_string(val1 + val2);
    if (op == "-") return std::to_string(val1 - val2);
    if (op == "*") return std::to_string(val1 * val2);
    if (op == "/") return std::to_string(val1 / val2);
    if (op == "%") return std::to_string(val1 % val2);
    if (op == "<") return std::to_string(val1 < val2);
    if (op == ">") return std::to_string(val1 > val2);
    if (op == "<=") return std::to_string(val1 <= val2);
    if (op == ">=") return std::to_string(val1 >= val2);
    if (op == "==") return std::to_string(val1 == val2);
    if (op == "!=") return std::to_string(val1 != val2);
    return "";
}

void LlvmIRGenerator::varDef(const SymbolItem &symbolItem) {
    if (symbolItem.scopeIndex == 1) {
        printf("%s\n", symbolItem.value.type.c_str());
        file << symbolItem.value.name << " = dso_local global ";
        if (isArray(symbolItem)) {
            file << "[" << std::to_string(symbolItem.arraySize) << " x " << DePtr(typeConvert(symbolItem.value.type)) << "] ";
        } else {
            file << DePtr(typeConvert(symbolItem)) << " ";
        }
    } else {
        file << symbolItem.value.name << " = alloca ";
        if (isArray(symbolItem)) {
            file << "[" << std::to_string(symbolItem.arraySize) << " x " << DePtr(typeConvert(symbolItem)) << "]" << std::endl;
        } else {
            file << DePtr(typeConvert(symbolItem)) << std::endl;
        }
    }
}

void LlvmIRGenerator::varInit(SymbolItem &symbolItem, std::vector<Value> &valueList, SymbolItem *context) {
    if (symbolItem.scopeIndex == 1) {
        //全局变量
        if (isArray(symbolItem)) {
            if (valueList.empty()) {
                file << "zeroinitializer" << std::endl;
            } else {
                file << "[";
                for (int i = 0; i < symbolItem.arraySize; i++) {
                    if (i < valueList.size()) {
                        file << DePtr(typeConvert(symbolItem)) << " " << valueList[i].name;
                    } else {
                        file << DePtr(typeConvert(symbolItem)) << " 0";
                    }
                    if (i != symbolItem.arraySize - 1) {
                        file << ", ";
                    }
                }
                file << std::endl;
            }
        } else {
            if (valueList.empty()) {
                file << "0" << std::endl;
                symbolItem.value.numValue = "0";
            } else {
                file << valueList[0].name << std::endl;
                symbolItem.value.numValue = valueList[0].name;
            }
        }

    } else {
        //局部变量
        if (valueList.empty()) {
            return;
        }
        for (auto &item: valueList) {
            if (symbolItem.type != item.type) {
                if (typeConvert(symbolItem) == "i8" && typeConvert(item.type) == "i32") {
                    item = i32Toi8(item, context);
                } else if (typeConvert(symbolItem) == "i32" && typeConvert(item.type) == "i8") {
                    item = i8Toi32(item, context);
                }
            }
            if (isArray(symbolItem)) {
                for (int i = 0; i < valueList.size(); i++) {
                    Value value = allocReg(symbolItem.type, context);
                    file << value.name << " = getelementptr inbounds [" << std::to_string(symbolItem.arraySize) << " x "
                         << typeConvert(symbolItem) << "], [" << std::to_string(symbolItem.arraySize) << " x "
                         << typeConvert(symbolItem) << "], ["
                         << std::to_string(symbolItem.arraySize) << " x " << std::to_string(i) << std::endl;
                    file << "store " << typeConvert(symbolItem) << " " << valueList[i].name << ", "
                         << typeConvert(symbolItem) << "* "
                         << value.name << "\n";
                }
            } else {
                file << "store " << typeConvert(symbolItem) << " " << valueList[0].name << ", "
                     << typeConvert(symbolItem) << "* " << symbolItem.value.name << std::endl;
            }
        }
    }
}

// 变量赋值
void LlvmIRGenerator::varAssign(SymbolItem *symbolItem, Value &value, SymbolItem *context) {
    Value temp = value;
    if (DePtr(symbolItem->value.type) != value.type) {
        if (DePtr(typeConvert(*symbolItem)) == "i8" && typeConvert(value.type) == "i32") {
            temp = i32Toi8(value, context);
        } else if (DePtr(typeConvert(*symbolItem)) == "i32" && typeConvert(value.type) == "i8") {
            temp = i8Toi32(value, context);
        }
    }
    if (symbolItem->scopeIndex == 1) {
//        printf("%p\n", symbolItem);
        symbolItem->value.numValue.clear();
    }
    file << "store " << typeConvert(temp.type) << " " << temp.name << ", " << typeConvert(symbolItem->value.type) << " "
         << symbolItem->value.name << std::endl;
}

//函数定义
void LlvmIRGenerator::FuncDef(const SymbolItem &symbolItem) {
    file << "\ndefine dso_local " << typeConvert(symbolItem.type) << " " << symbolItem.value.name << " ";
}

//return 语句的中间代码
void LlvmIRGenerator::returnStmt(Value &value, SymbolItem *context) {
    if (context->value.type == "void") {
        file << "ret void" << std::endl;
    } else {
        if (context->value.type != value.type) {
            if (typeConvert(*context) == "i8" && typeConvert(value.type) == "i32") {
                value = i32Toi8(value, context);
            } else if (typeConvert(*context) == "i32" && typeConvert(value.type) == "i8") {
                value = i8Toi32(value, context);
            }
        }
        file << "ret " << typeConvert(*context) << " " << value.name << std::endl;
    }
}


Value LlvmIRGenerator::AddOrSubOp(std::string &op, Value &value1, Value &value2, SymbolItem *context) {
    Value value;
    if (value1.isNum && value2.isNum) {
        value.type = "i32";
        value.isNum = true;
        if (op == "+") {
            value.name = std::to_string(std::stoi(value1.numValue) + std::stoi(value2.numValue));
        } else if (op == "-") {
            value.name = std::to_string(std::stoi(value1.numValue) - std::stoi(value2.numValue));
        }
        return value;
    }
    Value value1Temp = value1;
    Value value2Temp = value2;
    if (value1.type == "i8") {
        value1Temp = i8Toi32(value1, context);
    }
    if (value2.type == "i8") {
        value2Temp = i8Toi32(value2, context);
    }
    value = allocReg("i32", context);
    if (op == "+") {
        file << value.name << " = add " << value1Temp.type << " " << value1Temp.name << ", " << value2Temp.name
             << std::endl;
    } else if (op == "-") {
        file << value.name << " = sub " << value1Temp.type << " " << value1Temp.name << ", " << value2Temp.name
             << std::endl;
    }
    return value;
}

void LlvmIRGenerator::ConvertIfNeeded(Value &value, SymbolItem *context) {
    if (value.type == "i8") {
        value = i8Toi32(value, context);
    }
}

Value LlvmIRGenerator::PerformOperation(std::string &op, Value &value1, Value &value2, SymbolItem *context) {
    Value value;
    if (value1.isNum && value2.isNum) {
        value.isNum = true;
        value.name = CalculateNumericOperation(op, std::stoi(value1.numValue), std::stoi(value2.numValue));
        return value;
    }

    ConvertIfNeeded(value1, context);
    ConvertIfNeeded(value2, context);

    value = allocReg("i32", context);
    Op(op, value, value1, value2);
    return value;
}

Value LlvmIRGenerator::MulOrDivOp(std::string &op, Value &value1, Value &value2, SymbolItem *context) {
    Value value = PerformOperation(op, value1, value2, context);
    value.type = "i32";
    return value;
}

void LlvmIRGenerator::printStmt(const std::string &str, std::vector<Value> &valueList, SymbolItem *context) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '%') {
            if (str[i + 1] == 'c') {
                Value value = valueList.front();
                if (value.type == "i32") {
                    value = i32Toi8(value, context);
                }
                value = i8Toi32(value, context);
                file << "call void @putch(i32 " << value.name << ")" << std::endl;
                valueList.erase(valueList.begin());
            } else if (str[i + 1] == 'd') {
                Value value = valueList.front();
                if (value.type == "i8") {
                    value = i8Toi32(value, context);
                }
                file << "call void @putint(i32 " << value.name << ")" << std::endl;
                valueList.erase(valueList.begin());
            } else if (str[i + 1] == '%') {
                file << "call void @putch(i32 37)" << std::endl;
            }
            i++;
        } else if (str[i] == '\\') {
            // 转义字符有很多种
            int num = escapeChar[str[i + 1]];
            file << "call void @putch(i32 " << std::to_string(num) << ")" << std::endl;
            i++;
        } else if (str[i] == '\"') {
            continue;
        } else {
            file << "call void @putch(i32 " << std::to_string((int) str[i]) << ")" << std::endl;
        }
    }
}

Value LlvmIRGenerator::FuncCall(SymbolItem *funcSymbolItem, std::vector<Value> &valueList, SymbolItem *context) {
    funcSymbolItem->type = typeConvert(*funcSymbolItem);
    for (int i = 0; i < valueList.size(); i++) {
        if (typeConvert(funcSymbolItem->paramTypeList[i]) == "i8" && typeConvert(valueList[i].type) == "i32") {
            valueList[i] = i32Toi8(valueList[i], context);
        } else if (typeConvert(funcSymbolItem->paramTypeList[i]) == "i32" && typeConvert(valueList[i].type) == "i8") {
            valueList[i] = i8Toi32(valueList[i], context);
        }
    }
    Value value;
    if (funcSymbolItem->type == "VoidFunc") {
        file << "call void" << typeConvert(funcSymbolItem->value.name) << "(";
    } else {
        value = allocReg(funcSymbolItem->type, context);
        file << value.name << " = call " << typeConvert(funcSymbolItem->type) << " " << funcSymbolItem->value.name << "(";
    }
    for (int i = 0; i < valueList.size(); i++) {
        file << typeConvert(funcSymbolItem->paramTypeList[i]) << " " << valueList[i].name;
        if (i != valueList.size() - 1) {
            file << ", ";
        }
    }
    file << ")" << std::endl;
    return value;
}

Value LlvmIRGenerator::LValArray(SymbolItem *symbolItem, Value &value, bool &isLoad, SymbolItem *context) {
    Value value1;
    std::string type = symbolItem->type;

}

Value LlvmIRGenerator::LVal(SymbolItem *symbolItem, Value &value1, bool isLoad, SymbolItem *context) {
    Value value;
    if (isArray(*symbolItem)) {
        value = LlvmIRGenerator::LValArray(symbolItem, value1, isLoad, context);
    } else {
//        value = value1;
        value.type = symbolItem->value.type;
        value.name = symbolItem->value.name;
        if (symbolItem->scopeIndex == 1 && !symbolItem->value.numValue.empty()) {
            // 全局变量没有改变初值
            value.type = DePtr(value.type);
            value.name = symbolItem->value.numValue;
            value.isNum = true;
            return value;
        }
    }

    if (isLoad) {
        // 需要加载
        Value newValue = allocReg(DePtr(value.type), context);
        file << newValue.name << " = load " << newValue.type << ", " << value.type << " " << value.name << "\n";
        value = newValue;
    }
    return value;
}

std::vector<Value> LlvmIRGenerator::stringConst(const std::string &str) {
    std::vector<Value> valueList;
    Value value;
    for (char i: str) {
        if (i == '\"') {
            continue;
        }
        value.name = std::to_string((int) i);
        value.type = "i8";
        valueList.push_back(value);
    }
    return valueList;
}

Value LlvmIRGenerator::UnaryOp(std::string &op, Value &value, SymbolItem *context) {
    if (op == "+") {
        return value;
    } else if (op == "-") {
        if (value.isNum) {
            return {"-" + value.name, "i32", true};
        }
        if (value.type == "i8") {
            value = i8Toi32(value, context);
        }
        Value value1 = allocReg("i32", context);
//        printf("")
        file << value1.name << " = sub " << value.type << " 0, " << value.name << std::endl;
        return value1;
    } else if (op == "!") {
        if (value.type == "i8") {
            value = i8Toi32(value, context);
        }
        Value value1 = allocReg("i1", context);
        file << value1.name << " = icmp eq i32 " << value.name << ", 0" << std::endl;
        return value1;
    }
    return value;
}

void LlvmIRGenerator::FuncFParam(SymbolItem &symbolItem) {
    file << symbolItem.value.type << " " << symbolItem.value.name << " ";
}

void LlvmIRGenerator::FuncFParamAssign(SymbolItem *funcSymbol, SymbolItem *context) {
    std::vector<std::string> paramList = funcSymbol->paramNameList;
    for (auto &i: paramList) {
        SymbolItem temp = SymbolTable::getSymbolItem(i);
        SymbolItem *tmp = SymbolTable::getSymbolItemPtr(i);
        Value newValue = allocReg(AddPtr(typeConvert(tmp->value.type)), context);
        file << newValue.name << " = alloca " << DePtr(newValue.type) << "\n";
        file << "store " << tmp->value.type << " " << tmp->value.name << ", "
             << newValue.type << " " << newValue.name << "\n";
        tmp->value.name = newValue.name;
        tmp->value.type = newValue.type;
    }
}

Value LlvmIRGenerator::readStmt(std::string &func, SymbolItem *context) {
    Value value = allocReg("i32", context);
    if (func == "getint") {
        file << value.name << " = call i32 @getint()" << std::endl;
    } else if (func == "getchar") {
        file << value.name << " = call i32 @getchar()" << std::endl;
    }
    return value;
}
void LlvmIRGenerator::LandExp(Value &value1, Value &value2,std::string &TLabel,std::string &FLabel) {
    file << "br i1 " << value1.name << ", label %" << TLabel << ", label %" << FLabel << std::endl;

}