#include "pch.h"

namespace Generator
{
	void Generate(LT::LexTable lexTable, IT::IdTable idTable, Parm::PARM parm)
	{
		string outString;
		std::ofstream file(parm.out);
		if (!file.is_open())
		{
			throw ERROR_THROW(2);
		}

		outString += HEAD;
		outString += GetData(idTable);
		outString += GetCode(lexTable, idTable);


		file << outString;
		file.close();
	}

	string GetCode(LT::LexTable lexTable, IT::IdTable idTable)
	{
		string output = "\n.code\n";
		int idPos = 0;
		stack<LT::Entry> funcParams;
		bool isFunc = false;
		bool mainFunc = false;
		int funcIndx = 0;
		for (int i = 0; i < lexTable.size; i++)
		{
			std::cout << lexTable.table[i].lexema;
			switch (lexTable.table[i].lexema)
			{
			case LEX_BRACELET:
				if (isFunc)
				{
					output += string(idTable.table[lexTable.table[funcIndx].idxTI].id) + " ENDP\n\n";
				}
				else
				{
					output += "call ExitProcess\nmain ENDP\n";
				}
				break;

			case LEX_RETURN:
				if (mainFunc)
					output += "push 0\n";
				else
				{
					if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT)
						output += "\tmov eax, " + string(idTable.table[lexTable.table[i + 1].idxTI].id) + "\n\tret\n";
					if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
						output += "\tmov eax, offset " + string(idTable.table[lexTable.table[i + 1].idxTI].id) + "\n\tret\n";
				}
				break;

			case LEX_OUT:
				if (idTable.table[lexTable.table[i + 2].idxTI].iddatatype == IT::IDDATATYPE::STR)
				{
					if (lexTable.table[i + 2].lexema == 'i')
						output += "\tpush " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n";
					else
						output += "\tpush offset " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n";
					output += "\tcall prints\n";
				}
				else
				{
					output += "\tpush " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n";
					output += "\tcall printi\n";
				}
				break;

			case LEX_ID:
				if (lexTable.table[i - 1].lexema == LEX_FUNCTION)
				{
					funcIndx = i;
					output += string(idTable.table[lexTable.table[funcIndx].idxTI].id) + " PROC ";
					isFunc = true;
					i++;
					while (lexTable.table[i].lexema != LEX_RIGHTHESIS)
					{
						if (lexTable.table[i].lexema == LEX_ID)
							funcParams.push(lexTable.table[i]);
						i++;
					}

					while (!funcParams.empty())
					{
						output += string(idTable.table[funcParams.top().idxTI].id) + ":DWORD";
						if (funcParams.size() > 1)
							output += ", ";

						funcParams.pop();
					}
					output += "\n";
				}
				break;

			case LEX_MAINFUNC:
				output += "main PROC\n";
				mainFunc = true;
				break;

			case LEX_ASSIGN:
				idPos = i - 1;
				while (lexTable.table[i].lexema != LEX_SEMICOLON)
				{

					switch (lexTable.table[i].lexema)
					{
					case LEX_LITERAL:
					case LEX_ID:

						if (idTable.table[lexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::INT)
							output += "\tpush " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";
						else
							output += "\tpush offset " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";
						break;
					case '@':
						output += "\tcall " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n";
						output += "\tpush eax\n";
						break;

					case 'v':
						switch (lexTable.table[i].operation[0])
						{
						case '+':
							output += "\tpop eax\n";
							output += "\tpop ebx\n";
							output += "\tadd eax, ebx\n";
							output += "\tpush eax\n";
							break;
						case '-':
							output += "\tpop ebx\n";
							output += "\tpop eax\n";
							output += "\tsub eax, ebx\n";
							output += "\tpush eax\n";
							break;
						}
					}
					i++;
				}
				output += "\tpop " + string(idTable.table[lexTable.table[idPos].idxTI].id) + "\n\n";
				break;

			default:
				break;
			}
		}
		return output;
	}

	string GetData(IT::IdTable idTable)
	{
		string dataString, constants = ".const\n", variables = ".data\n";
		for (int i = 0; i < idTable.size; i++)
		{
			if (idTable.table[i].idtype == IT::IDTYPE::L)
			{
				constants += "\t\t" + string(idTable.table[i].id);
				switch (idTable.table[i].iddatatype)
				{
				case IT::IDDATATYPE::INT:
					constants += " sdword \t";
					constants += std::to_string(idTable.table[i].value.vint);
					constants += string("\n");
					break;
				case IT::IDDATATYPE::STR:
					constants += " byte \t'" + string(idTable.table[i].value.vstr->str) + "', 0\n";
					break;
				}
			}
			else if (idTable.table[i].idtype == IT::IDTYPE::V)
			{
				variables += "\t\t" + string(idTable.table[i].id);
				switch (idTable.table[i].iddatatype)
				{
				case IT::IDDATATYPE::INT:
					variables += " \tsdword \t0\n";
					break;
				case IT::IDDATATYPE::STR:
					variables += " \tdword \t?\n";
					break;
				}
			}
		}

		return constants + "\n\n" + variables;
	}
}