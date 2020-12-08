#include "pch.h"

void SemAnalize::SemAnalize(LT::LexTable lextable, IT::IdTable idtable)
{
	LT::LexTable lexT = lextable;
	IT::IdTable idT = idtable;
	CheckReturn(lexT, idT);
	FuncParamsCheck(lexT, idT);
}

void SemAnalize::CheckReturn(LT::LexTable lexT, IT::IdTable idT)
{
	for (int i = 0; i < lexT.size; i++)
	{
		if (lexT.table[i].lexema == LEX_RETURN)
		{
			if (lexT.table[i + 1].lexema == LEX_ID)
			{
				if (idT.table[lexT.table[i + 1].idxTI].idtype == IT::IDTYPE::F)
					throw ERROR_THROW_IN(400, lexT.table[i].sn, -1);
			}
		}
	}
}

void SemAnalize::FuncParamsCheck(LT::LexTable lexT, IT::IdTable idT)
{
	char buf[ID_MAXSIZE];
	int par = 0;
	int procpar = 0;
	int str = 0;
	for (int i = 0; i < lexT.size; i++)
	{
		if (lexT.table[i].lexema == '=')
		{
			str = lexT.table[i].sn;
			while (lexT.table[i].lexema != ';')
			{
				i++;
				if (lexT.table[i].lexema == LEX_ID)
				{
					if (idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
					{
						strcpy_s(buf, idT.table[lexT.table[i].idxTI].id);
						for (int j = 0; j < i; j++)
						{
							if (lexT.table[j].lexema == LEX_ID && lexT.table[j - 1].lexema == LEX_FUNCTION)
							{
								if (!strcmp(buf, idT.table[lexT.table[j].idxTI].id))
								{
									j++;
									for (j; lexT.table[j].lexema != ')'; j++)
									{
										if (lexT.table[j].lexema == LEX_ID)
										{
											procpar++;
											i += 2;
											if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::INT)
											{
												if (lexT.table[i].lexema == LEX_LITERAL || lexT.table[i].lexema == LEX_ID)
													if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
														par++;
											}
											if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::STR)
											{
												if (lexT.table[i].lexema == LEX_LITERAL || lexT.table[i].lexema == LEX_ID)
													if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
														par++;
											}
										}
									}
									if (procpar != par)
										throw ERROR_THROW_IN(401, str, -1);
								}
							}
						}
					}
				}
			}
		}
	}
}
