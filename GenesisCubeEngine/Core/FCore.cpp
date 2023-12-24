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
	
	void FCore::Init()
	{
		
		// 当为DEBUG模式时，内存泄漏检测
		if (GenesisCubeEngine::bIsDebug)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}
		
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
	
	HICON FCore::GetIcon(const TString &iconName, HINSTANCE hInstance)
	{
		return ::LoadIcon(hInstance, iconName.c_str());
	}
	
	HICON FCore::GetIcon(short iconId, HINSTANCE hInstance)
	{
		return ::LoadIcon(hInstance, MAKEINTRESOURCE(iconId));
	}
	
	HICON FCore::GetIcon(const TString &iconName)
	{
		return GetIcon(iconName, FCore::GetInstance());
	}
	
	HICON FCore::GetIcon(short iconId)
	{
		return GetIcon(iconId, FCore::GetInstance());
	}
	
} // GenesisCubeEngine

