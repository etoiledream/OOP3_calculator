#include"stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include"lexer.h"
#include"error.h"
#include"sym.h"
#include"parser.h"

using namespace lexer;

// 下面是模块内的全局变量之 “定义” 
token_value lexer::curr_tok=lexer::PRINT; // 当前读到的单词之种类 
double lexer::number_value; // lexer::是必须的
std::istream* lexer::input;
std::vector<std::string> lexer::fileNames;
// 下面是模块内的函数 “定义”
lexer::token_value lexer::get_token()
{
	char ch;
	do { // 这里是跳过空白字符
//		if (lexer::PRINT != curr_tok)
	//		return curr_tok = PRINT;
		if (!(input->get(ch)))
		{  // 当前文件结束了，尝试打开下一文件
			if (0 != switch_input())
				return curr_tok = END;
			else
			{
				 ch = ' ';continue;
			}
		}
	} while (ch != '\n'&& isspace(ch));

	switch (ch) {
	case '/n':
		return curr_tok = PRINT;
	case ';':
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return curr_tok = token_value(ch);
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
		std::cin.putback(ch);
		std::cin >> number_value;
		return curr_tok = NUMBER;
	default:
		if (isalpha(ch)) {
			parser::string_value = ch;
			while (std::cin.get(ch) && isalnum(ch))
				parser::string_value.push_back(ch);
			std::cin.putback(ch);
			return curr_tok = NAME;
		}
		else if (ch != '\n') {
			error::error("bad token");
			return curr_tok = ERR_CHAR;
		}
			
	}
}


int lexer::parseCommandLine(int argc, char* argv[])
{
	if (argc == 1) 
	{
		lexer::input = &std::cin; 
		return 0;
	}
	else 
	{
		for (int i = 1; i < argc; ++i) 
			fileNames.push_back(argv[i]);
		// 接着先打开第1个输入文件
		lexer::input = new std::ifstream(fileNames[0].c_str());
		//接着判断文件是否成功打开了—这个检测的方法较多，如：
		//为true时就表示成功打开了
		if (lexer::input->good())
		{
			//若成功打开则 接着可将第1个文件名剔除：
			//lexer::input = &std::cin;
			fileNames.erase(fileNames.begin());
			return 0;
		}
		else
			return 1;
			
			//最后若成功打开则返回0，否则返回非0值并报错。
	}
}

int lexer::switch_input()
{
	if (fileNames.empty())
	{
		return 1;
	}  /*没有文件了*/
	else 
	{
		delete lexer::input; //关闭上个文件，接着打开下个文件
		lexer::input = new std::ifstream(fileNames[0].c_str());
		//接着判断文件是否成功打开了—这个检测的方法较多，如：
		//为true时就表示成功打开了
		if (lexer::input->good()) {
			//若成功打开则 接着可将第1个文件名剔除：
			//lexer::input = &std::cin;
			fileNames.erase(fileNames.begin());
			return 0;
		}
		else {
			return 1;
		}
			
			//最后若成功打开则返回0，否则返回非0值并报错。
	}
}

void lexer::skip()
{
	error::no_of_errors++;
	while (*input)
	{
		char ch;
		input->get(ch);
		switch (ch)
		{
		case '\n':
		case ';':
			input->get(ch);
			return;
		}
	}
}


