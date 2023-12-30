#include "Parser.h"

using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;

std::shared_ptr<Expression> Parser::ParseInteger()
{
	std::shared_ptr<Integer> e(new Integer());
	e->token = currToken;
	e->value = std::atoll(currToken.GetLiteral().c_str());
	return e;
}
