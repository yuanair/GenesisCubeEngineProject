//
// Created by admin on 2023/12/30.
//

#include "Infix.h"


namespace GenesisCube::AST
{
	Json::Json Infix::ToJson() const noexcept
	{
		Json::Json json;
		json[TEXT(" left")] = left ? left->ToJson() : Json::Json(nullptr);
		json[TEXT(" token")] = token ? token->ToJson() : Json::Json(nullptr);
		json[TEXT("right")] = right ? right->ToJson() : Json::Json(nullptr);
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