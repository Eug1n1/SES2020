#pragma once
#include "pch.h"


#define LEXEMA_FIXSIZE 1 //‘» —»–ќ¬јЌЌџ… –ј«ћ≈– Ћ≈ —≈ћ
#define LT_MAXSIZE 1024 //max кол-во строк в таблице лексем
#define LT_TI_NULLIDX -1 // нет элемента таблицы идентификаторов
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_MAINFUNC 'm'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_OUT 'o'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_LEFTSQBRACKET '['
#define LEX_RIGHTSQBRACKET ']'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_ASSIGN '='
#define LEX_EQU 'c'
#define LEX_LESS 'c'
#define LEX_MORE 'c'
#define LEX_LESSOREQU 'c'
#define LEX_MOREOREQU 'c'
#define LEX_TWIRL 'w'
#define LEX_MOD 'k'
#define LEX_SQUARE 's'

namespace LT
{
	struct Entry //строка таблицы лексем
	{
		char lexema; //лексема
		int sn;				//номер строки в исходном тексте
		int idxTI;  //индекс в таблице идентификаторов или LT_TI_NULLDIX
		char* operation;
	};

	struct LexTable
	{
		int maxsize;	//Ємкость таблицы лексем < LT_MAXSIZE
		int size;		//текущий размер таблицы лексем < maxsize
		Entry* table;	//массив строк таблицы лексем
	};
	LexTable& Create( //создать таблицу лексем
		int size	 //Ємкость таблицы лексем < LT_MAXSIZE
	);
	void Add(	//добавить строку в таблицу лексем
		LexTable& lextable, //экземпл€р таблицы лексем
		Entry entry				//строка таблицы лексем
	);
	Entry GetEntry( //получить строку таблицы лексем
		LexTable& lextable,		//экземпл€р таблицы лексем
		int n					//номер получаемой строки
	);
	void Delete(LexTable& lextable); //удалить таблицу лексем(освободить пам€ть)

	void PrintLexTable(LexTable& lextable, wchar_t* in);
};

