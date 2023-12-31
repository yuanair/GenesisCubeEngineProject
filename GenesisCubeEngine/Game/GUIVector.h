//
// Created by admin on 2023/12/28.
//

#pragma once

#include "GUI.h"

namespace GenesisCube
{
	///
	/// UI容器
	///
	class GUIVector : public GObject
	{
	public:
		
		GUIVector();
		
		~GUIVector() override;
	
	public:
		
		///
		/// 渲染
		/// \param renderTarget 目标
		void Render(ID2D1RenderTarget *renderTarget);
		
		template<class T, class... Args>
		TPtr<T> AddUI(Args... args);
	
	public:
		
		[[nodiscard]]
		GUIVector *Clone() const noexcept override;
		
		GCLASS_BODY(GUIVector)
	
	private:
		
		std::vector<TPtr<GUI>> guis;
		
	};
	
	template<class T, class... Args>
	TPtr<T> GUIVector::AddUI(Args... args)
	{
		auto ptr = MakePtr<T>(args...);
		guis.push_back(ptr);
		return ptr;
	}
	
} // GenesisCube
