#pragma once
#include "pch.h"

bool tokenAnalyse(char token[3], int strNumber, LT::LexTable& lextable, IT::IdTable& idTable, int& lit)
{
	static flagForTypeOfVar FlagForTypeofVar;
	char arr[3];

	switch (token[0])
	{
	case LEX_SEMICOLON:
	{
		LT::Add(lextable, LT::Entry(LEX_SEMICOLON, strNumber, LT_TI_NULLIDX ));
		return true;
	}
	case LEX_LEFTSQBRACKET:
		LT::Add(lextable, LT::Entry(LEX_LEFTSQBRACKET, strNumber, LT_TI_NULLIDX));
		return true;

	case LEX_RIGHTSQBRACKET:
		LT::Add(lextable, LT::Entry(LEX_RIGHTSQBRACKET, strNumber, LT_TI_NULLIDX ));
		return true;

	case LEX_COMMA:
	{
		LT::Add(lextable, LT::Entry(LEX_COMMA, strNumber, LT_TI_NULLIDX ));
		return true;
	}

	case LEX_LEFTBRACE:
	{
		LT::Add(lextable, LT::Entry(LEX_LEFTBRACE, strNumber, LT_TI_NULLIDX));
		return true;
	}

	case LEX_BRACELET:
	{
		LT::Add(lextable, LT::Entry(LEX_BRACELET, strNumber, LT_TI_NULLIDX));
		return true;
	}

	case LEX_LEFTHESIS:
	{
		LT::Add(lextable, LT::Entry(LEX_LEFTHESIS, strNumber, LT_TI_NULLIDX));
		return true;
	}

	case LEX_RIGHTHESIS:
	{
		LT::Add(lextable, LT::Entry(LEX_RIGHTHESIS, strNumber, LT_TI_NULLIDX));
		return true;
	}

	case '+':
	{
		LT::Add(lextable, LT::Entry(LEX_PLUS, strNumber, LT_TI_NULLIDX));
		return true;
	}

	case '-':
	{
		LT::Add(lextable, LT::Entry(LEX_MINUS, strNumber, LT_TI_NULLIDX));
		return true;
	}

	case '=':
	{
		if (!strcmp(token, "="))
			LT::Add(lextable, LT::Entry( LEX_ASSIGN, strNumber, LT_TI_NULLIDX));
		else
			LT::Add(lextable, LT::Entry(LEX_EQU, strNumber, LT_TI_NULLIDX, token));

		return true;
	}

	case '<':
	case '>':
	{
		LT::Add(lextable, LT::Entry(LEX_EQU, strNumber, LT_TI_NULLIDX, token));
		return true;
	}

	case '!':
	{
		LT::Add(lextable, LT::Entry( LEX_NONEQU, strNumber, LT_TI_NULLIDX, token ));
		return true;
	}

	case 'm':
	{
		FST::FST* a_mod = new FST::FST(A_MOD(token));
		if (FST::execute(*a_mod))
		{
			addLibFunc(lextable, idTable, token, LEX_MOD, strNumber);
			return true;
		}
		else
		{
			delete a_mod;
			a_mod = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}

	case 'f':
	{
		FST::FST* a_function = new FST::FST(A_FUNCTION(token));
		if (FST::execute(*a_function))
		{
			LT::Add(lextable, { LEX_FUNCTION, strNumber, LT_TI_NULLIDX });
			delete a_function;
			a_function = nullptr;
			return true;
		}
		else
		{
			delete a_function;
			a_function = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}

	case 't':
	{
		FST::FST* a_twirl = new FST::FST(A_TWIRL(token));
		if (FST::execute(*a_twirl))
		{
			LT::Add(lextable, { LEX_TWIRL, strNumber, LT_TI_NULLIDX });
			delete a_twirl;
			a_twirl = nullptr;
			return true;
		}
		else
		{
			delete a_twirl;
			a_twirl = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}

	case 'i':
	{
		FST::FST* a_integer = new FST::FST(A_INTEGER(token));
		if (FST::execute(*a_integer))
		{
			LT::Add(lextable, { LEX_INTEGER, strNumber, LT_TI_NULLIDX });
			delete a_integer;
			a_integer = nullptr;
			FlagForTypeofVar.posInLT = lextable.size - 1;
			FlagForTypeofVar.type = flagForTypeOfVar::INT;
			return true;
		}
		else
		{
			delete a_integer;
			a_integer = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}
	case 's':
	{
		FST::FST* a_string = new FST::FST(A_STRING(token));
		FST::FST* a_square = new FST::FST(A_SQUARE(token));
		if (FST::execute(*a_string))
		{
			LT::Add(lextable, { LEX_STRING, strNumber, LT_TI_NULLIDX });
			delete a_string;
			a_string = nullptr;
			FlagForTypeofVar.posInLT = lextable.size - 1;
			FlagForTypeofVar.type = flagForTypeOfVar::STR;
			return true;
		}
		else if (FST::execute(*a_square))
		{
			addLibFunc(lextable, idTable, token, LEX_SQUARE, strNumber);
			return true;
		}
		else
		{
			delete a_string;
			a_string = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}
	case '\'':
	{
		FST::FST* string_literal = new FST::FST(A_STRING_LITERAL(token));
		if (FST::execute(*string_literal))
		{
			int i = IT::IsLit(idTable, token);
			if (i != LT_TI_NULLIDX)
				LT::Add(lextable, { LEX_LITERAL, strNumber, i });
			else
			{
				string id = "lit" + std::to_string(lit);
				lit++;
				IT::Entry entry;
				strcpy_s(entry.id, id.c_str());
				memset(entry.parrentFunc, '\0', ID_MAXSIZE);
				entry.iddatatype = IT::IDDATATYPE::STR;
				entry.idtype = IT::IDTYPE::L;
				entry.idxfirstLE = lextable.size;
				IT::Add(idTable, entry);

				idTable.table[idTable.size - 1].value.vstr->len = 0;
				int i = 0, j = 0;
				for (; token[i] != '\0'; i++)
				{
					if (token[i] != '\'')
					{
						idTable.table[idTable.size - 1].value.vstr->str[j] = token[i];
						idTable.table[idTable.size - 1].value.vstr->len++;
						j++;
					}
				}
				idTable.table[idTable.size - 1].value.vstr->str[j] = '\0';

				LT::Add(lextable, { LEX_LITERAL, strNumber, idTable.size - 1 });
			}

			delete string_literal;
			string_literal = NULL;
			return true;
		}

		delete string_literal;
		string_literal = NULL;
		return false;
	}
	case 'p':
	{
		FST::FST* a_set = new FST::FST(A_POO(token));
		if (FST::execute(*a_set))
		{
			LT::Entry entry;
			entry.lexema = LEX_DECLARE;
			entry.sn = strNumber;
			entry.idxTI = LT_TI_NULLIDX;
			LT::Add(lextable, entry);
			delete a_set;
			a_set = nullptr;
			return true;

		}
		else
		{
			delete a_set;
			a_set = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}
	case 'r':
	{
		FST::FST* a_return = new FST::FST(A_RETURN(token));
		if (FST::execute(*a_return))
		{
			LT::Add(lextable, { LEX_RETURN, strNumber, LT_TI_NULLIDX });
			delete a_return;
			a_return = nullptr;
			return true;
		}
		else
		{
			delete a_return;
			a_return = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}
	case 'o':
	{
		FST::FST* a_out = new FST::FST(A_OUT(token));
		if (FST::execute(*a_out))
		{
			LT::Add(lextable, { LEX_OUT, strNumber, LT_TI_NULLIDX });
			delete a_out;
			a_out = nullptr;
			return true;
		}
		else
		{
			delete a_out;
			a_out = nullptr;
			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}
	}
	default:
	{
		FST::FST* integer_literal = new FST::FST(A_LITERAL(token));
		if (FST::execute(*integer_literal))
		{
			IT::Entry entry;
			int i = IT::IsLit(idTable, token);
			if (i != LT_TI_NULLIDX)
				LT::Add(lextable, { LEX_LITERAL, strNumber, i });
			else
			{
				string id = "lit" + std::to_string(lit);
				lit++;
				strcpy_s(entry.id, id.c_str());
				entry.parrentFunc[0] = '\0';
				entry.iddatatype = IT::IDDATATYPE::INT;
				entry.idtype = IT::IDTYPE::L;
				entry.idxfirstLE = lextable.size;
				IT::Add(idTable, entry);
				idTable.table[idTable.size - 1].value.vint = atoi(token);
				LT::Add(lextable, { LEX_LITERAL, strNumber, idTable.size - 1 });
			}

			delete integer_literal;
			integer_literal = NULL;
			return true;
		}
		else
		{
			delete integer_literal;
			integer_literal = NULL;

			return a_func_var(token, strNumber, lextable, idTable, FlagForTypeofVar);
		}

	}
	}
}
void divisionIntoTokens(In::IN& in, LT::LexTable& lextable, IT::IdTable& idTable)
{
	int lit = 0;
	char* temp = new char[50]{};
	int strNum = 0;
	int posInStr = 0;
	for (int i = 0, j = 0; i < in.size; i++)
	{
		if ((in.text[i] >= 'A' && in.text[i] <= 'Z') ||
			(in.text[i] >= 'a' && in.text[i] <= 'z') ||
			(in.text[i] >= '0' && in.text[i] <= '9'))
		{
			temp[j++] = in.text[i];
			posInStr++;
			continue;
		}
		else
		{
			if (j != 0)
			{
				i--;
				temp[j] = '\0';

				if (tokenAnalyse(temp, strNum, lextable, idTable, lit))
				{
					temp[0] = '\0';
					j = 0;
					continue;
				}
				else
				{
					throw ERROR_THROW_IN(121, strNum, posInStr, lit);
				}
			}
			else
			{
				if ((in.text[i] == '>' || in.text[i] == '<' || in.text[i] == '=' || in.text[i] == '!') && in.text[i + 1] == '=')
				{
					temp[0] = in.text[i];
					temp[1] = in.text[i + 1];
					temp[2] = '\0';
					i++;
					if (tokenAnalyse(temp, strNum, lextable, idTable, lit))
					{
						temp[0] = '\0';
						j = 0;
						continue;
					}
				}

				if (in.text[i] == '>' || in.text[i] == '<')
				{
					temp[0] = in.text[i];
					temp[1] = '\0';
					i++;
					if (tokenAnalyse(temp, strNum, lextable, idTable, lit))
					{
						temp[0] = '\0';
						j = 0;
						continue;
					}
				}

				if (in.text[i] == '\'')
				{
					temp[j++] = in.text[i++];
					for (int c = 0; in.text[i] != '\''; c++)
					{
						if (c <= TI_STR_MAXSIZE)
						{
							temp[j++] = in.text[i++];
						}
						else
							throw ERROR_THROW_IN(126, strNum, posInStr);
					}
					if (in.text[i] == '\'')
					{
						temp[j] = in.text[i];
						temp[j + 1] = '\0';
						if (tokenAnalyse(temp, strNum, lextable, idTable, lit))
						{
							temp[0] = '\0'; j = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(121, strNum, posInStr);
					}
					else
						throw ERROR_THROW_IN(127, strNum, posInStr);
				}

				if (in.text[i] != '\n')
				{
					if (in.text[i] == ' ' || in.text[i] == '\t')
					{
						posInStr++;
						continue;
					}

					temp[0] = in.text[i]; temp[1] = '\0';
					if (tokenAnalyse(temp, strNum, lextable, idTable, lit))
						posInStr++;
					else
						throw ERROR_THROW_IN(121, strNum, posInStr);

					temp[0] = '\0'; j = 0;
				}
			}
		}

		if (in.text[i] == '\n')
		{
			strNum++;
			posInStr = 0;
		}

	}

	delete[] temp;
}
bool a_func_var(char* token, int strNumber, LT::LexTable& lextable, IT::IdTable& idTable, flagForTypeOfVar& FlagForTypeOfVar)
{
	FST::FST* identificator = new FST::FST(A_IDENF(token));
	if (FST::execute(*identificator))
	{
		bool alreadyChecked = false;
		//проверка на идентификатор функции
		if (strcmp(token, "main") == 0 ||
			(LT::GetEntry(lextable, lextable.size - 1).lexema == LEX_FUNCTION &&
				LT::GetEntry(lextable, lextable.size - 2).lexema == 't') &&
			FlagForTypeOfVar.posInLT == (lextable.size - 2))
		{
			IT::Entry entry;
			if (IT::IsId(idTable, token) == TI_NULLIDX)
			{
				if (FlagForTypeOfVar.type == IT::IDDATATYPE::INT)
				{
					memset(entry.parrentFunc, '\0', ID_MAXSIZE);
					strcpy_s(entry.id, token);
					entry.iddatatype = IT::IDDATATYPE::INT;
					entry.idtype = IT::IDTYPE::F;
					entry.idxfirstLE = lextable.size;
					IT::Add(idTable, entry);

				}

				if (FlagForTypeOfVar.type == IT::IDDATATYPE::STR)
				{
					if ((strlen(token) > ID_MAXSIZE && (strcmp(token, "strlen") == 0 || strcmp(token, "substr") == 0)) ||
						strlen(token) <= ID_MAXSIZE)
					{
						strcpy_s(entry.id, token);
					}
					else
						throw ERROR_THROW(128);
					memset(entry.parrentFunc, '\0', ID_MAXSIZE);
					entry.iddatatype = IT::IDDATATYPE::STR;
					entry.idtype = IT::IDTYPE::F;
					entry.idxfirstLE = lextable.size;
					IT::Add(idTable, entry);
				}

				if (strcmp(token, "main") == 0)
				{
					memset(entry.parrentFunc, '\0', ID_MAXSIZE);
					strcpy_s(entry.id, token);
					entry.iddatatype = IT::IDDATATYPE::INT;
					entry.idtype = IT::IDTYPE::F;
					entry.idxfirstLE = lextable.size;
					IT::Add(idTable, entry);

				}
				FlagForTypeOfVar.posInLT = -1;
				FlagForTypeOfVar.type = flagForTypeOfVar::DEF;
				if (strcmp(token, "main") == 0)
					LT::Add(lextable, { LEX_MAINFUNC, strNumber, idTable.size - 1 });
				else
					LT::Add(lextable, { LEX_ID, strNumber, idTable.size - 1 });
				alreadyChecked = true;

			}
			else
			{

				throw ERROR_THROW_IN(123, strNumber, -1);
			}
		}
		//для переменной + проверяется переопределение
		if (!alreadyChecked &&
			(LT::GetEntry(lextable, lextable.size - 1).lexema == 't' &&
				LT::GetEntry(lextable, lextable.size - 2).lexema == LEX_DECLARE &&
				FlagForTypeOfVar.posInLT == lextable.size - 1))
		{
			IT::Entry entry;
			bool isLeftBraceWas = false;
			for (int i = lextable.size - 1; i > 0; i--)
			{
				if (LT::GetEntry(lextable, i).lexema == LEX_LEFTBRACE)
					isLeftBraceWas = true;

				if (isLeftBraceWas &&
					(LT::GetEntry(lextable, i).lexema == LEX_ID || LT::GetEntry(lextable, i).lexema == LEX_MAINFUNC) &&
					idTable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					if (IT::IsId(idTable, token, idTable.table[lextable.table[i].idxTI].id) == TI_NULLIDX)
					{
						if (FlagForTypeOfVar.type == flagForTypeOfVar::INT)
						{
							strcpy_s(entry.parrentFunc, idTable.table[lextable.table[i].idxTI].id);
							strcpy_s(entry.id, token);
							entry.iddatatype = IT::IDDATATYPE::INT;
							entry.idtype = IT::IDTYPE::V;
							entry.idxfirstLE = lextable.size;
							IT::Add(idTable, entry);
						}

						if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
						{
							strcpy_s(entry.parrentFunc, idTable.table[lextable.table[i].idxTI].id);
							strcpy_s(entry.id, token);
							entry.iddatatype = IT::IDDATATYPE::STR;
							entry.idtype = IT::IDTYPE::V;
							entry.idxfirstLE = lextable.size;
							IT::Add(idTable, entry);
						}

						FlagForTypeOfVar.posInLT = -1;
						FlagForTypeOfVar.type = flagForTypeOfVar::DEF;

						LT::Add(lextable, { LEX_ID, strNumber, idTable.size - 1 });
						alreadyChecked = true;
						break;
					}
					else
						throw ERROR_THROW_IN(123, strNumber, -1);

				}
			}
		}

		//для параметра функции
		if (!alreadyChecked &&
			(LT::GetEntry(lextable, lextable.size - 1).lexema == 't' && FlagForTypeOfVar.posInLT == lextable.size - 1))
			for (int i = lextable.size - 1; i > 0; i--)
			{
				IT::Entry entry;
				if ((LT::GetEntry(lextable, i).lexema == LEX_ID || LT::GetEntry(lextable, i).lexema == LEX_MAINFUNC) &&
					idTable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					if (LT::GetEntry(lextable, i - 1).lexema == LEX_FUNCTION && LT::GetEntry(lextable, i - 2).lexema == 't')
					{
						if (IT::IsId(idTable, token, idTable.table[lextable.table[i].idxTI].id) == TI_NULLIDX)
						{
							if (FlagForTypeOfVar.type == flagForTypeOfVar::INT) {
								strcpy_s(entry.parrentFunc, idTable.table[lextable.table[i].idxTI].id);
								strcpy_s(entry.id, token);
								entry.iddatatype = IT::IDDATATYPE::INT;
								entry.idtype = IT::IDTYPE::P;
								entry.idxfirstLE = lextable.size;
								IT::Add(idTable, entry);
							}

							if (FlagForTypeOfVar.type == flagForTypeOfVar::STR)
							{
								strcpy_s(entry.parrentFunc, idTable.table[lextable.table[i].idxTI].id);
								strcpy_s(entry.id, token);
								entry.iddatatype = IT::IDDATATYPE::STR;
								entry.idtype = IT::IDTYPE::P;
								entry.idxfirstLE = lextable.size;
								IT::Add(idTable, entry);
							}

							FlagForTypeOfVar.posInLT = -1;
							FlagForTypeOfVar.type = flagForTypeOfVar::DEF;

							LT::Add(lextable, { LEX_ID, strNumber, idTable.size - 1 });
							alreadyChecked = true;
							break;
						}
						else
							throw ERROR_THROW_IN(123, strNumber, -1);
					}
				}
			}

		//добавление идентификаторов с учетом области видимости
		if (!alreadyChecked)
		{
			bool isLeftBraceWas = false;
			for (int i = lextable.size - 1; i > 0; i--)
			{
				if (LT::GetEntry(lextable, i).lexema == LEX_LEFTBRACE)
					isLeftBraceWas = true;

				if (isLeftBraceWas &&
					(LT::GetEntry(lextable, i).lexema == LEX_ID || LT::GetEntry(lextable, i).lexema == LEX_MAINFUNC) &&
					idTable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::F)
				{
					int tempIndex = IT::IsId(idTable, token, idTable.table[lextable.table[i].idxTI].id);
					if (tempIndex != TI_NULLIDX)
					{
						LT::Add(lextable, { LEX_ID, strNumber, tempIndex });
						break;
					}
					else
					{
						tempIndex = IT::IsId(idTable, token);
						if (tempIndex != TI_NULLIDX &&
							idTable.table[tempIndex].idtype == IT::IDTYPE::F)
						{
							LT::Add(lextable, { LEX_ID, strNumber, tempIndex });
							break;
						}
						else
							throw ERROR_THROW_IN(129, strNumber, -1);
					}

				}
			}
		}

		delete identificator;
		identificator = NULL;
		return true;
	}
	else
	{
		delete identificator;
		identificator = NULL;
		return false;
	}
}

void addLibFunc(LT::LexTable& lexTable, IT::IdTable& idTable, char* token, char lexema, int strNumber)
{

	int indx;
	if (indx = IT::IsId(idTable, token) == TI_NULLIDX)
	{
		strcpy_s(idTable.table[idTable.size].id, token);
		idTable.table[idTable.size].idxfirstLE = strNumber;
		idTable.table[idTable.size].iddatatype = IT::INT;
		idTable.table[idTable.size].idtype = IT::F;
		idTable.size++;
	}
	lexTable.table[lexTable.size].lexema = lexema;
	lexTable.table[lexTable.size].sn = strNumber;
	lexTable.table[lexTable.size].idxTI = indx;
	lexTable.size++;
}