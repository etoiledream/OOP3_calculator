#include "stdafx.h"
#include<iostream>
#include<string>
#include"error.h"

using namespace error;
int error::no_of_errors =0;
int error::line=1;//用于记录行数
double error::error(const std::string&s)
{
	no_of_errors++;
	std::cerr << "error:" << s << std::endl;
	std::cerr << "line " << line << " is error" << std::endl;
	return 0;
}