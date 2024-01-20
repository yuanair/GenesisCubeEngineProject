//
// Created by admin on 2023/12/30.
//

#include "Operators.h"
#include "../AST/Infix.h"
#include "../AST/Identifier.h"
#include "../Parser/Parser.h"

namespace GenesisCube::Token
{
	
	void
	OperatorToken::GetInfixExpression(TSharedPtr<AST::Expression> &expression, const TSharedPtr<AST::Expression> &left,
									  Parser::Parser &parser) noexcept
	{
		TSharedPtr<AST::Infix> infix = MakeShared<AST::Infix>();
		infix->left = left;
		infix->token = shared_from_this();
		// Token::Precedence precedence = parser.CurrTokenPrecedence();
		parser.NextToken();
		parser.ParseExpression(infix->right, GetPrecedence());
		expression = infix;
	}
	
	void ScopeToken::GetPrefixExpression(TSharedPtr<AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
	
	}
}