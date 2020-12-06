#include "pch.h"

namespace LT
{
	LexTable& Create(int size)
	{
		if (size > LT_MAXSIZE)
		{
			throw ERROR_THROW(113);
		}
		LexTable *lt = new LexTable();
		lt->maxsize = size;
		lt->size = 0;
		lt->table = new Entry[lt->maxsize];
		return *lt;
	}
	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size + 1 > lextable.maxsize)
		{
			throw ERROR_THROW(121);
		}
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}
	Entry GetEntry(LexTable& lextable, int n)
	{
		if(n < lextable.size && n >=0)
			return lextable.table[n];	
		else
			throw ERROR_THROW(124);
	}
	void Delete(LexTable& lextable)
	{
		delete [] lextable.table;
		delete &lextable;
	}

	void PrintLexTable(LexTable& lextable, wchar_t* in)
	{
		int i = 0;
		wchar_t lex[PARM_MAX_SIZE];
		for (; in[i] != '\0'; i++)
			lex[i] = in[i];
		lex[i] = '\0';
		wcscat_s(lex, PARM_LEX_DEFAULT_EXT);

		std::ofstream* lexStream = new std::ofstream;
		lexStream->open(lex);
		if(lexStream->fail())
			throw ERROR_THROW(125);
		int currentString = 0;
		(*lexStream) << std::setw(50) << std::setfill('-') << "Таблица лексем" << std::setw(50) << std::setfill('-') << '\n';
		(*lexStream) << currentString + 1 << '\t';
		for (int i = 0; i < lextable.size;)
		{
			if (currentString == lextable.table[i].sn)
				(*lexStream) << lextable.table[i++].lexema;
			else
			{
				currentString++;
				(*lexStream) << '\n' << currentString + 1 << '\t';

				if (currentString == lextable.table[i].sn)
					(*lexStream) << lextable.table[i++].lexema;
			}
		}
		(*lexStream) << "\n" << std::setw(100) << std::setfill('-') << "-";
		lexStream->close();
		delete lexStream;
	}
}