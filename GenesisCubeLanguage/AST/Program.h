//
// Created by admin on 2023/12/30.
//

#pragma once

#include "Node.h"

namespace GenesisCube::AST
{
	///
	/// 程序
	///
	class Program : public Node
	{
	public:
		
		[[nodiscard]]
		TString GetName() const noexcept override { return TEXT("Program"); }
		
		[[nodiscard]]
		JSON::Json ToJson() const noexcept override;
	
	public:
		
		std::list<TPtr<Statement>> statements;
		
	};
	
} // GenesisCube
