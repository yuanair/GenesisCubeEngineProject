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

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	InfoColor();
	{
		TPtr<Lexer::Lexer> lexer(new Lexer::Lexer(TEXT("Data/test.c")));
		Json json;
		Json &json1 = json[TEXT("tokens")];
		
		int32_t level = 0;
		
		while (true)
		{
			TPtr<Token::Token> token;
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
			
			if (token->Is<Token::SemicolonToken>())
			{
				wcout << token->ToString() << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					wcout << TEXT("\t");
				}
			}
			else if (token->Is<Token::RightBraceToken>())
			{
				level--;
				wcout << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					wcout << TEXT("\t");
				}
				wcout << token->ToString() << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					wcout << TEXT("\t");
				}
			}
			else if (token->Is<Token::LeftBraceToken>())
			{
				wcout << TEXT("\n");
				for (int32_t i = 0; i < level; i++)
				{
					wcout << TEXT("\t");
				}
				wcout << token->ToString() << TEXT("\n");
				level++;
				for (int32_t i = 0; i < level; i++)
				{
					wcout << TEXT("\t");
				}
			}
			else if (token->Is<Token::StringToken>())
				wcout << TEXT("\"") << FFormatter::ToShowString(token->ToString()) << TEXT("\"");
			else wcout << TEXT(" ") << token->ToString();
			
			
		}
		wcout << endl;
		
		ErrorColor();
		for (auto &error: lexer->GetErrors())
		{
			std::wcout << std::format(
				TEXT("Lexer::Error: {}({}, {}): {}\n"), (int32_t) error.type, error.pos.line, error.pos.ch,
				error.message
			);
		}
		InfoColor();
		
		TOFStream ofs(TEXT("Lexer.json"));
		if (ofs.is_open())
		{
			ofs << json.ToString();
			ofs.close();
		}
		
	}
	
	{
		TPtr<Lexer::Lexer> lexer(new Lexer::Lexer(TEXT("Data/test.c")));
		TPtr<Parser::Parser> parser(new Parser::Parser(lexer));

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
