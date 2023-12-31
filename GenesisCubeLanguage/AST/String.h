//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../Token/Token.h"
#include "Node.h"

namespace GenesisCube::AST
{
	
	///
	/// 抽象语法树字符串
	///
	class String : public Expression
	{
	public:
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override { return token->ToJson(); }
		
		String *Clone() const noexcept override { return new String(); }
		
		GCLASS_BODY(String)
		
	};
	
	
}