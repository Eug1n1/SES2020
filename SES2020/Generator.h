#pragma once
#include "pch.h"

#define HEAD	".586\n" \
				"\t.model flat, stdcall\n"\
				"\tincludelib libucrt.lib\n"\
				"\tincludelib libucrt.lib\n"\
				"\tincludelib kernel32.lib\n"\
				"\tExitProcess PROTO :DWORD\n"\
				"\n.stack 4096\n\n"

using std::string;

namespace Generator
{
	void Generate(LT::LexTable lexTable, IT::IdTable idTable, Parm::PARM parm);
	string GetData(IT::IdTable idTable);
	string GetCode(LT::LexTable lexTable, IT::IdTable idTable);
}