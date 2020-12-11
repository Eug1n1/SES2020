// SES2020StaticLib.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include <iostream>

extern "C"
{
	int __stdcall printi(unsigned  int num)
	{
		std::cout << num << std::endl;
		return 0;
	}
	int __stdcall prints(char* str)
	{
		std::cout << str << std::endl;
		return 0;
	}

	int __stdcall octat(unsigned  int b, unsigned   int a)
	{
		int rc = b % a;
		return rc;
	}
	int __stdcall elevate(unsigned  int b, unsigned   int a)
	{
		int rc = pow(a, b);
		return rc;
	}
	int __stdcall strl(char* c)
	{
		return strlen(c);
	}
}
