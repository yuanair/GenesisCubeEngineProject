#pragma once
#include "Node.h"

namespace GCL::AST
{
	// 根节点
	class Program : public Statement
	{
	public:

		Program() : Statement(Node_Program) {}
		virtual ~Program() {}

	public:

		virtual std::string ToJsonString() const override;

	public:

		std::list<std::shared_ptr<Statement>> statements;

	};
}

