#pragma once

#include "pch.h"

#define PARM_MAX_SIZE 300			
#define PARM_IN  L"-in:"					// ���� ��� ����� ��������� ����
#define PARM_OUT L"-out:"					// ���� ��� ����� ���������� ����	
#define PARM_LOG L"-log:"					// ���� ��� ����� ������� 
#define PARM_LEX  L"-lex:"
#define PARM_SYN  L"-syn:"
#define PARM_OUT_DEFAULT_EXT L".asm"		// ���������� ����� ���������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L".log"		// ���������� ����� ��������� �� ���������
#define PARM_LEX_DEFAULT_EXT  L".lex"
#define PARM_SYN_DEFAULT_EXT  L".syn"
#define PARM_ID_DEFAULT_EXT L".id"
#define PARM_DEBUG L"-d"
#define PARM_LINK L"-c"
#define PARM_LOG L"-lex"


namespace Parm
{
	struct PARM
	{
		wchar_t  in[PARM_MAX_SIZE];			// -in:     ��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];			// -out:    ��� ����� ���������� ����
		wchar_t log[PARM_MAX_SIZE];			// -log:    ��� ����� ���������
		bool writeLog = false;
		bool debug = false;
		bool link = true;
	};
	PARM getparm(int argc, _TCHAR* argv[]);		//������������ struct PARM �� ������ ������� ���������� ������� main
}