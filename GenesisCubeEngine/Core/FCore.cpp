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
	
	const int FCore::version_code = 0x0001;
	
	int32_t FCore::Running(FProgram *(*newProgramFn)())
	{
		FRectI desktopWindowRect;
		{
			Win32::FWindow desktopWindow;
			desktopWindow.Bind(Win32::FWindow::GetDesktopWindow());
			desktopWindowRect = desktopWindow.GetWindowRect();
		}
		
		FLogger::Inst().LogInfoODS(
			std::format(
				TEXT(
					R"(
	{0} {1} (code: {2})
	[running path: {3}]
	[logger file: {4}]
	[build time: {5}]
	[command line: {6}]
	[desktop size: {7}, {8}]
)"),
				FCore::appName, // 0
				FCore::versionString, // 1
				FCore::version_code, // 2
				Win32::GetModuleFileNameT(), // 3
				FLogger::Inst().GetFile(), // 4
				FCore::buildTime, // 5
				Win32::GetCommandLineT(), // 6
				desktopWindowRect.width, // 7
				desktopWindowRect.height // 8
			)
		);
		
		if (newProgramFn == nullptr)
		{
			FLogger::Inst().LogFatalODS(TEXT("newProgramFn is nullptr"));
			return 0;
		}
		
		FProgram *program = newProgramFn();
		if (program == nullptr)
		{
			FLogger::Inst().LogFatalODS(TEXT("program is nullptr"));
			return 0;
		}
		
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
				program->Tick();
			}
		}
		
		delete program;
		
		return (int) msg.wParam;
	}
	
} // GenesisCube



