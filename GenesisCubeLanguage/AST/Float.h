#pragma once
#include "Node.h"

namespace GCL
{
	namespace AST
	{
		// 浮点数
		class Float : public Expression
		{
		public:

			Float(float value = 0.0f) : Expression(Node_Float), value(value) {}
			virtual ~Float() {}

		public:

			// 获取json表示
			virtual std::string ToJsonString() const override;

		public:

			float value;

		};

		// 双精度浮点数
		class Double : public Expression
		{
		public:

			Double(double value = 0.0) : Expression(Node_Float), value(value) {}
			virtual ~Double() {}

		public:

			// 获取json表示
			virtual std::string ToJsonString() const override;

		public:

			double value;

		};
	}
}
