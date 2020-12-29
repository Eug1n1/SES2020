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
		ChangeIds(idTable);
		outString += HEAD;
		outString += FUNCS;
		outString += GetData(idTable);
		outString += GetCode(lexTable, idTable);
//TODO: ВЫЗОВЫ ФУНКЦИЙ ОНИ ВЕДЬ НЕ РАБОТАЮТ


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
		int funcIndx = 0, twirlCount = 0;
		string wtrue, wfalse;
		for (int i = 0; i < lexTable.size; i++)
		{
			switch (lexTable.table[i].lexema)
			{
			case LEX_BRACELET:
#pragma region EXIT_FUNC
				if (mainFunc)
				{
					output += "\tcall ExitProcess\nmain ENDP\nend main\n";
				}
				else
				{
					output += string(idTable.table[lexTable.table[funcIndx].idxTI].id) + " ENDP\n\n";
				}

				break;
#pragma endregion EXIT_FUNC

			case LEX_RETURN:
#pragma region RETURN
				if (mainFunc)
					output += "\tpush 0\n";
				else
				{
					if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT)
						output += "\tmov eax, " + string(idTable.table[lexTable.table[i + 1].idxTI].id) + "\n\tret\n";
					if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
						output += "\tmov eax,  " + string(idTable.table[lexTable.table[i + 1].idxTI].id) + "\n\tret\n";
				}
				break;
#pragma endregion RETURN

			case LEX_OUT:
#pragma region OUT
				if (lexTable.table[i + 2].lexema == LEX_RIGHTHESIS)
				{
					output += "\tcall newline\n";
					i += 2;
					continue;
				}

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
#pragma endregion OUT

			case LEX_ID:
#pragma region FUNC
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
#pragma endregion FUNC

			case LEX_MAINFUNC:
#pragma region MAIN
				funcIndx = i;
				output += "main PROC\n";
				mainFunc = true;
				break;
#pragma endregion MAIN

			case LEX_ASSIGN:
#pragma region ASSIGN
				idPos = i - 1;
				while (lexTable.table[i].lexema != LEX_SEMICOLON)
				{

					switch (lexTable.table[i].lexema)
					{
					case LEX_LITERAL:
					case LEX_ID:

						if (idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::P)
						{
							if (idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::L)
							{
								if (idTable.table[lexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
									output += "\tpush offset " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";
								else
									output += "\tpush " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";

							}
							else
							{
								output += "\tpush " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";
							}
							i++;
							continue;
						}

						if (idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::L)
						{
							if (idTable.table[lexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
								output += "\tpush offset " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";
							else
								output += "\tpush " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";

						}
						if(idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::V)
						{
							output += "\tpush " + string(idTable.table[lexTable.table[i].idxTI].id) + "\n";
						}

						break;
					case '@':
						output += "\tcall " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n";
						output += "\tpush eax\n";
						i += 2;
						break;

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
					case LEX_OCTAT:
						output += "\tpush " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n\tpush " + string(idTable.table[lexTable.table[i + 4].idxTI].id) + "\n";
						output += "\tcall octat\n";
						output += "\tpush eax\n";
						i += 5;
						break;
					case LEX_ELEVATE:
						output += "\tpush " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + "\n\tpush " + string(idTable.table[lexTable.table[i + 4].idxTI].id) + "\n";
						output += "\tcall elevate\n";
						output += "\tpush eax\n";
						i += 5;
						break;
					}
					i++;
				}
				output += "\tpop ebx\n\tmov " + string(idTable.table[lexTable.table[idPos].idxTI].id) + ", ebx\n\n";
				break;
#pragma endregion ASSIGN

			case LEX_TWIRL:
#pragma region TWIRL
				output += "twirl_start" + std::to_string(twirlCount) + ":\n";
				output += "\tmov eax, " + string(idTable.table[lexTable.table[i + 2].idxTI].id) + string("\n");
				output += "\tmov ebx, " + string(idTable.table[lexTable.table[i + 4].idxTI].id) + string("\n");
				output += "\tcmp eax, ebx\n";

				switch (lexTable.table[i + 3].operation[0])
				{
				case '=':
					wtrue = "je";
					wfalse = "jne";
					break;
				case '!':
					wtrue = "jne";
					wfalse = "jnz";
					break;
				case '>':
					if (!strcmp(lexTable.table[i + 3].operation, ">="))
					{
						wtrue = "jge";
						wfalse = "jl";
					}
					else
					{
						wtrue = "jg";
						wfalse = "jle";
					}
					break;
				case '<':
					if (!strcmp(lexTable.table[i + 3].operation, "<="))
					{
						wtrue = "jle";
						wfalse = "jg";
					}
					else
					{
						wtrue = "jl";
						wfalse = "jge";
					}
					break;
				}

				output += "\t" + wfalse + " twirl_end" + std::to_string(twirlCount) + "\n";
				i += 6;
				break;
#pragma endregion TWIRL

			case LEX_RIGHTSQBRACKET:
#pragma region TWIRL_END

				output += "\tjmp twirl_start" + std::to_string(twirlCount) + "\n";
				output += "twirl_end" + std::to_string(twirlCount) + ":\n";
				twirlCount++;
				break;
#pragma endregion TWIRL_END

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

	void ChangeIds(IT::IdTable& idTable)
	{
		int count = 48;
		int val = 0;
		for (int i = 0; i < idTable.size; i++)
		{
			if (idTable.table[i].idtype == IT::IDTYPE::F && idTable.table[i].id != "main")
			{
				if (count == 123)
					throw ERROR_THROW(406);
				while ((count < 48 || count >57) && (count < 65 || count > 90) && (count < 97 || count > 122))
				{
					count++;
				}
				val = strlen(idTable.table[i].id);
				idTable.table[i].id[val] = count;
				count++;
				idTable.table[i].id[val + 1] = '\0';
			}
		}
	}
}


