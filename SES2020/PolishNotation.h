#pragma once
#include "pch.h"


int Prior(char ch);
bool ToPolish(std::vector<LT::Entry>& source, IT::IdTable& idtable, int& correction);
void StartPolish(LT::LexTable& lextable, IT::IdTable& idtable, Parm::PARM parm);
void printLex(LT::LexTable lex);
