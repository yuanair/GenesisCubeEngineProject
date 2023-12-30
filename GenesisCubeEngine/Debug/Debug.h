///// Created on 2023/11/12.
//

#pragma once

#include "../Core/Header.h"

#include "../Core/FCore.h"
#include "../Core/FTimer.h"
#include "../Exception/Exception.h"
#include "../Object/GObject.h"
#include "../IO/GDirectoryName.h"

namespace GenesisCube
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
		static FLogger &Inst();
		
		///
		/// 获取栈帧（只在Debug模式编译有效）
		/// \param frameToSkip 跳过的栈帧
		/// \param framesToCapture 需要捕获的栈帧数量
		/// \return 栈帧格式化字符串
		static TString TraceStack(uint16_t frameToSkip = 1, uint16_t framesToCapture = 16);
		
		///
		/// LOG
		/// \param loggerLevel 日志等级
		/// \param message 消息
		void Log(LoggerLevel loggerLevel, const TString &message);
		
		///
		/// LOG
		/// \param hr HRESULT
		/// \param message 消息
		void LogMBox(HRESULT hr, const TString &message);
		
		///
		/// LOG DEBUG
		/// \param message 消息
		inline void LogDebug(const TString &message) { return Log(LoggerLevel::Debug, message); }
		
		///
		/// LOG TEST
		/// \param message 消息
		inline void LogTest(const TString &message) { return Log(LoggerLevel::Test, message); }
		
		///
		/// LOG INFO
		/// \param message 消息
		inline void LogInfo(const TString &message) { return Log(LoggerLevel::Info, message); }
		
		///
		/// LOG WARNING
		/// \param message 消息
		inline void LogWarning(const TString &message) { return Log(LoggerLevel::Warning, message); }
		
		///
		/// LOG ERROR
		/// \param message 消息
		inline void LogError(const TString &message) { return Log(LoggerLevel::Error, message); }
		
		///
		/// LOG FATAL
		/// \param message 消息
		inline void LogFatal(const TString &message) { return Log(LoggerLevel::Fatal, message); }
		
		
		///
		/// LOG DEBUG ODS
		/// \param message 消息
		inline void LogDebugODS(const TString &message)
		{
			return Log((LoggerLevel) (LoggerLevel::Debug | LoggerLevel::ODS), message);
		}
		
		///
		/// LOG TEST ODS
		/// \param message 消息
		inline void LogTestODS(const TString &message)
		{
			return Log((LoggerLevel) (LoggerLevel::Test | LoggerLevel::ODS), message);
		}
		
		///
		/// LOG INFO ODS
		/// \param message 消息
		inline void LogInfoODS(const TString &message)
		{
			return Log((LoggerLevel) (LoggerLevel::Info | LoggerLevel::ODS), message);
		}
		
		///
		/// LOG WARNING ODS
		/// \param message 消息
		inline void LogWarningODS(const TString &message)
		{
			return Log((LoggerLevel) (LoggerLevel::Warning | LoggerLevel::ODS), message);
		}
		
		///
		/// LOG ERROR ODS
		/// \param message 消息
		inline void LogErrorODS(const TString &message)
		{
			return Log((LoggerLevel) (LoggerLevel::Error | LoggerLevel::ODS), message);
		}
		
		///
		/// LOG FATAL ODS
		/// \param message 消息
		inline void LogFatalODS(const TString &message)
		{
			return Log((LoggerLevel) (LoggerLevel::Fatal | LoggerLevel::ODS), message);
		}
		
		/// 删除文件
		static void RemoveOldFile(GDirectoryName::ConstForeachEventArgs args);
		
		/// 删除.//log//下所有文件
		/// return 是否成功
		static bool RemoveOldLogFile();
		
		/// 写入缓冲区字符
		/// \return 是否成功打开文件
		bool Flush();
		
		///
		/// 如果FAILED(hr)则抛出异常
		/// \param hr HRESULT
		/// \param message 消息
		static void GThrowIfFailed(HRESULT hr, const TString &message = TEXT("DirectX"));
		
		///
		/// 抛出异常
		/// \param hr HRESULT
		/// \param message 消息
		static void GThrow(HRESULT hr, const TString &message = TEXT("DirectX"));
	
	private:
		
		static TString FormatFirstCallTime();
	
	public:
		
		/// 写入文件间隔时间（单位：秒）
		double_t writeDeltaTime = 0.1;
	
	public:
		
		/// 获取缓冲数据
		[[nodiscard]]
		inline const TString &GetBuffer() const { return this->buffer; }
		
		/// 获取文件名
		[[nodiscard]]
		inline const TString &GetFile() const { return this->file; }
	
	private:
		
		FTimer loggerTimer;
		
		TString file;
		
		TString buffer;
		
		const FLoggerFormat *formatter;
		
	};
	
	
}
