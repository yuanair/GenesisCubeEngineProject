//
// Created by admin on 2023/12/28.
//

#pragma once

#include "../Core/Header.h"
#include "../Object/GObject.h"
#include "../DirectX/GD2D1RenderTarget.h"

namespace GenesisCube
{
	///
	/// UI
	///
	class GUI : public GObject
	{
	public:
		
		GUI();
		
		~GUI() override;
	
	public:
		
		///
		/// 渲染
		/// \param renderTarget 渲染目标
		virtual void OnRender(ID2D1RenderTarget *renderTarget);
		
		///
		/// 判断点是否在UI上
		/// \param point 点
		/// \return 点是否在UI上
		virtual bool IsOnUI(const D2D1_POINT_2F &point);
		
		///
		/// \return 矩形
		[[nodiscard]]
		inline D2D1_RECT_F ToRect() const
		{
			return D2D1::RectF(
				this->x, this->y, this->x + this->w, this->y + this->h
			);
		}
		
		///
		/// \return 矩形
		[[nodiscard]]
		inline D2D1_POINT_2F GetPoint() const
		{
			return D2D1::Point2F(this->x, this->y);
		}
		
		///
		/// \return 矩形
		[[nodiscard]]
		inline D2D1_SIZE_F GetSize() const
		{
			return D2D1::SizeF(this->w, this->h);
		}
	
	public:
		
		[[nodiscard]]
		GUI *Clone() const noexcept override;
	
	public:
		
		/// x坐标
		float x = 0.f;
		
		/// y坐标
		float y = 0.f;
		
		/// 宽度
		float w = 0.f;
		
		/// 高度
		float h = 0.f;
		
	};
	
} // GenesisCube
