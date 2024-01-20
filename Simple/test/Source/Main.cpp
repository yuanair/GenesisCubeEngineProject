//
// Created by admin on 2024/1/8.
//

#include "Game.h"

///
/// running mode
///
#ifdef _DEBUG
static constexpr GenesisCube::FCore::RunningMode runningMode = GenesisCube::FCore::Debug;
#else
static constexpr GenesisCube::FCore::RunningMode runningMode = GenesisCube::FCore::Release;
#endif

int main()
{
	FCore::showName = TEXT("Genshin Impact Pianist");
	// 判断是否以管理员模式运行
	if (!Win32::IsRunAsAdministrator())
	{
		// 以管理员模式运行
		Win32::GainAdminPrivileges(Win32::GetModuleFileNameT());
		return 0;
	}
	MyProgram myProgram;
	return FCore::Running(myProgram, runningMode);
}
