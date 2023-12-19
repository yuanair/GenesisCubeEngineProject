#pragma once

#include "GenesisCubeEngine.h"
#include "../Exception/Exception.h"
#include <string>

namespace GenesisCubeEngine
{
    
    /// <summary>
    /// 格式化类
    /// </summary>
    class FFormatter
    {
    public:
        
        union NumberToChars
        {
            int32_t number;
            char chars[4];
            wchar_t wchars[2];
            char32_t uchar;
        };
    
    public:
        
        FFormatter() = delete;
        
        ~FFormatter() = delete;
    
    public:
        
        static String GbkToUtf8(const String &src_str);
        
        static String Utf8ToGbk(const String &src_str);
        
        static WString StringToWString(const String &s, UINT m_encode = CP_ACP);
        
        static String WStringToString(const WString &s, UINT m_encode = CP_ACP);
        
        static TString ToShowString(const TString &str);
        
        static TString FromShowString(const TString &str);
        
        /// <summary>
        /// 格式化
        /// </summary>
        /// <typeparam name="T">第一个参数的类型</typeparam>
        /// <typeparam name="...Args">参数类型</typeparam>
        /// <param name="dest">目标</param>
        /// <param name="format">格式</param>
        /// <param name="value">第一个参数</param>
        /// <param name="...args">参数</param>
        template<class T, class... Args>
        static void Format(TString &dest, const TString &format, const T &value, const Args &... args);
    
    private:
        
        template<class T, class... Args>
        static inline void
        PrivateFormat(TString &dest, size_t index, const TString &format, const T &value, const Args &... args);
        
        static inline void PrivateFormat(TString &dest, size_t index, const TString &format);
        
        static inline void Next(TString &dest, TString &buffer, size_t &index, const TString &format);
        
    };
    
    /// <summary>
    /// 格式化。
    /// 请不要在重载此函数时抛出异常，可能导致未定义的行为。
    /// </summary>
    /// <typeparam name="T">参数类型</typeparam>
    /// <param name="dest">目标</param>
    /// <param name="format">格式</param>
    /// <param name="value">参数</param>
    template<class T>
    static inline void FormatValue(TString &dest, const TString &format, const T &value) noexcept
    {
        dest.append(ToTString(value));
    }
    
    template<>
    static inline void FormatValue(TString &dest, const TString &format, const bool &value) noexcept
    {
        dest.append(value ? TEXT("true") : TEXT("false"));
    }
    
    template<>
    static inline void FormatValue(TString &dest, const TString &format, const TCHAR &value) noexcept
    {
        dest.push_back(value);
    }
    
    template<>
    static inline void FormatValue(TString &dest, const TString &format, const NTChar &value) noexcept = delete;
    
    template<>
    static inline void FormatValue(TString &dest, const TString &format, const TString &value) noexcept
    {
        dest.append(value);
    }
    
    
    template<class T, class ...Args>
    void FFormatter::Format(TString &dest, const TString &format, const T &value, const Args &... args)
    {
        size_t index = 0;
        {
            TString nextFormat;
            Next(dest, nextFormat, index, format);
            FormatValue(dest, nextFormat, value);
        }
        
        PrivateFormat(dest, index, format, args...);
    }
    
    template<class T, class ...Args>
    inline void
    FFormatter::PrivateFormat(TString &dest, size_t index, const TString &format, const T &value, const Args &...args)
    {
        {
            TString nextFormat;
            Next(dest, nextFormat, index, format);
            FormatValue(dest, nextFormat, value);
        }
        
        PrivateFormat(dest, index, format, args...);
    }
    
    inline void FFormatter::PrivateFormat(TString &dest, size_t index, const TString &format)
    {
        if (index == format.size()) return;
        dest.append(dest, index);
    }
    
    inline void FFormatter::Next(TString &dest, TString &buffer, size_t &index, const TString &format)
    {
        while (true)
        {
            if (index >= format.size() - 1)
                throw GInvalidArgumentException(
                    TEXT(__FUNCSIG__) TEXT(":: \"{}\" not found")
                );
            
            if (format[index] == TEXT('}'))
            {
                if (format[++index] == TEXT('}'))
                {
                    dest += TEXT('}');
                    continue;
                }
                throw GInvalidArgumentException(TEXT(__FUNCSIG__) TEXT(":: '{' not found"));
            }
            
            if (format[index] == TEXT('{'))
            {
                if (format[++index] == TEXT('{'))
                {
                    dest += TEXT('{');
                    continue;
                }
                break;
            }
            dest += format[index];
            index++;
        }
        
        while (true)
        {
            if (format[index] == TEXT('}'))
            {
                index++;
                break;
            }
            if (index >= format.size()) throw GInvalidArgumentException(TEXT(__FUNCSIG__) TEXT(":: '}' not found"));
            if (format[index] == L'{')
                throw GInvalidArgumentException(
                    TEXT(__FUNCSIG__) TEXT(":: '{' shouldn't be here")
                );
            buffer += format[index];
            index++;
        }
    }
    
}