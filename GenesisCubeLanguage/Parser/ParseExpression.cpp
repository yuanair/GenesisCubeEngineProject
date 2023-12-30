#include "Parser.h"


using namespace GCL::Parser;
using namespace GCL::Token;
using namespace GCL::AST;


std::shared_ptr<Expression> Parser::ParseExpression(int precedence)
{
	auto prefix = PrefixParseFns.find(currToken.GetType());
	if (prefix == PrefixParseFns.end())
	{
		NoPrefixParseFnError(currToken.GetType());
		return nullptr;
	}
	std::shared_ptr<Expression> e = (this->*(prefix->second))();
	while (peekToken.GetType() != Token::Token::GCL_Semicolon && precedence < PeekTokenPrecedence())
	{
		auto infix = InfixParseFns.find(peekToken.GetType());
		if (infix == InfixParseFns.end())
		{
			return e;
		}
		NextToken();
		e = (this->*infix->second)(e);
	}
	return e;
}
