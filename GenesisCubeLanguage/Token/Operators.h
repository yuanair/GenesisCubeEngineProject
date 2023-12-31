//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Token.h"

namespace GenesisCube::Token
{
	
	///
	/// 操作符
	///
	class OperatorToken : public Token
	{
	public:
		
		void GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Type GetType() const noexcept override { return OperatorType; }
		
		[[nodiscard]]
		inline TString GetName() const noexcept override = 0;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override = 0;
		
		[[nodiscard]]
		inline TString ToString() const noexcept override = 0;
		
		[[nodiscard]]
		inline OperatorToken *Clone() const noexcept override = 0;
		
	};
	
	///
	/// 加号
	///
	class PlusToken : public OperatorToken
	{
	public:
		
		void GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Sum; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("+"); }
		
		[[nodiscard]]
		inline PlusToken *Clone() const noexcept override { return new PlusToken(); }
		
		GCLASS_BODY(PlusToken)
		
	};
	
	///
	/// 减号
	///
	class MinusToken : public OperatorToken
	{
	public:
		
		void GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Sum; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("-"); }
		
		[[nodiscard]]
		inline MinusToken *Clone() const noexcept override { return new MinusToken(); }
		
		GCLASS_BODY(MinusToken)
		
	};
	
	///
	/// 乘号
	///
	class MultiplyToken : public OperatorToken
	{
	public:
		
		void GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Product; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("*"); }
		
		[[nodiscard]]
		inline MultiplyToken *Clone() const noexcept override { return new MultiplyToken(); }
		
		GCLASS_BODY(MultiplyToken)
		
	};
	
	///
	/// 除号
	///
	class DivideToken : public OperatorToken
	{
	public:
		
		void GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Product; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("/"); }
		
		[[nodiscard]]
		inline DivideToken *Clone() const noexcept override { return new DivideToken(); }
		
		GCLASS_BODY(DivideToken)
		
	};
	
	///
	/// 求模号
	///
	class ModToken : public OperatorToken
	{
	public:
		
		void GetInfixExpression(TPtr<AST::Expression> &expression, const TPtr<AST::Expression> &left,
								Parser::Parser &parser) noexcept override;
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Product; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("%"); }
		
		[[nodiscard]]
		inline ModToken *Clone() const noexcept override { return new ModToken(); }
		
		GCLASS_BODY(ModToken)
		
	};
	
}
