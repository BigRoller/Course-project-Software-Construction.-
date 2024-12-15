#include "stdafx.h"
#include "IT.h"
#include "Error.h"

IT::IdTable IT::Create(int size)
{
	IT::IdTable idtable;
	idtable.size = 0;
	idtable.literalsCount = 0;
	if (size < TI_MAXSIZE) {
		idtable.maxsize = size;
	}
	else {
		throw ERROR_THROW(103);
	}
	idtable.table = new IT::Entry[size];
	return idtable;
}

void IT::Add(IdTable& idtable, Entry& entry)
{
	if (idtable.size >= idtable.maxsize) {
		Entry* newTable = new Entry[idtable.size * 2];
		IdTable newIdtable = { idtable.size * 2, idtable.size, newTable, idtable.literalsCount};
		for (int i = 0; i < idtable.size; i++) {
			newTable[i].id = idtable.table[i].id;
			newTable[i].iddatatype = idtable.table[i].iddatatype;
			newTable[i].idtype = idtable.table[i].idtype;
			newTable[i].idxfirstLE = idtable.table[i].idxfirstLE;
			newTable[i].sufix = idtable.table[i].sufix;
			newTable[i].value = idtable.table[i].value;
		}
		IT::Delete(idtable);
		idtable = newIdtable;
	}
	idtable.table[idtable.size++] = entry;
	return;
}

IT::Entry IT::GetEntry(IdTable& idtable, int n)
{
 	return idtable.table[n - 1];
}

int IT::IsId(IdTable& idtable, std::string id)
{
	for (int i = idtable.size - 1; i >= 0; i--) {
		if (idtable.table[i].id == id) {
			return i;
		}
	}
	return TI_NULLIDX;
}

void IT::Delete(IdTable& idtable)
{
	delete[] idtable.table;
	return;
}