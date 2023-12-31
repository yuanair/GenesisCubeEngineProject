//
// Created by admin on 2023/12/31.
//

#include "Function.h"

namespace GenesisCube::AST
{
	JSON::Json Function::ToJson() const noexcept
	{
		JSON::Json json;
		JSON::Json &list = json[TEXT("statements")];
		size_t index = 0;
		for (auto &item: statements)
		{
			list[ToTString(index)] = item->ToJson();
			index++;
		}
		return json;
	}
} // GenesisCube