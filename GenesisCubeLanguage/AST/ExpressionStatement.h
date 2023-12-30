#pragma once
#include "Node.h"

namespace GCL
{
	namespace AST
	{
		// 表达式语句
		class ExpressionStatement : public Statement
		{
		public:

			ExpressionStatement() : Statement(Node_ExpressionStatement) {}
			virtual ~ExpressionStatement() {}

		public:

			virtual std::string ToJsonString() const override;

		public:

			std::shared_ptr<Expression> expression;

		};

	}
}