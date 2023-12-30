#pragma once
#include <format>
#include <string>
#include <map>
#include <memory>

namespace GCL::Token
{
	// 位置
	class TokenPos
	{
	public:

		TokenPos(long long ch = 0LL, long long line = 0LL) : ch(ch), line(line) {}
		~TokenPos() {}

	public:

		// 第几个字符
		long long ch;

		// 第几行
		long long line;

	};

	// 符号类
	class Token
	{
	public:

		// 符号类型枚举
		enum Type
		{
			GCL_Illegal = 0,			// illegal 非法的
			GCL_EOF,					// EOF 结束符
			GCL_Integer,				// integer 整数
			GCL_Float,					// float 浮点数
			GCL_Plus,					// + 加号
			GCL_Minus,					// - 减号
			GCL_Multiply,				// * 乘号
			GCL_Divide,					// / 除号
			GCL_Mod,					// % 求模
			GCL_LeftParen,				// ( 左括号
			GCL_RightParen,				// ) 右括号
			GCL_Semicolon,				// ; 分号
		};

	public:

		Token();
		~Token() = default;

		// type - 类型
		// _literal - 字面量
		// pos - 位置
		Token(Type type, const std::string& _literal, TokenPos pos);

	public:

		Token& operator=(const Token& other);

	public:

		// 获取类型
		Type GetType() const;

		// 获取字面量
		std::string GetLiteral() const;

		// 获取位置
		TokenPos GetPos() const;

		// 类型转换为字符串
		std::string ToTypeString() const;

		// 以json表示
		std::string ToJsonString() const;

		// 以字符串表示
		std::string ToString() const;

		// 类型是否为GCL_EOF
		bool IsEOF() const;

	private:

		static std::map<Type, std::string> names;

	private:

		Type type;

		std::string _literal;

		TokenPos pos;

	};

}

