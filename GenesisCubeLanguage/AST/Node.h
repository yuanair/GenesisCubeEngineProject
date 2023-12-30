//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../../GenesisCubeBase/Object/GObject.h"
#include "../Token/Token.h"

namespace GenesisCube::AST
{
	///
	/// 抽象语法树节点
	///
	class Node : public GObject
	{
	public:
		
		Node() = default;
		
		~Node() override = default;
	
	public:
		
		[[nodiscard]]
		virtual TString GetName() const noexcept = 0;
		
		[[nodiscard]]
		virtual JSON::Json ToJson() const noexcept = 0;
	
	public:
		
		TPtr<Token::Token> token;
		
	};
	
	///
	/// 抽象语法树前缀表达式
	///
	class Infix : public Node
	{
	public:
		
		[[nodiscard]]
		TString GetName() const noexcept override { return TEXT("Infix"); }
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override;
		
	};
	
	///
	/// 抽象语法树表达式语句
	///
	class ExpressionStatement : public Node
	{
	public:
		
		[[nodiscard]]
		TString GetName() const noexcept override { return TEXT("ExpressionStatement"); }
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override;
		
		
	};
	
	///
	/// 抽象语法树程序
	///
	class Program : public Node
	{
	public:
		
		[[nodiscard]]
		TString GetName() const noexcept override { return TEXT("Program"); }
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override;
		
		
	};
	
}
