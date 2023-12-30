//
// Created by admin on 2023/12/24.
//

#include "LRunner.h"


namespace GenesisCube::Language
{
	LRunner::LRunner()
	= default;
	
	LRunner::~LRunner()
	= default;
	
	LRunner *LRunner::Clone() const noexcept
	{
		return new LRunner();
	}
	
	void LRunner::Run()
	{
	
	}
	
	
}
