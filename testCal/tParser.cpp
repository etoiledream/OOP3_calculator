#include "stdafx.h"
#include"tParser.h"
#include"tError.h"
//成员实现方式2 模块成员定义！！！
using namespace Par;
Par::Token_value Par::curr_tok = Par::PRINT;
double Par::number_value;
std::string Par::string_value;
std::map<std::string, double> Par::table;

Par::Token_value Par::get_token()
{
	char ch;
	do {
		if (!std::cin.get(ch))
			return curr_tok = END;
	} while (ch != '/n' && isspace(ch));

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
		return curr_tok = Token_value(ch);
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
			string_value = ch;
			while (std::cin.get(ch) && isalnum(ch))
				string_value.push_back(ch);
			std::cin.putback(ch);
			return curr_tok = NAME;
		}
		Err::error("bad token");
		return curr_tok = PRINT;
	}
}
double Par::prim(bool get)
{
	if (get)
		get_token();

	switch (curr_tok) {
	case NUMBER:
	{
		double v = number_value;
		get_token();
		return v;
	}
	case NAME:
	{
		double v = table[string_value];
		get_token();
		return v;
	}
	case MINUS:
		return -prim(true);
	case LP:
	{
		double e = expr(true);
		if (curr_tok != RP)
			return Err::error(") expected");
		get_token();
		return e;
	}
	default:
		return Err::error("primary expected");
	}
}
double Par::term(bool get)
{
	double left = prim(get);

	for (;;)
		switch (curr_tok) {
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			return Err::error("divide by 0");
		default:
			return left;
		}
}
double Par::expr(bool get)
{
	double left = term(get);

	for (;;)
		switch (curr_tok) {
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}