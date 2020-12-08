#pragma once
#include "pch.h"


#define LEXEMA_FIXSIZE 1 //������������� ������ ������
#define LT_MAXSIZE 1024 //max ���-�� ����� � ������� ������
#define LT_TI_NULLIDX -1 // ��� �������� ������� ���������������
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
	struct Entry //������ ������� ������
	{
		char lexema; //�������
		int sn;				//����� ������ � �������� ������
		int idxTI;  //������ � ������� ��������������� ��� LT_TI_NULLDIX
		char* operation;
	};

	struct LexTable
	{
		int maxsize;	//������� ������� ������ < LT_MAXSIZE
		int size;		//������� ������ ������� ������ < maxsize
		Entry* table;	//������ ����� ������� ������
	};
	LexTable& Create( //������� ������� ������
		int size	 //������� ������� ������ < LT_MAXSIZE
	);
	void Add(	//�������� ������ � ������� ������
		LexTable& lextable, //��������� ������� ������
		Entry entry				//������ ������� ������
	);
	Entry GetEntry( //�������� ������ ������� ������
		LexTable& lextable,		//��������� ������� ������
		int n					//����� ���������� ������
	);
	void Delete(LexTable& lextable); //������� ������� ������(���������� ������)

	void PrintLexTable(LexTable& lextable, wchar_t* in);
};

