//
// Created by admin on 2023/12/30.
//

#include "Program.h"

namespace GenesisCube::AST
{
	Json::Json Program::ToJson() const noexcept
	{
		Json::Json json;
		Json::Json &list = json[TEXT("functions")];
		for (auto &item: functions)
		{
			list.Push(item->ToJson());
		}
		return json;
	}
	
	Program *Program::Clone() const noexcept
	{
		auto *ptr = new Program();
		ptr->token = token;
		ptr->functions = functions;
		return ptr;
	}
} // GenesisCube