#include"stdafx.h"
#include<iostream>
#include<string>
#include"parser.h"
#include"lexer.h"
#include"sym.h"
#include"error.h"

using namespace parser;

std::string parser::string_value;
double parser::expr(bool get)
{
	double left = term(get);
	for (;;)
		switch (lexer::curr_tok) {
		case lexer::PLUS:
			left += term(true);
			break;
		case lexer::MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}

double parser::term(bool get)
{
	double left = prim(get);
	for(;;)
		switch (lexer::curr_tok) {
		case lexer::MUL:
			left *= prim(true);
			break;
		case lexer::DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			return error::error("divide by 0");
		default:
			return left;
		}
}
double parser::prim(bool get)
{
	if (get)
		lexer::get_token();
	switch (lexer::curr_tok) {
	case lexer::NUMBER:
	{
		double v = lexer::number_value;
		lexer::get_token();
		return v;
	}
	case lexer::NAME:
	{
		double&v = Symbol_table::table[string_value];
		if (lexer::get_token() == lexer::ASSIGN)
			v = expr(true);
		return v;
	}
	case lexer::MINUS:
		return -prim(true);
	case lexer::LP:
	{
		double e = expr(true);
		if (lexer::curr_tok != lexer::RP)
			return error::error(")expected");
		lexer::get_token();
		return e;
	}
	default:
		error::error("primary expected");
		//cout << "Line " << error::line << " is error" << endl;
		while (lexer::curr_tok != lexer::PRINT)
			lexer::get_token();
		return 1;
	}
}
