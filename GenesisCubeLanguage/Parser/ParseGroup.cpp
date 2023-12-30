#include "Parser.h"


using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;

std::shared_ptr<Expression> Parser::ParseGroup()
{

	NextToken();
	auto e = ParseExpression(Lowest);
	if (!ExpectPeekToken(Token::Token::GCL_RightParen))
	{
		return nullptr;
	}
	return e;
}
