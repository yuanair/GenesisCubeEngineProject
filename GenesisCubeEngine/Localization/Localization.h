//
// Created by admin on 2023/12/21.
//

#pragma once

#include "../Core/GenesisCubeEngine.h"
#include "../Core/Core.h"

namespace GenesisCubeEngine
{
    
    
    typedef std::map<const class GLanguage *, TString> GLanguageString;
    
    typedef std::map<TString, GLanguageString> GStringList;
    
    ///
    /// 语言
    ///
    class GLanguage
    {
    public:
        
        static TString Find(const GStringList &list, const TString &key, const GLanguage *language);
    
    public:
        
        ///
        /// zh_cn, en_us, ...
        ///
        const TString name;
        
        ///
        /// 简体中文, English, ...
        ///
        const TString displayName;
        
    };
    
}