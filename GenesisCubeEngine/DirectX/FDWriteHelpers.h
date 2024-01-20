//
// Created by admin on 2024/1/19.
//

#pragma once

#include "../Core/Header.h"
#include "../../GenesisCubeBase/Core/TPtr.h"

namespace GenesisCube
{
	///
	/// DWrite 帮助类
	class FDWriteHelpers
	{
	public:
		
		///
		/// 创建工厂
		/// \param factory 工厂
		/// \return
		static HRESULT CreateFactory(TComPtr<IDWriteFactory> &factory);
		
	};
	
} // GenesisCube
