//
// Created by admin on 2023/12/30.
//

#include "Tokens.h"
#include "../AST/Identifier.h"

namespace GenesisCube::Token
{
	
	
	void IdentifierToken::GetPrefixExpression(TSharedPtr<AST::Expression> &expression, Parser::Parser &parser) noexcept
	{
		expression = NewNode<AST::Identifier>();
	}
} // GenesisCube