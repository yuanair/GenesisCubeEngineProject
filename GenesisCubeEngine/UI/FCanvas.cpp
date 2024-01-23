//
// Created by admin on 2024/1/19.
//

#include "FCanvas.h"

namespace GenesisCube
{
	void FCanvas::Render()
	{
		D2D1_SIZE_F size = renderTarget->GetSize();
		ui.SetMode(PPanel::ModeKeep);
		ui.SetCalRect(D2D1::RectF(0.0f, 0.0f, size.width, size.height));
		ui.SetHorizontal(PPanel::AlignmentDefault);
		ui.SetVertical(PPanel::AlignmentDefault);
		ui.Render(renderTarget.Get());
	}
} // GenesisCube