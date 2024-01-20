//
// Created by admin on 2023/12/31.
//

#pragma once

#include "Operators.h"

namespace GenesisCube::Token
{
	
	///
	/// 与
	///
	class ANDToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return AND; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("&&"); }
	
	GCLASS_BODY(ANDToken)
	
	};
	
	///
	/// 或
	///
	class ORToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return OR; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("||"); }
	
	GCLASS_BODY(ORToken)
	
	};
	
	
	///
	/// 位与
	///
	class BitANDToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return BitAND; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("&"); }
	
	GCLASS_BODY(BitANDToken)
	
	};
	
	///
	/// 位或
	///
	class BitORToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return BitOR; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("|"); }
	
	GCLASS_BODY(BitORToken)
	
	};
	
	///
	/// 位异或
	///
	class BitXORToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return BitXOR; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("^"); }
	
	GCLASS_BODY(BitXORToken)
	
	};
	
	
} // GenesisCube
