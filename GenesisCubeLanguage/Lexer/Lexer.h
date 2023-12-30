#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "../Token/Token.h"

namespace GCL
{
	namespace Lexer
	{
		// 词法分析器
		class Lexer
		{
		public:

			Lexer();
			~Lexer() = default;

			// file - 文件
			Lexer(const std::string& file);

		public:

			// 下一个符号
			Token::Token NextToken();

			// 获取位置
			Token::TokenPos GetTokenPos() const;

		private:

			void SkipWhiteSpace();

			void ReadChar();

			void UnreadChar();

			Token::Token NewToken(Token::Token::Type type, const std::string& _literal) const;

			std::string ReadNumber();

		private:

			std::string input;

			char ch;

			size_t pos;

			size_t nextPos;

			Token::TokenPos tokenPos;

		};

	}
}
