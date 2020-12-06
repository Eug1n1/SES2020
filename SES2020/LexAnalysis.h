#pragma once
#include "pch.h"

struct flagForTypeOfVar
{
	int posInLT = -1;
	enum { DEF = 0, INT = 1, STR = 2 }type = DEF;
};
void divisionIntoTokens(In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable); 
bool tokenAnalyse(char* token, int strNumber, LT::LexTable& lextable, IT::IdTable& idTable);
bool a_func_var(char* token, int strNumber, LT::LexTable& lextable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeofVar);

