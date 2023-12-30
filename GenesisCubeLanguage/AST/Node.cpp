//
// Created by admin on 2023/12/30.
//

#include "Node.h"


namespace GenesisCube::AST
{
	
	JSON::Json Infix::ToJson() const noexcept
	{
		return nullptr;
	}
	
	JSON::Json ExpressionStatement::ToJson() const noexcept
	{
		return JSON::Json();
	}
	
	JSON::Json Program::ToJson() const noexcept
	{
		return JSON::Json();
	}
	
}