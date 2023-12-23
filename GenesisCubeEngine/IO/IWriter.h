#pragma once
#include "../Core/Header.h"

#include "../Object/GObject.h"

namespace GenesisCubeEngine
{
	/// <summary>
	/// 写入器
	/// </summary>
	interface IWriter
	{

		/// <summary>
		/// 写入
		/// </summary>
		/// <param name="value">值</param>
		/// <return>*this</return>
		virtual IWriter& Write(const GObject& value) = 0;

	};

}
