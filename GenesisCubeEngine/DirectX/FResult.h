//
// Created by admin on 2023/12/28.
//

#pragma once

#include "../Core/Header.h"
#include "../Debug/Debug.h"

namespace GenesisCube
{
	///
	/// 返回值，被析构时抛出异常
	///
	class FResult
	{
	public:
		
		FResult(HRESULT result) noexcept;
		
		~FResult() noexcept(false);
	
	public:
		
		///
		/// 如果FAILED则抛出异常
		///
		void ThrowIfThrow() noexcept(false);
		
		
		///
		/// 抛出异常
		///
		void Throw() noexcept(false);
	
	public:
		
		const HRESULT result;
	
	private:
		
		bool bIsThrow;
		
	};
	
} // GenesisCube
