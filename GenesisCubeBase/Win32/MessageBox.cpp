//
// Created by admin on 2024/1/12.
//

#include "MessageBox.h"
#include "../Core/Debug.h"
#include <windows.h>

namespace GenesisCube::Win32
{
	
	MessageBoxResult MessageBoxT(
		const TString &message, const TString &caption, MessageBoxType type, MessageBoxIcon icon, uint8_t defaultButton)
	{
		return MessageBoxT(nullptr, message, caption, type, icon, defaultButton);
	}
	
	MessageBoxResult MessageBoxT(
		const TString &message, const TString &caption, MessageBoxIcon icon, MessageBoxType type, uint8_t defaultButton)
	{
		return MessageBoxT(nullptr, message, caption, type, icon, defaultButton);
	}
	
	MessageBoxResult MessageBoxT(
		void *hwnd, const TString &message, const TString &caption, MessageBoxIcon icon, MessageBoxType type,
		uint8_t defaultButton)
	{
		return MessageBoxT(hwnd, message, caption, type, icon, defaultButton);
	}
	
	MessageBoxResult MessageBoxT(
		void *hwnd, const TString &message, const TString &caption, MessageBoxType type, MessageBoxIcon icon,
		uint8_t defaultButton)
	{
		FLogger::Inst().LogInfoODS(
			std::format(
				TEXT(
					"[MessageBox] hWnd: 0x{:016X}, message: \"{}\", caption: \"{}\", type: {}, icon: {}, defaultButton: {}"),
				(uintptr_t) hwnd, message, caption, (int32_t) type, (int32_t) icon, (int32_t) defaultButton
			));
		return MessageBoxResultFromCode(
			::MessageBox(
				(HWND) hwnd,
				message.c_str(),
				caption.c_str(),
				MessageBoxTypeToCode(type) | MessageBoxIconToCode(icon) | MessageBoxDefaultButtonToCode(defaultButton)
			));
	}
	
	TString MessageBoxResultToString(MessageBoxResult result)
	{
		switch (result)
		{
			case MessageBoxResultOK:
				return TEXT("OK");
			case MessageBoxResultCancel:
				return TEXT("Cancel");
			case MessageBoxResultAbort:
				return TEXT("Abort");
			case MessageBoxResultRetry:
				return TEXT("Retry");
			case MessageBoxResultIgnore:
				return TEXT("Ignore");
			case MessageBoxResultYes:
				return TEXT("Yes");
			case MessageBoxResultNo:
				return TEXT("No");
			case MessageBoxResultTryAgain:
				return TEXT("TryAgain");
			case MessageBoxResultContinue:
				return TEXT("Continue");
			case MessageBoxResultTimeOut:
				return TEXT("TimeOut");
			case MessageBoxResultNull:
			default:
				return TEXT("<Unknown>");
		}
	}
	
	uint32_t MessageBoxTypeToCode(MessageBoxType messageBoxType)
	{
		switch (messageBoxType)
		{
			case MessageBoxTypeOK:
				return MB_OK;
			case MessageBoxTypeOKCancel:
				return MB_OKCANCEL;
			case MessageBoxTypeAbortRetryIgnore:
				return MB_ABORTRETRYIGNORE;
			case MessageBoxTypeYesNo:
				return MB_YESNO;
			case MessageBoxTypeYesNoCancel:
				return MB_YESNOCANCEL;
			case MessageBoxTypeRetryCancel:
				return MB_RETRYCANCEL;
			case MessageBoxTypeCancelTryContinue:
				return MB_CANCELTRYCONTINUE;
			default:
				return MB_OK;
		}
	}
	
	uint32_t MessageBoxIconToCode(MessageBoxIcon messageBoxIcon)
	{
		switch (messageBoxIcon)
		{
			case MessageBoxIconNull:
				return 0;
			case MessageBoxIconUser:
				return MB_USERICON;
			case MessageBoxIconInfo:
				return MB_ICONINFORMATION;
			case MessageBoxIconQuestion:
				return MB_ICONQUESTION;
			case MessageBoxIconWarning:
				return MB_ICONWARNING;
			case MessageBoxIconError:
			case MessageBoxIconStop:
			default:
				return MB_ICONERROR;
		}
	}
	
	uint32_t MessageBoxDefaultButtonToCode(uint8_t defaultButton)
	{
		switch (defaultButton)
		{
			case 0:
				return MB_DEFBUTTON1;
			case 1:
				return MB_DEFBUTTON2;
			case 2:
				return MB_DEFBUTTON3;
			case 3:
				return MB_DEFBUTTON4;
			default:
				return MB_DEFBUTTON1;
		}
	}
	
	MessageBoxResult MessageBoxResultFromCode(int32_t value)
	{
		switch (value)
		{
			case IDOK:
				return MessageBoxResultOK;
			case IDCANCEL:
				return MessageBoxResultCancel;
			case IDABORT:
				return MessageBoxResultAbort;
			case IDRETRY:
				return MessageBoxResultRetry;
			case IDIGNORE:
				return MessageBoxResultIgnore;
			case IDYES:
				return MessageBoxResultYes;
			case IDNO:
				return MessageBoxResultNo;
			case IDTRYAGAIN:
				return MessageBoxResultTryAgain;
			case IDCONTINUE:
				return MessageBoxResultContinue;
			case IDTIMEOUT:
				return MessageBoxResultTimeOut;
			case IDCLOSE:
			case IDHELP:
			default:
				return MessageBoxResultNull;
		}
	}
	
} // GenesisCube