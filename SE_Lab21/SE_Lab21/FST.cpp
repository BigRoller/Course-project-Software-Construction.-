#include "stdafx.h"

#include "FST.h"
#include <iostream>
#include <cstring>
#include <stdarg.h>

FST::RELATION::RELATION(char c, short nn)
{
	symbol = c;
	nnode = nn;
}

FST::NODE::NODE()
{
	n_relation = 0;
	RELATION* relations = NULL;
}

FST::NODE::NODE(short n, RELATION rel, ...)
{
	
	n_relation = n;
	relations = new RELATION[n];
	/*
	RELATION* p = &rel;
	for (short i = 0; i < n; i++) {
		relations[i] = *(p + 2 * i);
	}
	*/

	va_list factor;
	va_start(factor, rel);
	relations[0] = rel;

	for (int i = 1; i < n; i++) {
		relations[i] = va_arg(factor, RELATION);
	}

	va_end(factor);
}

FST::FST::FST(char* s, short ns, NODE n, ...)
{
	string = s;
	nstates = ns;
	nodes = new NODE[ns];
	va_list factor;
	va_start(factor, n);
	nodes[0] = n;

	for (int i = 1; i < ns; i++) {
		nodes[i] = va_arg(factor, NODE);
	}

	va_end(factor);

	rstates = new short[nstates];

	memset(rstates, 0xff, sizeof(short) * nstates);
	rstates[0] = 0;
	position = -1;
}

bool step(FST::FST& fst, short*& rstates)
{
	bool rc = false;
	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; i++) {
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; j++) {
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}
			}
	}
	return rc;
}

bool FST::execute(FST& fst)
{
	short* rstates = new short[fst.nstates];

	memset(rstates, 0xff, sizeof(short) * fst.nstates);
	short lstring = strlen(fst.string);
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++)
	{
		fst.position++;
		rc = step(fst, rstates);
	}
	delete[] rstates;
	return { rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc };
}

FST::FST fst_integer(
	(char*)"",
	8,
	FST::NODE(1, FST::RELATION('i', 1)),
	FST::NODE(1, FST::RELATION('n', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE(1, FST::RELATION('g', 5)),
	FST::NODE(1, FST::RELATION('e', 6)),
	FST::NODE(1, FST::RELATION('r', 7)),
	FST::NODE()
);

FST::FST fst_string(
	(char*)"",
	7,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('t', 2)),
	FST::NODE(1, FST::RELATION('r', 3)),
	FST::NODE(1, FST::RELATION('i', 4)),
	FST::NODE(1, FST::RELATION('n', 5)),
	FST::NODE(1, FST::RELATION('g', 6)),
	FST::NODE()
);

FST::FST fst_function(
	(char*)L"",
	9,
	FST::NODE(1, FST::RELATION('f', 1)),
	FST::NODE(1, FST::RELATION('u', 2)),
	FST::NODE(1, FST::RELATION('n', 3)),
	FST::NODE(1, FST::RELATION('c', 4)),
	FST::NODE(1, FST::RELATION('t', 5)),
	FST::NODE(1, FST::RELATION('i', 6)),
	FST::NODE(1, FST::RELATION('o', 7)),
	FST::NODE(1, FST::RELATION('n', 8)),
	FST::NODE()
);

FST::FST fst_symbol(
	(char*)L"",
	7,
	FST::NODE(1, FST::RELATION('s', 1)),
	FST::NODE(1, FST::RELATION('y', 2)),
	FST::NODE(1, FST::RELATION('m', 3)),
	FST::NODE(1, FST::RELATION('b', 4)),
	FST::NODE(1, FST::RELATION('o', 5)),
	FST::NODE(1, FST::RELATION('l', 6)),
	FST::NODE()
);

FST::FST fst_byte(
	(char*)L"",
	5,
	FST::NODE(1, FST::RELATION('b', 1)),
	FST::NODE(1, FST::RELATION('y', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('e', 4)),
	FST::NODE()
);

FST::FST fst_declare(
	(char*)L"",
	8,
	FST::NODE(1, FST::RELATION('d', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('c', 3)),
	FST::NODE(1, FST::RELATION('l', 4)),
	FST::NODE(1, FST::RELATION('a', 5)),
	FST::NODE(1, FST::RELATION('r', 6)),
	FST::NODE(1, FST::RELATION('e', 7)),
	FST::NODE()
);

FST::FST fst_return(
	(char*)L"",
	7,
	FST::NODE(1, FST::RELATION('r', 1)),
	FST::NODE(1, FST::RELATION('e', 2)),
	FST::NODE(1, FST::RELATION('t', 3)),
	FST::NODE(1, FST::RELATION('u', 4)),
	FST::NODE(1, FST::RELATION('r', 5)),
	FST::NODE(1, FST::RELATION('n', 6)),
	FST::NODE()
);

FST::FST fst_print(
	(char*)"",
	6,
	FST::NODE(1, FST::RELATION('w', 1)),
	FST::NODE(1, FST::RELATION('r', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('t', 4)),
	FST::NODE(1, FST::RELATION('e', 5)),
	FST::NODE()
);

FST::FST fst_writeln(
	(char*)"",
	10,
	FST::NODE(1, FST::RELATION('w', 1)),
	FST::NODE(1, FST::RELATION('r', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('t', 4)),
	FST::NODE(1, FST::RELATION('e', 5)),
	FST::NODE(1, FST::RELATION('l', 6)),
	FST::NODE(1, FST::RELATION('i', 7)),
	FST::NODE(1, FST::RELATION('n', 8)),
	FST::NODE(1, FST::RELATION('e', 9)),
	FST::NODE()
);

FST::FST fst_writeint(
	(char*)"",
	9,
	FST::NODE(1, FST::RELATION('w', 1)),
	FST::NODE(1, FST::RELATION('r', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('t', 4)),
	FST::NODE(1, FST::RELATION('e', 5)),
	FST::NODE(1, FST::RELATION('i', 6)),
	FST::NODE(1, FST::RELATION('n', 7)),
	FST::NODE(1, FST::RELATION('t', 8)),
	FST::NODE()
);

FST::FST fst_for(
	(char*)"",
	4,
	FST::NODE(1, FST::RELATION('f', 1)),
	FST::NODE(1, FST::RELATION('o', 2)),
	FST::NODE(1, FST::RELATION('r', 3)),
	FST::NODE()
);

FST::FST fst_main(
	(char*)"",
	5,
	FST::NODE(1, FST::RELATION('m', 1)),
	FST::NODE(1, FST::RELATION('a', 2)),
	FST::NODE(1, FST::RELATION('i', 3)),
	FST::NODE(1, FST::RELATION('n', 4)),
	FST::NODE()
);

FST::FST fst_semicolon(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION(';', 1)),
	FST::NODE()
);

FST::FST fst_equally(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('=', 1)),
	FST::NODE()
);

FST::FST fst_comma(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION(',', 1)),
	FST::NODE()
);

FST::FST fst_leftbrace(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('{', 1)),
	FST::NODE()
);

FST::FST fst_bracelet(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('}', 1)),
	FST::NODE()
);

FST::FST fst_lefthesis(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('(', 1)),
	FST::NODE()
);

FST::FST fst_righthesis(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION(')', 1)),
	FST::NODE()
);

FST::FST fst_plus(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('+', 1)),
	FST::NODE()
);

FST::FST fst_minus(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('-', 1)),
	FST::NODE()
);

FST::FST fst_star(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('*', 1)),
	FST::NODE()
);

FST::FST fst_dirslash(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('/', 1)),
	FST::NODE()
);

FST::FST fst_equallyequally(
	(char*)"",
	3,
	FST::NODE(1, FST::RELATION('=', 1)),
	FST::NODE(1, FST::RELATION('=', 2)),
	FST::NODE()
);

FST::FST fst_notequally(
	(char*)"",
	3,
	FST::NODE(1, FST::RELATION('!', 1)),
	FST::NODE(1, FST::RELATION('=', 2)),
	FST::NODE()
);

FST::FST fst_greater(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('>', 1)),
	FST::NODE()
);

FST::FST fst_less(
	(char*)"",
	2,
	FST::NODE(1, FST::RELATION('<', 1)),
	FST::NODE()
);

FST::FST fst_greaterOrEqual(
	(char*)"",
	3,
	FST::NODE(1, FST::RELATION('>', 1)),
	FST::NODE(1, FST::RELATION('=', 2)),
	FST::NODE()
);

FST::FST fst_lessOrEqual(
	(char*)"",
	3,
	FST::NODE(1, FST::RELATION('<', 1)),
	FST::NODE(1, FST::RELATION('=', 2)),
	FST::NODE()
);

FST::FST fst_id(
	(char*)"",
	2,
	FST::NODE(52, FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0), FST::RELATION('e', 0), FST::RELATION('f', 0), FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0), FST::RELATION('l', 0), FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0), FST::RELATION('q', 0), FST::RELATION('r', 0), FST::RELATION('s', 0), FST::RELATION('t', 0), FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0), FST::RELATION('x', 0), FST::RELATION('y', 0), FST::RELATION('z', 0),
		FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1), FST::RELATION('z', 1)),
	FST::NODE()
);

//FST::FST fst_integerlexema(
	//	(char*)"",
	//	2,
	//	FST::NODE(20, FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0), FST::RELATION('0', 0),
	//		FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1)),
	//	FST::NODE()
	//);
	//fst_vector.push_back(&fst_integerlexema);
	//FST::FST fst_integerLiteral(
	//	(char*)"",
	//	4,
	//	FST::NODE(20, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), 
	//								FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 2),
	//								FST::RELATION('1', 3), FST::RELATION('2', 3), FST::RELATION('3', 3), FST::RELATION('4', 3), FST::RELATION('5', 3),
	//								FST::RELATION('6', 3), FST::RELATION('7', 3), FST::RELATION('8', 3), FST::RELATION('9', 3), FST::RELATION('0', 3)),
	//	FST::NODE(20, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
	//								FST::RELATION('6', 1), FST::RELATION('7', 1),
	//								FST::RELATION('1', 3), FST::RELATION('2', 3), FST::RELATION('3', 3), FST::RELATION('4', 3), FST::RELATION('5', 3),
	//								FST::RELATION('6', 3), FST::RELATION('7', 3)),
	//	FST::NODE(1,	FST::RELATION('o', 1)),
	//	FST::NODE()
	//);

FST::FST fst_integerLiteral(
	(char*)"",
	7,
	FST::NODE(21, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1),
		FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('8', 6), FST::RELATION('9', 6),
		FST::RELATION('0', 2), FST::RELATION('0', 6), FST::RELATION('-', 3)),
	FST::NODE(20, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),
		FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('8', 6), FST::RELATION('9', 6), FST::RELATION('0', 6)),
	FST::NODE(1, FST::RELATION('o', 4)),
	FST::NODE(19, FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1),
		FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('8', 6), FST::RELATION('9', 6),
		FST::RELATION('0', 2)),
	FST::NODE(14, FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5), FST::RELATION('5', 5), FST::RELATION('6', 5), FST::RELATION('7', 5),
		FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6)),
	FST::NODE(16, FST::RELATION('1', 5), FST::RELATION('2', 5), FST::RELATION('3', 5), FST::RELATION('4', 5), FST::RELATION('5', 5), FST::RELATION('6', 5), FST::RELATION('7', 5), FST::RELATION('0', 5),
		FST::RELATION('1', 6), FST::RELATION('2', 6), FST::RELATION('3', 6), FST::RELATION('4', 6), FST::RELATION('5', 6), FST::RELATION('6', 6), FST::RELATION('7', 6), FST::RELATION('0', 6)),
	FST::NODE()
);

FST::FST fst_stringLiteral(
	(char*)"",
	4,
	FST::NODE(2, FST::RELATION('\"', 1), FST::RELATION('\"', 2)),
	FST::NODE(144, FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2), FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),
		FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),
		FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), FST::RELATION('y', 2), FST::RELATION('z', 2),
		FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1), FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1), FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1), FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1), FST::RELATION('y', 1), FST::RELATION('z', 1),
		FST::RELATION('à', 2), FST::RELATION('á', 2), FST::RELATION('â', 2), FST::RELATION('ã', 2), FST::RELATION('ä', 2), FST::RELATION('å', 2), FST::RELATION('¸', 2), FST::RELATION('æ', 2), FST::RELATION('ç', 2), FST::RELATION('è', 2), FST::RELATION('é', 2), FST::RELATION('ê', 2), FST::RELATION('ë', 2), FST::RELATION('ì', 2), FST::RELATION('í', 2), FST::RELATION('î', 2), FST::RELATION('ï', 2), FST::RELATION('ð', 2), FST::RELATION('ñ', 2), FST::RELATION('ò', 2), FST::RELATION('ó', 2), FST::RELATION('ô', 2), FST::RELATION('õ', 2), FST::RELATION('ö', 2), FST::RELATION('÷', 2), FST::RELATION('ø', 2), FST::RELATION('ù', 2), FST::RELATION('ú', 2), FST::RELATION('û', 2), FST::RELATION('ü', 2), FST::RELATION('ý', 2), FST::RELATION('þ', 2), FST::RELATION('ÿ', 2),
		FST::RELATION('à', 1), FST::RELATION('á', 1), FST::RELATION('â', 1), FST::RELATION('ã', 1), FST::RELATION('ä', 1), FST::RELATION('å', 1), FST::RELATION('¸', 1), FST::RELATION('æ', 1), FST::RELATION('ç', 1), FST::RELATION('è', 1), FST::RELATION('é', 1), FST::RELATION('ê', 1), FST::RELATION('ë', 1), FST::RELATION('ì', 1), FST::RELATION('í', 1), FST::RELATION('î', 1), FST::RELATION('ï', 1), FST::RELATION('ð', 1), FST::RELATION('ñ', 1), FST::RELATION('ò', 1), FST::RELATION('ó', 1), FST::RELATION('ô', 1), FST::RELATION('õ', 1), FST::RELATION('ö', 1), FST::RELATION('÷', 1), FST::RELATION('ø', 1), FST::RELATION('ù', 1), FST::RELATION('ú', 1), FST::RELATION('û', 1), FST::RELATION('ü', 1), FST::RELATION('ý', 1), FST::RELATION('þ', 1), FST::RELATION('ÿ', 1),
		FST::RELATION(' ', 1), FST::RELATION(' ', 2), FST::RELATION('-', 1), FST::RELATION('-', 2), FST::RELATION(',', 1), FST::RELATION(',', 2)),
	FST::NODE(1, FST::RELATION('\"', 3)),
	FST::NODE()
);

FST::FST fst_symbolLiteral(
	(char*)"",
	4,
	FST::NODE(1, FST::RELATION('\'', 1)),
	FST::NODE(59, FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2),
		FST::RELATION('f', 2), FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2),
		FST::RELATION('k', 2), FST::RELATION('l', 2), FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2),
		FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2), FST::RELATION('s', 2), FST::RELATION('t', 2),
		FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2), FST::RELATION('y', 2),
		FST::RELATION('z', 2), FST::RELATION('à', 2), FST::RELATION('á', 2), FST::RELATION('â', 2), FST::RELATION('ã', 2),
		FST::RELATION('ä', 2), FST::RELATION('å', 2), FST::RELATION('¸', 2), FST::RELATION('æ', 2), FST::RELATION('ç', 2),
		FST::RELATION('è', 2), FST::RELATION('é', 2), FST::RELATION('ê', 2), FST::RELATION('ë', 2), FST::RELATION('ì', 2),
		FST::RELATION('í', 2), FST::RELATION('î', 2), FST::RELATION('ï', 2), FST::RELATION('ð', 2), FST::RELATION('ñ', 2),
		FST::RELATION('ò', 2), FST::RELATION('ø', 2), FST::RELATION('ó', 2), FST::RELATION('ô', 2), FST::RELATION('õ', 2),
		FST::RELATION('ö', 2), FST::RELATION('÷', 2), FST::RELATION('ù', 2), FST::RELATION('ú', 2), FST::RELATION('û', 2),
		FST::RELATION('ü', 2), FST::RELATION('ý', 2), FST::RELATION('þ', 2), FST::RELATION('ÿ', 2)),
	FST::NODE(1, FST::RELATION('\'', 3)),
	FST::NODE()
);