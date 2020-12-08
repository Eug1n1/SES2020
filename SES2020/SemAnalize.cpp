#include "pch.h"

void SemAnalize::SemAnalize(LT::LexTable lextable, IT::IdTable idtable)
{
	LT::LexTable lexT = lextable;
	IT::IdTable idT = idtable;
	CheckReturn(lexT, idT);
	FuncParamsCheck(lexT, idT);
	FuncsTypeCheck(lexT, idT);
	TypesCheck(lexT, idT);
	TwirlParamsCheck(lexT, idT);
	TwirlCheck(lexT, idT);
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
	char buf[ID_MAXSIZE];  // буфер для имени функции
	int sparams = 0;  // количество аргументов
	int fparms = 0;  // количество параметров в функции
	int str = 0;   // номер строки вызова функции
	for (int i = 0; i < lexT.size; i++)
	{
		if (lexT.table[i].lexema == LEX_ASSIGN)
		{
			str = lexT.table[i].sn;
			while (lexT.table[i].lexema != LEX_SEMICOLON)
			{
				i++;
				if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					strcpy_s(buf, idT.table[lexT.table[i].idxTI].id);
					for (int j = 0; j < i; j++)
					{
						if (lexT.table[j].lexema == LEX_ID && lexT.table[j - 1].lexema == LEX_FUNCTION && !strcmp(buf, idT.table[lexT.table[j].idxTI].id))
						{
							j++;
							for (j; lexT.table[j].lexema != ')'; j++)
							{
								if (lexT.table[j].lexema == LEX_ID)
								{
									fparms++;
									i += 2;
									if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::INT)
									{
										if (lexT.table[i].lexema == LEX_LITERAL || lexT.table[i].lexema == LEX_ID)
											if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
												sparams++;
									}
									if (idT.table[lexT.table[j].idxTI].iddatatype == IT::IDDATATYPE::STR)
									{
										if (lexT.table[i].lexema == LEX_LITERAL || lexT.table[i].lexema == LEX_ID)
											if (idT.table[lexT.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
												sparams++;
									}
								}
							}
							if (fparms != sparams)
								throw ERROR_THROW_IN(401, str, -1);
						}
					}
				}
			}
		}
	}
}

void SemAnalize::FuncsTypeCheck(LT::LexTable lexT, IT::IdTable idT)
{
	int datatype;
	for (int i = 0; i < lexT.size; i++)
	{
		int str = 0;
		if (lexT.table[i].lexema == LEX_ASSIGN)
		{
			str = lexT.table[i].sn;
			datatype = idT.table[lexT.table[i - 1].idxTI].iddatatype;
			while (lexT.table[i].lexema != LEX_SEMICOLON)
			{
				if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F && idT.table[lexT.table[i].idxTI].iddatatype != datatype)
				{
					// если мы нашли идентификатор функции которая возвращает значение не того типа
					throw ERROR_THROW_IN(402, str, -1);
				}
				if ((lexT.table[i].lexema == 's' || lexT.table[i].lexema == 'k') && datatype == IT::IDDATATYPE::STR)
				{
					// если в строку присваивается возвращаемое значение мат. функции
					throw ERROR_THROW_IN(402, str, -1);
				}
				i++;
			}
		}
	}
}

void SemAnalize::TypesCheck(LT::LexTable lexT, IT::IdTable idT)
{
	int str = 0;
	int datatype = 0;
	for (int i = 0; i < lexT.size; i++)
	{
		if (lexT.table[i].lexema == LEX_ASSIGN)
		{
			str = lexT.table[i].sn;
			datatype = idT.table[lexT.table[i - 1].idxTI].iddatatype;
			while (lexT.table[i].lexema != LEX_SEMICOLON)
			{
				if (lexT.table[i].lexema == 's' || lexT.table[i].lexema == 'q')
					i += 3;

				// пролистываем функции
				if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].idtype == IT::IDTYPE::F)
					while (lexT.table[i].lexema != LEX_RIGHTHESIS)
						i++;

				if (lexT.table[i].lexema == LEX_ID && idT.table[lexT.table[i].idxTI].iddatatype != datatype)
				{
					ERROR_THROW_IN(403, str, -1);
				}
				i++;
			}
		}
	}
}

//проверка на тип аргументов
void SemAnalize::TwirlParamsCheck(LT::LexTable lexT, IT::IdTable idT)
{
	for (int i = 0; i < lexT.size; i++)
	{
		if (lexT.table[i].lexema == LEX_TWIRL)
		{
			i++;
			while (lexT.table[i].lexema != LEX_SEMICOLON)
			{
				if ((lexT.table[i].lexema == LEX_ID || lexT.table[i].lexema == LEX_LITERAL) && idT.table[lexT.table[i].idxTI].iddatatype != IT::IDDATATYPE::INT)
					throw ERROR_THROW_IN(404, lexT.table[i].sn, -1);
				i++;
			}
		}
	}
}

//проверка на количество переменных в цикле и на наличие знака
void SemAnalize::TwirlCheck(LT::LexTable lexT, IT::IdTable idT)
{
	int count = 0;

	for (int i = 0; i < lexT.size; i++)
	{
		if (lexT.table[i].lexema == LEX_TWIRL)
		{
			i += 2;
			while (lexT.table[i].lexema != LEX_RIGHTHESIS)
			{
				if (lexT.table[i].lexema == LEX_ID || lexT.table[i].lexema == LEX_LITERAL || lexT.table[i].lexema == LEX_EQU)
				{
					if (lexT.table[i].lexema == LEX_ID || lexT.table[i].lexema == LEX_LITERAL)
						count++;
				}
				else
				{
					throw ERROR_THROW_IN(405, lexT.table[i].sn, -1);
				}
				i++;
			}
			if (lexT.table[i - 2].lexema != LEX_EQU || count != 2)
				throw ERROR_THROW_IN(405, lexT.table[i - 2].sn, -1);

			count = 0;
		}
	}
}
