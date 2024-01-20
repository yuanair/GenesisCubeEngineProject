//
// Created by admin on 2024/1/12.
//

#pragma once

#include "../Core/Header.h"
#include "../Core/FCore.h"
#include "../Object/GObject.h"
#include "../Core/GenesisCubeDef.h"
#include "Core.h"

namespace GenesisCube::Win32
{
	
	///
	/// 窗口类
	///
	class FWindowClass
	{
	public:
		
		///
		/// \param name 类名
		/// \param hInstance 应用实例
		inline FWindowClass(TString name, void *hInstance) noexcept
			: name(std::move(name)), hInstance(hInstance)
		{
		
		}
		
		inline ~FWindowClass() noexcept {}
	
	public:
		
		///
		/// 注册窗口类
		/// \param hIcon 图标
		/// \param hIconSm 小图标
		/// \param hCursor 鼠标指针
		/// \param style 样式
		/// \return 是否成功
		[[nodiscard]]
		bool Register(void *hIcon = nullptr, void *hIconSm = nullptr,
					  void *hCursor = nullptr, uint32_t style = 0) const noexcept;
		
		///
		/// 取消注册（windows会自动在程序退出时取消注册所有窗口类）
		/// \return 是否成功（当还有使用该窗口类创建的窗口时，无法取消注册该窗口类）
		[[nodiscard]]
		bool Unregister() const noexcept;
	
	public:
		
		///
		/// \return 窗口类名
		[[nodiscard]]
		inline TString GetName() const noexcept { return this->name; }
		
		///
		/// \return 应用实例
		[[nodiscard]]
		inline void *GetHInstance() const noexcept { return this->hInstance; }
	
	private:
		
		const TString name;
		
		void *hInstance;
		
	};
	
	///
	/// Win32窗口
	///
	class FWindow
	{
		
		friend class FWindowClass;
	
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
			// 鼠标x坐标
			//
			int32_t mouseX;
			
			//
			// 鼠标y坐标
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
		
		///
		/// 构造
		inline FWindow() noexcept
			: hWnd(INVALID_HANDLE_VALUE)
		{
		
		}
		
		///
		/// 拷贝构造
		FWindow(const FWindow &) = delete;
		
		///
		/// 析构
		inline virtual ~FWindow() noexcept { Destroy(); }
		
		///
		/// 赋值
		FWindow &operator=(const FWindow &) = delete;
	
	public:
		
		///
		/// \return 桌面分辨率
		[[nodiscard]]
		static FSize2I GetDesktopSize() noexcept;
		
		///
		/// 查找窗口
		static void *FindWindowFromName(const TString &windowName);
		
		///
		/// 查找窗口
		static void *FindWindowFromName(const TString &windowName, const TString &windowClassName);
		
		///
		/// 设为前景窗口
		/// \param hWnd 句柄
		static void SetForegroundWindow(void *hWnd);
		
		///
		/// 按下键
		/// \param hwnd 句柄
		/// \param vk 虚拟键
		static void SeedKeyDown(void *hwnd, TChar vk);
		
		///
		/// 松开键
		/// \param hwnd 句柄
		/// \param vk 虚拟键
		static void SeedKeyUp(void *hwnd, TChar vk);
		
		///
		/// 创建窗口
		/// \param windowClass 窗口类（必须已经成功注册）
		/// \param windowName 窗口名
		/// \param x 横坐标
		/// \param y 纵坐标
		/// \param w 宽
		/// \param h 高
		/// \param hinstance 应用实例
		/// \param hWndParent 父窗口句柄
		void Create(
			const FWindowClass &windowClass, const TString &windowName,
			int32_t x = INT_MIN, int32_t y = INT_MIN, int32_t w = INT_MIN, int32_t h = INT_MIN,
			void *hInstance = nullptr, void *hWndParent = nullptr
		) noexcept;
		
		///
		/// 第一次显示窗口时调用
		///
		/// \param nCmdShow 可传入WinMain的参数nShowCmd。否则，传入SW_SHOW
		inline void ShowAndUpdate() const noexcept
		{
			Show(Win32::GetCommandShow());
			Update();
		}
		
		///
		/// 显示窗口时调用
		///
		/// \param nCmdShow
		void Show(int32_t nCmdShow) const noexcept;
		
		///
		/// 更新窗口时调用
		///
		void Update() const noexcept;
		
		///
		/// 获取文件拖动权限
		[[nodiscard]]
		bool GetFileDragAndDropPermission() const noexcept;
		
		///
		/// 销毁窗口
		void Destroy() const noexcept;
		
		///
		/// 每帧调用
		///
		/// \param deltaTime 帧时间间隔
		void Tick(float deltaTime);
		
		///
		/// \return 是否可用
		[[nodiscard]]
		bool Good() const noexcept;
		
		///
		/// \return 是否不可用
		[[nodiscard]]
		bool Bad() const noexcept;
		
		///
		/// \return 窗口矩形
		[[nodiscard]]
		FRectI GetClientRect() const noexcept;
		
		///
		/// \return 窗口矩形
		[[nodiscard]]
		FRectI GetWindowRect() const noexcept;
		
		///
		/// \return 鼠标位置
		[[nodiscard]]
		FPoint2I GetMousePosition() const noexcept;
	
	protected:
		
		///
		/// 按下按键事件
		///
		/// \param args 参数
		virtual void OnKeyDown(const EventKeyArgs &args) {}
		
		///
		/// 松开按键事件
		///
		/// \param args 参数
		virtual void OnKeyUp(const EventKeyArgs &args) {}
		
		///
		/// 鼠标移动事件
		///
		/// \param args 参数
		virtual void OnMouseMoved(const EventOnMouseMoveArgs &args) {}
		
		///
		/// 窗口大小改变事件
		///
		/// \param args 参数
		virtual void OnResize(const EventOnResizeArgs &args) {}
		
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
		virtual void OnTick(float_t deltaTIme) {}
		
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
	
	public:
		
		///
		/// \return 窗口句柄
		[[nodiscard]]
		inline void *GetHWnd() const noexcept { return this->hWnd; }
	
	private:
		
		static LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		static LRESULT DefaultWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		LRESULT OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);
		
		void UpdateInputPoint(HIMC hIMC) const;
	
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
		/// 鼠标光标
		void *hCursor = nullptr;
	
	private:
		
		void *hWnd;
		
		FPoint2I mousePosition{};
		
	};
	
} // GenesisCube
