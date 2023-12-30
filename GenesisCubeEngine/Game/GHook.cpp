//
// Created by admin on 2023/12/27.
//

#include "GHook.h"

namespace GenesisCube
{
	
	GHook::GHook(HWND hwnd, int32_t idHook)
		: hHook(nullptr)
	{
		this->hHook = SetWindowsHookEx(
			idHook, HookProc, FCore::GetInstance(),
			GetWindowThreadProcessId(hwnd, nullptr)
		);
	}
	
	
	GHook::~GHook()
	{
		UnhookWindowsHookEx(hHook);
	}
	
	LRESULT GHook::HookProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		switch (wParam)
		{
			case WM_MOUSEMOVE:
				return 0;
			case WM_MOUSEWHEEL:
				return 0;
			default:
				return CallNextHookEx(nullptr, nCode, wParam, lParam);
		}
		
	}
	
	
} // GenesisCube