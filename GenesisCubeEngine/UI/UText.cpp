//
// Created by admin on 2024/1/19.
//

#include "UText.h"

namespace GenesisCube
{
	void UText::OnRender(UUI::RenderTarget *renderTarget)
	{
		UUI::OnRender(renderTarget);
		
		renderTarget->DrawText(
			showText.c_str(), (uint32_t) showText.size(), textFormat.Get(), GetParentRect(), defaultFillBrush.Get(),
			drawTextOptions, measuringMode
		);
	}
} // GenesisCube