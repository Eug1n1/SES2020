#include "pch.h"

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

		for (int i = 0; i < lextable.size; i++)
		{
			cout << lextable.table[i].lexema;
		}
		cout << endl;

		//MFST_TRACE_START
		//	MFST::Mfst mfst(lextable, GRB::getGreibach());
		//mfst.start();

		//mfst.saveDeducation();		// сохранить, вывести правила вывода

		//mfst.printRules();			// отладка: вывести правила вывода

		StartPolish(lextable, idtable);

		for (int i = 0; i < lextable.size; i++)
		{
			cout << lextable.table[i].lexema;
		}
		cout << endl;

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
