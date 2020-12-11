#pragma once
#include "pch.h"

#define HEAD	".586\n" \
				".model flat, stdcall\n"\
				"includelib libucrt.lib\n"\
				"includelib libucrt.lib\n"\
				"includelib kernel32.lib\n"\
				"ExitProcess PROTO :DWORD\n"\
				".stack 4096\n\n"

using std::string;

namespace Generator
{
	void Generate(LT::LexTable lexTable, IT::IdTable idTable, Parm::PARM parm);
	string GetData(IT::IdTable idTable);
	string GetCode(LT::LexTable lexTable, IT::IdTable idTable);
}