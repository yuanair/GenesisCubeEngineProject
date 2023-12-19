//
// Created by admin on 2023/12/19.
//

#pragma once

#include "GenesisCubeEngine.h"
#include "FTimer.h"

namespace GenesisCubeEngine
{
    //
    // 核心类
    //
    class Core
    {
    public:
        
        ///
        /// 退出主循环
        /// \param nExitCode 退出码
        ///
        static void Exit(int nExitCode = 0);
        
        //
        // 测试
        //
        static void TestGenesisCubeEngine();
    
    public:
        
        //
        // 项目名称
        //
        static const TCHAR name[];
        
        //
        // 版本字符串
        // 样式：大版本号 ## . ## 小版本号 ## - ## 版本类型
        // 例如：1.0-alpha
        // alpha - Debug测试版
        // beta - Release测试版
        // release - Release正式版
        //
        static const TCHAR versionString[];
        
        //
        // 编译时间
        //
        static const TCHAR buildTime[];
        
        //
        // 版本代码
        // 样式：0x ## 大版本号 ## 小版本号
        // 例如：0x0100
        //
        static const int version_code;
        
        //
        // 应用实例
        //
        static HINSTANCE hInstance;
        
        //
        // 应用实例
        //
        static HINSTANCE hPrevInstance;
        
        //
        // 运行参数
        //
        static LPSTR cmdLine;
        
        //
        // 显示
        //
        static int nShowCmd;
        
    };

#if defined(_DEBUG) || defined(DEBUG)
    static const bool bIsDebug = true;
    static const bool bIsRelease = false;
#else
    static const bool bIsDebug = false;
    static const bool bIsRelease = true;
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
    class GProgram
    {
    public:
        
        GProgram() noexcept = default;
        
        virtual ~GProgram() noexcept = default;
    
    public:
        
        ///
        /// 程序初始化时
        ///
        virtual void Init() = 0;
        
        ///
        /// 每帧调用
        ///
        /// \param deltaTime 帧间隔时间，以秒记
        virtual void Tick(double deltaTime) = 0;
        
        ///
        /// 结束
        ///
        virtual void End() = 0;
        
    };
    
} // GenesisCubeEngine


//
// 程序入口
//
void GCProgram();

//
// 每帧调用
//
void GCTick();
