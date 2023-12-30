//
// Created by admin on 2023/12/24.
//

#pragma once

#include "Header.h"
#include "../Debug/Debug.h"

namespace GenesisCube
{
	///
	/// 服务定位器
	///
	class FLocator
	{
	public:
		
		///
		/// 获取Logger
		/// \return Logger
		inline static FLogger *Logger() { return loggerInstance; }
		
		///
		/// 提供Logger
		/// \param logger Logger
		inline static void ProvideLogger(FLogger *logger) { loggerInstance = logger; }
	
	private:
		
		static FLogger *loggerInstance;
		
	};
	
} // GenesisCube
