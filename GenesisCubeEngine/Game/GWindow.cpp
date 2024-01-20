//
// Created by admin on 2023/12/19.
//

#include "GWindow.h"
#include "windowsx.h"

namespace GenesisCube
{
	
	GWindow::GWindow()
	{
		this->windowSizeClamp =
			{
				.minSize=
					{
						.width=400,
						.height=300
					},
				.maxSize=
					{
						.width=0,
						.height=0
					}
			};
		this->windowRect =
			{
				.x=CW_USEDEFAULT,
				.y=CW_USEDEFAULT,
				.width=CW_USEDEFAULT,
				.height=CW_USEDEFAULT
			};
	}
	
	GWindow::~GWindow()
	{
		Destroy();
	}
	
	
	bool GWindow::Create(const TString &className, const TString &windowName, DWORD dwStyle, DWORD dwExStyle,
						 HWND hWndParent, HMENU hMenu)
	{
		this->hWnd = CreateWindowEx
			(
				dwExStyle,
				className.c_str(),
				windowName.c_str(),
				dwStyle,
				this->windowRect.x,
				this->windowRect.y,
				this->windowRect.width,
				this->windowRect.height,
				hWndParent,
				hMenu,
				(HINSTANCE) Win32::GetInstance(),
				this
			);
		if (!this->hWnd)
			throw EBadException(
				(__FUNCSIG__ TEXT(":: FWindow::Create(")) + windowName + TEXT(") Failed")
			);
		return true;
	}
	
	bool GWindow::SubWindowCreate(
		const TString &className, HWND hWndParent, const TString &windowName, DWORD dwStyle, DWORD dwExStyle,
		HMENU hMenu)
	{
		this->hWnd = CreateWindowEx
			(
				dwExStyle,
				className.c_str(),
				windowName.c_str(),
				dwStyle,
				this->windowRect.x,
				this->windowRect.y,
				this->windowRect.width,
				this->windowRect.height,
				hWndParent,
				hMenu,
				(HINSTANCE) Win32::GetInstance(),
				this
			);
		if (!this->hWnd)
			throw EBadException(
				(__FUNCSIG__ TEXT(":: FWindow::Create(")) + windowName + TEXT(") Failed")
			);
		return true;
	}
	
	bool GWindow::Register(const TString &className, HICON hIcon, HICON hIconSm, UINT style,
						   HCURSOR hCursor, HBRUSH hbrBackground, const TString &menuName)
	{
		WNDCLASSEX wnd
			{
				.cbSize = sizeof(wnd),
				.style = style,
				.lpfnWndProc = GWindow::WindowProc,
				.cbClsExtra = 0,
				.cbWndExtra = sizeof(GWindow *),
				.hInstance = (HINSTANCE) Win32::GetInstance(),
				.hIcon = hIcon,
				.hCursor = hCursor,
				.hbrBackground = hbrBackground,
				.lpszMenuName = menuName.c_str(),
				.lpszClassName = className.c_str(),
				.hIconSm = hIconSm
			};
		return RegisterClassEx(&wnd);
	}
	
	LRESULT GWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		GWindow *pThis;
		
		if (msg == WM_NCCREATE)
		{
			auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
			pThis = reinterpret_cast<GWindow *>(pCreate->lpCreateParams);
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			
			pThis->hWnd = hWnd;
		}
		else
		{
			pThis = reinterpret_cast<GWindow *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}
		
		if (pThis) return pThis->OnMessage(msg, wParam, lParam);
		
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}
	
	LRESULT GWindow::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		HIMC hIMC;
		DWORD dwSize;
		HGLOBAL hstr;
		LPTSTR lpstr;
		switch (message)
		{
			case WM_KEYDOWN:
			{
				OnKeyDown(EventKeyArgs{.virtualKey=wParam});
				return 0;
			}
			case WM_KEYUP:
			{
				OnKeyUp(EventKeyArgs{.virtualKey=wParam});
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				int32_t newMouseX = GET_X_LPARAM(lParam);
				int32_t newMouseY = GET_Y_LPARAM(lParam);
				int32_t deltaX = newMouseX - mouseX;
				int32_t deltaY = newMouseY - mouseY;
				mouseX = newMouseX;
				mouseY = newMouseY;
				OnMouseMoved(EventOnMouseMoveArgs{.mouseX=mouseX, .mouseY=mouseY, .deltaX=deltaX, .deltaY=deltaY});
				return 0;
			}
			case WM_ACTIVATE:
			{
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
			}
			case WM_MOVE:
				this->windowRect.x = LOWORD(lParam);
				this->windowRect.y = HIWORD(lParam);
				return 0;
			case WM_SIZE:
				this->windowRect.width = LOWORD(lParam);
				this->windowRect.height = HIWORD(lParam);
				OnResize(EventOnResizeArgs{.width=this->windowRect.width, .height=this->windowRect.height});
				return 0;
			case WM_DROPFILES:
				OnDropFiles((HDROP) wParam);
				::DragFinish((HDROP) wParam);
				return 0;
			case WM_IME_STARTCOMPOSITION:
			{
				if (!bEnableOnChar)return ::DefWindowProc(this->hWnd, message, wParam, lParam);
				
				hIMC = ImmGetContext(hWnd);
				
				if (hIMC) UpdateInputPoint(hIMC);
				else FLogger::Inst().LogErrorODS(TEXT("ImmGetContext Failed"));
				
				ImmReleaseContext(hWnd, hIMC);
				return 0;
			}
			case WM_IME_COMPOSITION:
			{
				if (!bEnableOnChar)return ::DefWindowProc(this->hWnd, message, wParam, lParam);
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
			case WM_CHAR:
			{
				if (!bEnableOnChar)return ::DefWindowProc(this->hWnd, message, wParam, lParam);
				OnChar((TChar) wParam);
				return 0;
			}
			case WM_GETMINMAXINFO:
			{
				if (this->windowSizeClamp.maxSize.width == 0 || this->windowSizeClamp.maxSize.height == 0)
				{
					RECT rect;
					GetClientRect(GetDesktopWindow(), &rect);
					
					this->windowSizeClamp.maxSize.width = rect.right - rect.left;
					this->windowSizeClamp.maxSize.height = rect.bottom - rect.top;
				}
				((MINMAXINFO *) lParam)->ptMinTrackSize.x = this->windowSizeClamp.minSize.width;
				((MINMAXINFO *) lParam)->ptMinTrackSize.y = this->windowSizeClamp.minSize.height;
				((MINMAXINFO *) lParam)->ptMaxTrackSize.x = this->windowSizeClamp.maxSize.width;
				((MINMAXINFO *) lParam)->ptMaxTrackSize.y = this->windowSizeClamp.maxSize.height;
				return 0;
			}
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
				return ::DefWindowProc(this->hWnd, message, wParam, lParam);
		}
		throw EException(__FUNCSIG__ TEXT("A Bug"));
	}
	
	void GWindow::UpdateInputPoint(HIMC hIMC) const
	{
		CANDIDATEFORM candidateForm;
		candidateForm.dwIndex = 0;
		candidateForm.dwStyle = CFS_CANDIDATEPOS;
		candidateForm.ptCurrentPos = inputPoint;
		ImmSetCandidateWindow(hIMC, &candidateForm);
	}
	
	void GWindow::ShowAndUpdate(int nCmdShow)
	{
		::ShowWindow(this->hWnd, nCmdShow);
		::UpdateWindow(this->hWnd);
	}
	
	void GWindow::Show() const
	{
		::ShowWindow(this->hWnd, SW_SHOW);
	}
	
	void GWindow::Hide() const
	{
		::ShowWindow(this->hWnd, SW_HIDE);
	}
	
	void GWindow::Minimize() const
	{
		::ShowWindow(this->hWnd, SW_MINIMIZE);
	}
	
	void GWindow::Maximize() const
	{
		::ShowWindow(this->hWnd, SW_MAXIMIZE);
	}
	
	void GWindow::Destroy() const
	{
		::DestroyWindow(this->hWnd);
	}
	
	void GWindow::SetWindowSize(FSize<int32_t> size)
	{
		::MoveWindow(this->hWnd, this->windowRect.x, this->windowRect.y, size.width, size.height, true);
	}
	
	void GWindow::SetWindowRect(FRect<int32_t> rect)
	{
		::MoveWindow(this->hWnd, rect.x, rect.y, rect.width, rect.height, true);
	}
	
	TString GWindow::GetWindowName() const
	{
		if (this->hWnd == nullptr) return TEXT("nullptr");
		int length = ::GetWindowTextLength(this->hWnd) + 1;
		auto *string = new TChar[length];
		::GetWindowText(this->hWnd, string, length);
		TString result = string;
		delete[] string;
		return result;
	}
	
	void GWindow::SetWindowName(const TString &name) const
	{
		if (this->hWnd == nullptr) return;
		::SetWindowText(this->hWnd, name.c_str());
	}
	
	void GWindow::Tick(float deltaTime)
	{
		OnTick(deltaTime);
	}
	
	WINDOWPLACEMENT GWindow::GetWindowPlacement() const
	{
		WINDOWPLACEMENT windowPlacement;
		::GetWindowPlacement(this->hWnd, &windowPlacement);
		return windowPlacement;
	}
	
	bool GWindow::IsWindowed() const
	{
		return GetWindowPlacement().showCmd != SW_MAXIMIZE;
	}
	
} // GenesisCube