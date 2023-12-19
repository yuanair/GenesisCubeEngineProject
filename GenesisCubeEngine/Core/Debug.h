///// Created on 2023/11/12.
//

#pragma once

#include "../Core/GenesisCubeEngine.h"

#include "Core.h"
#include "FTimer.h"
#include "../Exception/Exception.h"
#include "../Object/GObject.h"
#include "../IO/GDirectory.h"

#include <fstream>
#include <utility>

namespace GenesisCubeEngine
{
    
    ///
    /// 日志级别
    ///
    enum LoggerLevel : uint8_t
    {
        /// 输出测试数据信息
        Debug = 0x00,
        /// 输出测试数据信息
        Test = 0x01,
        /// 消息
        Info = 0x02,
        /// 警告
        Warning = 0x03,
        /// 错误
        Error = 0x04,
        /// 致命
        Fatal = 0x05,
        
        /// 输出到日志文件
        File = 0x00,
        /// OutputDebugString 可与MBox连用
        ODS = 0x10,
        /// MessageBox 可与ODS连用
        MBox = 0x20,
    };


/// 日志输出格式类
    class FLoggerFormat
    {
    public:
        
        FLoggerFormat() = default;
        
        virtual ~FLoggerFormat() = default;
    
    public:
        
        ///
        /// 日志输出格式化
        ///
        virtual TString Format(const TString &message, LoggerLevel loggerLevel, const TString &file, int32_t line,
                               const TString &func) const;
        
        ///
        /// 日志级别格式化
        ///
        static TString Format(LoggerLevel loggerLevel);
        
        ///
        /// 时间格式化
        ///
        static TString Format(SYSTEMTIME time);
        
        ///
        /// 时间格式化
        ///
        static TString Format(FILETIME time);
        
        ///
        /// 时间格式化
        ///
        static TString Format(time_t time);
        
    };
    
    
    ///
    /// 日志类
    ///
    class FLogger
    {
    public:
        
        /// dir - 日志文件夹
        /// filename - 日志文件名（无需扩展名）
        /// formatter - 日志输出格式类
        FLogger(const TString &dir, const TString &filename, const FLoggerFormat *formatter);
        
        ~FLogger();
        
        FLogger(const FLogger &) = delete;
        
        FLogger &operator=(const FLogger &) = delete;
    
    
    public:
        
        /// 获取实例，程序结束时必须调用DeleteInstance()
        static FLogger &GetInstance();
        
        /// 删除实例
        static void DeleteInstance();
        
        /// 不支持写入char*字符串
        FLogger &operator<<(const NTChar *str) = delete;
        
        /// 不支持写入char字符
        FLogger &operator<<(NTChar c) = delete;
        
        /// 写入nullptr
        /// ptr - nullptr
        FLogger &operator<<(const std::nullptr_t ptr);
        
        /// 写入字符串
        /// str - 字符串
        FLogger &operator<<(const TString &str);
        
        /// 写入字符串
        /// str - 字符串
        FLogger &operator<<(const TCHAR *str);
        
        /// 写入字符
        /// c - 字符
        FLogger &operator<<(TCHAR c);
        
        /// 写入布尔
        /// value - 布尔
        FLogger &operator<<(bool value);
        
        /// 写入数字
        /// value - 数字
        FLogger &operator<<(int32_t value);
        
        /// 写入数字
        /// value - 数字
        FLogger &operator<<(uint32_t value);
        
        /// 写入数字
        /// value - 数字
        FLogger &operator<<(int64_t value);
        
        /// 写入数字
        /// value - 数字
        FLogger &operator<<(uint64_t value);
        
        /// 写入数字
        /// value - 数字
        FLogger &operator<<(float_t value);
        
        /// 写入数字
        /// value 数字
        FLogger &operator<<(double_t value);
        
        /// 写入Json
        /// json Json
        FLogger &operator<<(const GObject &object);
        
        /// 写入指针地址
        /// ptr - 指针
        FLogger &operator<<(const void *ptr);
        
        /// 结束一行写入
        /// loggerLevel - 日志级别
        /// file - 文件路径
        /// line - 行号
        /// func - 函数名
        /// hWnd - 窗口句柄（可为nullptr）
        /// mBoxCaption - 消息框标题
        bool
        EndLine(LoggerLevel loggerLevel, const TString &file, int32_t line, const TString &func, HWND hWnd = nullptr,
                const TString &mBoxCaption = Core::name);
        
        /// 写入一行
        /// exception - 异常
        /// hWnd - 窗口句柄（可为nullptr）
        /// mBoxCaption - 消息框标题
        void
        Write(const class LoggerException &exception, HWND hWnd = nullptr, const TString &mBoxCaption = Core::name);
        
        /// 清除当前行缓冲区
        void Clear();
        
        /// 获取日志文件是否打开
        bool IsOpen() const;
        
        /// 删除过老创建的文件
        static void RemoveOldFile(GDirectory::ConstForeachEventArgs args);
        
        /// 在文件夹下，删除过老创建的文件
        /// dirName - 要删除文件的目录
        /// _time - 文件创建时间到现在的时间超过此数值则删除
        /// return 返回0为正常
        void RemoveOldLogFile(time_t _time);
    
    private:
        
        static TString FormatFirstCallTime();
        
        bool ReOpen();
        
        bool WriteClose();
    
    public:
        
        /// Logger唯一id
        const uint64_t id;
        
        /// 写入文件间隔时间（单位：秒）
        double_t writeDeltaTime = 0.1;
    
    public:
        
        /// 获取缓冲数据
        inline const TString &GetLineBuffer() const { return lineBuffer; }
        
        /// 获取缓冲数据
        inline const TString &GetBuffer() const { return buffer; }
    
    private:
        
        static uint64_t count;
        
        TString file;
        
        TString lineBuffer;
        
        TString buffer;
        
        std::basic_ofstream<TCHAR, std::char_traits<TCHAR>> ofs;
        
        const FLoggerFormat *formatter;
        
    };
    
    
    ///
    /// 语法糖
    ///
    class FLoggerLine
    {
    
    public:
        
        inline FLoggerLine(LoggerLevel loggerLevel, TString file, int32_t line, TString func, HWND hWnd = nullptr,
                           TString mBoxCaption = Core::name)
            : loggerLevel(loggerLevel), file(std::move(file)), line(line), func(std::move(func)), hWnd(hWnd),
              mBoxCaption(std::move(mBoxCaption)) {}
        
        inline ~FLoggerLine() = default;
    
    public:
        
        ///
        /// 输出日志
        ///
        /// \return 保留，用于语法糖
        inline bool operator==(class FLogger &_logger) const
        {
            return _logger.EndLine(
                loggerLevel, file, line, func, hWnd, mBoxCaption
            );
        }
    
    private:
        
        const LoggerLevel loggerLevel;
        
        const TString file;
        
        const int32_t line;
        
        const TString func;
        
        HWND hWnd;
        
        const TString mBoxCaption;
        
    };
    
    /// 日志可打印的异常
    class LoggerException : public GException
    {
    public:
        
        LoggerException(const TString &message, const LoggerLevel &loggerLevel, TString file, const int32_t line,
                        TString func)
            : GException(message), loggerLevel(loggerLevel), file(std::move(file)), line(line), func(std::move(func))
        {
        
        }
    
    public:
        
        const LoggerLevel loggerLevel;
        
        const TString file;
        
        const int32_t line;
        
        const TString func;
        
    };
    
    void GThrowIfFailed(HRESULT hr, const TString &file, int32_t line, const TString &func);
    
    TString GFormatMessage(DWORD messageId);
    
}


#define LOG_LEVEL(loggerLevel)                        GenesisCubeEngine::FLoggerLine((GenesisCubeEngine::LoggerLevel)(loggerLevel), TEXT(__FILE__), __LINE__, TEXT(__FUNCSIG__)) ==
#define LOG_LEVEL_M(loggerLevel, hWnd, mBoxCaption)    GenesisCubeEngine::FLoggerLine((GenesisCubeEngine::LoggerLevel)(loggerLevel), TEXT(__FILE__), __LINE__, TEXT(__FUNCSIG__), hWnd, mBoxCaption) ==

#if defined(DEBUG) || defined(_DEBUG)

#define LOG_DEBUG									LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug)
#define LOG_DEBUG_ODS								LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_DEBUG_M(hWnd, mBoxCaption)				LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_DEBUG_ODS_M(hWnd, mBoxCaption)			LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)

#else

#define LOG_DEBUG                                    false && LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug)
#define LOG_DEBUG_ODS                                false && LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_DEBUG_M(hWnd, mBoxCaption)                false && LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_DEBUG_ODS_M(hWnd, mBoxCaption)            false && LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)

#endif

#define LOG_TEST                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Test)
#define LOG_INFO                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Info)
#define LOG_WARNING                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Warning)
#define LOG_ERROR                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Error)
#define LOG_FATAL                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Fatal)

#define LOG_TEST_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Test | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_INFO_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Info | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_WARNING_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Warning | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_ERROR_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Error | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_FATAL_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS)

#define LOG_TEST_M(hWnd, mBoxCaption)                LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Test | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_INFO_M(hWnd, mBoxCaption)                LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Info | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_WARNING_M(hWnd, mBoxCaption)            LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Warning | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_ERROR_M(hWnd, mBoxCaption)                LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Error | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_FATAL_M(hWnd, mBoxCaption)                LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)

#define LOG_TEST_ODS_M(hWnd, mBoxCaption)            LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Test | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_INFO_ODS_M(hWnd, mBoxCaption)            LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Info | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_WARNING_ODS_M(hWnd, mBoxCaption)        LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Warning | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_ERROR_ODS_M(hWnd, mBoxCaption)            LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Error | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)
#define LOG_FATAL_ODS_M(hWnd, mBoxCaption)            LOG_LEVEL_M(GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox, hWnd, mBoxCaption)

#define LOG_EXCEPTION(message, loggerLevel)            GenesisCubeEngine::LoggerException(message, (GenesisCubeEngine::LoggerLevel)(loggerLevel), TEXT(__FILE__), __LINE__, TEXT(__FUNCSIG__))

#define LOG_EXCEPTION_TEST(message)                    LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Test | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_DEBUG(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_INFO(message)                    LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Info | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_WARNING(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Warning | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_ERROR(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Error | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_FATAL(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)

#define ThrowIfFailed(hr)                            GenesisCubeEngine::GThrowIfFailed(hr, TEXT(__FILE__), __LINE__, TEXT(__FUNCSIG__))

