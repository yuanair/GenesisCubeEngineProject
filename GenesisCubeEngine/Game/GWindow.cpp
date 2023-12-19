//
// Created by admin on 2023/12/19.
//

#include "GWindow.h"

namespace GenesisCubeEngine
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
    
    
    bool GWindow::Create(const TString &className, const TString &windowName)
    {
        this->hWnd = CreateWindowEx
            (
                WS_EX_ACCEPTFILES,
                className.c_str(),
                windowName.c_str(),
                WS_OVERLAPPEDWINDOW,
                this->windowRect.x,
                this->windowRect.y,
                this->windowRect.width,
                this->windowRect.height,
                nullptr,
                nullptr,
                Core::hInstance,
                this
            );
        return this->hWnd;
    }
    
    bool GWindow::Register(const TString &className, HICON hIcon, HICON hIconSm,
                           HCURSOR hCursor, const TString &menuName)
    {
        WNDCLASSEX wnd
            {
                .cbSize = sizeof(wnd),
                .style = CS_HREDRAW | CS_VREDRAW,
                .lpfnWndProc = GWindow::WindowProc,
                .cbClsExtra = 0,
                .cbWndExtra = sizeof(GWindow *),
                .hInstance = Core::hInstance,
                .hIcon = hIcon,
                .hCursor = hCursor,
                .hbrBackground = (HBRUSH) GetStockBrush(NULL_BRUSH),
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
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
            
            pThis->hWnd = hWnd;
        }
        else
        {
            pThis = reinterpret_cast<GWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }
        
        if (pThis) return pThis->OnMessage(msg, wParam, lParam);
        
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    
    LRESULT GWindow::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
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
            case WM_SIZE:
                eOnResize.Trigger(EventOnResizeArgs(*this, LOWORD(lParam), HIWORD(lParam)));
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
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(this->hWnd, message, wParam, lParam);
        }
    }
    
    int GWindow::MBox(const TString &text, const TString &caption, UINT uType, WORD wLanguageId)
    {
        return MessageBoxEx(this->hWnd, text.c_str(), caption.c_str(), uType, wLanguageId);
    }
    
    int GWindow::MBox(HWND hwnd, const TString &text, const TString &caption, UINT uType, WORD wLanguageId)
    {
        return MessageBoxEx(hwnd, text.c_str(), caption.c_str(), uType, wLanguageId);
    }
    
    void GWindow::Tick()
    {
        this->timer.Tick();
        this->eOnTick.Trigger(EventOnTickArgs(*this, (float) this->timer.GetDeltaTime()));
    }
    
    void GWindow::ShowAndUpdate(int nCmdShow)
    {
        this->timer.Reset();
        ShowWindow(this->hWnd, nCmdShow);
        UpdateWindow(this->hWnd);
    }
    
    void GWindow::Show() const
    {
        ShowWindow(this->hWnd, SW_SHOW);
    }
    
    void GWindow::Hide() const
    {
        ShowWindow(this->hWnd, SW_HIDE);
    }
    
    void GWindow::Minimize() const
    {
        ShowWindow(this->hWnd, SW_MINIMIZE);
    }
    
    void GWindow::Maximize() const
    {
        ShowWindow(this->hWnd, SW_MAXIMIZE);
    }
    
    void GWindow::Destroy() const
    {
        DestroyWindow(this->hWnd);
    }
    
} // GenesisCubeEngine