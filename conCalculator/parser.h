#ifndef _PARSER_H
#define _PARSER_H
#include "stdafx.h"

namespace parser {
	extern std::string string_value;
	double expr(bool);
	double expr(bool get);
	double term(bool get);
	double prim(bool get);
}
#endif
