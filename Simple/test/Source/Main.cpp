//
// Created by admin on 2024/1/8.
//

#include "GenesisCubeEngine/Core/WinMain.h"
#include "Game.h"

FProgram *NewProgram()
{
	return new MyProgram();
}

int main()
{
#if defined(_DEBUG) || defined(DEBUG)
	// 当为DEBUG模式时，启用内存泄漏检测
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	FCore::showName = TEXT("Genshin Impact Pianist");
	// 判断是否以管理员模式运行
	if (!Win32::IsRunAsAdministrator())
	{
		// 以管理员模式运行
		Win32::GainAdminPrivileges(Win32::GetModuleFileNameT());
		return 0;
	}
	return FCore::Running(NewProgram);
}
