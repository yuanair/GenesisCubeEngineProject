//
// Created by admin on 2023/12/24.
//

#pragma once

#include "../Core/Header.h"

#include "../../GenesisCubeBase/Object/GObject.h"

namespace GenesisCube::Language
{
	///
	/// 运行器
	///
	class LRunner : public GObject
	{
	public:
		
		LRunner();
		
		~LRunner() override;
	
	public:
		
		///
		/// \return 运行
		void Run();
	
	public:
		
		[[nodiscard]]
		LRunner *Clone() const noexcept override;
		
		GCLASS_BODY(LRunner)
		
	};
	
} // Language
// GenesisCube
