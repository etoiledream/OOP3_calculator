#ifndef _ERR_H
#define _ERR_H
#include "stdafx.h"

namespace error {
	extern int no_of_errors;
	extern int line;
	double error(const std::string&s);
}
#endif