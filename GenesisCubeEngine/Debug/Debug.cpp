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
		
		buffer += std::format(
			TEXT("\n\n{1} Start {0}  {1}\n"), FLoggerFormat::Format(FTimer::LocalTime()),
			TEXT("----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")
		);
		LOG_INFO_ODS *this << TEXT("[") << FCore::name << TEXT(" ") << FCore::versionString << TEXT("(code: ")
						   << ToTString(FCore::version_code)
						   << TEXT(")]\n")
						   << TEXT(" - [logger file: \"") << this->file << TEXT("\"]\n")
						   << TEXT(" - [build time: ") << FCore::buildTime << TEXT("]\n")
						   << TEXT(" - [build type: ") << buildType << TEXT("]\n")
						   << TEXT(" - [running path: ") << GDirectoryName::ModuleFile().GetFileName() << TEXT("]\n");
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
		TOFStream ofs(this->file, std::ios::out | std::ios::app);
		if (ofs.is_open())
		{
			ofs << TEXT(
				"\n----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----  End ")
				<< FLoggerFormat::Format(FTimer::LocalTime())
				<< TEXT(
					"  ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- \n\n");
			ofs.close();
		}
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
	
	FLogger &FLogger::GetInstance()
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
	
	FLogger &FLogger::operator<<(const std::nullptr_t)
	{
		lineBuffer.append(TEXT("nullptr"));
		return *this;
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
		
		// Write
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
	
	void FLogger::Write(const class ELoggerLevelException &exception)
	{
		this->operator<<(exception.What());
		EndLine(exception.loggerLevel);
	}
	
	void FLogger::RemoveOldFile(GDirectoryName::ConstForeachEventArgs args)
	{
		
		LOG_INFO GetInstance()
			<< TEXT("[File : \"") << args.fileName->GetFileName() << TEXT("\"]\n")
			//	<< TEXT("\t - [Size : ") << size << TEXT(" bytes]\n")
			//	<< TEXT("\t - [Drive : ") << (TCHAR)(buf.st_dev + TEXT('A') << TEXT("]\n")
			<< TEXT("\t - [Created Times:       ") << FLoggerFormat::Format(args.creationTime) << TEXT("]\n")
			<< TEXT("\t - [Last Accessed Times: ") << FLoggerFormat::Format(args.lastAccessTime) << TEXT("]\n")
			<< TEXT("\t - [Last Modified Times: ") << FLoggerFormat::Format(args.lastWriteTime) << TEXT("]");
		
		DeleteFile(args.fileName->GetFileName().c_str());
		LOG_INFO_ODS GetInstance() << TEXT("> Remove file : \"") << args.fileName->GetFileName() << TEXT("\"");
	}
	
	bool FLogger::RemoveOldLogFile()
	{
		return GDirectoryName(TEXT(".\\log")).FindForeach(TEvent<GDirectoryName::ConstForeachEventArgs>(RemoveOldFile));
	}
	
	void FLogger::LogDebug(const TString &message)
	{
		EndLine(LoggerLevel::Debug);
	}
	
	void FLogger::LogTest(const TString &message)
	{
	
	}
	
	void FLogger::Log(const TString &message)
	{
	
	}
	
	void FLogger::LogWarning(const TString &message)
	{
	
	}
	
	void FLogger::LogError(const TString &message)
	{
	
	}
	
	void FLogger::LogFatal(const TString &message)
	{
	
	}

#pragma endregion

#pragma region LoggerFormat
	
	
	TString FLoggerFormat::Format(const TString &message, LoggerLevel loggerLevel) const
	{
		TString buffer;
		buffer.append(TEXT("[")).append(Format(loggerLevel));
		buffer.append(TEXT("] [")).append(Format(FTimer::LocalTime()));
		if (bIsEditor || bIsDebug) buffer.append(TEXT("] [")).append(FLogger::TraceStack(3, 16));
		buffer.append(TEXT("]"));
		
		if (message.empty())
		{
			buffer.push_back(TEXT('\n'));
			return buffer;
		}
		buffer.push_back(TEXT('\t'));
		for (TCHAR ch: message)
		{
			if (ch == TEXT('\n'))
			{
				buffer.append(TEXT("\n\t"));
			}
			else
			{
				buffer.push_back(ch);
			}
		}
		buffer.push_back(TEXT('\n'));
		return buffer;
	}
	
	TString FLoggerFormat::Format(LoggerLevel loggerLevel)
	{
		TString result;
		switch (loggerLevel & 0x000F)
		{
			case LoggerLevel::Debug:
				result += TEXT("Debug");
				break;
			case LoggerLevel::Test:
				result += TEXT("Test");
				break;
			case LoggerLevel::Info:
				result += TEXT("Info");
				break;
			case LoggerLevel::Warning:
				result += TEXT("Warning");
				break;
			case LoggerLevel::Error:
				result += TEXT("Error");
				break;
			case LoggerLevel::Fatal:
				result += TEXT("Fatal");
				break;
			default:
				result += TEXT("<error>");
				break;
		}
		
		if (loggerLevel & LoggerLevel::ODS) result += TEXT(" ODS");
		
		return result;
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
//        TCHAR microseconds[45];
//        wsprintf
//            (
//                microseconds,
//                TEXT("%d-%d-%d %d:%d:%d.%d"),
//                time.wYear,
//                time.wMonth,
//                time.wDay,
//                time.wHour,
//                time.wMinute,
//                time.wSecond,
//                time.wMilliseconds
//            );
//        return microseconds;
	
	}
	
	TString FLoggerFormat::Format(FILETIME time)
	{
		SYSTEMTIME st;
		FileTimeToSystemTime(&time, &st);
		return Format(st);
		
	}

#pragma endregion
	
	
	void GThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			TCHAR strBufferHr[300]{};
			wsprintf(strBufferHr, TEXT("%s (0x%0.8x)"), GFormatMessage(hr).c_str(), hr);
			throw GenesisCubeEngine::ELoggerLevelException(
				strBufferHr,
				(GenesisCubeEngine::LoggerLevel) (
					GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS
				),
				FLogger::TraceStack(2, 16)
			);
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