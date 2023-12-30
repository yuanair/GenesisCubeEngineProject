//
// Created by admin on 2023/12/28.
//

#include "GUIVector.h"

namespace GenesisCube
{
	GUIVector::GUIVector() {}
	
	GUIVector::~GUIVector()
	{
	
	}
	
	void GUIVector::Render(ID2D1RenderTarget *renderTarget)
	{
		for (auto &ptr: guis)
		{
			ptr->OnRender(renderTarget);
		}
	}
	
	GUIVector *GUIVector::Clone() const noexcept
	{
		return new GUIVector();
	}
	
} // GenesisCube