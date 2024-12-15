#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include "FST.h"

LT::LexTable LT::Create(int size)
{
	LT::LexTable table;
	table.size = 0;
	if (size < LT_MAXSIZE) {
		table.maxsize = size;
	}
	else {
		throw ERROR_THROW(105);
	}
	table.table = new LT::Entry[size];
	return table;
}

void LT::Add(LexTable& lextable, Entry& entry)
{
	if (lextable.size >= lextable.maxsize) {
		Entry* newTable = new Entry[lextable.size * 2];
		LexTable newIdtable = { lextable.size * 2, lextable.size, newTable };
		for (int i = 0; i < lextable.size; i++) {
			newTable[i].idxTI= lextable.table[i].idxTI;
			newTable[i].lexema = lextable.table[i].lexema;
			newTable[i].operation = lextable.table[i].operation;
			newTable[i].sn = lextable.table[i].sn;
			newTable[i].stringLexema = lextable.table[i].stringLexema;
		}
		LT::Delete(lextable);
		lextable = newIdtable;
	}
	lextable.table[lextable.size++] = entry;
	return;
}

LT::Entry LT::GetEntry(LexTable& lextable, int n)
{
	return lextable.table[--n];
}

void LT::Delete(LexTable& lextable)
{
	delete[] lextable.table;
	return;
}