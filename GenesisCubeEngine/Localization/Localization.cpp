//
// Created by admin on 2023/12/21.
//
#include "Localization.h"

namespace GenesisCubeEngine
{
    
    
    TString GLanguage::Find(const GenesisCubeEngine::GStringList &list,
                            const GenesisCubeEngine::TString &key,
                            const GenesisCubeEngine::GLanguage *language)
    {
        auto string = list.find(key);
        if (string == list.end()) return key;
        auto value = string->second.find(language);
        if (value == string->second.end()) return key;
        return value->second;
    }
}