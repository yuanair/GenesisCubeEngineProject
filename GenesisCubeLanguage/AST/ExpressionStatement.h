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
		JSON::Json ToJson() const noexcept override = 0;
	
	public:
		
		TPtr<Expression> expressions;
		
	};
	
} // GenesisCube
