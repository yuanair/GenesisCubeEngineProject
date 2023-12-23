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
						   << FCore::version_code
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
	
	FLogger &FLogger::operator<<(bool value)
	{
		lineBuffer.append(value ? TEXT("true") : TEXT("false"));
		return *this;
	}
	
	FLogger &FLogger::operator<<(int32_t value)
	{
		lineBuffer.append(ToTString(value));
		return *this;
	}
	
	FLogger &FLogger::operator<<(uint32_t value)
	{
		lineBuffer.append(ToTString(value));
		return *this;
	}
	
	FLogger &FLogger::operator<<(int64_t value)
	{
		lineBuffer.append(ToTString(value));
		return *this;
	}
	
	FLogger &FLogger::operator<<(uint64_t value)
	{
		lineBuffer.append(ToTString(value));
		return *this;
	}
	
	FLogger &FLogger::operator<<(float_t value)
	{
		lineBuffer.append(ToTString(value));
		return *this;
	}
	
	FLogger &FLogger::operator<<(double_t value)
	{
		lineBuffer.append(ToTString(value));
		return *this;
	}
	
	FLogger &FLogger::operator<<(const void *ptr)
	{
		lineBuffer.append(ptr == nullptr ? TEXT("nullptr") : ToTString((uintptr_t) ptr));
		return *this;
	}
	
	bool FLogger::EndLine(LoggerLevel loggerLevel, HWND hWnd,
						  const TString &mBoxCaption)
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
		
		// MBox
		if ((loggerLevel & MBox) != 0)
		{
			UINT uType;
			switch (loggerLevel & 0x000F)
			{
				case LoggerLevel::Debug:
				case LoggerLevel::Test:
					uType = MB_OK;
					break;
				case LoggerLevel::Info:
					uType = MB_OK | MB_ICONINFORMATION;
					break;
				case LoggerLevel::Warning:
					uType = MB_OK | MB_ICONWARNING;
					break;
				case LoggerLevel::Error:
				case LoggerLevel::Fatal:
				default:
					uType = MB_OK | MB_ICONERROR;
					break;
			}
			MessageBox(hWnd, sBuffer.c_str(), mBoxCaption.c_str(), uType);
		}
		
		return true;
	}
	
	void FLogger::Write(const class ELoggerLevelException &exception, HWND hWnd, const TString &mBoxCaption)
	{
		this->operator<<(exception.What());
		EndLine(exception.loggerLevel, hWnd, mBoxCaption);
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
	
	TString FLogger::TraceStack(uint16_t frameToSkip, uint16_t framesToCapture)
	{
		auto *pStack = new PVOID[framesToCapture];
		TString szStackInfo;
		
		HANDLE process = GetCurrentProcess();
		SymInitialize(process, nullptr, TRUE);
		WORD frames = CaptureStackBackTrace(frameToSkip, framesToCapture, pStack, nullptr);
		
		for (WORD i = 0; i < frames; ++i)
		{
			auto address = (DWORD64) (pStack[i]);
			
			DWORD64 displacementSym = 0;
#ifdef UNICODE
			TChar buffer[sizeof(SYMBOL_INFOW) + MAX_SYM_NAME * sizeof(TChar)];
			auto pSymbol = (PSYMBOL_INFOW) buffer;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFOW);
#else
			TChar buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TChar)];
			auto pSymbol = (PSYMBOL_INFO) buffer;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
#endif
			pSymbol->MaxNameLen = MAX_SYM_NAME;
			
			DWORD displacementLine = 0;
			IMAGEHLP_LINE64 line;
			line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
			
			if (
#ifdef UNICODE
SymFromAddrW
#else
					SymFromAddr
#endif
					(process, address, &displacementSym, pSymbol) &&
SymGetLineFromAddr64(process, address, &displacementLine, &line))
			{
				szStackInfo.append(
					std::format(
						TEXT("\t{}() at {}: {}(0x{:016X})\n"), pSymbol->Name,
#ifdef UNICODE
						FFormatter::StringToWString(line.FileName),
#else
						line.FileName,
#endif
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

#pragma endregion

#pragma region LoggerFormat
	
	
	TString FLoggerFormat::Format(const TString &message, LoggerLevel loggerLevel) const
	{
		TString buffer;
		buffer.append(TEXT("[")).append(Format(loggerLevel));
		buffer.append(TEXT("] [")).append(Format(FTimer::LocalTime()));
		buffer.append(TEXT("] [")).append(FLogger::TraceStack(3, 16));
		buffer.append(TEXT("]\n"));
		
		if (message.empty()) return buffer;
		buffer.append(TEXT("\t"));
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
		if (loggerLevel & LoggerLevel::MBox) result += TEXT(" MB");
		
		
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
					GenesisCubeEngine::LoggerLevel::Fatal | GenesisCubeEngine::LoggerLevel::ODS |
					GenesisCubeEngine::LoggerLevel::MBox
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