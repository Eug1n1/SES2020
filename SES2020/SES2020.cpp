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

		if (parm.writeLog)
		{
			LT::PrintLexTable(lextable, parm.in);
			IT::PrintIdTable(idtable, parm.in, lextable);
		}


		if (parm.debug)
		{
			printLexT(lextable);
			MFST_TRACE_START
		}

		MFST::Mfst mfst(lextable, GRB::getGreibach(), parm);
		mfst.start();
		mfst.saveDeducation();

		if (parm.debug)
			mfst.printRules();

		SemAnalize::SemAnalize(lextable, idtable);

		StartPolish(lextable, idtable, parm);

		Generator::Generate(lextable, idtable, parm);

		string out;

		out += string("out: ") + string(fromWide(parm.out)) + string("\n");
		std::cout << out;

		string compile = "";
		char* parmout = new char[wcslen(parm.out)];
		for (int i = 0; i < wcslen(parm.out); i++)
		{
			parmout[i] = parm.out[i];
			parmout[i + 1] = '\0';
		}

		if (parm.link)
		{
			compile += string("ml.exe ") + string(parmout) + string(" /link /subsystem:console");
			system(compile.c_str());
		}
		else
		{
			compile += string("ml.exe ") + string(parmout) + string(" /c /coff");
			system(compile.c_str());
		}

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

char* fromWide(wchar_t out[])
{
	char* parmbuf = new char[wcslen(out)];
	for (int i = 0; i < wcslen(out); i++)
		parmbuf[i] = (char)out[i];
	parmbuf[wcslen(out)] = '\0';

	return parmbuf;
}
