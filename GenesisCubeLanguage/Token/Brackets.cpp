//
// Created by admin on 2023/12/30.
//

#include "Brackets.h"
#include "../Parser/Parser.h"

namespace GenesisCube::Token
{
	void
	LeftParenToken::GetPrefixExpression(TSharedPtr<class AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		parser.NextToken();
		parser.ParseExpression(expression, Lowest);
		if (!parser.ExpectPeekToken<RightParenToken>())
		{
			expression = nullptr;
		}
	}
}