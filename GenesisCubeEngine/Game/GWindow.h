//
// Created by admin on 2023/12/19.
//

#pragma once

#include "../Object/GObject.h"

namespace GenesisCubeEngine
{
    //
    // 窗口
    //
    class GWindow : public GObject
    {
    public:
        
        GWindow();
        
        ~GWindow() override;
    
    public:
        
        void Show();
    
    public:
        
        [[nodiscard]]
        inline HWND GetHWnd() const noexcept { return this->hWnd; }
    
    private:
        
        HWND hWnd;
        
        int mouseX;
        
        int mouseY;
        
    };
    
} // GenesisCubeEngine
