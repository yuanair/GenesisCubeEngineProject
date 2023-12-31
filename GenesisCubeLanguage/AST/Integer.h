//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../Token/Token.h"
#include "Node.h"

namespace GenesisCube::AST
{
	
	///
	/// 抽象语法树整数
	///
	class Integer : public Expression
	{
	public:
		
		[[nodiscard]]
		GenesisCube::JSON::Json ToJson() const noexcept override { return token->ToJson(); }
		
		[[nodiscard]]
		Integer *Clone() const noexcept override { return new Integer(); }
		
		GCLASS_BODY(Integer)
		
	};
	
}