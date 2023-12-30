//
// Created by admin on 2023/12/19.
//

#pragma once

#include "Header.h"

namespace GenesisCube
{
	
	// char
	
	typedef wchar_t WChar;
	
	typedef char Char;

#ifdef UNICODE
	typedef WChar TChar;
	typedef Char NTChar;
#else
	typedef Char TChar;
	typedef WChar NTChar;
#endif
	
	// string
	
	typedef std::basic_string<WChar> WString;
	
	typedef std::basic_string<Char> String;
	
	typedef std::basic_string<TChar> TString;
	
	typedef std::basic_string<NTChar> NTString;
	
	// in stream
	
	typedef std::basic_istream<WChar> WIStream;
	
	typedef std::basic_istream<Char> IStream;
	
	typedef std::basic_istream<TChar> TIStream;
	
	typedef std::basic_istream<NTChar> NTIStream;
	
	// out stream
	
	typedef std::basic_ostream<WChar> WOStream;
	
	typedef std::basic_ostream<Char> OStream;
	
	typedef std::basic_ostream<TChar> TOStream;
	
	typedef std::basic_ostream<NTChar> NTOStream;
	
	// in out stream
	
	typedef std::basic_iostream<WChar> WIOStream;
	
	typedef std::basic_iostream<Char> IOStream;
	
	typedef std::basic_iostream<TChar> TIOStream;
	
	typedef std::basic_iostream<NTChar> NTIOStream;
	
	// string stream
	
	typedef std::basic_stringstream<WChar> WStringStream;
	
	typedef std::basic_stringstream<Char> StringStream;
	
	typedef std::basic_stringstream<TChar> TStringStream;
	
	typedef std::basic_stringstream<NTChar> NTStringStream;
	
	// input string stream
	
	typedef std::basic_istringstream<WChar> WIStringStream;
	
	typedef std::basic_istringstream<Char> IStringStream;
	
	typedef std::basic_istringstream<TChar> TIStringStream;
	
	typedef std::basic_istringstream<NTChar> NTIStringStream;
	
	// output string stream
	
	typedef std::basic_ostringstream<WChar> WOStringStream;
	
	typedef std::basic_ostringstream<Char> OStringStream;
	
	typedef std::basic_ostringstream<TChar> TOStringStream;
	
	typedef std::basic_ostringstream<NTChar> NTOStringStream;
	
	// file stream
	
	typedef std::basic_fstream<WChar> WFStream;
	
	typedef std::basic_fstream<Char> FStream;
	
	typedef std::basic_fstream<TChar> TFStream;
	
	typedef std::basic_fstream<NTChar> NTFStream;
	
	// input file stream
	
	typedef std::basic_ifstream<WChar> WIFStream;
	
	typedef std::basic_ifstream<Char> IFStream;
	
	typedef std::basic_ifstream<TChar> TIFStream;
	
	typedef std::basic_ifstream<NTChar> NTIFStream;
	
	// output file stream
	
	typedef std::basic_ofstream<WChar> WOFStream;
	
	typedef std::basic_ofstream<Char> OFStream;
	
	typedef std::basic_ofstream<TChar> TOFStream;
	
	typedef std::basic_ofstream<NTChar> NTOFStream;
	
}


