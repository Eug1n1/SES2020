#pragma once
#include "pch.h"

namespace SemAnalize
{
	void SemAnalize(LT::LexTable lextable, IT::IdTable idtable);
	void CheckReturn(LT::LexTable lexT, IT::IdTable idT);
	void FuncParamsCheck(LT::LexTable lexT, IT::IdTable idT);
}



