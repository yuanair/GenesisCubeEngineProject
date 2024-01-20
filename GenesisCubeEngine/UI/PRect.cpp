//
// Created by admin on 2024/1/19.
//

#include "PRect.h"

namespace GenesisCube
{
	
	void PRect::OnRender(UUI::RenderTarget *renderTarget)
	{
		UUI::OnRender(renderTarget);
		D2D1_RECT_F rect = GetRect();
		if (fillBrush) renderTarget->FillRectangle(rect, fillBrush.Get());
		if (drawBrush) renderTarget->DrawRectangle(rect, drawBrush.Get());
	}
	
} // GenesisCube