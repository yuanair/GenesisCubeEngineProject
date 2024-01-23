//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../Token/Token.h"
#include "Node.h"

namespace GenesisCube::AST
{
	
	///
	/// 抽象语法树浮点数
	///
	class Float : public Expression
	{
	public:
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override { return token->ToJson(); }
		
		Float *Clone() const noexcept override { return new Float(); }
		
	};
	
}
