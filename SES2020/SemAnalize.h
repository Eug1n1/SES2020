#pragma once
#include "pch.h"

namespace SemAnalize
{
	void SemAnalize(LT::LexTable lextable, IT::IdTable idtable);
	void CheckReturn(LT::LexTable lexT, IT::IdTable idT);
	void FuncParamsCheck(LT::LexTable lexT, IT::IdTable idT);
	void FuncsTypeCheck(LT::LexTable lexT, IT::IdTable idT);
	void TypesCheck(LT::LexTable lexT, IT::IdTable idT);
	void TwirlParamsCheck(LT::LexTable lexT, IT::IdTable idT);
	void TwirlCheck(LT::LexTable lexT, IT::IdTable idT);
}




