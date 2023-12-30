#pragma once
#include "../Token/Token.h"
#include <list>

namespace GCL
{
	namespace AST
	{
		// AST节点
		class Node
		{
		public:

			// 节点类型枚举
			enum Type
			{
				Node_Program = 0,			// 根节点
				Node_Integer,				// 整数
				Node_Float,					// 浮点数
				Node_Infix,					// 中缀表达式
				Node_ExpressionStatement,	// 语句
			};

		public:

			Node() : Node(Node_Program) {}
			virtual ~Node() {}

			// type - 类型
			Node(Type type) : type(type) {}

		public:

			// 获取类型
			Type GetType() const { return this->type; }

			// 获取符号
			GCL::Token::Token GetToken() const { return this->token; }

			// 获取类型的字符串表示形式
			std::string ToTypeString() const;

			// 获取json表示
			virtual std::string ToJsonString() const;

		public:

			Type type;

			GCL::Token::Token token;

		private:

			static std::map<Type, std::string> names;

		};

		// AST表达式
		class Expression : public Node
		{
		public:

			Expression() : Node() {}
			virtual ~Expression() {}

			// type - 类型
			Expression(Type type) : Node(type) {}


		};

		// AST语句
		class Statement : public Node
		{
		public:

			Statement() : Node() {}
			virtual ~Statement() {}

			// type - 类型
			Statement(Type type) : Node(type) {}

		};

	}
}