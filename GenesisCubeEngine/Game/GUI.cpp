//
// Created by admin on 2023/12/28.
//

#include "GUI.h"

namespace GenesisCube
{
	GUI::GUI() = default;
	
	GUI::~GUI() = default;
	
	bool GUI::IsOnUI(const D2D1_POINT_2F &point)
	{
		return point.x > x && point.x < x + w && point.y > y && point.y < y + h;
	}
	
	GUI *GUI::Clone() const noexcept
	{
		GUI *ptr = new GUI();
		ptr->x = this->x;
		ptr->y = this->y;
		ptr->w = this->w;
		ptr->h = this->h;
		return ptr;
	}
	
	void GUI::OnRender(ID2D1RenderTarget *renderTarget)
	{
	
	}
	
} // GenesisCube