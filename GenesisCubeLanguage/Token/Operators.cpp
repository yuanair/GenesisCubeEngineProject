//
// Created by admin on 2023/12/30.
//

#include "Operators.h"
#include "../AST/Infix.h"
#include "../Parser/Parser.h"

namespace GenesisCube::Token
{
	
	
	void PlusToken::GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
									   Parser::Parser &parser) noexcept
	{
		OperatorToken::GetInfixExpression(expression, left, parser);
	}
	
	void ModToken::GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
									  Parser::Parser &parser) noexcept
	{
		OperatorToken::GetInfixExpression(expression, left, parser);
	}
	
	void DivideToken::GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
										 Parser::Parser &parser) noexcept
	{
		OperatorToken::GetInfixExpression(expression, left, parser);
	}
	
	void MultiplyToken::GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
										   Parser::Parser &parser) noexcept
	{
		OperatorToken::GetInfixExpression(expression, left, parser);
	}
	
	void MinusToken::GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
										Parser::Parser &parser) noexcept
	{
		OperatorToken::GetInfixExpression(expression, left, parser);
	}
	
	void OperatorToken::GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
										   Parser::Parser &parser) noexcept
	{
		TPtr<AST::Infix> infix = MakePtr<AST::Infix>();
		infix->left = left;
		infix->token = shared_from_this();
		// Token::Precedence precedence = parser.CurrTokenPrecedence();
		parser.NextToken();
		parser.ParseExpression(infix->right, GetPrecedence());
		expression = infix;
	}
}