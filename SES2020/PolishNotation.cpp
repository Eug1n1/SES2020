#include "pch.h"

int Prior(char ch)
{
	if (ch == '(' || ch == ')')
		return 0;
	else if (ch == ',')
		return 1;
	else if (ch == '+' || ch == '-')
		return 2;
	return -1;
}

void StartPolish(LT::LexTable& lextable, IT::IdTable& idtable)
{
	LT::LexTable newTable = LT::Create(lextable.maxsize);
	vector<LT::Entry> temp;
	int semiInd = 0, lextablePos = 0, correction = 0;


	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema == LEX_ASSIGN) 
		{
			i++;
			correction = 0;
			lextablePos = i;
			temp.clear();
			for (; lextable.table[i].lexema != LEX_SEMICOLON; i++)
			{
				temp.push_back(lextable.table[i]);
			}
			semiInd = i;
			ToPolish(temp, idtable, correction);

			for (int i = lextablePos, k = 0; i < lextablePos + temp.size(); i++, k++)
			{
				lextable.table[i] = temp[k];												
			}
			lextable.table[lextablePos + temp.size()] = lextable.table[semiInd];

			for (int i = 0; i < correction; i++)
			{
				for (int j = lextablePos + temp.size() + 1; j < lextable.size; j++)				//сдвигаем на лишнее место
				{
					lextable.table[j] = lextable.table[j + 1];
				}
				lextable.size--;
			}

			printLex(lextable);
			
		}
		
	}
}

void printLex(LT::LexTable lex)
{
	for (int i = 0; i < lex.size; i++)
	{
		std::cout << lex.table[i].lexema;
	}
	std::cout << std::endl;
}

bool ToPolish(vector<LT::Entry>& source, IT::IdTable& idtable, int& correction)
{
	std::vector<LT::Entry> result;
	std::stack<LT::Entry> stack;
	int elemIndex = 1;
	bool isFunc = false;
	int elemCount = 0;
	LT::Entry func;

	for (int i = 0; i < source.size(); i++)
	{
		switch (source[i].lexema)
		{
		case '-':
		case '+':
			if (stack.empty() || stack.top().lexema == '(')
			{
				stack.push(source[i]);
			}

			else
			{
				int symbolPrior = Prior(source[i].lexema);
				while (!stack.empty() && stack.top().lexema != '(' && symbolPrior <= Prior(stack.top().lexema))
				{
					result.push_back(stack.top());
					stack.pop();
				}
				stack.push(source[i]);
			}
			break;
		case '(':
			stack.push(source[i]);
			break;
		case ')':
			while (!stack.empty() && stack.top().lexema != '(')
			{
				result.push_back(stack.top());
				stack.pop();
			}

			if (!stack.empty())
				stack.pop();

			if (isFunc)
			{
				isFunc = false;
				correction += 2 + elemCount - 1 - 2;
				result.push_back({ '@', func.sn, -1 });
				result.push_back({ (char)(elemCount + '0'), func.sn, -1});
				result.push_back(func);
			}
			break;
		case ',':
			while (!stack.empty() && stack.top().lexema != '(')
			{
				result.push_back(stack.top());
				stack.pop();
			}
			break;
		case 'k':
		case 's':
			isFunc = true;
			func = source[i];
			break;
		case 'i':
		case 'l':
			if (isFunc)
			{
				elemCount++;
			}

			if (source.size() - 1 > i ? source[i + 1].lexema == '(' : false && idtable.table[source[i].idxTI].idtype == IT::IDTYPE::F)
			{
				isFunc = true;
				elemCount = 0;
				func = source[i];
			}
			else
			{
				result.push_back(source[i]);
			}

			break;
		}
	}
	while (!stack.empty())
	{
		result.push_back(stack.top());
		stack.pop();
	}
	source = result;
	return true;
}