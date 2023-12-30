#include "Parser.h"


using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;


std::shared_ptr<Expression> Parser::ParseInfix(const std::shared_ptr<GCL::AST::Expression>& left)
{
	std::shared_ptr<Infix> e(new Infix());

	e->token = currToken;
	e->_operator = currToken.GetLiteral();
	e->left = left;
	int precedence = CurrTokenPrecedence();
	NextToken();
	e->right = ParseExpression(precedence);
	return e;
}
