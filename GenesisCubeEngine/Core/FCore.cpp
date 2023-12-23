//
// Created by admin on 2023/12/19.
//

#include "FCore.h"
#include "../Debug/Debug.h"

namespace GenesisCubeEngine
{
	
	const TCHAR FCore::name[] = TEXT("Genesis Cube Engine");
	
	const TCHAR FCore::versionString[] = TEXT("0.1-alpha");
	
	const TCHAR FCore::buildTime[] = TEXT(__DATE__);
	
	const int FCore::version_code = 1;
	
	void FCore::Exit(int nExitCode)
	{
		PostQuitMessage(nExitCode);
	}
	
	HINSTANCE FCore::Shell(HWND hWnd, const TString &operation, const TString &file, const TString &parameters,
						   const TString &directory, INT showCmd)
	{
		return ShellExecute(hWnd, operation.c_str(), file.c_str(), parameters.c_str(), directory.c_str(), showCmd);
	}
	
	HINSTANCE FCore::GetInstance()
	{
		return GetModuleHandle(nullptr);
	}
	
	TString FCore::GetCmdLine()
	{
		return GetCommandLine();
	}
	
	int FCore::Run(GProgram &program)
	{
		// 定义
		MSG msg = {};
		
		// 当为DEBUG模式时，内存泄漏检测
		if (GenesisCubeEngine::bIsDebug)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
		
		// log
		{
			TString buffer;
			buffer += std::format(
				TEXT(
					R"([{0} {1} (code: {2})]
	[running path: {3}]
	[logger file: {4}]
	[build time: {5}]
	[build type: {6}{7}]
	[lpCmdLine: {8}]
)"),
				FCore::name, // 0
				FCore::versionString, // 1
				FCore::version_code, // 2
				GDirectoryName::ModuleFile().GetFileName(), // 3
				FLogger::Inst().GetFile(), // 4
				FCore::buildTime, // 5
				buildType, // 6
				bIsDebug ? TEXT("Debug") : TEXT("Release"), // 7
				FCore::GetCmdLine()// 8
			);
			
			FLogger::Inst().LogInfoODS(buffer);
		}
		
		// 开始
		program.Start();
		
		// 消息循环
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Tick
				program.Tick();
			}
		}
		
		// 结束
		program.End();
		
		// 删除日志实例
		GenesisCubeEngine::FLogger::DeleteInstance();
		
		return (int) msg.wParam;
	}
	
} // GenesisCubeEngine

