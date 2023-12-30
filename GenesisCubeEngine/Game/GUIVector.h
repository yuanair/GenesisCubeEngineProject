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
		
		template<class T>
		TPtr<T> AddUI();
	
	public:
		
		[[nodiscard]]
		GUIVector *Clone() const noexcept override;
	
	private:
		
		std::vector<TPtr<GUI>> guis;
		
	};
	
	template<class T>
	TPtr<T> GUIVector::AddUI()
	{
		T *ptr = new T;
		guis.push_back(ptr);
		return ptr;
	}
	
} // GenesisCube
