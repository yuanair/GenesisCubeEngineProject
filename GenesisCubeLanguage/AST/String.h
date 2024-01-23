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
		Json::Json ToJson() const noexcept override { return token->ToJson(); }
		
		[[nodiscard]]
		String *Clone() const noexcept override { return new String(); }
		
	};
	
	///
	/// 抽象语法树字符
	///
	class Char : public Expression
	{
	public:
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override { return token->ToJson(); }
		
		[[nodiscard]]
		Char *Clone() const noexcept override { return new Char(); }
		
	};
	
	
}