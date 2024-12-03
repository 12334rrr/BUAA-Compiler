/**
 * Cond -> (Exp) Stmt [ELSE Stmt]
 */

#include "Cond.h"
#include "../multiexp/LOrExp.h"
#include "../../../util/Util.h"

void Cond::condParser() {
    LOrExp::lOrExpParser();
    Util::printParserInfo("<Cond>");
}