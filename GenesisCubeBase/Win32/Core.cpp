//
// Created by admin on 2024/1/12.
//

#include "Core.h"
#include "../Core/Debug.h"

namespace GenesisCube::Win32
{
	
	void Exit(int32_t result)
	{
		::PostQuitMessage(result);
	}
	
	int32_t GetCommandShow()
	{
		STARTUPINFOW startup_info{};
		GetStartupInfoW(&startup_info);
		
		return startup_info.dwFlags & STARTF_USESHOWWINDOW
			   ? startup_info.wShowWindow
			   : SW_SHOWDEFAULT;
	}
	
	void *GetInstance()
	{
		static void *hInstance = ::GetModuleHandle(nullptr);
		return hInstance;
	}
	
	void *GetIcon(int32_t id)
	{
		return ::LoadImage((HINSTANCE) GetInstance(), MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	}
	
	void *GetIcon(int32_t id, void *hInstance)
	{
		return ::LoadImage((HINSTANCE) hInstance, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	}
	
	void *GetCursor(int32_t id)
	{
		return ::LoadImage((HINSTANCE) GetInstance(), MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR);
	}
	
	void *GetCursor(int32_t id, void *hInstance)
	{
		return ::LoadImage((HINSTANCE) hInstance, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR);
	}
	
	void GainAdminPrivileges(const TString &strApp)
	{
		SHELLEXECUTEINFO execInfo;
		memset(&execInfo, 0, sizeof(execInfo));
		execInfo.lpFile = strApp.c_str();
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpVerb = TEXT("runas");
		execInfo.fMask = SEE_MASK_NO_CONSOLE;
		execInfo.nShow = SW_SHOWDEFAULT;
		
		ShellExecuteEx(&execInfo);
	}
	
	bool IsRunAsAdministrator()
	{
		BOOL fIsRunAsAdmin = FALSE;
		DWORD dwError = ERROR_SUCCESS;
		PSID pAdministratorsGroup = nullptr;
		
		SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
		if (!AllocateAndInitializeSid(
			&NtAuthority,
			2,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0,
			&pAdministratorsGroup
		))
		{
			dwError = GetLastError();
			goto Cleanup;
		}
		
		if (!CheckTokenMembership(nullptr, pAdministratorsGroup, &fIsRunAsAdmin))
		{
			dwError = GetLastError();
			goto Cleanup;
		}

Cleanup:
		
		if (pAdministratorsGroup)
		{
			FreeSid(pAdministratorsGroup);
			pAdministratorsGroup = nullptr;
		}
		
		if (ERROR_SUCCESS != dwError)
		{
			ThrowIfFailed((HRESULT) dwError);
		}
		
		return fIsRunAsAdmin;
	}
	
	
	TString GetCommandLineT()
	{
		return ::GetCommandLine();
	}
	
}