//
// Created by admin on 2023/12/28.
//

#include "GBox.h"

namespace GenesisCube
{
	void GBox::OnRender(ID2D1RenderTarget *renderTarget)
	{
		if (!brush) return;
		renderTarget->FillRectangle(ToRect(), brush.Get());
	}
	
	bool GBox::IsOnUI(const D2D1_POINT_2F &point)
	{
		return GUI::IsOnUI(point);
	}
	
	GBox *GBox::Clone() const noexcept
	{
		GBox *ptr = new GBox;
		ptr->x = this->x;
		ptr->y = this->y;
		ptr->w = this->w;
		ptr->h = this->h;
		this->brush.As(&ptr->brush);
		return ptr;
	}
} // GenesisCube