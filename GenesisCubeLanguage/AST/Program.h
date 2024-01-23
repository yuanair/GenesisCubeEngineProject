//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Node.h"
#include "Function.h"

namespace GenesisCube::AST
{
	///
	/// 程序
	///
	class Program : public Node
	{
	public:
		
		[[nodiscard]]
		Json::Json ToJson() const noexcept override;
		
		[[nodiscard]]
		Program *Clone() const noexcept override;
	
	public:
		
		std::list<TSharedPtr<Function>> functions;
		
	};
	
} // GenesisCube
