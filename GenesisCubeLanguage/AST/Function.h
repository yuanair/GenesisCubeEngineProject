//
// Created by admin on 2023/12/31.
//

#pragma once

#include "Node.h"

namespace GenesisCube::AST
{
	///
	/// 函数
	///
	class Function : public Node
	{
	public:
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override;
		
		GCLASS_BODY(Function)
		
		[[nodiscard]]
		Function *Clone() const noexcept override
		{
			auto ptr = new Function;
			ptr->token = token;
			ptr->statements = statements;
			return ptr;
		}
	
	public:
		
		std::list<TPtr<Statement>> statements;
		
	};
	
} // GenesisCube
