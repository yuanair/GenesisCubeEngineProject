#pragma once
#include "Node.h"

namespace GCL
{
	namespace AST
	{

		// 整数
		class Integer : public Expression
		{
		public:

			Integer(int64_t value = 0LL) : Expression(Node_Integer), value(value) {}
			virtual ~Integer() {}

		public:

			// 获取json表示
			virtual std::string ToJsonString() const override;

		public:

			int64_t value;

		};

	}
}