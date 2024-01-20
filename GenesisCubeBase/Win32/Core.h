//
// Created by admin on 2024/1/12.
//

#pragma once

#include "../Core/FCore.h"

namespace GenesisCube::Win32
{
	
	///
	/// 退出消息循环
	/// \param result 返回值
	void Exit(int32_t result = 0);
	
	///
	/// \return 是否以管理员模式运行
	bool IsRunAsAdministrator();
	
	///
	/// 以管理员权限启动应用
	/// \param strApp 模块文件名
	void GainAdminPrivileges(const TString &strApp);
	
	///
	/// \return
	int32_t GetCommandShow();
	
	///
	/// \return 命令行
	TString GetCommandLineT();
	
	///
	/// \return 应用实例
	void *GetInstance();
	
	///
	/// \param id 图标资源ID
	/// \return 图标
	void *GetIcon(int32_t id);
	
	///
	/// \param id 图标资源ID
	/// \param hInstance 应用实例
	/// \return 图标
	void *GetIcon(int32_t id, void *hInstance);
	
	///
	/// \param id 光标资源ID
	/// \return 光标
	void *GetCursor(int32_t id);
	
	///
	/// \param id 光标资源ID
	/// \param hInstance 应用实例
	/// \return 光标
	void *GetCursor(int32_t id, void *hInstance);
	
}
