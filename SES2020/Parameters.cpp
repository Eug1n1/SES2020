#include "pch.h"

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		bool isIn = false,
			 isOut = false,
			 isLog = false,
			 isLex = false,
			 isSyn = false;
		PARM parm;
		wchar_t *buf;

		for (int i = 1; i < argc; i++) 
		{
			if (wcslen(argv[i]) >= PARM_MAX_SIZE)
				throw ERROR_THROW(3);

			if (buf = wcsstr(argv[i], PARM_IN))
			{
				wcscpy_s(parm.in, buf + wcslen(PARM_IN));
				isIn = true;
			}

			if (buf = wcsstr(argv[i], PARM_OUT))
			{
				wcscpy_s(parm.out, buf + wcslen(PARM_OUT));
				isOut = true;
			}

			if (buf = wcsstr(argv[i], PARM_LOG))
			{
				wcscpy_s(parm.log, buf + wcslen(PARM_LOG));
				isLog = true;
				parm.writeLog = true;
			}

			if (!wcscmp(argv[i], PARM_DEBUG))
			{
				parm.debug = true;
			}

			if (!wcscmp(argv[i], PARM_LINK))
			{
				parm.link = false;
			}

			if (!wcscmp(argv[i], PARM_LOG))
			{
				parm.writeLog = true;
			}
		}

		if (!isIn)
			throw ERROR_THROW(4);

		if (!isOut) 
		{
			wcscpy_s(parm.out, parm.in);
			wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT));
		}
		if (!isLog)
		{
			wcscpy_s(parm.log, parm.in);
			wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT));
		}
		
		return parm;
	}
};