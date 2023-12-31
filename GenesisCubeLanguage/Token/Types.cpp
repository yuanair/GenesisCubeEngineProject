//
// Created by admin on 2023/12/30.
//

#include "Types.h"
#include "../AST/Integer.h"
#include "../AST/String.h"
#include "../AST/Float.h"

namespace GenesisCube::Token
{
	void StringToken::GetPrefix(TPtr<AST::Expression> &expression) noexcept
	{
		expression = NewNode<AST::String>();
	}
	
	void IntegerToken::GetPrefix(TPtr<AST::Expression> &expression) noexcept
	{
		expression = NewNode<AST::Integer>();
	}
	
	void FloatToken::GetPrefix(TPtr<AST::Expression> &expression) noexcept
	{
		expression = NewNode<AST::Float>();
	}
}