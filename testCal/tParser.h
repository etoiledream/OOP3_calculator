#pragma once
#include "stdafx.h"
#include<iostream>
#include<map>
namespace Par {
	enum Token_value {
		NAME, NUMBER, END,
		PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
		PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
	};
	//模块成员声明！！！
	extern Token_value curr_tok;
	extern double number_value;
	extern std::string string_value;
	extern std::map<std::string, double> table;
	Token_value get_token();
	
	double prim(bool get);
	double term(bool get);
	double expr(bool get);
}
