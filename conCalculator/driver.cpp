#include "stdafx.h"
#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "error.h"
#include "sym.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (lexer::parseCommandLine(argc, argv) != 0)
	{
		cout << "文件无法打开" << endl;
		return 1;
	}

	// 先登记预定义的符号.
	Symbol_table::table["pi"] = 3.1415926535897932385;
	Symbol_table::table["e"] = 2.7182818284590452354;

	while (lexer::END != lexer::get_token())
		// 输入未结束就继续分析下一个表达式
	{
		if (lexer::curr_tok == lexer::END) break;
		if (lexer::curr_tok == lexer::PRINT) continue;
		if (lexer::curr_tok == lexer::ERR_CHAR)
		{   //自己定义的操作，丢弃错误表达式的剩余部分
			lexer::skip();//该函数可参考教材P192 Driver::skip()实现。
			continue;
		}

		double  value = parser::expr(false);//此处对表达式做计算
		error::line++;
		switch (lexer::curr_tok)
		{
		case lexer::PRINT:
		case lexer::END:
			cout << "Result is " << value << endl;//
			continue;

		case lexer::ERR_CHAR: //自己定义的操作，丢弃错误表达式的剩余部分
			lexer::skip();
			continue;
		case lexer::ERR_TOKEN:
			lexer::skip();
			continue;
		default:
			error::error( "may need expression ending");//lexer::curr_tok,
			lexer::skip();
			continue;
		}

	}

	if (lexer::input != &std::cin)
		delete lexer::input;

	return 0;
}
