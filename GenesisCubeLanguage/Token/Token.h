#pragma once

#include "../../GenesisCubeBase/Core/FCore.h"

#include "../../GenesisCubeBase/Json/Json.h"

namespace GenesisCube::Token
{
	// 位置
	class TokenPos
	{
	public:
		
		TokenPos(int64_t ch = 0, int64_t line = 0) : ch(ch), line(line) {}
		
		~TokenPos() = default;
	
	public:
		
		// 第几个字符
		int64_t ch;
		
		// 第几行
		int64_t line;
		
	};
	
	/// 符号类
	class Token : public GObject
	{
	public:
		
		/// 优先级
		enum Precedence : int32_t
		{
			NullPrecedence = 0,             // 无优先级
			Lowest,             // 最低优先级
			Sum,                    // +与-优先级
			Product,                // *与/优先级
		};
		
		/// 类别
		enum Type : int32_t
		{
			ErrorType = 0,             // 错误类型
			IllegalType,                // 非法符号
			SemicolonType,                // 分号
			NumberType,                // 数字
			StringType,                    // 字符串
			OperatorType,                // 运算符
			BracketType,                // 括号
			IdentifierType,                // 标识符
		};
	
	public:
		
		Token();
		
		~Token() override = default;
		
		///
		/// \param pos 位置
		Token(TokenPos pos);
	
	public:
		
		Token &operator=(const Token &other) = delete;
	
	public:
		
		///
		/// \return 符号名
		[[nodiscard]]
		inline virtual TString GetName() const noexcept = 0;
		
		///
		/// \return 优先级
		[[nodiscard]]
		inline virtual Precedence GetPrecedence() const noexcept { return NullPrecedence; }
		
		///
		/// \return 类别
		[[nodiscard]]
		inline virtual Type GetType() const noexcept = 0;
	
	public:
		
		/// 获取位置
		[[nodiscard]] TokenPos GetPos() const;
		
		/// 以json表示
		[[nodiscard]] JSON::Json ToJson() const;
		
		/// 类型是否为EOF
		[[nodiscard]] bool IsEOF() const;
		
		template<class T>
		[[nodiscard]] bool Is() const { return typeid(*this) == typeid(T); }
	
	public:
		
		[[nodiscard]]
		inline Token *Clone() const noexcept override = 0;
		
		/// 以字符串表示
		[[nodiscard]] TString ToString() const noexcept override = 0;
	
	public:
		
		TokenPos pos;
		
	};
	
}

