#pragma once

#define A_INTEGER(string) string, 4, \
		FST::NODE(1, FST::RELATION('i', 1)), \
		FST::NODE(1, FST::RELATION('n', 2)), \
		FST::NODE(1, FST::RELATION('t', 3)), \
		FST::NODE() 

#define A_STRING(string) string, 7,	\
		FST::NODE(1, FST::RELATION('s', 1)), \
		FST::NODE(1, FST::RELATION('t', 2)), \
		FST::NODE(1, FST::RELATION('r', 3)), \
		FST::NODE(1, FST::RELATION('i', 4)), \
		FST::NODE(1, FST::RELATION('n', 5)), \
		FST::NODE(1, FST::RELATION('g', 6)), \
		FST::NODE()

#define A_FUNCTION(string)string, 5,	\
		FST::NODE(1, FST::RELATION('f', 1)), \
		FST::NODE(1, FST::RELATION('u', 2)), \
		FST::NODE(1, FST::RELATION('n', 3)), \
		FST::NODE(1, FST::RELATION('c', 4)), \
		FST::NODE() 

#define A_SQUARE(string)string, 7,	\
		FST::NODE(1, FST::RELATION('s', 1)), \
		FST::NODE(1, FST::RELATION('q', 2)), \
		FST::NODE(1, FST::RELATION('u', 3)), \
		FST::NODE(1, FST::RELATION('a', 4)), \
		FST::NODE(1, FST::RELATION('r', 5)), \
		FST::NODE(1, FST::RELATION('e', 6)), \
		FST::NODE()

#define A_MOD(string)string, 4,	\
		FST::NODE(1, FST::RELATION('m', 1)), \
		FST::NODE(1, FST::RELATION('o', 2)), \
		FST::NODE(1, FST::RELATION('d', 3)), \
		FST::NODE()

#define A_POO(string) string, 4,	\
		FST::NODE(1, FST::RELATION('p', 1)),	\
		FST::NODE(1, FST::RELATION('o', 2)),	\
		FST::NODE(1, FST::RELATION('o', 3)),	\
		FST::NODE()

#define A_TWIRL(string) string, 6,	\
		FST::NODE(1, FST::RELATION('t', 1)),	\
		FST::NODE(1, FST::RELATION('w', 2)),	\
		FST::NODE(1, FST::RELATION('i', 3)),	\
		FST::NODE(1, FST::RELATION('r', 4)),	\
		FST::NODE(1, FST::RELATION('l', 5)),	\
		FST::NODE()

#define A_RETURN(string) string, 7,	\
		FST::NODE(1, FST::RELATION('r', 1)),	\
		FST::NODE(1, FST::RELATION('e', 2)),	\
		FST::NODE(1, FST::RELATION('t', 3)),	\
		FST::NODE(1, FST::RELATION('u', 4)),	\
		FST::NODE(1, FST::RELATION('r', 5)),	\
		FST::NODE(1, FST::RELATION('n', 6)),	\
		FST::NODE()	

#define A_MAIN(string) string, 5,	\
		FST::NODE(1, FST::RELATION('m', 1)),	\
		FST::NODE(1, FST::RELATION('a', 2)),	\
		FST::NODE(1, FST::RELATION('i', 3)),	\
		FST::NODE(1, FST::RELATION('n', 4)),	\
		FST::NODE()

#define A_OUT(string) string, 4,	\
		FST::NODE(1, FST::RELATION('o', 1)),	\
		FST::NODE(1, FST::RELATION('u', 2)),	\
		FST::NODE(1, FST::RELATION('t', 3)),	\
		FST::NODE()	

#define A_EXPRESSION(string)string, 2,	\
		FST::NODE(2,	\
			FST::RELATION('+', 1),	\
			FST::RELATION('-', 1),	\
		FST::NODE()

#define A_SPACE(string) string, 2,	\
		FST::NODE(1, FST::RELATION(' ', 1)),	\
		FST::NODE()	

#define A_LEFTBRACE(string)string, 2,	\
		FST::NODE(1, FST::RELATION('{', 1)),	\
		FST::NODE()

#define A_RIGHTBRACE(string)string, 2,	\
		FST::NODE(1, FST::RELATION('}', 1)),	\
		FST::NODE()

#define A_LEFTHESIS(string)string, 2,	\
		FST::NODE(1, FST::RELATION('(', 1)),	\
		FST::NODE()

#define A_RIGHTHESIS(string)string, 2,	\
		FST::NODE(1, FST::RELATION(')', 1)),	\
		FST::NODE()

#define A_SEMICOLON(string) string, 2, \
		FST::NODE(1, FST::RELATION(';', 1)), \
		FST::NODE()

#define A_COMMA(string)string, 2,	\
		FST::NODE(1, FST::RELATION(',', 1)),	\
		FST::NODE()

#define A_PLUS(string)string, 2,	\
		FST::NODE(1, FST::RELATION('+', 1)),	\
		FST::NODE()
#define A_MINUS(string)string, 2,	\
		FST::NODE(1, FST::RELATION('-', 1)),	\
		FST::NODE()

#define A_ASSIGN(string)string, 2,	\
		FST::NODE(1, FST::RELATION('=', 1)),	\
		FST::NODE()

#define A_EQU(string)string, 3,	\
		FST::NODE(1, FST::RELATION('=', 1)), \
		FST::NODE(1, FST::RELATION('=', 2)), \
		FST::NODE()

#define A_NONEEQU(string)string, 3,	\
		FST::NODE(1, FST::RELATION('!', 1)), \
		FST::NODE(1, FST::RELATION('=', 2)), \
		FST::NODE()

#define A_MORE(string)string, 2,	\
		FST::NODE(1, FST::RELATION('>', 1)), \
		FST::NODE()

#define A_LESS(string)string, 2,	\
		FST::NODE(1, FST::RELATION('<', 1)), \
		FST::NODE()

#define A_MOREOREQU(string)string, 3,	\
		FST::NODE(1, FST::RELATION('>', 1)), \
		FST::NODE(1, FST::RELATION('=', 2)), \
		FST::NODE()

#define A_LESSOREQU(string)string, 3,	\
		FST::NODE(1, FST::RELATION('<', 1)), \
		FST::NODE(1, FST::RELATION('=', 2)), \
		FST::NODE()

#define A_LITERAL(string)string, 2,	\
		FST::NODE(20,	\
			FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0),	\
			FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0),	\
			FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0),	\
			FST::RELATION('9', 0), FST::RELATION('0', 1), FST::RELATION('1', 1),	\
			FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),	\
			FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1),	\
			FST::RELATION('8', 1), FST::RELATION('9', 1)),	\
		FST::NODE()	

#define A_IDENF(string) string, 2,	\
		FST::NODE(52,	\
			FST::RELATION('a', 1), FST::RELATION('a', 0), FST::RELATION('b', 1), FST::RELATION('b', 0), \
			FST::RELATION('c', 1), FST::RELATION('c', 0), FST::RELATION('d', 1), FST::RELATION('d', 0), FST::RELATION('e', 1), FST::RELATION('e', 0), \
			FST::RELATION('f', 1), FST::RELATION('f', 0), FST::RELATION('g', 1), FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('h', 1), FST::RELATION('i', 0), FST::RELATION('i', 1), \
			FST::RELATION('j', 0), FST::RELATION('j', 1), FST::RELATION('k', 0), FST::RELATION('k', 1), FST::RELATION('l', 0), FST::RELATION('l', 1), \
			FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('n', 0), FST::RELATION('n', 1), FST::RELATION('o', 0), FST::RELATION('o', 1), \
			FST::RELATION('p', 0), FST::RELATION('p', 1), FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('r', 0), FST::RELATION('r', 1), \
			FST::RELATION('s', 0), FST::RELATION('s', 1), FST::RELATION('t', 0), FST::RELATION('t', 1), FST::RELATION('u', 0), FST::RELATION('u', 1), \
			FST::RELATION('v', 0), FST::RELATION('v', 1), FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('x', 0), FST::RELATION('x', 1), \
			FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('z', 0), FST::RELATION('z', 1)),	\
		FST::NODE()

#define A_STRING_LITERAL(string) string, 3,	\
	FST::NODE(1, FST::RELATION('\'', 1)),	\
	FST::NODE(78,	FST::RELATION(' ', 1),	\
					FST::RELATION('A', 1),	\
					FST::RELATION('B', 1),	\
					FST::RELATION('C', 1),	\
					FST::RELATION('D', 1),	\
					FST::RELATION('E', 1),	\
					FST::RELATION('F', 1),	\
					FST::RELATION('G', 1),	\
					FST::RELATION('H', 1),	\
					FST::RELATION('I', 1),	\
					FST::RELATION('J', 1),	\
					FST::RELATION('K', 1),	\
					FST::RELATION('L', 1),	\
					FST::RELATION('M', 1),	\
					FST::RELATION('N', 1),	\
					FST::RELATION('O', 1),	\
					FST::RELATION('P', 1),	\
					FST::RELATION('Q', 1),	\
					FST::RELATION('R', 1),	\
					FST::RELATION('S', 1),	\
					FST::RELATION('T', 1),	\
					FST::RELATION('U', 1),	\
					FST::RELATION('V', 1),	\
					FST::RELATION('W', 1),	\
					FST::RELATION('X', 1),	\
					FST::RELATION('Y', 1),	\
					FST::RELATION('Z', 1),	\
					FST::RELATION('a', 1),	\
					FST::RELATION('b', 1),	\
					FST::RELATION('c', 1),	\
					FST::RELATION('d', 1),	\
					FST::RELATION('e', 1),	\
					FST::RELATION('f', 1),	\
					FST::RELATION('g', 1),	\
					FST::RELATION('h', 1),	\
					FST::RELATION('i', 1),	\
					FST::RELATION('j', 1),	\
					FST::RELATION('k', 1),	\
					FST::RELATION('l', 1),	\
					FST::RELATION('m', 1),	\
					FST::RELATION('n', 1),	\
					FST::RELATION('o', 1),	\
					FST::RELATION('p', 1),	\
					FST::RELATION('q', 1),	\
					FST::RELATION('r', 1),	\
					FST::RELATION('s', 1),	\
					FST::RELATION('t', 1),	\
					FST::RELATION('u', 1),	\
					FST::RELATION('v', 1),	\
					FST::RELATION('w', 1),	\
					FST::RELATION('x', 1),	\
					FST::RELATION('y', 1),	\
					FST::RELATION('z', 1),	\
					FST::RELATION('0', 1),	\
					FST::RELATION('1', 1),	\
					FST::RELATION('2', 1),	\
					FST::RELATION('3', 1),	\
					FST::RELATION('4', 1),	\
					FST::RELATION('5', 1),	\
					FST::RELATION('6', 1),	\
					FST::RELATION('7', 1),	\
					FST::RELATION('8', 1),	\
					FST::RELATION('9', 1),	\
					FST::RELATION('=', 1),	\
					FST::RELATION('+', 1),	\
					FST::RELATION('-', 1),	\
					FST::RELATION('*', 1),	\
					FST::RELATION('/', 1),	\
					FST::RELATION('(', 1),	\
					FST::RELATION(')', 1),	\
					FST::RELATION('{', 1),	\
					FST::RELATION('}', 1),	\
					FST::RELATION(';', 1),	\
					FST::RELATION(',', 1),	\
					FST::RELATION('?', 1),	\
					FST::RELATION('!', 1),	\
					FST::RELATION('\\', 1),\
					FST::RELATION('\'', 2)),\
				FST::NODE()