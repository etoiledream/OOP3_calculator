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

// ������ģ���ڵ�ȫ�ֱ���֮ �����塱 
token_value lexer::curr_tok=lexer::PRINT; // ��ǰ�����ĵ���֮���� 
double lexer::number_value; // lexer::�Ǳ����
std::istream* lexer::input;
std::vector<std::string> lexer::fileNames;
// ������ģ���ڵĺ��� �����塱
lexer::token_value lexer::get_token()
{
	char ch;
	do { // �����������հ��ַ�
//		if (lexer::PRINT != curr_tok)
	//		return curr_tok = PRINT;
		if (!(input->get(ch)))
		{  // ��ǰ�ļ������ˣ����Դ���һ�ļ�
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
		// �����ȴ򿪵�1�������ļ�
		lexer::input = new std::ifstream(fileNames[0].c_str());
		//�����ж��ļ��Ƿ�ɹ����ˡ�������ķ����϶࣬�磺
		//Ϊtrueʱ�ͱ�ʾ�ɹ�����
		if (lexer::input->good())
		{
			//���ɹ����� ���ſɽ���1���ļ����޳���
			//lexer::input = &std::cin;
			fileNames.erase(fileNames.begin());
			return 0;
		}
		else
			return 1;
			
			//������ɹ����򷵻�0�����򷵻ط�0ֵ������
	}
}

int lexer::switch_input()
{
	if (fileNames.empty())
	{
		return 1;
	}  /*û���ļ���*/
	else 
	{
		delete lexer::input; //�ر��ϸ��ļ������Ŵ��¸��ļ�
		lexer::input = new std::ifstream(fileNames[0].c_str());
		//�����ж��ļ��Ƿ�ɹ����ˡ�������ķ����϶࣬�磺
		//Ϊtrueʱ�ͱ�ʾ�ɹ�����
		if (lexer::input->good()) {
			//���ɹ����� ���ſɽ���1���ļ����޳���
			//lexer::input = &std::cin;
			fileNames.erase(fileNames.begin());
			return 0;
		}
		else {
			return 1;
		}
			
			//������ɹ����򷵻�0�����򷵻ط�0ֵ������
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


