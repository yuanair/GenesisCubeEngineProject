#pragma once

#include "../Token/Token.h"
#include "../AST/Node.h"

namespace GenesisCube::Lexer
{
	// 词法分析器
	class Lexer : public GObject
	{
	public:
		
		union NumberToChars
		{
			int32_t number;
			char str[4];
			wchar_t wStr[2];
			TChar tStr[4 / sizeof(TChar)];
			char32_t uchar;
		};
		
		// 词法错误
		class Error
		{
		public:
			
			// 语法错误类型枚举
			enum Type : int32_t
			{
				// 错误：非法的符号
				Error_Illegal = 0x0000,
				
				// 错误：错误数字
				Error_ErrorNumber,
				
				// 错误：错误字符常量
				Error_ErrorChar,
				
				// 警告：非法符号
				Warning_Illegal = 0x1000,
				
				// 警告：错误字符常量
				Warning_ErrorChar,
			};
		
		public:
			
			Error(Type type, TString message, Token::TokenPos pos)
				: type(type), message(std::move(message)), pos(pos) {}
			
			~Error() = default;
		
		public:
			
			Type type;
			
			TString message;
			
			Token::TokenPos pos;
			
		};
	
	public:
		
		Lexer();
		
		~Lexer() override = default;
		
		// file - 文件
		Lexer(const TString &file);
	
	public:
		
		// 下一个符号
		void NextToken(TSharedPtr<Token::Token> &token);
		
		// 获取位置
		[[nodiscard]]
		Token::TokenPos GetTokenPos() const;
		
		[[nodiscard]]
		inline std::list<Error> GetErrors() const { return this->errors; }
	
	private:
		
		void SkipWhiteSpace();
		
		void ReadChar();
		
		TChar PeekChar();
		
		void UnreadChar();
		
		template<class T, class... Args>
		TSharedPtr<T> NewToken(Args... args) const;
		
		void ReadNumber(TSharedPtr<Token::Token> &token);
		
		void ReadString(TString &token, TChar stopChar);
		
		void ReadHex(NumberToChars &number, int32_t count);
		
		void ReadIdentifier(TSharedPtr<Token::Token> &token);
		
		void NewError(Error::Type type, const TString &message);
	
	public:
		
		[[nodiscard]]
		Lexer *Clone() const noexcept override;
	
	private:
		
		TString input;
		
		TChar ch;
		
		size_t pos;
		
		size_t nextPos;
		
		Token::TokenPos tokenPos;
		
		std::list<Error> errors;
		
	};
	
	template<class T, class... Args>
	TSharedPtr<T> Lexer::NewToken(Args... args) const
	{
		auto ptr = MakeShared<T>(args...);
		ptr->pos = tokenPos;
		return ptr;
	}
	
}

