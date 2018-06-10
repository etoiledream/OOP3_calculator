#include "stdafx.h"
#include<iostream>
#include<string>
#include"tError.h"
using namespace Err;
int Err::no_of_errors = 0;
double Err::error(const std::string &s)
{
	++no_of_errors;
	std::cerr << "error: " << s << '\n';//没有与这些操作符匹配的<<运算符解决：<string>
	return 0;
}