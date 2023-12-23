///// Created on 2023/11/12.
//

#pragma once

#include "../Core/Header.h"

#include "../Core/FCore.h"
#include "../Core/FTimer.h"
#include "../Exception/Exception.h"
#include "../Object/GObject.h"
#include "../IO/GDirectoryName.h"

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
		
		/// OutputDebugString
		ODS = 0x10,
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
		[[nodiscard]]
		virtual TString Format(const TString &message, LoggerLevel loggerLevel) const;
		
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
		
		///
		/// 获取栈帧（只在Debug模式编译有效）
		/// \param frameToSkip 跳过的栈帧
		/// \param framesToCapture 需要捕获的栈帧数量
		/// \return 栈帧格式化字符串
		static TString TraceStack(uint16_t frameToSkip = 1, uint16_t framesToCapture = 16);
		
		///
		/// LOG DEBUG
		/// \param message 消息
		void LogDebug(const TString &message);
		
		///
		/// LOG TEST
		/// \param message 消息
		void LogTest(const TString &message);
		
		///
		/// LOG INFO
		/// \param message 消息
		void Log(const TString &message);
		
		///
		/// LOG WARNING
		/// \param message 消息
		void LogWarning(const TString &message);
		
		///
		/// LOG ERROR
		/// \param message 消息
		void LogError(const TString &message);
		
		///
		/// LOG FATAL
		/// \param message 消息
		void LogFatal(const TString &message);
		
		FLogger &operator<<(const NTChar *str) = delete;
		
		FLogger &operator<<(NTChar c) = delete;
		
		/// 写入nullptr
		/// ptr - nullptr
		FLogger &operator<<(std::nullptr_t ptr);
		
		/// 写入字符串
		/// str - 字符串
		FLogger &operator<<(const TString &str);
		
		/// 写入字符串
		/// str - 字符串
		FLogger &operator<<(const TCHAR *str);
		
		/// 写入字符
		/// c - 字符
		FLogger &operator<<(TCHAR c);
		
		/// 结束一行写入
		/// loggerLevel - 日志级别
		bool EndLine(LoggerLevel loggerLevel);
		
		/// 写入一行
		/// exception - 异常
		void Write(const class ELoggerLevelException &exception);
		
		/// 删除文件
		static void RemoveOldFile(GDirectoryName::ConstForeachEventArgs args);
		
		/// 删除.//log//下所有文件
		/// return 是否成功
		static bool RemoveOldLogFile();
		
		/// 写入缓冲区字符
		/// \return 是否成功打开文件
		bool Flush();
	
	private:
		
		static TString FormatFirstCallTime();
	
	public:
		
		/// Logger唯一id
		const uint64_t id;
		
		/// 写入文件间隔时间（单位：秒）
		double_t writeDeltaTime = 0.1;
	
	public:
		
		/// 获取行缓冲数据
		[[nodiscard]]
		inline const TString &GetLineBuffer() const { return this->lineBuffer; }
		
		/// 获取缓冲数据
		[[nodiscard]]
		inline const TString &GetBuffer() const { return this->buffer; }
		
		/// 获取文件名
		[[nodiscard]]
		inline const TString &GetFile() const { return this->file; }
	
	private:
		
		static uint64_t count;
		
		FTimer loggerTimer;
		
		TString file;
		
		TString lineBuffer;
		
		TString buffer;
		
		const FLoggerFormat *formatter;
		
	};
	
	
	///
	/// 语法糖
	///
	class FLoggerLine
	{
	
	public:
		
		inline explicit FLoggerLine(LoggerLevel loggerLevel)
			: loggerLevel(loggerLevel) {}
		
		inline ~FLoggerLine() = default;
	
	public:
		
		///
		/// 输出日志
		///
		/// \return 保留，用于语法糖
		inline bool operator==(class FLogger &_logger) const
		{
			return _logger.EndLine(
				loggerLevel
			);
		}
	
	private:
		
		const LoggerLevel loggerLevel;
		
	};
	
	/// 日志可打印的异常
	class ELoggerLevelException : public EException
	{
	public:
		
		ELoggerLevelException(const TString &message, const LoggerLevel &loggerLevel, TString traceStack)
			: EException(message), loggerLevel(loggerLevel), traceStack(std::move(traceStack))
		{
		
		}
	
	public:
		
		const LoggerLevel loggerLevel;
		
		TString traceStack;
		
	};
	
	///
	/// 如果FAILED(hr)则抛出异常
	///
	/// \param hr HRESULT
	/// \param file
	/// \param line
	/// \param func
	void GThrowIfFailed(HRESULT hr);
	
	///
	/// 格式化Windows错误
	///
	/// \param dwMessageId 消息ID
	/// \param dwLanguageId 语言ID
	/// \param dwBufferSize 缓冲区大小，包括'\0'字符，以TChar为单位
	/// \return 字符串
	TString GFormatMessage(DWORD dwMessageId, DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
						   DWORD dwBufferSize = 256);
	
	
}


#define LOG_LEVEL(loggerLevel)                      GenesisCubeEngine::FLoggerLine((GenesisCubeEngine::LoggerLevel)(loggerLevel)) ==

#if defined(DEBUG) || defined(_DEBUG)

#define LOG_DEBUG                                   LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug)
#define LOG_DEBUG_ODS                               LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS)

#else

#define LOG_DEBUG                                   false && LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug)
#define LOG_DEBUG_ODS                               false && LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS)

#endif

#define LOG_TEST                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Test)
#define LOG_INFO                                    LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Info)
#define LOG_WARNING                                 LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Warning)
#define LOG_ERROR                                   LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Error)
#define LOG_FATAL                                   LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Fatal)

#define LOG_TEST_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Test | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_INFO_ODS                                LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Info | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_WARNING_ODS                             LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Warning | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_ERROR_ODS                               LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Error | GenesisCubeEngine::LoggerLevel::ODS)
#define LOG_FATAL_ODS                               LOG_LEVEL(GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS)

#define LOG_EXCEPTION(message, loggerLevel)         GenesisCubeEngine::LoggerException(message, (GenesisCubeEngine::LoggerLevel)(loggerLevel), GenesisCubeEngine::FLogger::TraceStack(1, 16))

#define LOG_EXCEPTION_TEST(message)                 LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Test | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_DEBUG(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Debug | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_INFO(message)                 LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Info | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_WARNING(message)              LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Warning | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_ERROR(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Error | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)
#define LOG_EXCEPTION_FATAL(message)                LOG_EXCEPTION(message, GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS | GenesisCubeEngine::LoggerLevel::MBox)

#define ThrowIfFailed(hr)                           GenesisCubeEngine::GThrowIfFailed(hr)

