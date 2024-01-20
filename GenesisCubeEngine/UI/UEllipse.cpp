//
// Created by admin on 2024/1/19.
//

#include "UEllipse.h"

namespace GenesisCube
{
	void UEllipse::OnRender(UUI::RenderTarget *renderTarget)
	{
		UUI::OnRender(renderTarget);
		if (fillBrush) renderTarget->FillEllipse(this->ellipse, fillBrush.Get());
		if (drawBrush) renderTarget->DrawEllipse(this->ellipse, drawBrush.Get());
	}
} // GenesisCube