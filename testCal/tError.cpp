#include "stdafx.h"
#include<iostream>
#include<string>
#include"tError.h"
using namespace Err;
int Err::no_of_errors = 0;
double Err::error(const std::string &s)
{
	++no_of_errors;
	std::cerr << "error: " << s << '\n';//û������Щ������ƥ���<<����������<string>
	return 0;
}