#pragma once

#include "../Core/GenesisCubeEngine.h"
#include "../Object/GObject.h"
#include "../Core/TPtr.h"

namespace GenesisCubeEngine
{
	/// <summary>
	/// 文件名类
	/// </summary>
	class GFileName : public GObject
	{
	public:

		GFileName() = default;

		explicit GFileName(TString fileName);

		~GFileName() override = default;

	public:

		/// <summary>
		/// 设置文件名
		/// </summary>
		/// <param name="_fileName">文件名</param>
		inline virtual void SetFileName(const TString& _fileName) { this->fileName = _fileName; }

	public:

		/// <summary>
		/// 克隆
		/// </summary>
		/// <returns></returns>
		[[nodiscard]]
        inline GFileName* Clone() const noexcept override { return new GFileName(this->fileName); }

		/// <summary>
		/// 获取文件名
		/// </summary>
		/// <returns>文件名</returns>
		[[nodiscard]]
        inline const TString& GetFileName() const noexcept { return this->fileName; }

	protected:

		TString fileName;

	};

}