#pragma once

#include "../../GenesisCubeBase/Core/FCore.h"
#include "../../GenesisCubeBase/Json/Json.h"

namespace GenesisCube::AST
{
	class Expression;
}

namespace GenesisCube::Parser
{
	class Parser;
}

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
	class Token : public GObject, public std::enable_shared_from_this<Token>
	{
	public:
		
		/// 优先级
		enum Precedence : int32_t
		{
			Lowest = 0,                // 最低优先级
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
		inline TString GetName() const noexcept override = 0;
		
		///
		/// \return 优先级
		[[nodiscard]]
		inline virtual Precedence GetPrecedence() const noexcept { return Lowest; }
		
		///
		/// \return 类别
		[[nodiscard]]
		inline virtual Type GetType() const noexcept = 0;
		
		///
		/// \return 前缀表达式
		inline virtual void
		GetPrefixExpression(TPtr<class AST::Expression> &expression, class Parser::Parser &parser) noexcept {}
		
		///
		/// \return 中缀表达式
		inline virtual void
		GetInfixExpression(TPtr<class AST::Expression> &expression, const TPtr<class AST::Expression> &left,
						   class Parser::Parser &parser) noexcept {}
	
	public:
		
		/// 获取位置
		[[nodiscard]] TokenPos GetPos() const;
		
		/// 以json表示
		virtual JSON::Json ToJson() const;
		
		/// 类型是否为EOF
		[[nodiscard]] bool IsEOF() const;
		
		template<class T, class... Args>
		inline TPtr<T> NewNode(Args... args) noexcept
		{
			TPtr<T> ptr = MakePtr<T>(args...);
			ptr->token = shared_from_this();
			return ptr;
		}
	
	public:
		
		[[nodiscard]]
		inline Token *Clone() const noexcept override = 0;
		
		/// 以字符串表示
		[[nodiscard]] TString ToString() const noexcept override = 0;
	
	public:
		
		TokenPos pos;
		
	};
	
}

