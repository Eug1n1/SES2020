﻿#include "pch.h"

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::Getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		

		In::IN in = In::Getin(parm.in);
		Log::WriteIn(log, in);

		LT::LexTable& lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable& idtable = IT::Create(TI_MAXSIZE);
		divisionIntoTokens(in, lextable, idtable);

		LT::PrintLexTable(lextable, parm.in);
		IT::PrintIdTable(idtable, parm.in, lextable);



		LT::Delete(lextable);
		IT::Delete(idtable);
		Log::Close(log);
	}
	catch (Error::ERROR error) 
	{
		Log::WriteError(log, error);
		std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line;
	}

}