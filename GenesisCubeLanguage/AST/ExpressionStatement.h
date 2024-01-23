//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Node.h"

namespace GenesisCube::AST
{
	
	class ExpressionStatement : public Statement
	{
	public:
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override
		{
			return expression != nullptr ? expression->ToJson() : Json::Json(
				nullptr
			);
		}
		
		[[nodiscard]]
		ExpressionStatement *Clone() const noexcept override
		{
			auto ptr = new ExpressionStatement;
			ptr->token = token;
			ptr->expression = expression;
			return ptr;
		}
	
	public:
		
		TSharedPtr<Expression> expression;
		
	};
	
} // GenesisCube
