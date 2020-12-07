#include "pch.h"

namespace In 
{


	IN Getin(wchar_t infile[]) {
		In::IN in;
		in.size = -1;
		in.ignor = in.lines = 0;
		int temp[256]IN_CODE_TABLE;
		memcpy(in.code, temp, sizeof(temp)); //заполнение таблицы проверки в структуре
		std::ifstream file;
		std::ofstream out;
		file.open(infile, std::ios::ate); //устанавливает указатель в конец файла, поэтому можно узнать его размер
		if (!file.is_open())
			throw ERROR_THROW(110);
		short size = file.tellg();
		in.text = new unsigned char[size + 1]; //tellg() - выводит размер файла
		file.seekg(0, std::ios::beg);
		while (!file.eof()) {
			std::string str = "";
			std::getline(file, str);
			if (str.length())
				in.lines++;
			bool space = false;
			bool isOperation = false;
			std::string operations = "+-/*(),;=";
			for (int i = 0; i < (int)str.length(); i++)
			{
				if ((space ||
					isOperation ||
					operations.find_first_of(str[i + 1]) != std::string::npos) &&
					str[i] == ' ')
				{
					continue;
				}
				else if (space && str[i] != ' ')
				{
					space = false;
				}
				else if (isOperation && operations.find_first_of(str[i]) == std::string::npos && str[i] != ' ')
				{
					isOperation = false;
				}
				if (str[i] == ' ')
				{
					space = true;
				}
				else if (operations.find_first_of(str[i]) != std::string::npos)
				{
					isOperation = true;
				}
				if (str[i] == '\'')
				{
					do {
						in.size++;
						in.text[in.size] = str[i];
					} while (str[++i] != '\'' && i < (int)str.length());
				}
				if (in.code[(unsigned char)str[i]] == in.F)
				{
					throw ERROR_THROW_IN(111, in.lines - 1, i);
				}
				else if (in.code[(unsigned char)str[i]] == in.I)
				{

					in.ignor++;
				}
				else if (in.code[(unsigned char)str[i]] == in.T)
				{
					in.size++;
					in.text[in.size] = str[i];
					
				}
				else
				{
					in.text[in.size] = in.code[(unsigned char)str[i]];
					in.size++;
				}
			}
			in.text[++in.size] = IN_CODE_ENDL;
		}
		file.close();
		in.text[in.size] = '\0';
		return in;
	}
}