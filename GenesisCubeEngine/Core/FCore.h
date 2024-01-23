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
		/// 每帧
		///
		virtual void Tick() = 0;
		
	};
	
	///
	/// 核心类
	///
	class FCore
	{
	public:
		
		///
		/// 运行
		///
		/// \param newProgramFn 创建程序函数
		/// \return 返回值
		static int32_t Running(FProgram *(*newProgramFn)());
	
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
		/// 例如：1.0 -> 0x10
		///
		static const int version_code;
		
	};
	
} // GenesisCube

// 入口函数
int main();
