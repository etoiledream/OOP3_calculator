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
	};//ö�����Ͷ���

							// ������ģ���ڵ�ȫ�ֱ����� ���Ƕ���������
	extern token_value curr_tok; // ��ǰ�����ĵ���֮���� 
	extern double number_value;
	extern std::istream *input;  // ����ָ���׼�����豸���ļ���ָ��
	extern std::vector<std::string> fileNames;
	// ������ģ���ڵĺ��� ���Ƕ��塱���� 
	token_value get_token();
	int parseCommandLine(int argc, char* argv[]);
	int switch_input();
	void skip();
}
#endif
