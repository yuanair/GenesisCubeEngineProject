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
		TString GetName() const noexcept override { return TEXT("ExpressionStatement"); }
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override
		{
			return expression != nullptr ? expression->ToJson() : JSON::Json(
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
		
		TPtr <Expression> expression;
		
	};
	
} // GenesisCube
