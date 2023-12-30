//
// Created by admin on 2023/12/27.
//

#include "GD2D1SolidColorBrush.h"

namespace GenesisCube
{
	
	
	void GD2D1SolidColorBrush::SetColor(float r, float g, float b, float a)
	{
		ThrowIfNull();
		GetComPtr()->SetColor(D2D1::ColorF(r, g, b, a));
	}
	
	void GD2D1SolidColorBrush::SetColor(const D2D1_COLOR_F &color)
	{
		ThrowIfNull();
		GetComPtr()->SetColor(color);
	}
	
	D2D1_COLOR_F GD2D1SolidColorBrush::GetColor()
	{
		ThrowIfNull();
		return GetComPtr()->GetColor();
	}
} // GenesisCube