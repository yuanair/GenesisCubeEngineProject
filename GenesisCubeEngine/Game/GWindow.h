//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Core/GenesisCubeEngine.h"

#include "../Core/Core.h"
#include "../Object/GObject.h"
#include "../Core/TEvent.h"
#include "../Core/FTimer.h"
#include "../Helpers/Helpers.h"

namespace GenesisCubeEngine
{
    //
    // 窗口
    //
    class GWindow : public GObject
    {
    public:
        
        // 
        // 事件参数
        // 
        struct EventArgs
        {
            // 
            // 事件发生的窗口
            // 
            GWindow &window;
            
            explicit EventArgs(GWindow &window) : window(window) {}
        };
        
        // 
        // Tick事件参数
        // 
        struct EventOnTickArgs : public EventArgs
        {
            // 
            // 帧间隔时间
            // 
            float deltaTime;
            
            EventOnTickArgs(GWindow &window, float deltaTime) : EventArgs(window), deltaTime(deltaTime) {}
        };
        
        // 
        // 鼠标移动事件参数
        // 
        struct EventOnMouseMoveArgs : public EventArgs
        {
            // 
            // 鼠标x坐标偏移
            // 
            int32_t deltaX;
            
            // 
            // 鼠标y坐标偏移
            // 
            int32_t deltaY;
            
            EventOnMouseMoveArgs(GWindow &window, int32_t deltaX, int32_t deltaY) : EventArgs(window), deltaX(deltaX),
                                                                                    deltaY(deltaY) {}
        };
        
        // 
        // 改变大小事件参数
        // 
        struct EventOnResizeArgs : public EventArgs
        {
            // 
            // 窗口宽度
            // 
            int32_t width;
            
            // 
            // 窗口高度
            // 
            int32_t height;
            
            EventOnResizeArgs(GWindow &window, int32_t width, int32_t height) : EventArgs(window), width(width),
                                                                                height(height) {}
        };
        
        //
        // 拖放文件事件参数
        //
        struct EventOnDropFilesArgs : public EventArgs
        {
            // 
            // 拖放的文件
            // 
            HDROP hDropInfo;
            
            EventOnDropFilesArgs(GWindow &window, HDROP hDropInfo) : EventArgs(window), hDropInfo(hDropInfo) {}
        };
    
    public:
        
        GWindow();
        
        ~GWindow() override;
    
    public:
        
        ///
        /// 注册窗口类
        ///
        /// \param className 类名
        /// \param hIcon 图标
        /// \param hIconSm 小图标
        /// \param hCursor 光标
        /// \param menuName 菜单名
        /// \return 是否成功
        static bool Register
            (
                const TString &className,
                HICON hIcon = LoadIcon(nullptr, IDI_APPLICATION),
                HICON hIconSm = LoadIcon(nullptr, IDI_APPLICATION),
                HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW),
                const TString &menuName = TString()
            );
        
        ///
        /// 消息框
        ///
        /// \param hwnd 窗口句柄
        /// \param text 文字
        /// \param caption 标题
        /// \param uType 类型
        /// \param wLanguageId 语言ID
        /// \return 按下的按钮
        ///
        static int MBox(HWND hwnd, const TString &text, const TString &caption, UINT uType = MB_OK,
                        WORD wLanguageId = SUBLANG_DEFAULT);
        
        /// 
        /// 创建窗口
        /// 
        /// \param className 类名
        /// \param windowName 窗口名
        /// \return 是否成功
        /// 
        bool Create(const TString &className, const TString &windowName);
        
        /// 
        /// 消息框
        /// 
        /// \param text 显示的文字
        /// \param caption 消息框标题
        /// \param uType 类型
        /// \param wLanguageId 语言ID
        /// \return 按下的按钮
        /// 
        int MBox(const TString &text, const TString &caption, UINT uType = MB_OK,
                 WORD wLanguageId = SUBLANG_DEFAULT);
        
        /// 
        /// Tick
        /// 
        void Tick();
        
        /// 
        /// 第一次显示窗口时调用
        /// 
        /// \param nCmdShow 显示代码
        ///
        void ShowAndUpdate(int nCmdShow = Core::nShowCmd);
        
        /// 
        /// 显示窗口
        /// 
        void Show() const;
        
        /// 
        /// 隐藏窗口
        /// 
        void Hide() const;
        
        /// 
        /// 最小化窗口
        /// 
        void Minimize() const;
        
        /// 
        /// 最大化窗口
        /// 
        void Maximize() const;
        
        /// 
        /// 销毁窗口
        /// 
        void Destroy() const;
    
    private:
        
        static LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        
        LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);
    
    public:
        
        ///
        /// \return 窗口句柄
        ///
        [[nodiscard]]
        inline HWND GetHwnd() const noexcept { return this->hWnd; }
        
        ///
        /// \return 鼠标x坐标
        ///
        [[nodiscard]]
        inline int32_t GetMouseX() const noexcept { return this->mouseX; }
        
        ///
        /// \return 鼠标y坐标
        ///
        [[nodiscard]]
        inline int32_t GetMouseY() const noexcept { return this->mouseY; }
    
    public:
        
        /// 
        /// 窗口Tick事件
        /// 
        TEvent<EventOnTickArgs> eOnTick;
        
        /// 
        /// 鼠标移动事件
        /// 
        TEvent<EventOnMouseMoveArgs> eOnMouseMoved;
        
        /// 
        /// 窗口大小改变事件
        /// 
        TEvent<EventOnResizeArgs> eOnResize;
        
        /// 
        /// 活动事件
        /// 
        TEvent<EventArgs> eOnInactive;
        
        /// 
        /// 窗口活动事件
        /// 
        TEvent<EventArgs> eOnActive;
        
        /// 
        /// 点击窗口使其活动事件
        /// 
        TEvent<EventArgs> eOnClickActive;
        
        /// 
        /// 拖放文件到窗口事件
        /// 
        TEvent<EventOnDropFilesArgs> eOnDropFiles;
        
        /// 
        /// 窗口关闭事件
        /// 
        TEvent<EventArgs> eOnClose;
        
        /// 
        /// 询问关机事件
        /// 
        TEvent<EventArgs> eOnQueryEndSession;
        
        /// 
        /// 关机事件
        /// 
        TEvent<EventArgs> eOnEndSession;
        
        /// 
        /// 窗口销毁事件
        /// 
        TEvent<EventArgs> eOnDestroy;
        
        /// 
        /// 计时器
        /// 
        FTimer timer;
        
        /// 
        /// 是否可以关机
        /// 
        bool bCanEndSession = false;
        
        ///
        /// 窗口大小限制
        ///
        FSizeClamp<int32_t> windowSizeClamp = {};
    
    private:
        
        HWND hWnd = nullptr;
        
        int32_t mouseX = 0;
        
        int32_t mouseY = 0;
        
        FRect<int32_t> windowRect = {};
        
    };
    
} // GenesisCubeEngine
