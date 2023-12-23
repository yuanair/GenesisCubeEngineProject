//
// Created on 2023/11/12.
//

#include "Debug.h"
#include "../Core/FFormatter.h"

namespace GenesisCubeEngine
{


#pragma region Logger
	
	
	uint64_t FLogger::count = 0;
	
	FLogger::FLogger(const TString &dir, const TString &filename, const FLoggerFormat *formatter)
		: id(count++)
	{
		if (formatter)
		{
			this->formatter = formatter;
		}
		else
		{
			this->formatter = new FLoggerFormat();
		}
		
		CreateDirectory(dir.c_str(), nullptr);
		
		this->file = dir;
		this->file += TEXT("\\");
		this->file += filename;
		this->file += TEXT(".log");
		
		buffer = std::format(
			TEXT("\n\n{1} Start {0}  {1}\n"), FLoggerFormat::Format(FTimer::LocalTime()),
			TEXT("----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")
		);
	}
	
	bool FLogger::Flush()
	{
		FILE *fp;
#ifdef UNICODE
		_wfopen_s
#else
			fopen_s
#endif
			(&fp, this->file.c_str(), TEXT("a"));
		
		if (fp == nullptr) return false;

#ifdef UNICODE
		fputws
#else
			fputs
#endif
			(buffer.c_str(), fp);
		fclose(fp);
		buffer.clear();
		return true;
	}
	
	FLogger::~FLogger()
	{
		Flush();
		buffer = std::format(
			TEXT("\n\n{1} End {0}  {1}\n"), FLoggerFormat::Format(FTimer::LocalTime()),
			TEXT("----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")
		);
		Flush();
		delete this->formatter;
	}
	
	TString FLogger::FormatFirstCallTime()
	{
//        static TCHAR file[32] = {};
//        static time_t firstCallTime = time(nullptr);
//        static tm tm_t = {};
//        localtime_s(&tm_t, &firstCallTime);
//        wsprintf(
//            file,
//            TEXT("%.4d%.2d%.2d%.2d%.2d%.2d"),
//            tm_t.tm_year + 1900,
//            tm_t.tm_mon + 1,
//            tm_t.tm_mday,
//            tm_t.tm_hour,
//            tm_t.tm_min,
//            tm_t.tm_sec
//        );
		auto localTime = FTimer::LocalTime();
		return std::format(TEXT("{:0<4}{:0<2}{:0<2}"), localTime.wYear, localTime.wMonth, localTime.wDay);
	}
	
	static FLogger *logger;
	
	FLogger &FLogger::Inst()
	{
		if (logger == nullptr)
		{
			logger = new FLogger(TEXT(".\\log"), FormatFirstCallTime(), nullptr);
		}
		return *logger;
	}
	
	void FLogger::DeleteInstance()
	{
		if (logger != nullptr)
		{
			delete logger;
			logger = nullptr;
		}
	}
	
	
	TString FLogger::TraceStack(uint16_t frameToSkip, uint16_t framesToCapture)
	{
		auto pStack = new PVOID[framesToCapture];
		TString szStackInfo;
		
		HANDLE process = GetCurrentProcess();
		SymInitialize(process, nullptr, TRUE);
		WORD frames = CaptureStackBackTrace(frameToSkip, framesToCapture, pStack, nullptr);
		
		if (frames > framesToCapture) frames = framesToCapture;
		
		for (WORD i = 0; i < frames; ++i)
		{
			auto address = (DWORD64) (pStack[i]);
			
			DWORD64 displacementSym = 0;
#ifdef UNICODE
			TChar buffer[sizeof(SYMBOL_INFOW) + MAX_SYM_NAME * sizeof(TChar)];
			auto pSymbol = (PSYMBOL_INFOW) buffer;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFOW);
			
			pSymbol->MaxNameLen = MAX_SYM_NAME;
			
			DWORD displacementLine = 0;
			IMAGEHLP_LINEW64 line;
			line.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);
#else
			TChar buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TChar)];
			auto pSymbol = (PSYMBOL_INFO) buffer;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			
			pSymbol->MaxNameLen = MAX_SYM_NAME;
			
			DWORD displacementLine = 0;
			IMAGEHLP_LINE64 line;
			line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
#endif

#ifdef UNICODE
			if (SymFromAddrW(process, address, &displacementSym, pSymbol) &&
				SymGetLineFromAddrW64(process, address, &displacementLine, &line))
#else
				if (SymFromAddr(process, address, &displacementSym, pSymbol) && SymGetLineFromAddr64(process, address, &displacementLine, &line))
#endif
			{
				szStackInfo.append(
					std::format(
						TEXT("\t{}() at {}({})(0x{:016X})\n"), pSymbol->Name, line.FileName,
						line.LineNumber, pSymbol->Address
					));
			}
			else
			{
				auto lastError = GetLastError();
				szStackInfo.append(std::format(TEXT("\terror(0x{:08X}): {}"), lastError, GFormatMessage(lastError)));
			}
		}
		delete[] pStack;
		
		return szStackInfo;
	}
	
	FLogger &FLogger::operator<<(const TString &str)
	{
		lineBuffer.append(str);
		return *this;
	}
	
	FLogger &FLogger::operator<<(const TCHAR *str)
	{
		lineBuffer.append(str);
		return *this;
	}
	
	FLogger &FLogger::operator<<(TCHAR c)
	{
		lineBuffer.push_back(c);
		return *this;
	}
	
	bool FLogger::EndLine(LoggerLevel loggerLevel)
	{
		loggerTimer.Tick();
		
		TString sBuffer = formatter->Format(lineBuffer, loggerLevel);
		lineBuffer.clear();
		
		buffer.append(sBuffer);
		
		// Log
		if ((loggerLevel & 0x000F) >= LoggerLevel::Warning)
		{
			Flush();
		}
		else if (loggerTimer.TotalTime() > writeDeltaTime)
		{
			loggerTimer.Reset();
			Flush();
		}
		
		// ODS
		if ((loggerLevel & ODS) != 0)
		{
			OutputDebugString(sBuffer.c_str());
		}
		
		return true;
	}
	
	void FLogger::Log(const struct ELoggerLevelException &exception)
	{
		Log(exception.loggerLevel, exception.What());
	}
	
	void FLogger::RemoveOldFile(GDirectoryName::ConstForeachEventArgs args)
	{
		
		LOG_INFO Inst()
			<< TEXT("[File : \"") << args.fileName->GetFileName() << TEXT("\"]\n")
			<< TEXT("\t - [Created Times:       ") << FLoggerFormat::Format(args.creationTime) << TEXT("]\n")
			<< TEXT("\t - [Last Accessed Times: ") << FLoggerFormat::Format(args.lastAccessTime) << TEXT("]\n")
			<< TEXT("\t - [Last Modified Times: ") << FLoggerFormat::Format(args.lastWriteTime) << TEXT("]");
		
		DeleteFile(args.fileName->GetFileName().c_str());
		LOG_INFO_ODS Inst() << TEXT("> Remove file : \"") << args.fileName->GetFileName() << TEXT("\"");
	}
	
	bool FLogger::RemoveOldLogFile()
	{
		return GDirectoryName(TEXT(".\\log")).FindForeach(TEvent<GDirectoryName::ConstForeachEventArgs>(RemoveOldFile));
	}
	
	void FLogger::Log(LoggerLevel loggerLevel, const TString &message)
	{
		loggerTimer.Tick();
		
		TString sBuffer = formatter->Format(message, loggerLevel);
		
		buffer.append(sBuffer);
		
		// Log
		if ((loggerLevel & 0x000F) >= LoggerLevel::Warning || loggerTimer.TotalTime() > writeDeltaTime)
		{
			loggerTimer.Reset();
			Flush();
		}
		
		// ODS
		if ((loggerLevel & ODS) != 0)
		{
			OutputDebugString(sBuffer.c_str());
		}
	}

#pragma endregion

#pragma region LoggerFormat
	
	
	TString FLoggerFormat::Format(const TString &message, LoggerLevel loggerLevel) const
	{
		if (bIsEditor || bIsDebug)
		{
			return std::format(
				TEXT("[{}] [{}] [\n{}] {}\n"), Format(loggerLevel), Format(FTimer::LocalTime()),
				FLogger::TraceStack(3, 16), message
			);
		}
		else
		{
			return std::format(
				TEXT("[{}] [{}] {}\n"), Format(loggerLevel), Format(FTimer::LocalTime()), message
			);
		}
	}
	
	TString FLoggerFormat::Format(LoggerLevel loggerLevel)
	{
		switch (loggerLevel)
		{
			case LoggerLevel::Debug:
				return TEXT("Debug");
			case LoggerLevel::Test:
				return TEXT("Test");
			case LoggerLevel::Info:
				return TEXT("Info");
			case LoggerLevel::Warning:
				return TEXT("Warning");
			case LoggerLevel::Error:
				return TEXT("Error");
			case LoggerLevel::Fatal:
				return TEXT("Fatal");
			case LoggerLevel::Debug | LoggerLevel::ODS:
				return TEXT("Debug ODS");
			case LoggerLevel::Test | LoggerLevel::ODS:
				return TEXT("Test ODS");
			case LoggerLevel::Info | LoggerLevel::ODS:
				return TEXT("Info ODS");
			case LoggerLevel::Warning | LoggerLevel::ODS:
				return TEXT("Warning ODS");
			case LoggerLevel::Error | LoggerLevel::ODS:
				return TEXT("Error ODS");
			case LoggerLevel::Fatal | LoggerLevel::ODS:
				return TEXT("Fatal ODS");
			default:
				return TEXT("<error>");
		}
	}
	
	TString FLoggerFormat::Format(SYSTEMTIME time)
	{
		return std::format(
			TEXT("{:0>4}-{:0>2}-{:0>2} {:0>2}:{:0>2}:{:0>2}.{:0>3}"),
			time.wYear,
			time.wMonth,
			time.wDay,
			time.wHour,
			time.wMinute,
			time.wSecond,
			time.wMilliseconds
		);
	}
	
	TString FLoggerFormat::Format(FILETIME time)
	{
		SYSTEMTIME st;
		FileTimeToSystemTime(&time, &st);
		return std::format(
			TEXT("{:0>4}-{:0>2}-{:0>2} {:0>2}:{:0>2}:{:0>2}.{:0>3}"),
			st.wYear,
			st.wMonth,
			st.wDay,
			st.wHour,
			st.wMinute,
			st.wSecond,
			st.wMilliseconds
		);
	}

#pragma endregion
	
	
	void GThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			TString message = std::format(TEXT("{} (0x{:08X})"), GFormatMessage(hr), hr);
			FLogger::Inst().Log((LoggerLevel) (LoggerLevel::Fatal | LoggerLevel::ODS), message);
			throw ELoggerLevelException(message, (LoggerLevel) (LoggerLevel::Fatal | LoggerLevel::ODS));
		}
	}
	
	TString GFormatMessage(DWORD dwMessageId, DWORD dwLanguageId, DWORD dwBufferSize)
	{
		auto strBufferError = new TChar[dwBufferSize];
		FormatMessage
			(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, dwMessageId, dwLanguageId,
				strBufferError, dwBufferSize, nullptr
			);
		TString buffer = strBufferError;
		delete[] strBufferError;
		return buffer;
	}
	
	
}