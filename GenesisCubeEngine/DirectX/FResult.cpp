//
// Created by admin on 2023/12/28.
//

#include "FResult.h"

namespace GenesisCube
{
	FResult::FResult(HRESULT result) noexcept
		: result(result), bIsThrow(false)
	{
	
	}
	
	FResult::~FResult() noexcept(false)
	{
		if (!this->bIsThrow) Throw();
	}
	
	void FResult::ThrowIfThrow() noexcept(false)
	{
		this->bIsThrow = true;
		FLogger::GThrowIfFailed(this->result);
	}
	
	void FResult::Throw() noexcept(false)
	{
		this->bIsThrow = true;
		FLogger::GThrow(this->result);
	}
} // GenesisCube