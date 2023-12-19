//
// Created by admin on 2023/12/19.
//

#include "GObject.h"
#include "../Core/FFormatter.h"

namespace GenesisCubeEngine
{
    
    GObject::GObject() noexcept
        : ref(0)
    {
    
    }
    
    GObject::~GObject() noexcept(false)
    {
        if (this->ref != 0)
        {
            throw GNotReleasedException(TEXT(__FUNCSIG__) TEXT(":: GetRef() should be zero"));
        }
    }
    
    TString GObject::ToString() const noexcept
    {
        TCHAR buffer[20];
        wsprintf(buffer, TEXT("0x%p"), this);
        return buffer;
    }
    
    TString GObject::ToShowString() const noexcept
    {
        TString buffer;
#ifdef UNICODE
        buffer.append(FFormatter::StringToWString(typeid(*this).name()));
#else
        buffer.append(typeid(*this).name());
#endif // UNICODE
        buffer.append(TEXT("<"));
        buffer.append(GObject::ToString());
        buffer.append(TEXT(">"));
        return buffer;
    }
    
    size_t GObject::AddRef() noexcept
    {
        return ++this->ref;
    }
    
    size_t GObject::Release() noexcept
    {
        if (--this->ref == 0)
        {
            delete this;
            return 0;
        }
        return this->ref;
    }
    
} // GenesisCubeEngine