#pragma once

#include "pch.h"
#include "LT.h"

#define ID_MAXSIZE 10 //max ���-�� �������� � id
#define TI_MAXSIZE 1024 //max ���-�� ����� � ������� id
#define TI_INT_DEFAULT 0x00000000 //�������� �� ��������� ��� integer
#define TI_STR_DEFAULT 0x00		//�������� �� ����� ��� string
#define TI_NULLIDX -1 //��� ��-�� ������� id
#define TI_STR_MAXSIZE 255

namespace IT // ������� id
{
	enum IDDATATYPE {DEF = 0, INT = 1, STR = 2}; //���� ������ id: integer, string
	enum IDTYPE {D = 0, V = 1, F = 2, P = 3, L = 4};	  //���� id: ����������, �������, ��������, �������


	struct Entry //������ ������� id
	{
		int idxfirstLE;		//������ ������ ������ � ��
		char parrentFunc[ID_MAXSIZE * 2];
		char id[ID_MAXSIZE * 2]; //id (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE iddatatype; //��� ������
		IDTYPE idtype;			//��� ��������������
		union
		{
			int vint; //�������� integer
			struct
			{
				char len;	//���-�� �������� � string
				char str[TI_STR_MAXSIZE - 1]; //������� string
			} vstr[TI_STR_MAXSIZE]; //�������� string
		}value;
	};
	
	struct IdTable //��������� ������� id
	{
		int maxsize; //������� ������� id < TI_MAXSIZE
		int size;	//������� ������ ������� id
		Entry* table; //������ ����� ������� id
	};
	IdTable& Create(	//������� ������� id
		int size //������� ������� id < TI_MAXSIZE
	);

	void Add(	//�������� ������ � ������� id 
		IdTable& idtable, //��������� ������� id
		Entry entry		//������ ������� ���������������
	);
	Entry GetEntry(	//�������� ������ ������� id
		IdTable& idtable, //��������� ������� id
		int n		//����� ���������� ������
	);
	int IsId(		//�������: ����� ������(���� ����), TI_NULLIDX(���� ���)
		IdTable& idtable,	//��������� ������� ���������������
		char id[ID_MAXSIZE * 2] //�������������
	);
	int IsId(		
		IdTable& idtable,	
		char id[ID_MAXSIZE * 2],
		char parentFunc[ID_MAXSIZE * 2]
	);
	int IsLit(IdTable& idtable, char lit[TI_STR_MAXSIZE]);
	void Delete(IdTable& idtable); //������� ������� ���������������(���������� ������)

	void PrintIdTable(IdTable& idtable, wchar_t* in, LT::LexTable& lextable);
}