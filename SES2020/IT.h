#pragma once

#include "pch.h"
#include "LT.h"

#define ID_MAXSIZE 10 //max кол-во символов в id
#define TI_MAXSIZE 1024 //max кол-во строк в таблице id
#define TI_INT_DEFAULT 0x00000000 //значение по умолчанию дл€ integer
#define TI_STR_DEFAULT 0x00		//значение по умолч дл€ string
#define TI_NULLIDX -1 //нет эл-та таблицы id
#define TI_STR_MAXSIZE 255

namespace IT // таблица id
{
	enum IDDATATYPE {DEF = 0, INT = 1, STR = 2}; //типы данных id: integer, string
	enum IDTYPE {D = 0, V = 1, F = 2, P = 3, L = 4};	  //типы id: переменна€, функци€, параметр, литерал


	struct Entry //строка таблицы id
	{
		int idxfirstLE;		//индекс первой строки в “Ћ
		char parrentFunc[ID_MAXSIZE * 2];
		char id[ID_MAXSIZE * 2]; //id (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE iddatatype; //тип данных
		IDTYPE idtype;			//тип идентификатора
		union
		{
			int vint; //значение integer
			struct
			{
				char len;	//кол-во символов в string
				char str[TI_STR_MAXSIZE - 1]; //символы string
			} vstr[TI_STR_MAXSIZE]; //значение string
		}value;
	};
	
	struct IdTable //экземпл€р таблицы id
	{
		int maxsize; //Ємкость таблицы id < TI_MAXSIZE
		int size;	//текущий размер таблицы id
		Entry* table; //массив строк таблицы id
	};
	IdTable& Create(	//создать таблицу id
		int size //Ємкость таблицы id < TI_MAXSIZE
	);

	void Add(	//добавить строку в таблицу id 
		IdTable& idtable, //экземпл€р таблицы id
		Entry entry		//строка таблицы идентификаторов
	);
	Entry GetEntry(	//получить строку таблицы id
		IdTable& idtable, //экземпл€р таблицы id
		int n		//номер получаемой строки
	);
	int IsId(		//возврат: номер строки(если есть), TI_NULLIDX(если нет)
		IdTable& idtable,	//экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE * 2] //идентификатор
	);
	int IsId(		
		IdTable& idtable,	
		char id[ID_MAXSIZE * 2],
		char parentFunc[ID_MAXSIZE * 2]
	);
	int IsLit(IdTable& idtable, char lit[TI_STR_MAXSIZE]);
	void Delete(IdTable& idtable); //удалить таблицу идентификаторов(освободить пам€ть)

	void PrintIdTable(IdTable& idtable, wchar_t* in, LT::LexTable& lextable);
}