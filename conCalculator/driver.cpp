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
		cout << "�ļ��޷���" << endl;
		return 1;
	}

	// �ȵǼ�Ԥ����ķ���.
	Symbol_table::table["pi"] = 3.1415926535897932385;
	Symbol_table::table["e"] = 2.7182818284590452354;

	while (lexer::END != lexer::get_token())
		// ����δ�����ͼ���������һ�����ʽ
	{
		if (lexer::curr_tok == lexer::END) break;
		if (lexer::curr_tok == lexer::PRINT) continue;
		if (lexer::curr_tok == lexer::ERR_CHAR)
		{   //�Լ�����Ĳ���������������ʽ��ʣ�ಿ��
			lexer::skip();//�ú����ɲο��̲�P192 Driver::skip()ʵ�֡�
			continue;
		}

		double  value = parser::expr(false);//�˴��Ա��ʽ������
		error::line++;
		switch (lexer::curr_tok)
		{
		case lexer::PRINT:
		case lexer::END:
			cout << "Result is " << value << endl;//
			continue;

		case lexer::ERR_CHAR: //�Լ�����Ĳ���������������ʽ��ʣ�ಿ��
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
