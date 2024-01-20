//
// Created by admin on 2024/1/19.
//

#pragma once

#include "../Core/Header.h"
#include "../../GenesisCubeBase/Core/GenesisCubeDef.h"
#include "../../GenesisCubeBase/Core/TPtr.h"

namespace GenesisCube
{
	///
	/// UI
	class UUI
	{
		
		friend class PPanel;
	
	public:
		
		typedef ID2D1RenderTarget RenderTarget;
		
		typedef ID2D1Brush Brush;
		
		typedef IDWriteTextFormat TextFormat;
	
	public:
		
		UUI() {}
		
		UUI(const UUI &) = delete;
		
		virtual ~UUI() {}
		
		UUI &operator=(const UUI &) = delete;
	
	public:
		
		///
		/// \param renderTarget 渲染目标
		virtual void Render(RenderTarget *renderTarget);
		
		///
		/// \param point 点
		/// \return 点是否在内部
		virtual bool IsInnerPoint(const D2D1_POINT_2F &point) const { return false; }
	
	protected:
		
		///
		/// \param renderTarget 渲染目标
		virtual void OnRender(RenderTarget *renderTarget) {}
	
	public:
		
		///
		/// \return 父面板矩形
		[[nodiscard]]
		D2D1_RECT_F GetParentRect() const noexcept;
		
		///
		/// \return 父面板
		[[nodiscard]]
		inline class PPanel *GetParent() const noexcept { return this->parent; }
	
	private:
		
		virtual void SetParent(class PPanel *newParent) noexcept { this->parent = newParent; }
	
	private:
		
		class PPanel *parent = nullptr;
		
	};
	
	///
	/// 面板
	class PPanel : public UUI
	{
		
		friend class UUI;
	
	public:
		
		/// 模式
		enum Mode : uint8_t
		{
			// 默认百分比(left, top, right, bottom)
			ModeDefault,
			// 保持不变(left, top, right, bottom)
			ModeKeep,
			// 保持长宽比（填充内部）
			KeepAspectRatioFullInner,
			// 保持长宽比（填充外部）
			KeepAspectRatioFullOuter
		};
		
		/// 对齐模式
		enum AlignmentMode : uint8_t
		{
			// 默认
			AlignmentDefault,
			// 居中
			Center,
		};
	
	public:
		
		PPanel() {}
		
		~PPanel() override;
	
	public:
		
		///
		/// 计算对齐模式
		/// \param in
		/// \param out
		/// \param parent
		/// \param mode
		/// \param horizontal
		/// \param vertical
		static void Calculator(
			D2D1_RECT_F &out, const D2D1_RECT_F &in, const D2D1_RECT_F &parent, Mode mode = ModeDefault,
			AlignmentMode horizontal = AlignmentDefault, AlignmentMode vertical = AlignmentDefault);
	
	public:
		
		void Render(RenderTarget *renderTarget) override;
		
		[[nodiscard]]
		bool IsInnerPoint(const D2D1_POINT_2F &point) const override;
		
		///
		/// 创建子控件
		/// \tparam T
		/// \tparam Args
		/// \param args
		/// \return
		template<class T, class ... Args>
		inline T *NewChild(Args... args)
		{
			T *ptr = new T(args...);
			this->childs.push_back(ptr);
			ptr->SetParent(this);
			return ptr;
		}
		
		///
		/// 移除
		/// \param ui
		void RemoveChild(UUI *ui);
		
		///
		/// 重计算
		inline void ReCalculator() noexcept
		{
			Calculator(
				rect, calculatorRect, GetParentRect(), mode, horizontal, vertical
			);
		};
		
		///
		/// 设置计算矩形
		/// \param newRect 新计算矩形
		void SetCalRect(const D2D1_RECT_F &newRect) noexcept
		{
			this->calculatorRect = newRect;
			ReCalculator();
		}
		
		///
		/// 设置模式
		/// \param newRect 新模式
		void SetMode(Mode newMode) noexcept
		{
			this->mode = newMode;
			ReCalculator();
		}
		
		///
		/// 设置模式
		/// \param newRect 新模式
		void SetHorizontal(AlignmentMode newMode) noexcept
		{
			this->horizontal = newMode;
			ReCalculator();
		}
		
		///
		/// 设置模式
		/// \param newRect 新模式
		void SetVertical(AlignmentMode newMode) noexcept
		{
			this->vertical = newMode;
			ReCalculator();
		}
	
	private:
		
		void SetParent(PPanel *newParent) noexcept override
		{
			UUI::SetParent(newParent);
			ReCalculator();
		}
	
	public:
		
		///
		/// \return 子UI
		[[nodiscard]]
		inline const std::list<UUI *> &GetChilds() const noexcept { return this->childs; };
		
		///
		/// \return 矩形
		[[nodiscard]]
		inline const D2D1_RECT_F &GetRect() const noexcept { return this->rect; };
		
		///
		/// \return 计算矩形
		[[nodiscard]]
		inline const D2D1_RECT_F &GetCalRect() const noexcept { return this->calculatorRect; };
		
		///
		/// \return 模式
		[[nodiscard]]
		inline Mode GetMode() const noexcept { return this->mode; }
		
		///
		/// \return 水平模式
		[[nodiscard]]
		inline AlignmentMode GetHorizontal() const noexcept { return this->horizontal; }
		
		///
		/// \return 垂直模式
		[[nodiscard]]
		inline AlignmentMode GetVertical() const noexcept { return this->vertical; }
	
	private:
		
		std::list<class UUI *> childs;
		
		D2D1_RECT_F rect{};
		
		D2D1_RECT_F calculatorRect{0.0f, 0.0f, 1.0f, 1.0f};
		
		Mode mode = ModeDefault;
		
		AlignmentMode horizontal = AlignmentDefault;
		
		AlignmentMode vertical = AlignmentDefault;
		
	};
	
	///
	/// 面板
	class PClipPanel : public PPanel
	{
		
		friend class UUI;
	
	public:
		
		PClipPanel() {}
		
		~PClipPanel() override {}
	
	public:
		
		void Render(RenderTarget *renderTarget) override;
		
		void Init(UUI::RenderTarget *renderTarget);
	
	private:
		
		TComPtr<ID2D1BitmapRenderTarget> bitmapRenderTarget;
		
	};
	
} // GenesisCube
