//
// Created by admin on 2024/1/12.
//

#include "Window.h"
#include "../Core/Debug.h"
#include <windows.h>
#include <windowsx.h>

namespace GenesisCube::Win32
{
	
	void FWindow::Create(
		const FWindowClass &windowClass, const TString &windowName,
		int32_t x, int32_t y, int32_t w, int32_t h, void *hInstance, HWND hWndParent) noexcept
	{
		this->hWnd = ::CreateWindowEx(
			WS_EX_ACCEPTFILES,
			windowClass.GetName().c_str(), windowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			x,
			y,
			w,
			h,
			hWndParent,
			nullptr,
			(HINSTANCE) hInstance,
			this
		);
	}
	
	void FWindow::Bind(HWND pHwnd) noexcept
	{
		Destroy();
		this->hWnd = pHwnd;
	}
	
	void FWindow::Destroy() const noexcept
	{
		::DestroyWindow(this->hWnd);
	}
	
	bool FWindow::Good() const noexcept
	{
		return this->hWnd != INVALID_HANDLE_VALUE && this->hWnd != nullptr;
	}
	
	bool FWindow::Bad() const noexcept
	{
		return this->hWnd == INVALID_HANDLE_VALUE || this->hWnd == nullptr;
	}
	
	
	HWND FWindow::GetDesktopWindow() noexcept
	{
		return ::GetDesktopWindow();
	}
	
	HWND FWindow::FindWindowFromName(const TString &windowName)
	{
		return ::FindWindow(nullptr, windowName.c_str());
	}
	
	HWND FWindow::FindWindowFromName(const TString &windowName, const TString &windowClassName)
	{
		return ::FindWindow(windowClassName.c_str(), windowName.c_str());
	}
	
	void FWindow::SetForegroundWindow() const
	{
		HWND hCurWnd = ::GetForegroundWindow();
		DWORD dwMyID = ::GetCurrentThreadId();
		DWORD dwCurID = ::GetWindowThreadProcessId(hCurWnd, nullptr);
		::AttachThreadInput(dwCurID, dwMyID, TRUE);
		::SetForegroundWindow(this->hWnd);
		::AttachThreadInput(dwCurID, dwMyID, FALSE);
	}
	
	void FWindow::SeedKeyDown(TChar vk) const
	{
		::PostMessage(this->hWnd, WM_KEYDOWN, vk, 0);
	}
	
	void FWindow::SeedKeyUp(TChar vk) const
	{
		::PostMessage(this->hWnd, WM_KEYUP, vk, 1LL << 31);
	}
	
	FRectI FWindow::GetClientRect() const noexcept
	{
		RECT rect{};
		::GetClientRect(this->hWnd, &rect);
		FRectI result
			{
				.x = rect.left,
				.y = rect.top,
				.width = rect.right - rect.left,
				.height = rect.bottom - rect.top
			};
		return result;
	}
	
	FRectI FWindow::GetWindowRect() const noexcept
	{
		RECT rect{};
		::GetWindowRect(this->hWnd, &rect);
		FRectI result
			{
				.x = rect.left,
				.y = rect.top,
				.width = rect.right - rect.left,
				.height = rect.bottom - rect.top
			};
		return result;
	}
	
	LRESULT FWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		FWindow *pThis;
		
		if (msg == WM_NCCREATE)
		{
			auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
			pThis = reinterpret_cast<FWindow *>(pCreate->lpCreateParams);
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			
			pThis->hWnd = hWnd;
		}
		else
		{
			pThis = reinterpret_cast<FWindow *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}
		
		if (pThis) return pThis->OnMessage(msg, wParam, lParam);
		
		return DefaultWindowProc(hWnd, msg, wParam, lParam);
	}
	
	void FWindow::UpdateInputPoint(HIMC hIMC) const
	{
		CANDIDATEFORM candidateForm;
		candidateForm.dwIndex = 0;
		candidateForm.dwStyle = CFS_CANDIDATEPOS;
		candidateForm.ptCurrentPos = inputPoint;
		ImmSetCandidateWindow(hIMC, &candidateForm);
	}
	
	LRESULT FWindow::DefaultWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
	LRESULT FWindow::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_KEYDOWN:
				OnKeyDown(EventKeyArgs{.virtualKey=wParam});
				return 0;
			case WM_KEYUP:
				OnKeyUp(EventKeyArgs{.virtualKey=wParam});
				return 0;
			case WM_MOUSEMOVE:
			{
				int32_t newMouseX = GET_X_LPARAM(lParam);
				int32_t newMouseY = GET_Y_LPARAM(lParam);
				int32_t deltaX = newMouseX - mousePosition.x;
				int32_t deltaY = newMouseY - mousePosition.y;
				mousePosition.x = newMouseX;
				mousePosition.y = newMouseY;
				OnMouseMoved(
					EventOnMouseMoveArgs{.mouseX=mousePosition.x, .mouseY=mousePosition.y, .deltaX=deltaX, .deltaY=deltaY}
				);
				return 0;
			}
			case WM_ACTIVATE:
				switch (LOWORD(wParam))
				{
					case WA_INACTIVE:
						OnInactive();
						break;
					case WA_ACTIVE:
						OnActive();
						break;
					case WA_CLICKACTIVE:
						OnClickActive();
						break;
					default:
						break;
				}
				return 0;
			case WM_SIZE:
				OnResize(EventOnResizeArgs{.width=LOWORD(lParam), .height=HIWORD(lParam)});
				return 0;
			case WM_DROPFILES:
				OnDropFiles((HDROP) wParam);
				::DragFinish((HDROP) wParam);
				return 0;
			case WM_CHAR:
				if (!bEnableOnChar) return DefaultWindowProc(this->hWnd, msg, wParam, lParam);
				OnChar((TChar) wParam);
				return 0;
//			case WM_GETMINMAXINFO:
//				((MINMAXINFO *) lParam)->ptMinTrackSize.x = this->windowSizeClamp.minSize.width;
//				((MINMAXINFO *) lParam)->ptMinTrackSize.y = this->windowSizeClamp.minSize.height;
//				((MINMAXINFO *) lParam)->ptMaxTrackSize.x = this->windowSizeClamp.maxSize.width;
//				((MINMAXINFO *) lParam)->ptMaxTrackSize.y = this->windowSizeClamp.maxSize.height;
//				return 0;
			
			case WM_IME_STARTCOMPOSITION:
			{
				HIMC hIMC;
				
				hIMC = ImmGetContext(hWnd);
				
				if (hIMC) UpdateInputPoint(hIMC);
				else FLogger::Inst().LogErrorODS(TEXT("ImmGetContext Failed"));
				
				ImmReleaseContext(hWnd, hIMC);
				return 0;
			}
			case WM_IME_COMPOSITION:
			{
				HIMC hIMC;
				DWORD dwSize;
				HGLOBAL hstr;
				LPTSTR lpstr;
				if (!bEnableOnChar) return DefaultWindowProc(this->hWnd, msg, wParam, lParam);
				if (lParam & GCS_RESULTSTR)
				{
					hIMC = ImmGetContext(hWnd);
					
					if (hIMC);
					else FLogger::Inst().LogErrorODS(TEXT("ImmGetContext Failed"));
					
					// Get the size of the result string.
					dwSize = ImmGetCompositionString(hIMC, GCS_RESULTSTR, nullptr, 0);
					
					// increase buffer size for terminating null character,
					//   maybe it is in UNICODE
					dwSize += sizeof(WCHAR);
					
					hstr = GlobalAlloc(GHND, dwSize);
					if (hstr == nullptr) FLogger::Inst().LogErrorODS(TEXT("GlobalAlloc Failed"));
					
					lpstr = (LPTSTR) GlobalLock(hstr);
					if (lpstr == nullptr) FLogger::Inst().LogErrorODS(TEXT("GlobalLock Failed"));
					
					// Get the result strings that is generated by IME into lpstr.
					ImmGetCompositionString(hIMC, GCS_RESULTSTR, lpstr, dwSize);
					ImmReleaseContext(hWnd, hIMC);
					
					// add this string into text buffer of application
					if (lpstr != nullptr) OnString(lpstr);
					
					GlobalUnlock(hstr);
					GlobalFree(hstr);
				}
				return 0;
			}
			case WM_SETCURSOR:
				if (LOWORD(lParam) == HTCLIENT)
				{
					if (hCursor == nullptr) return DefaultWindowProc(this->hWnd, msg, wParam, lParam);
					SetCursor((HCURSOR) hCursor);
					return TRUE;
				}
				return DefaultWindowProc(this->hWnd, msg, wParam, lParam);
			case WM_MENUCHAR:
				// 禁用 alt-enter.
				return MAKELRESULT(0, MNC_CLOSE);
			case WM_CLOSE:
				OnClose();
				return 0;
			case WM_QUERYENDSESSION:
				return OnQueryEndSession();
			case WM_ENDSESSION:
				return OnEndSession();
			case WM_DESTROY:
				this->hWnd = nullptr;
				OnDestroy();
				return 0;
			default:
				return DefaultWindowProc(this->hWnd, msg, wParam, lParam);
		}
	}
	
	void FWindow::Show(int32_t nCmdShow) const noexcept
	{
		::ShowWindow(this->hWnd, nCmdShow);
	}
	
	void FWindow::Update() const noexcept
	{
		::UpdateWindow(this->hWnd);
	}
	
	void FWindow::Tick(float deltaTime)
	{
		OnTick(deltaTime);
	}
	
	FPoint2I FWindow::GetMousePosition() const noexcept
	{
		POINT point;
		::GetCursorPos(&point);
		::ScreenToClient(this->hWnd, &point);
		return FPoint2I{.x = point.x, .y = point.y};
	}
	
	bool FWindow::GetFileDragAndDropPermission() const noexcept
	{
		if (!ChangeWindowMessageFilterEx(this->hWnd, WM_DROPFILES, MSGFLT_ADD, nullptr))
		{
			return false;
		}
		if (!ChangeWindowMessageFilterEx(this->hWnd, WM_COPYDATA, MSGFLT_ADD, nullptr))
		{
			return false;
		}
		if (!ChangeWindowMessageFilterEx(this->hWnd, 0x49 /* WM_COPYGLOBALDATA */, MSGFLT_ADD, nullptr))
		{
			return false;
		}
		return true;
	}
	
	bool FWindowClass::Register(void *hIcon, void *hIconSm, void *hCursor, uint32_t style) const noexcept
	{
		if (hIcon == nullptr) hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		if (hIconSm == nullptr) hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		if (hCursor == nullptr) hCursor = LoadCursor(nullptr, IDC_ARROW);
		WNDCLASSEX wnd
			{
				.cbSize = sizeof wnd,
				.style = style,
				.lpfnWndProc = FWindow::WindowProc,
				.cbClsExtra = 0,
				.cbWndExtra = sizeof(FWindow *),
				.hInstance = (HINSTANCE) this->hInstance,
				.hIcon = (HICON) hIcon,
				.hCursor = (HCURSOR) hCursor,
				.hbrBackground = nullptr,
				.lpszMenuName = nullptr,
				.lpszClassName = this->name.c_str(),
				.hIconSm = (HICON) hIconSm
			};
		return ::RegisterClassEx(&wnd);
	}
	
	bool FWindowClass::Unregister() const noexcept
	{
		return ::UnregisterClass(this->name.c_str(), (HINSTANCE) this->hInstance);
	}
	
} // GenesisCube