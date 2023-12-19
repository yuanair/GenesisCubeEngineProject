#pragma once

#include "../Core/GenesisCubeEngine.h"
#include "GException.h"

namespace GenesisCubeEngine
{

	/// <summary>
	/// 越界异常
	/// </summary>
	class GOutOfRangeException : public GException
	{
	public:

		inline GOutOfRangeException() = default;

		inline explicit GOutOfRangeException(const TString& message) : GException(message) {}

	};

	/// <summary>
	/// 空指针异常
	/// </summary>
	class GNullptrException : public GException
	{
	public:

		inline GNullptrException() = default;

		inline explicit GNullptrException(const TString& message) : GException(message) {}

	};

	/// <summary>
	/// 无效参数异常
	/// </summary>
	class GInvalidArgumentException : public GException
	{
	public:

		inline GInvalidArgumentException() = default;

		inline explicit GInvalidArgumentException(const TString& message) : GException(message) {}

	};

	/// <summary>
	/// 未释放异常
	/// </summary>
	class GNotReleasedException : public GException
	{
	public:

		inline GNotReleasedException() = default;

		inline explicit GNotReleasedException(const TString& message) : GException(message) {}

	};

	/// <summary>
	/// 不好的异常
	/// </summary>
	class GBadException : public GException
	{
	public:

		inline GBadException() = default;

		inline explicit GBadException(const TString& message) : GException(message) {}

	};

}