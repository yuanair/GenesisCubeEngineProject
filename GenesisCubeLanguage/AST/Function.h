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
		Json::Json ToJson() const noexcept override;
		
		[[nodiscard]]
		Function *Clone() const noexcept override
		{
			auto ptr = new Function;
			ptr->token = token;
			ptr->statements = statements;
			return ptr;
		}
	
	public:
		
		std::list<TSharedPtr<Statement>> statements;
		
	};
	
} // GenesisCube
