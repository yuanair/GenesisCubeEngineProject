#pragma once

#include "../Core/Header.h"
#include "EException.h"

namespace GenesisCubeEngine
{
	
	/// <summary>
	/// 越界异常
	/// </summary>
	class EOutOfRangeException : public EException
	{
	public:
		
		inline EOutOfRangeException() = default;
		
		inline explicit EOutOfRangeException(const TString &message) : EException(message) {}
		
	};
	
	/// <summary>
	/// 空指针异常
	/// </summary>
	class ENullptrException : public EException
	{
	public:
		
		inline ENullptrException() = default;
		
		inline explicit ENullptrException(const TString &message) : EException(message) {}
		
	};
	
	/// <summary>
	/// 无效参数异常
	/// </summary>
	class EInvalidArgumentException : public EException
	{
	public:
		
		inline EInvalidArgumentException() = default;
		
		inline explicit EInvalidArgumentException(const TString &message) : EException(message) {}
		
	};
	
	/// <summary>
	/// 未释放异常
	/// </summary>
	class ENotReleasedException : public EException
	{
	public:
		
		inline ENotReleasedException() = default;
		
		inline explicit ENotReleasedException(const TString &message) : EException(message) {}
		
	};
	
	/// <summary>
	/// 不好的异常
	/// </summary>
	class EBadException : public EException
	{
	public:
		
		inline EBadException() = default;
		
		inline explicit EBadException(const TString &message) : EException(message) {}
		
	};
	
}