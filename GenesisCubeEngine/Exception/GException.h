#pragma once

#include <utility>

#include "../Core/GenesisCubeEngine.h"
#include "../Object/GObject.h"

namespace GenesisCubeEngine
{

	/// <summary>
	/// 异常
	/// </summary>
    class GException : private std::exception
	{
	public:

	public:

		/// <summary>
		/// 无参构造
		/// </summary>
		inline GException() = default;

		/// <summary>
		/// 有参构造
		/// </summary>
		/// <param name="_message">消息</param>
		inline explicit GException(TString _message) : message(std::move(_message)) {}

		/// <summary>
		/// 析构
		/// </summary>
		inline ~GException() override = default;

	public:

		/// <summary>
		/// 获取异常的消息
		/// </summary>
		/// <returns>消息</returns>
		[[nodiscard]]
        inline virtual TString What() const { return this->message; }

	private:

		const TString message;

	};

	

}