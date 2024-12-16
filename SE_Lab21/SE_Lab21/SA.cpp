#include "stdafx.h"
#include "SA.h"

void SA::performSemanticAnalysis(LT::LexTable lextable, IT::IdTable idtable)
{
	// Обработка соответствия формальных и фактических параметров функций
	for (int i = 0; i < lextable.size; i++) {
		LT::Entry function;
		int currentParametersCount = 0;
		int counter = 0;
		if (lextable.table[i].lexema == LEX_FUNCTION) {
			function = lextable.table[i + 1];
			std::vector<LT::Entry> entryVector;
			int index = i + 1;
			while (lextable.table[index].lexema != LEX_LEFTHESIS) { index++; }
			for (index++; lextable.table[index].lexema != LEX_RIGHTHESIS; index++) {
				if (lextable.table[index].lexema == LEX_ID) {
					entryVector.push_back(lextable.table[index]);
				}
			}
			currentParametersCount = entryVector.size();

			if (currentParametersCount != 0) {
				std::vector<LT::Entry> copyStack(entryVector);
				for (int j = i + 2; j < lextable.size; j++) {
					if (lextable.table[j].stringLexema == function.stringLexema) {
						for (int k = j + 1; lextable.table[k].lexema != LEX_RIGHTHESIS; k++) {
 							if (lextable.table[k].lexema == LEX_ID || lextable.table[k].lexema == LEX_LITERAL) {
								if (currentParametersCount == counter) {
									throw ERROR_THROW_IN(204, lextable.table[j].sn, -1)
								}
								// string => string
								if (IT::GetEntry(idtable, entryVector[counter].idxTI + 1).iddatatype == IT::STR) {
									if (IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::STR) {
										counter++;
									}
									else {
										throw ERROR_THROW_IN(204, lextable.table[j].sn, -1)
									}
								} 
								// byte, symbol, integer => integer
								else if (IT::GetEntry(idtable, entryVector[counter].idxTI + 1).iddatatype == IT::INT) {
									if (IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::INT
										 || IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::CHR
										 || IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::BYTE
										 ) {
										counter++;
									}
									else {
										throw ERROR_THROW_IN(204, lextable.table[j].sn, -1)
									}
								}
								// byte, symbol => symbol
								else if (IT::GetEntry(idtable, entryVector[counter].idxTI + 1).iddatatype == IT::CHR) {
									if (IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::CHR
										|| IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::BYTE
										) {
										counter++;
									}
									else {
										throw ERROR_THROW_IN(204, lextable.table[j].sn, -1)
									}
								}
								// symbol, byte => byte
								else if (IT::GetEntry(idtable, entryVector[counter].idxTI + 1).iddatatype == IT::BYTE) {
									if (IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::BYTE
										|| IT::GetEntry(idtable, lextable.table[k].idxTI + 1).iddatatype == IT::CHR
										) {
										counter++;
									}
									else {
										throw ERROR_THROW_IN(204, lextable.table[j].sn, -1)
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Обработка допустимости типов в операциях присваивания
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexema == LEX_EQUALLY) {
			int leftOperand = i - 1;
			// string => string
			if (IT::GetEntry(idtable, lextable.table[leftOperand].idxTI + 1).iddatatype == IT::STR) {
				for (int j = i + 1; lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
						if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).idtype == IT::F) { //////////
							while (lextable.table[j].lexema != LEX_RIGHTHESIS) { j++; }
						}
					}
						if (lextable.table[j].stringLexema == "-") {
							throw ERROR_THROW_IN(205, lextable.table[i].sn, -1)
						}
						else if (lextable.table[j].stringLexema == "+") {
							throw ERROR_THROW_IN(205, lextable.table[i].sn, -1) // пока не поддерживается
						}
						else if (lextable.table[j].stringLexema == "*") {
							throw ERROR_THROW_IN(205, lextable.table[i].sn, -1)
						}
						else if (lextable.table[j].stringLexema == "/") {
							throw ERROR_THROW_IN(205, lextable.table[i].sn, -1)
						}
				}

				for (int j = i + 1; lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
						if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).idtype == IT::F) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 2).iddatatype != IT::STR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
							}
							while (lextable.table[j].lexema != LEX_RIGHTHESIS) { j++; }
						}
						if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype != IT::STR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
							}
						}
					}
				}
			}
			// symbol, byte, integer => integer (+, -, *, /)
			else if (IT::GetEntry(idtable, lextable.table[leftOperand].idxTI + 1).iddatatype == IT::INT) {
				for (int j = i + 1; lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
						if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).idtype == IT::F) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 2).iddatatype == IT::STR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
							}
							while (lextable.table[j].lexema != LEX_RIGHTHESIS) { j++; }
						}
						if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype != IT::INT) {
								if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype == IT::STR) {
									throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
								}
							}
						}
					}
				}
			}
			// symbol, byte => byte (+, -, *, /)
			else if (IT::GetEntry(idtable, lextable.table[leftOperand].idxTI + 1).iddatatype == IT::BYTE) {
				for (int j = i + 1; lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
						if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).idtype == IT::F) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 2).iddatatype == IT::STR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
							}
							while (lextable.table[j].lexema != LEX_RIGHTHESIS) { j++; }
						}
						if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype != IT::BYTE 
								&& IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype != IT::CHR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)	
							}
						}
					}
				}
			}
			// byte, symbol => symbol (+, -, *, /)
			else if (IT::GetEntry(idtable, lextable.table[leftOperand].idxTI + 1).iddatatype == IT::CHR) {
				for (int j = i + 1; lextable.table[j].lexema != LEX_SEMICOLON; j++) {
					if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
						if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).idtype == IT::F) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 2).iddatatype == IT::STR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
							}
							while (lextable.table[j].lexema != LEX_RIGHTHESIS) { j++; }
						}
						if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL) {
							if (IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype != IT::BYTE
								&& IT::GetEntry(idtable, lextable.table[j].idxTI + 1).iddatatype != IT::CHR) {
								throw ERROR_THROW_IN(206, lextable.table[i].sn, -1)
							}
						}
					}
				}
			}
		}
	}

	// Проверка значений возвращающий значение функций
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexema == LEX_FUNCTION) {
			LT::Entry function = lextable.table[i + 1];
			int index;
			for (index = i + 1; lextable.table[index].lexema != LEX_RIGHTHESIS; index++) {}
			if (lextable.table[index + 1].lexema == LEX_LEFTBRACE) {
				for (index = i + 1; lextable.table[index].lexema != LEX_RETURN; index++) {}
				index++;
				if (IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype
					!= IT::GetEntry(idtable, function.idxTI + 1).iddatatype)
				{
					if (IT::GetEntry(idtable, function.idxTI + 1).iddatatype == IT::STR) {
						if (IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype != IT::STR) {
							throw ERROR_THROW_IN(207, function.sn, -1)
						}
					}
					else if (IT::GetEntry(idtable, function.idxTI + 1).iddatatype == IT::INT) {
						if (IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype == IT::STR) {
							throw ERROR_THROW_IN(207, function.sn, -1)
						}
					}
					else if (IT::GetEntry(idtable, function.idxTI + 1).iddatatype == IT::BYTE) {
						if (IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype == IT::STR 
							|| IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype == IT::INT) {
							throw ERROR_THROW_IN(207, function.sn, -1)
						}
					}
					else if (IT::GetEntry(idtable, function.idxTI + 1).iddatatype == IT::CHR) {
						if (IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype == IT::STR
							|| IT::GetEntry(idtable, lextable.table[index].idxTI + 1).iddatatype == IT::INT) {
							throw ERROR_THROW_IN(207, function.sn, -1)
						}
					}
				}
			}
		}
	}

	// Проверка аргументов вывода в стандартный поток
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].lexema == LEX_PRINT) {
			if (lextable.table[i].stringLexema == "write") {
				if (IT::GetEntry(idtable, lextable.table[i + 1].idxTI + 1).iddatatype != IT::STR) {
					throw ERROR_THROW_IN(209, lextable.table[i].sn, -1);
				}
			}
			else if (lextable.table[i].stringLexema == "writeline") {
				if (IT::GetEntry(idtable, lextable.table[i + 1].idxTI + 1).iddatatype != IT::STR) {
					throw ERROR_THROW_IN(209, lextable.table[i].sn, -1);
				}
			}
			else if (lextable.table[i].stringLexema == "writeint") {
				if (IT::GetEntry(idtable, lextable.table[i + 1].idxTI + 1).iddatatype == IT::STR) {
					throw ERROR_THROW_IN(209, lextable.table[i].sn, -1);
				}
			}
		}
	}
}