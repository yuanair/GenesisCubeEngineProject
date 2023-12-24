//
// Created by admin on 2023/12/24.
//

#pragma once

#include "../Core/Header.h"

#include "../Object/GObject.h"

namespace GenesisCubeEngine::Language
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
		
	};
	
} // Language
// GenesisCubeEngine