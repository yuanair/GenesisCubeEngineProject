//
// Created by admin on 2023/12/19.
//

#include "FWindow.h"

namespace GenesisCubeEngine
{
    
    FWindow::FWindow()
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
    
    FWindow::~FWindow()
    {
        Destroy();
    }
    
    
    bool FWindow::Create(const TString &className, const TString &windowName, DWORD dwStyle, DWORD dwExStyle,
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
                Core::GetInstance(),
                this
            );
        if (!this->hWnd)
            throw EBadException(
                (__FUNCSIG__ TEXT(":: FWindow::Create(")) + windowName + TEXT(") Failed")
            );
        return true;
    }
    
    bool FWindow::SubWindowCreate(
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
                Core::GetInstance(),
                this
            );
        if (!this->hWnd)
            throw EBadException(
                (__FUNCSIG__ TEXT(":: FWindow::Create(")) + windowName + TEXT(") Failed")
            );
        return true;
    }
    
    bool FWindow::Register(const TString &className, HICON hIcon, HICON hIconSm, UINT style,
                           HCURSOR hCursor, HBRUSH hbrBackground, const TString &menuName)
    {
        WNDCLASSEX wnd
            {
                .cbSize = sizeof(wnd),
                .style = style,
                .lpfnWndProc = FWindow::WindowProc,
                .cbClsExtra = 0,
                .cbWndExtra = sizeof(FWindow *),
                .hInstance = Core::GetInstance(),
                .hIcon = hIcon,
                .hCursor = hCursor,
                .hbrBackground = hbrBackground,
                .lpszMenuName = menuName.c_str(),
                .lpszClassName = className.c_str(),
                .hIconSm = hIconSm
            };
        if (!RegisterClassEx(&wnd))
            throw EBadException(
                (__FUNCSIG__ TEXT(":: FWindow::Register(")) + className + TEXT(") Failed")
            );
        return true;
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
        
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
    
    LRESULT FWindow::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_MOUSEMOVE:
            {
                int32_t newMouseX = GET_X_LPARAM(lParam);
                int32_t newMouseY = GET_Y_LPARAM(lParam);
                int32_t deltaX = newMouseX - mouseX;
                int32_t deltaY = newMouseY - mouseY;
                mouseX = newMouseX;
                mouseY = newMouseY;
                eOnMouseMoved.Trigger(EventOnMouseMoveArgs(*this, deltaX, deltaY));
                return 0;
            }
            case WM_ACTIVATE:
            {
                EventArgs args(*this);
                switch (LOWORD(wParam))
                {
                    case WA_INACTIVE:
                        eOnInactive.Trigger(args);
                        break;
                    case WA_ACTIVE:
                        eOnActive.Trigger(args);
                        break;
                    case WA_CLICKACTIVE:
                        eOnClickActive.Trigger(args);
                        break;
                    default:
                        break;
                }
                return 0;
            }
            case WM_MOVE:
                this->windowRect.x = LOWORD(lParam);
                this->windowRect.y = HIWORD(lParam);
                return TRUE;
            case WM_SIZE:
                this->windowRect.width = LOWORD(lParam);
                this->windowRect.height = HIWORD(lParam);
                eOnResize.Trigger(EventOnResizeArgs(*this, this->windowRect.width, this->windowRect.height));
                return 0;
            case WM_DROPFILES:
                eOnDropFiles.Trigger(EventOnDropFilesArgs(*this, (HDROP) wParam));
                ::DragFinish((HDROP) wParam);
                return 0;
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
                eOnClose.Trigger(EventArgs(*this));
                return 0;
            case WM_QUERYENDSESSION:
                eOnQueryEndSession.Trigger(EventArgs(*this));
                return this->bCanEndSession;
            case WM_ENDSESSION:
                eOnEndSession.Trigger(EventArgs(*this));
                return this->bCanEndSession;
            case WM_DESTROY:
                this->hWnd = nullptr;
                eOnDestroy.Trigger(EventArgs(*this));
                return 0;
            default:
                return ::DefWindowProc(this->hWnd, message, wParam, lParam);
        }
    }
    
    int FWindow::SubMBox(const TString &text, const TString &caption, UINT uType, WORD wLanguageId)
    {
        return ::MessageBoxEx(this->hWnd, text.c_str(), caption.c_str(), uType, wLanguageId);
    }
    
    int FWindow::MBox(const TString &text, const TString &caption, UINT uType, HWND hWnd, WORD wLanguageId)
    {
        return ::MessageBoxEx(hWnd, text.c_str(), caption.c_str(), uType, wLanguageId);
    }
    
    void FWindow::ShowAndUpdate()
    {
        this->timer.Reset();
        ::ShowWindow(this->hWnd, Core::GetShowCmd());
        ::UpdateWindow(this->hWnd);
    }
    
    void FWindow::Show() const
    {
        ::ShowWindow(this->hWnd, SW_SHOW);
    }
    
    void FWindow::Hide() const
    {
        ::ShowWindow(this->hWnd, SW_HIDE);
    }
    
    void FWindow::Minimize() const
    {
        ::ShowWindow(this->hWnd, SW_MINIMIZE);
    }
    
    void FWindow::Maximize() const
    {
        ::ShowWindow(this->hWnd, SW_MAXIMIZE);
    }
    
    void FWindow::Destroy() const
    {
        ::DestroyWindow(this->hWnd);
    }
    
    void FWindow::SetWindowSize(FSize<int32_t> size)
    {
        ::MoveWindow(this->hWnd, this->windowRect.x, this->windowRect.y, size.width, size.height, true);
    }
    
    void FWindow::SetWindowRect(FRect<int32_t> rect)
    {
        ::MoveWindow(this->hWnd, rect.x, rect.y, rect.width, rect.height, true);
    }
    
    void FWindow::DestroyOnClose(FWindow::EventArgs args)
    {
        args.window.Destroy();
    }
    
    void FWindow::ExitOnDestroy(FWindow::EventArgs args)
    {
        Core::Exit();
    }
    
    TString FWindow::GetWindowName() const
    {
        if (this->hWnd == nullptr) return TEXT("nullptr");
        int length = ::GetWindowTextLength(this->hWnd) + 1;
        auto *string = new TChar[length];
        ::GetWindowText(this->hWnd, string, length);
        TString result = string;
        delete[] string;
        return result;
    }
    
    void FWindow::SetWindowName(const TString &name) const
    {
        if (this->hWnd == nullptr) return;
        ::SetWindowText(this->hWnd, name.c_str());
    }
    
    HICON FWindow::GetIcon(const TString &iconName, HINSTANCE hInstance)
    {
        return ::LoadIcon(hInstance, iconName.c_str());
    }
    
    HICON FWindow::GetIcon(short iconId, HINSTANCE hInstance)
    {
        return ::LoadIcon(hInstance, MAKEINTRESOURCE(iconId));
    }
    
    HICON FWindow::GetIcon(const TString &iconName)
    {
        return GetIcon(iconName, Core::GetInstance());
    }
    
    HICON FWindow::GetIcon(short iconId)
    {
        return GetIcon(iconId, Core::GetInstance());
    }
    
    void FWindow::Tick()
    {
        this->timer.Tick();
        this->eOnTick.Trigger({*this, (float) this->timer.GetDeltaTime()});
    }
    
} // GenesisCubeEngine