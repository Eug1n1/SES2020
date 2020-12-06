#include "pch.h"

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::Getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::Close(log);
	}
	catch (Error::ERROR error) 
	{
		Log::WriteError(log, error);
		std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line;
	}

}
