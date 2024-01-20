//
// Created by admin on 2024/1/20.
//

#pragma once

#include "../Core/Header.h"

namespace GenesisCube
{
	///
	/// 读取器
	template<class T>
	class IReader
	{
	public:
		
		IReader() = default;
		
		virtual ~IReader() = 0;
	
	public:
		
		///
		/// 下一个
		virtual void Next(T &value) = 0;
		
		///
		/// \return 是否正常
		virtual bool Good() = 0;
		
	};
	
} // GenesisCube
