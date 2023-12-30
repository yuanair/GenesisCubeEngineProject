//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Core/Header.h"

#include "../Core/FCore.h"
#include "../../GenesisCubeBase/Object/GObject.h"
#include "../../GenesisCubeBase/Core/TEvent.h"
#include "../../GenesisCubeBase/Core/FTimer.h"
#include "../Helpers/Helpers.h"
#include "../Debug/Debug.h"

namespace GenesisCube
{
	///
	/// 窗口
	///
	class GWindow : public GObject
	{
	public:
		
		///
		/// 按键事件参数
		///
		struct EventKeyArgs
		{
			///
			/// 虚拟按键。例如VK_BACK
			///
			uint64_t virtualKey;
			
		};
		
		///
		/// 鼠标移动事件参数
		///
		struct EventOnMouseMoveArgs
		{
			
			//
			// 鼠标x坐标偏移
			//
			int32_t mouseX;
			
			//
			// 鼠标y坐标偏移
			//
			int32_t mouseY;
			
			//
			// 鼠标x坐标偏移
			//
			int32_t deltaX;
			
			//
			// 鼠标y坐标偏移
			//
			int32_t deltaY;
			
		};
		
		//
		// 改变大小事件参数
		//
		struct EventOnResizeArgs
		{
			
			//
			// 窗口宽度
			//
			int32_t width;
			
			//
			// 窗口高度
			//
			int32_t height;
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
		/// 触发事件（有多少消息触发多少事件）
		/// \return 是否成功，返回false说明程序已经调用了FCore::Exit()
		static bool PeekEvents();
		
		///
		/// 第一次显示窗口时调用
		///
		/// \param nCmdShow 可传入WinMain的参数nShowCmd。否则，传入SW_SHOW
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
		/// \param deltaTime 帧时间间隔
		void Tick(float deltaTime);
		
		///
		/// 获取窗口名字，在创建窗口后
		///
		[[nodiscard]]
		TString GetWindowName() const;
		
		///
		/// \return 窗口的显示状态
		[[nodiscard]]
		WINDOWPLACEMENT GetWindowPlacement() const;
		
		///
		/// \return 是否为窗口模式
		[[nodiscard]]
		bool IsWindowed() const;
		
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
	
	protected:
		
		///
		/// 按下按键事件
		///
		/// \param args 参数
		virtual void OnKeyDown(EventKeyArgs args) {}
		
		///
		/// 松开按键事件
		///
		/// \param args 参数
		virtual void OnKeyUp(EventKeyArgs args) {}
		
		///
		/// 鼠标移动事件
		///
		/// \param args 参数
		virtual void OnMouseMoved(EventOnMouseMoveArgs args) {}
		
		///
		/// 窗口大小改变事件
		///
		/// \param args 参数
		virtual void OnResize(EventOnResizeArgs args) {}
		
		///
		/// 输入字符事件
		///
		/// \param input 输入的字符
		virtual void OnChar(const TChar &input) {}
		
		///
		/// 输入字符串事件，用于输入法
		///
		/// \param input 输入的字符串
		virtual void OnString(const TString &input) {}
		
		///
		/// Tick事件
		///
		/// \param deltaTIme 间隔时间
		virtual void OnTick(float deltaTIme) {}
		
		///
		/// 活动事件
		///
		virtual void OnInactive() {}
		
		///
		/// 窗口活动事件
		///
		virtual void OnActive() {}
		
		///
		/// 点击窗口使其活动事件
		///
		virtual void OnClickActive() {}
		
		///
		/// 拖放文件到窗口事件
		///
		/// \param hDropInfo 拖放的文件
		virtual void OnDropFiles(HDROP hDropInfo) {};
		
		///
		/// 关闭事件
		///
		virtual void OnClose() { Destroy(); }
		
		///
		/// 销毁事件
		///
		virtual void OnDestroy() {}
		
		///
		/// 询问关机事件
		///
		/// \return 是否可以关机
		virtual bool OnQueryEndSession() { return true; }
		
		///
		/// 关机事件
		///
		/// \return 是否可以关机
		virtual bool OnEndSession() { return true; }
	
	private:
		
		static LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		LRESULT OnMessage(UINT message, WPARAM wParam, LPARAM lParam);
		
		void UpdateInputPoint(HIMC hIMC) const;
	
	public:
		
		///
		/// \return 窗口句柄
		///
		[[nodiscard]]
		inline auto GetHWnd() const noexcept { return this->hWnd; }
		
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
		
		///
		/// \return 无法克隆窗口，只会返回一个新的GWindow对象
		[[nodiscard]]
		GWindow *Clone() const noexcept override;
	
	public:
		
		///
		/// 是否启用OnChar事件
		///
		bool bEnableOnChar = false;
		
		///
		/// 输入位置，用于输入法定位
		///
		POINT inputPoint = {};
		
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
	
} // GenesisCube
