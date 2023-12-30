//
// Created by admin on 2023/12/19.
//

#pragma once

#include "Header.h"

namespace GenesisCube
{


#if defined(_DEBUG) || defined(DEBUG)
	static const bool bIsDebug = true;
#else
	static const bool bIsDebug = false;
#endif

#if defined(GenesisCubeEditor)
	static const TCHAR buildType[] = TEXT("Editor");
	static const bool bIsEditor = true;
	static const bool bIsGame = false;
#else
	static const TCHAR buildType[] = TEXT("Game");
	static const bool bIsEditor = false;
	static const bool bIsGame = true;
#endif
	
	// char
	
	typedef wchar_t WChar;
	
	typedef char Char;

#ifdef UNICODE
	typedef WChar TChar;
	typedef Char NTChar;
#else
	typedef Char TChar;
	typedef WChar NTChar;
#endif
	
	// string
	
	typedef std::basic_string<WChar> WString;
	
	typedef std::basic_string<Char> String;
	
	typedef std::basic_string<TChar> TString;
	
	typedef std::basic_string<NTChar> NTString;
	
	// in stream
	
	typedef std::basic_istream<WChar> WIStream;
	
	typedef std::basic_istream<Char> IStream;
	
	typedef std::basic_istream<TChar> TIStream;
	
	typedef std::basic_istream<NTChar> NTIStream;
	
	// out stream
	
	typedef std::basic_ostream<WChar> WOStream;
	
	typedef std::basic_ostream<Char> OStream;
	
	typedef std::basic_ostream<TChar> TOStream;
	
	typedef std::basic_ostream<NTChar> NTOStream;
	
	// in out stream
	
	typedef std::basic_iostream<WChar> WIOStream;
	
	typedef std::basic_iostream<Char> IOStream;
	
	typedef std::basic_iostream<TChar> TIOStream;
	
	typedef std::basic_iostream<NTChar> NTIOStream;
	
	// string stream
	
	typedef std::basic_stringstream<WChar> WStringStream;
	
	typedef std::basic_stringstream<Char> StringStream;
	
	typedef std::basic_stringstream<TChar> TStringStream;
	
	typedef std::basic_stringstream<NTChar> NTStringStream;
	
	// input string stream
	
	typedef std::basic_istringstream<WChar> WIStringStream;
	
	typedef std::basic_istringstream<Char> IStringStream;
	
	typedef std::basic_istringstream<TChar> TIStringStream;
	
	typedef std::basic_istringstream<NTChar> NTIStringStream;
	
	// output string stream
	
	typedef std::basic_ostringstream<WChar> WOStringStream;
	
	typedef std::basic_ostringstream<Char> OStringStream;
	
	typedef std::basic_ostringstream<TChar> TOStringStream;
	
	typedef std::basic_ostringstream<NTChar> NTOStringStream;
	
	// file stream
	
	typedef std::basic_fstream<WChar> WFStream;
	
	typedef std::basic_fstream<Char> FStream;
	
	typedef std::basic_fstream<TChar> TFStream;
	
	typedef std::basic_fstream<NTChar> NTFStream;
	
	// input file stream
	
	typedef std::basic_ifstream<WChar> WIFStream;
	
	typedef std::basic_ifstream<Char> IFStream;
	
	typedef std::basic_ifstream<TChar> TIFStream;
	
	typedef std::basic_ifstream<NTChar> NTIFStream;
	
	// output file stream
	
	typedef std::basic_ofstream<WChar> WOFStream;
	
	typedef std::basic_ofstream<Char> OFStream;
	
	typedef std::basic_ofstream<TChar> TOFStream;
	
	typedef std::basic_ofstream<NTChar> NTOFStream;
	
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
			GameRelease,
			GameDebug,
			EditorRelease,
			EditorDebug
		};
	
	public:
		
		///
		/// 退出主循环
		/// \param nExitCode 退出码
		///
		static void Exit(int nExitCode = 0);
		
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
		
		///
		/// 应用实例
		///
		static HINSTANCE GetInstance();
		
		///
		/// 运行参数
		///
		static TString GetCmdLine();
		
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
	
	public:
		
		///
		/// 项目名称
		///
		static const TCHAR name[];
		
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


