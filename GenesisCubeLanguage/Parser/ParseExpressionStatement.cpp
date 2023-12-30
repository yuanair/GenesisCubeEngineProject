#include "Parser.h"


using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;


std::shared_ptr<GCL::AST::ExpressionStatement> Parser::ParseExpressionStatement()
{
	std::shared_ptr<ExpressionStatement> s(new ExpressionStatement());
	s->token = currToken;
	s->expression = ParseExpression(Lowest);
	while (peekToken.GetType() == Token::Token::GCL_Semicolon)
	{
		NextToken();
	}
	return s;
}