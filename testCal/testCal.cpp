// testCal.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>  
#include <string>  
#include <map>  
#include <cctype>  
#include <sstream>  
#include"tError.h"
#include"tParser.h"
//using namespace Par;
//using namespace Err;

std::istream *input;
int main(int argc, char *argv[])
{
	switch (argc) {
	case 1:
		input = &std::cin;
		break;
	case 2:
		input = new std::istringstream(argv[1]);
		break;
	default:
		Err::error("too many arguments");
		return 1;
	}

	Par::table["pi"] = 3.1415926535897932385;
	Par::table["e"] = 2.7182818284590452354;

	while (*input) {
		Par::get_token();
		if (Par::curr_tok == Par::END)
			break;
		if (Par::curr_tok == Par::PRINT)
			continue;
		std::cout << Par::expr(false) << std::endl;
	}

	if (input != &std::cin)
		delete input;

	return Err::no_of_errors;//*
}
