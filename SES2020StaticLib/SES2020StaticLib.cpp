// SES2020StaticLib.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "SES2020StaticLib.h"
#include <iostream>

// TODO: Это пример библиотечной функции.
int pow(int a, int b)
{
	return a ^ b;
}

int octat(int a, int b) 
{
	return a % b;
}

void outstr(char* s)
{
	if (s != nullptr)
		std::cout << s << std::endl;
	else
		std::cout << "Empty line!";
}
void outint(int i)
{
	std::cout << i << std::endl;
}
