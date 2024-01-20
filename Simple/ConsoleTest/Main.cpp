//
// Created by admin on 2023/12/21.
//

#include <iostream>
#include <GenesisCubeLanguage/Parser/Parser.h>
#include <GenesisCubeLanguage/Lexer/Lexer.h>
#include <GenesisCubeBase/Json/Json.h>
#include <GenesisCubeLanguage/Token/Tokens.h>
#include <GenesisCubeBase/Core/FFormatter.h>

using namespace std;
using namespace GenesisCube;
using namespace GenesisCube;
using namespace JSON;
using Microsoft::WRL::ComPtr;

void InfoColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x07);
}

void ErrorColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x0C);
}

void OperatorColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x0B);
}

void NumberColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x06);
}

void StringColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x02);
}

void BracketColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0x08);
}

#ifdef UNICODE
#define TOut std::wcout
#else
#define TOut std::cout
#endif

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	system("chcp 65001");
	InfoColor();
	{
		TUniquePtr<Lexer::Lexer> lexer(new Lexer::Lexer(TEXT("Data/test.c")));
		Json json;
		Json &json1 = json[TEXT("tokens")];
		
		int32_t level = 0;
		
		while (true)
		{
			TSharedPtr<Token::Token> token;
			lexer->NextToken(token);
			if (!token) throw ENullptrException();
			json1.Push(token->ToJson());
			if (token->IsEOF())
			{
				break;
			}
			
			switch (token->GetType())
			{
				case Token::Token::SemicolonType:
					OperatorColor();
					break;
				case Token::Token::NumberType:
					NumberColor();
					break;
				case Token::Token::StringType:
					StringColor();
					break;
				case Token::Token::OperatorType:
					OperatorColor();
					break;
				case Token::Token::BracketType:
					BracketColor();
					break;
				case Token::Token::IdentifierType:
					InfoColor();
					break;
				case Token::Token::IllegalType:
				case Token::Token::ErrorType:
				default:
					ErrorColor();
					break;
			}
			
			if (Is<Token::SemicolonToken>(token))
			{
				TOut << token->ToString() << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					TOut << TEXT("\t");
				}
			}
			else if (Is<Token::RightBraceToken>(token))
			{
				level--;
				TOut << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					TOut << TEXT("\t");
				}
				TOut << token->ToString() << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					TOut << TEXT("\t");
				}
			}
			else if (Is<Token::LeftBraceToken>(token))
			{
				TOut << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					TOut << TEXT("\t");
				}
				TOut << token->ToString() << TEXT("\n");
				level++;
				for (int32_t i = 0; i < level; i++)
				{
					TOut << TEXT("\t");
				}
			}
			else if (Is<Token::StringToken>(token))
				TOut << TEXT(" \"") << FFormatter::ToShowString(token->ToString()) << TEXT("\"");
			else if (Is<Token::CharToken>(token))
				TOut << TEXT(" '") << FFormatter::ToShowString(token->ToString()) << TEXT("'");
			else
				TOut << TEXT(" ") << token->ToString();
			
			
		}
		TOut << endl;
		
		TOFStream ofs(TEXT("../../../../Lexer.json "));
		if (ofs.is_open())
		{
			ofs << json.ToString();
			ofs.close();
		}
		
	}
	
	{
		TUniquePtr<Lexer::Lexer> lexer = MakeUnique<Lexer::Lexer>(TEXT("Data/test.c"));
		TUniquePtr<Parser::Parser> parser(new Parser::Parser(lexer));
		
		
		TSharedPtr<AST::Function> function;
		parser->ParseFunction(function);
		
		ErrorColor();
		for (auto &error: parser->lexer->GetErrors())
		{
			TOut << std::format(
				TEXT("Lexer::Error: {}({}, {}): {}\n"), (int32_t) error.type, error.pos.line, error.pos.ch,
				error.message
			);
		}
		for (auto &error: parser->GetErrors())
		{
			TOut << std::format(
				TEXT("Parser::Error: {}({}, {}): {}\n"), (int32_t) error.type, error.pos.line, error.pos.ch,
				error.message
			);
		}
		InfoColor();
		
		if (function)
		{
			TOFStream ofs(TEXT("../../../../Parser.json"));
			ofs << function->ToJson().ToString();
			ofs.close();
		}

//		auto program = parser->ParseProgram();
//
//		auto errors = parser->GetErrors();
//		for (auto &error: errors)
//		{
//			std::wcout << TEXT("Error: ") << error.type << TEXT("(") << error.pos.line << TEXT(": ") << error.pos.ch
//					   << TEXT("): ")
//					   << error.message << std::endl;
//		}
//
//		TString jsonBuffer = program->ToJsonString();
//		TOFStream ofs(TEXT("Parser.json"));
//		if (ofs.is_open())
//		{
//			ofs << jsonBuffer;
//			ofs.close();
//		}
	}
	
	
	InfoColor();
	getchar();
	return 0;
}
