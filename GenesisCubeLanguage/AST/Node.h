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
		
		virtual ~Node() = default;
	
	public:
		
		[[nodiscard]]
		virtual Json::Json ToJson() const noexcept = 0;
		
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
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override = 0;
		
	};
	
	///
	/// 抽象语法树语句
	///
	class Statement : public Node
	{
	public:
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override = 0;
		
	};
	
}
