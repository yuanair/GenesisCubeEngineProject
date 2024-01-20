//
// Created by admin on 2023/12/31.
//

#pragma once

#include "Operators.h"

namespace GenesisCube::Token
{
	
	///
	/// 赋值号
	///
	class AssignmentToken : public OperatorToken
	{
	public:
		
		[[nodiscard]]
		inline Precedence GetPrecedence() const noexcept override { return Assign; }
		
		[[nodiscard]]
		inline TString ToString() const noexcept override { return TEXT("="); }
	
	GCLASS_BODY(AssignmentToken)
		
	};
	
} // GenesisCube
