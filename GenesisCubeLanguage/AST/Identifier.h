//
// Created by admin on 2023/12/31.
//

#pragma once

#include "Node.h"

namespace GenesisCube::AST
{
	///
	/// 标识符
	///
	class Identifier : public Expression
	{
	public:
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override { return token->ToJson(); }
		
		[[nodiscard]]
		Identifier *Clone() const noexcept override { return new Identifier(); }
		
	};
	
} // GenesisCube
