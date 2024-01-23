//
// Created by admin on 2023/12/31.
//

#pragma once

#include "Operators.h"

namespace GenesisCube::Token
{
	
	///
	/// 左移运算符
	///
	class LeftShiftToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Shift; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("<<"); }
		
		
	};
	
	///
	/// 右移运算符
	///
	class RightShiftToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Shift; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT(">>"); }
		
		
	};
	
} // GenesisCube
