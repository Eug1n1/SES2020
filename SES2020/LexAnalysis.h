#pragma once
#include "pch.h"
#define LEX_ERROR_SERIES 200

struct flagForTypeOfVar
{
	int posInLT = -1;
	enum { DEF = 0, INT = 1, STR = 2 }type = DEF;
};
void divisionIntoTokens(In::IN& in, LT::LexTable& lextable, IT::IdTable& idtable); 
bool tokenAnalyse(char* token, int strNumber, LT::LexTable& lextable, IT::IdTable& idTable, int& lit);
bool a_func_var(char* token, int strNumber, LT::LexTable& lextable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeofVar);
void addLibFunc(LT::LexTable& lexTable, IT::IdTable& idTable, char* token, char lexema, int strNumber);
void printLexT(LT::LexTable lextable);
int isFunc(IT::IdTable idtable, char* id);