#ifndef _LEXER_H
#define _LEXER_H
#include "stdafx.h"
#include<vector>
using namespace std;
namespace lexer {
	enum token_value {
		NAME, NUMBER, END,
		PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
		PRINT = ';', ASSIGN = '=', LP = '(', RP = ')',
		ENDCHAR, ERR_CHAR, ERR_TOKEN
	};//枚举类型定义

							// 下面是模块内的全局变量的 “非定义声明”
	extern token_value curr_tok; // 当前读到的单词之种类 
	extern double number_value;
	extern std::istream *input;  // 定义指向标准输入设备或文件的指针
	extern std::vector<std::string> fileNames;
	// 下面是模块内的函数 “非定义”声明 
	token_value get_token();
	int parseCommandLine(int argc, char* argv[]);
	int switch_input();
	void skip();
}
#endif
