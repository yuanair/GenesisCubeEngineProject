#pragma once
#include "../Core/GenesisCubeEngine.h"

#include "../Object/GObject.h"

namespace GenesisCubeEngine
{
	/// <summary>
	/// 读取器
	/// </summary>
	interface IReader
	{

		/// <summary>
		/// 检查是否可以读写
		/// </summary>
		inline virtual operator bool() const { return Good(); }

		/// <summary>
		/// 检查是否可以读写
		/// </summary>
		/// <returns>是否可以读写</returns>
		virtual bool Good() const = 0;

		/// <summary>
		/// 读取下一个
		/// </summary>
		virtual GObject* Next() = 0;

	};

}
