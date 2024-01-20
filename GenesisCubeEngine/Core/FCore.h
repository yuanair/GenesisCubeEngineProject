//
// Created by admin on 2023/12/19.
//

#pragma once

#include "Header.h"
#include "../../GenesisCubeBase/Core/FCore.h"

namespace GenesisCube
{
	
	///
	/// 程序类
	///
	class FProgram
	{
	public:
		
		FProgram() noexcept = default;
		
		virtual ~FProgram() noexcept = default;
	
	public:
		
		///
		/// 开始
		///
		virtual void Start() = 0;
		
		///
		/// 每帧
		///
		virtual void Tick() = 0;
		
		///
		/// 结束
		///
		virtual void End() = 0;
		
	};
	
	///
	/// 核心类
	///
	class FCore
	{
	public:
		
		///
		/// 运行模式
		///
		enum RunningMode
		{
			ErrorRunningMode = 0,
			Debug = 1,
			Release = 2
		};
		
		///
		/// \param runningMode
		static TString ToString(RunningMode runningMode);
	
	public:
		
		///
		/// 运行命令
		///
		/// \param hWnd 窗口句柄
		/// \param operation 操作
		/// \param file 文件
		/// \param parameters 参数
		/// \param directory 运行目录
		/// \param showCmd 显示
		/// \return 应用实例
		static HINSTANCE Shell(HWND hWnd, const TString &operation, const TString &file, const TString &parameters,
							   const TString &directory, INT showCmd);
		
		///
		/// 运行
		///
		/// \param program 程序
		/// \param runningMode 模式
		/// \return 返回值
		static int32_t Running(FProgram &program, RunningMode runningMode);
		
		///
		/// \return 运行模式
		static RunningMode GetRunningMode();
	
	public:
		
		///
		/// 项目名称
		///
		static const TCHAR appName[];
		
		///
		/// 显示名称
		///
		static TString showName;
		
		///
		/// 版本字符串
		/// 样式：大版本号 ## . ## 小版本号 ## - ## 版本类型
		/// 例如：1.0-alpha
		/// alpha - Debug测试版
		/// beta - Release测试版
		/// release - Release正式版
		///
		static const TCHAR versionString[];
		
		///
		/// 编译时间
		///
		static const TCHAR buildTime[];
		
		///
		/// 版本代码
		/// 样式：0x ## 大版本号 ## 小版本号
		/// 例如：0x0100
		///
		static const int version_code;
		
	};
	
} // GenesisCube

// 入口函数
int main();
