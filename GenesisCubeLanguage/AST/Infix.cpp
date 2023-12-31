//
// Created by admin on 2023/12/30.
//

#include "Infix.h"


namespace GenesisCube::AST
{
	JSON::Json Infix::ToJson() const noexcept
	{
		JSON::Json json;
		json[TEXT(" left")] = left ? left->ToJson() : JSON::Json(nullptr);
		json[TEXT(" token")] = token ? token->ToJson() : JSON::Json(nullptr);
		json[TEXT("right")] = right ? right->ToJson() : JSON::Json(nullptr);
		return json;
	}
	
	Infix *Infix::Clone() const noexcept
	{
		auto *ptr = new Infix();
		ptr->token = token;
		ptr->left = left;
		ptr->right = right;
		return ptr;
	}
}