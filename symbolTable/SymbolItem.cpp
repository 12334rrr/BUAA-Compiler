/**
 * SymbolItem.cpp -- Source file for the SymbolItem class
 * @author 王春博
 */

#include "SymbolItem.h"
#include "SymbolTable.h"
#include "../util/Constants.h"
#include <utility>

SymbolItem::SymbolItem(std::string name) {
    this->name = std::move(name);
    this->type = "";
    this->scopeIndex = 0;
    this->arraySize = 0;
    this->paramNum = 0;
    this->value = Value();
}
SymbolItem::SymbolItem() {
    this->name = "";
    this->type = "";
    this->scopeIndex = 0;
    this->arraySize = 0;
    this->paramNum = 0;
}
SymbolItem::SymbolItem(std::string name, std::string type, int scopeIndex, int value, int arraySize, int paramNum) {
    this->name = std::move(name);
    this->type = std::move(type);
    this->scopeIndex = scopeIndex;
    this->arraySize = arraySize;
    this->paramNum = paramNum;
}
SymbolItem::SymbolItem(std::string name, std::string type, int scopeIndex, int value, int arraySize, int paramNum, const std::vector<std::string>& paramTypeList) {
    this->name = std::move(name);
    this->type = std::move(type);
    this->scopeIndex = scopeIndex;
    this->arraySize = arraySize;
    this->paramNum = paramNum;
    this->paramTypeList = paramTypeList;
}

SymbolItem::SymbolItem(int scopeIndex) {
    this->name = "";
    this->type = "";
    this->scopeIndex = scopeIndex;
    this->arraySize = 0;
    this->paramNum = 0;
}
void SymbolItem::initCurrentFuncSymbol(SymbolItem *symbolItem) {
    curFuncSymbol =  symbolItem;
}

SymbolItem::SymbolItem(const std::string& name, const std::string& type) {
    this->name = name;
    this->type = type;
}
