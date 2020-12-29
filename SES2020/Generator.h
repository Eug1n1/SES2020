#pragma once
#include "pch.h"

#define HEAD	".586\n" \
				".model flat, stdcall\n"\
				"includelib libucrt.lib\n"\
				"includelib libucrt.lib\n"\
				"includelib SES2020StaticLib.lib\n"\
				"includelib kernel32.lib\n"\
				"ExitProcess PROTO :DWORD\n"\
				".stack 4096\n\n"

#define FUNCS	"printi PROTO : DWORD\n"\
				"prints PROTO : DWORD\n"\
				"octat PROTO : DWORD, : DWORD\n"\
				"elevate PROTO : DWORD, : DWORD\n"\
				"newline PROTO\n\n"

using std::string;

namespace Generator
{
	void Generate(LT::LexTable lexTable, IT::IdTable idTable, Parm::PARM parm);
	string GetData(IT::IdTable idTable);
	string GetCode(LT::LexTable lexTable, IT::IdTable idTable);
	void ChangeIds(IT::IdTable& idTable);
}