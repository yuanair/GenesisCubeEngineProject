//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Core/Header.h"

#include "../Core/FCore.h"
#include "../Object/GObject.h"
#include "../Core/TEvent.h"
#include "../Core/FTimer.h"
#include "../Helpers/Helpers.h"
#include "../Debug/Debug.h"

namespace GenesisCubeEngine
{
	//
	// 窗口
	//
	class FWindow
	{
		
		friend int Run();
	
	public:
		
		//
		// 事件参数
		//
		struct EventArgs
		{
			//
			// 事件发生的窗口
			//
			FWindow &window;
			
			explicit EventArgs(FWindow &window) : window(window) {}
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
			
			EventOnTickArgs(FWindow &window, float deltaTime) : EventArgs(window), deltaTime(deltaTime) {}
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
			
			EventOnMouseMoveArgs(FWindow &window, int32_t deltaX, int32_t deltaY) : EventArgs(window), deltaX(deltaX),
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
			
			EventOnResizeArgs(FWindow &window, int32_t width, int32_t height) : EventArgs(window), width(width),
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
			
			EventOnDropFilesArgs(FWindow &window, HDROP hDropInfo) : EventArgs(window), hDropInfo(hDropInfo) {}
		};
	
	public:
		
		FWindow();
		
		~FWindow();
	
	public:
		
		///
		/// 销毁args.window窗口，可添加到eOnClose事件中
		///
		/// \param args 参数
		///
		static void DestroyOnClose(EventArgs args);
		
		///
		/// 退出程序，可添加到eOnDestroy事件中
		///
		/// \param args 参数
		///
		static void ExitOnDestroy(EventArgs args);
		
		///
		/// 注册窗口类
		///
		/// \param className 类名
		/// \param hIcon 图标
		/// \param hIconSm 小图标
		/// \param style 样式
		/// \param hCursor 光标
		/// \param hbrBackground 背景笔刷
		/// \param menuName 菜单名
		/// \return 是否成功
		static bool Register
			(
				const TString &className,
				HICON hIcon = LoadIcon(nullptr, IDI_APPLICATION),
				HICON hIconSm = LoadIcon(nullptr, IDI_APPLICATION),
				UINT style = CS_HREDRAW | CS_VREDRAW,
				HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW),
				HBRUSH hbrBackground = (HBRUSH) GetStockBrush(NULL_BRUSH),
				const TString &menuName = TString()
			);
		
		///
		/// 消息框
		///
		/// \param text 文字
		/// \param caption 标题
		/// \param uType 类型
		/// \param hwnd 窗口句柄
		/// \param wLanguageId 语言ID
		/// \return 按下的按钮
		///
		static int MBox(const TString &text, const TString &caption, UINT uType = MB_OK, HWND hWnd = nullptr,
						WORD wLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
		
		///
		/// 窗口创建
		///
		/// \param className 类名，必须的参数
		/// \param windowName 窗口名，必须的参数
		/// \param dwStyle 样式
		/// \param dwExStyle 扩展样式，可为0
		/// \param hWndParent 父窗口句柄，可为nullptr
		/// \param hMenu 菜单，可为nullptr
		/// \return 是否成功
		///
		bool Create(const TString &className, const TString &windowName,
					DWORD dwStyle = WS_OVERLAPPEDWINDOW, DWORD dwExStyle = WS_EX_ACCEPTFILES, HWND hWndParent = nullptr,
					HMENU hMenu = nullptr);
		
		///
		/// 获取图标
		/// \param iconName 图标名
		/// \param hInstance 应用实例
		/// \return 图标
		static HICON GetIcon(const TString &iconName, HINSTANCE hInstance);
		
		
		///
		/// 获取图标
		/// \param iconId 图标ID
		/// \param hInstance 应用实例
		/// \return 图标
		static HICON GetIcon(short iconId, HINSTANCE hInstance);
		
		///
		/// 获取图标
		/// \param iconName 图标名
		/// \return 图标
		static HICON GetIcon(const TString &iconName);
		
		
		///
		/// 获取图标
		/// \param iconId 图标ID
		/// \return 图标
		static HICON GetIcon(short iconId);
		
		///
		/// 子窗口创建
		///
		/// \param className 类名，必须的参数
		/// \param hWndParent 父窗口句柄，不可为nullptr
		/// \param windowName 窗口名，非必须
		/// \param dwStyle 样式
		/// \param dwExStyle 扩展样式，可为0
		/// \param hMenu 菜单，可为nullptr
		/// \return 是否成功
		///
		bool SubWindowCreate(const TString &className, HWND hWndParent, const TString &windowName = TEXT(""),
							 DWORD dwStyle = WS_OVERLAPPED | WS_CHILD | WS_VISIBLE,
							 DWORD dwExStyle = WS_EX_ACCEPTFILES, HMENU hMenu = nullptr);
		
		///
		/// 消息框
		///
		/// \param text 显示的文字
		/// \param caption 消息框标题
		/// \param uType 类型
		/// \param wLanguageId 语言ID
		/// \return 按下的按钮
		///
		int SubMBox(const TString &text, const TString &caption, UINT uType = MB_OK,
					WORD wLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
		
		///
		/// 第一次显示窗口时调用
		///
		/// \param nCmdShow 可传入WinMain的参数nShowCmd
		void ShowAndUpdate(int nCmdShow);
		
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
		
		///
		/// 每帧调用
		///
		void Tick();
		
		///
		/// 获取窗口名字
		///
		[[nodiscard]]
		TString GetWindowName() const;
		
		///
		/// 设置窗口名字，在创建窗口后
		///
		void SetWindowName(const TString &name) const;
		
		///
		/// 设置窗口大小
		///
		void SetWindowSize(FSize<int32_t> size);
		
		///
		/// 设置窗口矩形
		///
		void SetWindowRect(FRect<int32_t> rect);
	
	private:
		
		static LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);
	
	public:
		
		///
		/// \return 窗口句柄
		///
		[[nodiscard]]
		inline auto GetHwnd() const noexcept { return this->hWnd; }
		
		///
		/// \return 鼠标x坐标
		///
		[[nodiscard]]
		inline auto GetMouseX() const noexcept { return this->mouseX; }
		
		///
		/// \return 鼠标y坐标
		///
		[[nodiscard]]
		inline auto GetMouseY() const noexcept { return this->mouseY; }
		
		///
		/// \return 窗口矩形
		///
		[[nodiscard]]
		inline auto GetWindowRect() const noexcept { return this->windowRect; }
	
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
