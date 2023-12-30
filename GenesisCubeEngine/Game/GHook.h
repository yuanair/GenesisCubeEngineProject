//
// Created by admin on 2023/12/27.
//

#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"
#include "GWindow.h"

namespace GenesisCube
{
	///
	/// 钩子
	///
	class GHook : public GObject
	{
	public:
		
		///
		/// 绑定到窗口
		/// \param hwnd 句柄
		/// \param idHook 钩子类型
		explicit GHook(HWND hwnd, int32_t idHook = WH_MOUSE_LL);
		
		~GHook() override;
	
	public:
		
		[[nodiscard]]
		inline HHOOK GetHHook() const noexcept { return this->hHook; }
	
	private:
		
		static LRESULT HookProc(int nCode, WPARAM wParam, LPARAM lParam);
	
	private:
		
		HHOOK hHook;
		
	};
	
} // GenesisCube
