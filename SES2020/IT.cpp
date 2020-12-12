#include "pch.h"

namespace IT
{
	IdTable& Create(int size)
	{
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(115); 
		}
		IdTable *it = new IdTable();
		it->maxsize = size;
		it->size = 0;
		it->table = new Entry[it->maxsize];
		return *it;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size < idtable.maxsize)
		{
			idtable.table[idtable.size] = entry;
			if (entry.iddatatype == IT::IDDATATYPE::INT)
				idtable.table[idtable.size].value.vint = TI_INT_DEFAULT;
			if (entry.iddatatype == IT::IDDATATYPE::STR)
			{
				idtable.table[idtable.size].value.vstr->str[0] = TI_STR_DEFAULT;
				idtable.table[idtable.size].value.vstr->len = 0;
			}
			idtable.size++;
		}
		else 
			throw ERROR_THROW(122);
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n >= 0 && n < idtable.size)
			return idtable.table[n];
		else
			throw ERROR_THROW(124);
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;

	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE * 2], char parentFunc[ID_MAXSIZE * 2])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if ((strcmp(idtable.table[i].id, id) == 0) &&
				(strcmp(idtable.table[i].parrentFunc, parentFunc) == 0))
				return i;
		}
		return TI_NULLIDX;
	}

	int IsLit(IdTable& idtable, char lit[TI_STR_MAXSIZE])
	{
		char* temp = new char[TI_STR_MAXSIZE];
		int j = 0;
		for (int i = 0; lit[i] != '\0'; i++)
		{
			if (lit[i] != '\'')
			{
				temp[j] = lit[i];
				j++;
			}
		}
		temp[j] = '\0';

		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::IDTYPE::L)
			{
				if (idtable.table[i].value.vint == atoi(lit))
				{
					delete[] temp;
					return i;
				}

				if (strcmp(idtable.table[i].value.vstr->str, temp) == 0)
				{
					delete[] temp;
					return i;
				}
			}
		}

		delete[] temp;
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete [] idtable.table;
		delete &idtable;
	}

	void PrintIdTable(IdTable& idtable ,wchar_t* in, LT::LexTable& lextable)
	{
		int i = 0;
		wchar_t id[300];
		for (; in[i] != '\0'; i++)
			id[i] = in[i];
		id[i] = '\0';
		wcscat_s(id, PARM_ID_DEFAULT_EXT);

		std::ofstream* idStream = new std::ofstream;
		idStream->open(id);

		if (idStream->is_open())
		{

			*(idStream) << std::setw(50) << std::setfill(' ') << "------------- Литералы ------------- " << std::setw(50) << std::endl;
		
			*(idStream) << std::setw(15) << "Тип данных: " << std::setw(50) << "Значение: " << std::setw(15) << "Длина строки: " << std::endl;

			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::L)
				{
					switch (idtable.table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << std::setw(15) << "integer  " << std::setw(50) << idtable.table[i].value.vint  << std::setw(15)  << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << std::setw(15) << "string  " << std::setw(50) << idtable.table[i].value.vstr->str  << std::setw(15) << (int)idtable.table[i].value.vstr->len << std::endl;
						break;
					}
					}

				}
			}

			*(idStream) << std::setfill('-')  << std::setw(100) << "-" << std::setfill('-') << std::endl;

			*(idStream) << std::setw(50) << std::setfill(' ') << "------------- Функции -------------" << std::setw(50) << std::endl;
			*(idStream) << std::setw(20) << "Идентификатор: " << std::setw(25) << "Тип возвращаемого значения: "<< std::endl;

			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::F)
				{


					switch (idtable.table[i].iddatatype)
					{
						case IT::IDDATATYPE::INT:
						{
							*(idStream) << std::setw(20) << idtable.table[i].id  << std::setw(25) << "integer " << std::endl;
							break;
						}
						case IT::IDDATATYPE::STR:
						{
							*(idStream) << std::setw(20) << idtable.table[i].id  << std::setw(25) << "string " << std::endl;
							break;
						}
					}

				}

			}

			*(idStream) << std::setfill('-') << std::setw(100) << "-" << std::endl;

			*(idStream) << std::setw(50) << std::setfill(' ') << "------------- Переменные -------------" << std::setw(50) << std::endl;
			*(idStream) << std::setw(30) << "Блок-родитель: " << std::setw(20) << "Идентификатор: "  << std::setw(15) << "Тип данных: "  << std::setw(25) << "Тип идентификатора: " << std::setw(50) << "Значение: " << std::setw(15) << "Длина строки: " << std::endl;
			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::V)
				{
					switch (idtable.table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << std::setw(30) << idtable.table[i].parrentFunc  << std::setw(20) << idtable.table[i].id << std::setw(15) << "integer "  << std::setw(25) << "переменная"  << std::setw(50) << idtable.table[i].value.vint  << std::setw(15) << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << std::setw(30) << idtable.table[i].parrentFunc  << std::setw(20) << idtable.table[i].id  << std::setw(15) << "string "  << std::setw(25) << "переменная" << std::setw(50) << idtable.table[i].value.vstr->str << std::setw(15) << (int)idtable.table[i].value.vstr->len << std::endl;
						break;
					}
					}

				}

				if (idtable.table[i].idtype == IT::IDTYPE::P)
				{

					switch (idtable.table[i].iddatatype)
					{
						case IT::IDDATATYPE::INT:
						{
							*(idStream) << std::setw(30) << idtable.table[i].parrentFunc  << std::setw(20) << idtable.table[i].id  << std::setw(15) << "integer "  << std::setw(25) << "параметр"  << std::setw(50) << idtable.table[i].value.vint  << std::setw(15) << std::endl;
							break;
						}
						case IT::IDDATATYPE::STR:
						{
							*(idStream) << std::setw(30) << idtable.table[i].parrentFunc  << std::setw(20) << idtable.table[i].id  << std::setw(15) << "string " << std::setw(25) << "параметр"  << std::setw(50) << idtable.table[i].value.vstr->str << std::setw(15) << (int)idtable.table[i].value.vstr->len  << std::endl;
							break;
						}
					}
				}


			}
			*(idStream) << std::setfill('-') << std::setw(100) << "-" << std::endl;
			*(idStream) << std::setw(20) << std::setfill(' ') << "Идентификатор" << std::setw(35) << "Индекс первого вхождения в ТЛ:" << std::endl;

			for (int i = 0; i < idtable.size; i++)
			{
				if (idtable.table[i].id[0] != '\0')
					*(idStream) << std::setw(20) << idtable.table[i].id << std::setw(35) << idtable.table[i].idxfirstLE << std::endl;
				else
					*(idStream) << std::setw(20) << "Литерал" << std::setw(35) << idtable.table[i].idxfirstLE << std::endl;
			}
		}
		else
			throw ERROR_THROW(125);
		idStream->close();
		delete idStream;
	}

}