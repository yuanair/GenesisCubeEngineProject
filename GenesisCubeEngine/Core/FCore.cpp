//
// Created by admin on 2023/12/19.
//

#include "FCore.h"
#include "../../GenesisCubeBase/Core/Debug.h"
#include "../../GenesisCubeBase/Win32/Win32.h"

namespace GenesisCube
{
	
	const TCHAR FCore::appName[] = TEXT("Genesis Cube Engine");
	
	TString FCore::showName = TEXT("Genesis Cube Engine");
	
	const TCHAR FCore::versionString[] = TEXT("0.1-alpha");
	
	const TCHAR FCore::buildTime[] = TEXT(__DATE__);
	
	const int FCore::version_code = 1;
	
	static FCore::RunningMode globalRunningMode = FCore::ErrorRunningMode;
	
	HINSTANCE FCore::Shell(HWND hWnd, const TString &operation, const TString &file, const TString &parameters,
						   const TString &directory, INT showCmd)
	{
		return ShellExecute(hWnd, operation.c_str(), file.c_str(), parameters.c_str(), directory.c_str(), showCmd);
	}
	
	int32_t FCore::Running(FProgram &program, RunningMode runningMode)
	{
		if (globalRunningMode != ErrorRunningMode)
		{
			throw EBadException(
				__FUNCSIG__ TEXT(":: Duplicate runs are not allowed")
			);
		}
		globalRunningMode = runningMode;
		
		if (runningMode == ErrorRunningMode)
		{
			throw EInvalidArgumentException(
				__FUNCSIG__ TEXT(":: runningMode is invalid")
			);
		}
		
		// 当为DEBUG模式时，内存泄漏检测
		if (runningMode <= Debug)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
		
		TString buffer;
		buffer += std::format(
			TEXT(
				R"(
	{0} {1} (code: {2})
	[running path: {3}]
	[logger file: {4}]
	[build time: {5}]
	[build type: {6}]
	[command line: {7}]
	[desktop size: {8}, {9}]
)"),
			FCore::appName, // 0
			FCore::versionString, // 1
			FCore::version_code, // 2
			Win32::GetModuleFileNameT(), // 3
			FLogger::Inst().GetFile(), // 4
			FCore::buildTime, // 5
			ToString(runningMode), // 6
			Win32::GetCommandLineT(), // 7
			Win32::FWindow::GetDesktopSize().width, // 8
			Win32::FWindow::GetDesktopSize().height // 9
		);
		
		FLogger::Inst().LogInfoODS(buffer);
		
		program.Start();
		
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				program.Tick();
			}
		}
		
		program.End();
		
		globalRunningMode = FCore::ErrorRunningMode;
		return (int) msg.wParam;
	}
	
	FCore::RunningMode FCore::GetRunningMode()
	{
		if (globalRunningMode == FCore::ErrorRunningMode)
		{
			FLogger::Inst().LogFatalODS(__FUNCSIG__ TEXT("No call FCore::Running"));
			exit(-1);
		}
		return globalRunningMode;
	}
	
	TString FCore::ToString(FCore::RunningMode runningMode)
	{
		switch (runningMode)
		{
			case Release:
				return TEXT("Release");
			case Debug:
				return TEXT("Debug");
			case ErrorRunningMode:
			default:
				return TEXT("ErrorRunningMode");
		}
	}
	
} // GenesisCube


///
/// define TWinMain
///
#ifdef UNICODE

#define TWinMain() WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)

#else

#define TWinMain() WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)

#endif

///
/// TWinMain
///
#ifdef _DEBUG

int TWinMain()
{
	return main();
}

#else

int TWinMain()
{
	try
	{
		return main();
	}
	catch (const GenesisCube::EException &exception)
	{
		GenesisCube::FLogger::MessageBoxFromException(exception);
	}
	catch (const std::exception &ex)
	{
		GenesisCube::FLogger::MessageBoxFromException(ex);
	}
	return 0;
}

#endif
