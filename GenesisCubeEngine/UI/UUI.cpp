//
// Created by admin on 2024/1/19.
//

#include "UUI.h"
#include "../../GenesisCubeBase/Core/Debug.h"

namespace GenesisCube
{
	void UUI::Render(UUI::RenderTarget *renderTarget)
	{
		OnRender(renderTarget);
	}
	
	D2D1_RECT_F UUI::GetParentRect() const noexcept
	{
		return this->parent ? this->parent->GetRect() : D2D1::RectF();
	}
	
	PPanel::~PPanel()
	{
		for (auto &item: this->childs)
		{
			if (item == nullptr) continue;
			delete item;
			item = nullptr;
		}
	}
	
	
	bool PPanel::IsInnerPoint(const D2D1_POINT_2F &point)
	{
		UUI::IsInnerPoint(point);
		D2D1_RECT_F rect = GetRect();
		return point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom;
	}
	
	void PPanel::RemoveChild(UUI *ui)
	{
		if (ui == nullptr) return;
		delete ui;
		this->childs.remove(ui);
	}
	
	void PPanel::Render(UUI::RenderTarget *renderTarget)
	{
		UUI::Render(renderTarget);
		ReCalculator();
		for (auto &item: this->childs)
		{
			if (item == nullptr) continue;
			item->Render(renderTarget);
		}
	}
	
	void PPanel::Calculator(
		D2D1_RECT_F &out, const D2D1_RECT_F &in, const D2D1_RECT_F &parent, PPanel::Mode mode,
		PPanel::AlignmentMode horizontal, PPanel::AlignmentMode vertical)
	{
		switch (mode)
		{
			case ModeKeep:
				out = in;
				break;
			case ModeDefault:
			default:
				out = D2D1::RectF(
					in.left * parent.left,
					in.top * parent.top,
					in.right * parent.right,
					in.bottom * parent.bottom
				);
				break;
		}
	}
	
	void PClipPanel::Render(UUI::RenderTarget *renderTarget)
	{
		if (this->bitmapRenderTarget == nullptr) Init(renderTarget);
		this->bitmapRenderTarget->BeginDraw();
		PPanel::Render(this->bitmapRenderTarget.Get());
		ThrowIfFailed(this->bitmapRenderTarget->EndDraw());
		ID2D1Bitmap *bitmap;
		bitmapRenderTarget->GetBitmap(&bitmap);
		renderTarget->DrawBitmap(bitmap, GetRect());
	}
	
	void PClipPanel::Init(UUI::RenderTarget *renderTarget)
	{
		D2D1_RECT_F rect = GetRect();
		ThrowIfFailed(
			renderTarget->CreateCompatibleRenderTarget(
				D2D1::SizeF(rect.right - rect.left, rect.bottom - rect.top),
				this->bitmapRenderTarget.ReleaseAndGetAddressOf())
		);
	}
} // GenesisCube