#include"lexer/Lexer.h"
#include"parser/Parser.h"
#include"util/Util.h"
#include "error/Error.h"
#include "semantic/Semantic.h"
int main() {
    Util::initEnv();
    Lexer::lexicalAnalysis();
    Parser::parse();
    Error::sortError();
    Semantic::sortSemantic();
    Util::releaseEnv();
    return 0;
}
