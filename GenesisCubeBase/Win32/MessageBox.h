//
// Created by admin on 2024/1/12.
//

#pragma once

#include "../Core/FCore.h"

namespace GenesisCube::Win32
{
	
	
	///
	/// 消息框返回值
	///
	enum MessageBoxResult
	{
		/// 无返回值
		MessageBoxResultNull,
		
		/// 按下OK
		MessageBoxResultOK,
		
		/// 按下Cancel
		MessageBoxResultCancel,
		
		/// 按下Abort
		MessageBoxResultAbort,
		
		/// 按下Retry
		MessageBoxResultRetry,
		
		/// 按下Ignore
		MessageBoxResultIgnore,
		
		/// 按下Yes
		MessageBoxResultYes,
		
		/// 按下No
		MessageBoxResultNo,
		
		/// 重试
		MessageBoxResultTryAgain,
		
		/// 继续
		MessageBoxResultContinue,
		
		/// 超时
		MessageBoxResultTimeOut,
	};
	
	///
	/// 消息框类型
	///
	enum MessageBoxType
	{
		/// 仅有一个OK按钮
		MessageBoxTypeOK,
		
		/// 一个OK按钮与一个Cancel按钮
		MessageBoxTypeOKCancel,
		
		/// 一个Abort按钮，一个Retry按钮与一个Ignore按钮
		MessageBoxTypeAbortRetryIgnore,
		
		/// 一个Yes按钮与一个No按钮
		MessageBoxTypeYesNo,
		
		/// 一个Yes按钮，一个No按钮与一个Cancel按钮
		MessageBoxTypeYesNoCancel,
		
		/// 一个Retry按钮与一个Cancel按钮
		MessageBoxTypeRetryCancel,
		
		/// 一个Cancel按钮，一个Try按钮与一个Continue按钮
		MessageBoxTypeCancelTryContinue,
	};
	
	///
	/// 消息框图标
	///
	enum MessageBoxIcon
	{
		/// 无图标
		MessageBoxIconNull,
		
		/// 用户自定义图标
		MessageBoxIconUser,
		
		/// 消息图标
		MessageBoxIconInfo,
		
		/// 问号图标
		MessageBoxIconQuestion,
		
		/// 警告图标
		MessageBoxIconWarning,
		
		/// 错误图标
		MessageBoxIconError,
		
		/// 错误图标
		MessageBoxIconStop,
	};
	
	///
	/// 消息框
	/// \param message 消息
	/// \param caption 标题
	/// \param type 类型
	/// \param icon 图标
	/// \param defaultButton 默认按钮编号
	/// \return 按下的按钮
	MessageBoxResult MessageBoxT(
		const TString &message, const TString &caption,
		MessageBoxType type = MessageBoxTypeOK, MessageBoxIcon icon = MessageBoxIconNull,
		uint8_t defaultButton = 0
	);
	
	///
	/// 消息框
	/// \param message 消息
	/// \param caption 标题
	/// \param icon 图标
	/// \param type 类型
	/// \param defaultButton 默认按钮编号
	/// \return 按下的按钮
	MessageBoxResult MessageBoxT(
		const TString &message, const TString &caption,
		MessageBoxIcon icon, MessageBoxType type = MessageBoxTypeOK,
		uint8_t defaultButton = 0
	);
	
	///
	/// 消息框
	/// \param hwnd 父窗口句柄
	/// \param message 消息
	/// \param caption 标题
	/// \param type 类型
	/// \param icon 图标
	/// \param defaultButton 默认按钮编号
	/// \return 按下的按钮
	MessageBoxResult MessageBoxT(
		void *hwnd, const TString &message, const TString &caption, MessageBoxType type = MessageBoxTypeOK,
		MessageBoxIcon icon = MessageBoxIconNull, uint8_t defaultButton = 0
	);
	
	///
	/// 消息框
	/// \param hwnd 父窗口句柄
	/// \param message 消息
	/// \param caption 标题
	/// \param icon 图标
	/// \param type 类型
	/// \param defaultButton 默认按钮编号
	/// \return 按下的按钮
	MessageBoxResult MessageBoxT(
		void *hwnd, const TString &message, const TString &caption,
		MessageBoxIcon icon, MessageBoxType type = MessageBoxTypeOK,
		uint8_t defaultButton = 0
	);
	
	///
	/// \param result 返回值
	/// \return 字符串
	TString MessageBoxResultToString(MessageBoxResult result);
	
	///
	/// \param messageBoxType
	/// \return
	uint32_t MessageBoxTypeToCode(MessageBoxType messageBoxType);
	
	///
	/// \param messageBoxIcon
	/// \return
	uint32_t MessageBoxIconToCode(MessageBoxIcon messageBoxIcon);
	
	///
	/// \param defaultButton
	/// \return
	uint32_t MessageBoxDefaultButtonToCode(uint8_t defaultButton);
	
	///
	/// \param value
	/// \return
	MessageBoxResult MessageBoxResultFromCode(int32_t value);
	
	
} // GenesisCube
