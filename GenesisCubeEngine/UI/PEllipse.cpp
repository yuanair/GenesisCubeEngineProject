//
// Created by admin on 2024/1/19.
//

#include "PEllipse.h"

namespace GenesisCube
{
	void PEllipse::OnRender(UUI::RenderTarget *renderTarget)
	{
		PPanel::OnRender(renderTarget);
		D2D1_ELLIPSE ellipse;
		D2D1_RECT_F rect = GetRect();
		ellipse.point = D2D1::Point2F((rect.right + rect.left) / 2.0f, (rect.bottom + rect.top) / 2.0f);
		ellipse.radiusX = (rect.right - rect.left) / 2.0f;
		ellipse.radiusY = (rect.bottom - rect.top) / 2.0f;
		if (fillBrush) renderTarget->FillEllipse(ellipse, fillBrush.Get());
		if (drawBrush) renderTarget->DrawEllipse(ellipse, drawBrush.Get());
	}
} // GenesisCube