#pragma once
#include "Node.h"

namespace GCL
{
	namespace AST
	{

		// 中缀表达式
		class Infix : public Expression
		{
		public:

			Infix() : Expression(Node_Infix) {}
			virtual ~Infix() {}

		public:

			virtual std::string ToJsonString() const override;

		public:

			std::string _operator;
			
			std::shared_ptr<Expression> left;

			std::shared_ptr<Expression> right;

		};

	}
}