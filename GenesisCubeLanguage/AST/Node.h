//
// Created by admin on 2023/12/30.
//

#pragma once

#include "../../GenesisCubeBase/Object/GObject.h"
#include "../../GenesisCubeBase/Json/Json.h"
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
		
		explicit Node(class Token::Token *token) : token(token) {}
		
		~Node() override = default;
	
	public:
		
		[[nodiscard]]
		virtual JSON::Json ToJson() const noexcept = 0;
		
		[[nodiscard]]
		inline Node *Clone() const noexcept override = 0;
	
	public:
		
		TSharedPtr<class Token::Token> token;
		
	};
	
	///
	/// 抽象语法树表达式
	///
	class Expression : public Node
	{
	public:
		
		GCLASS_BODY(Expression)
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override = 0;
		
	};
	
	///
	/// 抽象语法树语句
	///
	class Statement : public Node
	{
	public:
		
		GCLASS_BODY(Statement)
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override = 0;
		
	};
	
}
