//
// Copyright (c) 2016 Lo�c HAMOT
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma warning(push, 0)
#pragma warning(disable: 4265)
#include <clang/ASTMatchers/ASTMatchFinder.h>
#pragma warning(pop)

#include "../DPrinter.h"
#include "../MatchContainer.h"
#include "../CustomPrinters.h"

using namespace clang;
using namespace clang::ast_matchers;

void c_stdlib_port(MatchContainer& mc, MatchFinder& finder)
{
	// <stdio>
	char const* stdioFuncs[] =
	{
		"remove", "rename", "tmpfile", "tmpnam",
		"fclose", "fflush", "fopen", "freopen", "setbuf", "setvbuf",
		"fprintf", "fscanf", "printf", "scanf", "snprintf", "sprintf",
		"sscanf", "vfprintf", "vfscanf", "vprintf", "vscanf", "vsnprintf", "vsprintf", "vsscanf",
		"fgetc", "fgets", "fputc", "fputs", "getc", "getchar", "gets", "putc", "putchar", "puts", "ungetc",
		"fread", "fwrite",
		"fgetpos", "fseek", "fsetpos", "ftell", "rewind",
		"clearerr", "feof", "ferror", "perror",
	};
	for(char const* func : stdioFuncs)
		mc.cFuncPrinter("stdio", func);

	// <string>
	char const* stringFuncs[] =
	{
		"memcpy", "memmove", "strcpy", "strncpy", "strcat", "strncat",
		"memcmp", "strcmp", "strcoll", "strncmp", "strxfrm",
		"memchr", "strchr", "strcspn", "strpbrk", "strrchr", "strspn", "strstr", "strtok",
		"memset", "strerror", "strlen"
	};
	for(char const* func : stringFuncs)
		mc.cFuncPrinter("string", func);

	// <stdlib>
	char const* stdlibFuncs[] =
	{
		"abort", "abs", "alloca", "atexit", "atof", "atoi", "atol", "atoll", "bsearch", "calloc", 
		"div", "div_t", "exit", "free", "getenv", "labs", "ldiv", "ldiv_t", "llabs", "lldiv", 
		"lldiv_t", "malloc", "mblen", "mbstowcs", "mbtowc", "qsort", "rand", "realloc", "srand", 
		"strtod", "strtof", "strtol", "strtold", "strtoll", "strtoul", "strtoull", "system", 
		"wcstombs", "wctomb" 
	};
	for (char const* func : stdlibFuncs)
		mc.cFuncPrinter("stdlib", func);

	// <cmath>
	char const* mathFuncs[] =
	{
		"cos", "sin", "tan", "acos", "asin", "atan", "atan2",
		"cosh", "sinh", "tanh", "acosh", "asinh", "atanh",
		"exp", "frexp", "ldexp", "log", "log10", "modf", "exp2", "expm1", "ilogb", "log1p", "log2", "logb", "scalbn", "scalbln",
		"pow", "sqrt", "cbrt", "hypot",
		"erf", "erfc", "tgamma", "lgamma",
		"ceil", "floor", "fmod", "trunc", "round", "lround", "llround", "rint", "lrint", "llrint", "nearbyint", "remainder", "remquo",
		"copysign", "nan", "nextafter", "nexttoward",
		"fdim", "fmax", "fmin",
		"fabs", "abs", "fma",
		"fpclassify", "isfinite", "isinf", "isnan", "isnormal", "signbit",
		"isgreater", "isgreaterequal", "isless", "islessequal", "islessgreater", "isunordered",
	};
	for(char const* func : mathFuncs)
		mc.cFuncPrinter("math", func);

	// <ctime>
	mc.cFuncPrinter("time", "time");
	mc.cFuncPrinter("time", "clock");
	mc.rewriteType(finder, "clock_t", "core.stdc.time.clock_t", "core.stdc.time");
	mc.rewriteType(finder, "std::clock_t", "core.stdc.time.clock_t", "core.stdc.time");

	//<assert>
	mc.globalFuncPrinter("^(::std)?::_wassert$", [](DPrinter&, Stmt*) {});
	mc.globalFuncPrinter("^(::)?__assert_fail$", [](DPrinter&, Stmt*) {});
}

REG_CUSTOM_PRINTER(c_stdlib_port);
