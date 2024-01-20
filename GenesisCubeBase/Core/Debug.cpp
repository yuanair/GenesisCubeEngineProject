//
// Created on 2023/11/12.
//

#include "Debug.h"

#include "FFormatter.h"
#include "../Win32/Win32.h"

namespace GenesisCube
{


#pragma region Logger
	
	
	FLogger::FLogger(TString dir, const TString &filename, const FLoggerFormat *formatter)
		: file(std::move(dir))
	{
		this->formatter = formatter == nullptr ? new FLoggerFormat() : formatter;
		
		CreateDirectory(this->file.c_str(), nullptr);
		
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
		TOFStream ofStream(this->file, std::ios::in | std::ios::app);
		if (!ofStream.is_open()) return false;
		ofStream << buffer;
		ofStream.close();
		buffer.clear();
		return true;
	}
	
	FLogger::~FLogger()
	{
		buffer += std::format(
			TEXT("\n\n{1} End {0}  {1}\n"), FLoggerFormat::Format(FTimer::LocalTime()),
			TEXT("----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----")
		);
		Flush();
		delete this->formatter;
	}
	
	TString FLogger::FormatFirstCallTime()
	{
		auto localTime = FTimer::LocalTime();
		return std::format(TEXT("{:0<4}{:0<2}{:0<2}"), localTime.wYear, localTime.wMonth, localTime.wDay);
	}
	
	
	FLogger &FLogger::Inst()
	{
		static auto logger = FLogger(TEXT(".\\log"), FormatFirstCallTime(), nullptr);
		return logger;
	}
	
	
	TString FLogger::TraceStack(uint16_t frameToSkip, uint16_t framesToCapture)
	{
		if (FCore::GetRunningMode() > FCore::Debug) return TEXT("no Debug");
#if defined(_DEBUG) || defined(DEBUG)
		auto pStack = new PVOID[framesToCapture];
		TString szStackInfo(TEXT("\n"));
		
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
				szStackInfo.append(
					std::format(TEXT("\terror(0x{:08X}): {}"), lastError, FFormatter::FormatMessageT(lastError)));
			}
		}
		delete[] pStack;
		
		return szStackInfo;
#else
		return TEXT("no DEBUG");
#endif
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
	
	void ThrowIfFailed(HRESULT hr, const TString &message)
	{
		if (SUCCEEDED(hr)) return;
		
		TString hrMessage = std::format(
			TEXT("{} (0x{:08X}): {}"),
			message, (uint32_t) hr, FFormatter::FormatMessageT(hr));
		FLogger::Inst().LogFatalODS(hrMessage);
		throw EHResultException(hrMessage);
		
	}
	
	void ThrowHResult(HRESULT hr, const TString &message)
	{
		TString hrMessage = std::format(
			TEXT("{} (0x{:08X}): {}"),
			message, (uint32_t) hr, FFormatter::FormatMessageT(hr));
		FLogger::Inst().LogFatalODS(hrMessage);
		throw EHResultException(hrMessage);
	}
	
	void FLogger::MessageBoxFromException(const std::exception &exception)
	{
		TString buffer = std::format(TEXT("{}: {}"), FFormatter::GetTypeName(&exception), GText(exception.what()));
		Win32::MessageBoxT(buffer, FCore::showName, Win32::MessageBoxTypeOK, Win32::MessageBoxIconStop);
	}
	
	void FLogger::MessageBoxFromException(const EException &exception)
	{
		TString buffer = std::format(TEXT("{}: {}"), FFormatter::GetTypeName(&exception), exception.What());
		Win32::MessageBoxT(buffer, FCore::showName, Win32::MessageBoxTypeOK, Win32::MessageBoxIconStop);
	}

#pragma endregion

#pragma region LoggerFormat
	
	
	TString FLoggerFormat::Format(const TString &message, LoggerLevel loggerLevel) const
	{
		if (FCore::GetRunningMode() <= FCore::Debug)
		{
			return std::format(
				TEXT("[{}] [{}] [{}] {}\n"), Format(loggerLevel), Format(FTimer::LocalTime()),
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
	
	
}