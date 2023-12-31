//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Node.h"


namespace GenesisCube::AST
{
	
	///
	/// 抽象语法树前缀表达式
	///
	class Infix : public Expression
	{
	public:
		
		[[nodiscard]]
		TString GetName() const noexcept override { return TEXT("Infix"); }
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override;
	
	public:
		
		/// 左表达式
		TPtr<Expression> left;
		
		/// 右表达式
		TPtr<Expression> right;
		
	};
	
}
