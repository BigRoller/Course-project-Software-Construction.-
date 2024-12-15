#include "stdafx.h"
#include "Lexer.h"

extern FST::FST fst_integer;
extern FST::FST fst_string;
extern FST::FST fst_function;
extern FST::FST fst_symbol;
extern FST::FST fst_byte;
extern FST::FST fst_declare;
extern FST::FST fst_return;
extern FST::FST fst_print;
extern FST::FST fst_writeint;
extern FST::FST fst_writeln;
extern FST::FST fst_for;
extern FST::FST fst_main;
extern FST::FST fst_semicolon;
extern FST::FST fst_equally;
extern FST::FST fst_comma;
extern FST::FST fst_leftbrace;
extern FST::FST fst_bracelet;
extern FST::FST fst_lefthesis;
extern FST::FST fst_righthesis;
extern FST::FST fst_plus;
extern FST::FST fst_minus;
extern FST::FST fst_star;
extern FST::FST fst_dirslash;
extern FST::FST fst_equallyequally;
extern FST::FST fst_notequally;
extern FST::FST fst_greater;
extern FST::FST fst_less;
extern FST::FST fst_greaterOrEqual;
extern FST::FST fst_lessOrEqual;
extern FST::FST fst_id;
extern FST::FST fst_integerLiteral;
extern FST::FST fst_symbolLiteral;
extern FST::FST fst_stringLiteral;

std::string GetLexAndIdTable(LT::LexTable& lextable, IT::IdTable& idtable, char* str)
{
	auto getArray = [](std::string sen) {
		std::vector<std::string> words;
		std::string word;
		bool flag = false;

		for (int i = 0; i < sen.length(); i++) {
			// Обработка символа новой строки
			if (sen[i] == '\n') {
				if (!word.empty()) {
					words.push_back(word);
				}
				// Проверяем, добавляли ли мы уже новую строку
				if (words.empty() || words.back() != "\n") {
					words.push_back("\n");
				}
				word.clear();
				continue;
			}

			// Обработка кавычек
			if (sen[i] == '\"') {
				flag = !flag;
				word += sen[i]; // Добавляем кавычку в любом случае
				continue;
			}

			// Если мы внутри кавычек, добавляем символы
			if (flag) {
				word += sen[i];
				continue;
			}

			// Обработка операторов сравнения
			if (i < sen.length() - 1) {
				std::string op = sen.substr(i, 2);
				if (op == "==" || op == "!=" || op == ">=" || op == "<=") {
					if (!word.empty()) {
						words.push_back(word);
						word.clear();
					}
					words.push_back(op); // Добавляем оператор сравнения
					i++; // Пропускаем следующий символ, так как он уже обработан
					continue;
				}
			}

			// Обработка других символов
			if (sen[i] != ' ') {
				// Проверяем, является ли символ разделителем
				if (sen[i] == ';' || sen[i] == ',' || sen[i] == '{' ||
					sen[i] == '}' || sen[i] == '(' || sen[i] == ')' ||
					sen[i] == '+' || sen[i] == '-' || sen[i] == '*' ||
					sen[i] == '/' || sen[i] == '=' || sen[i] == '>' || sen[i] == '<') {

					if (!word.empty()) {
						words.push_back(word);
						word.clear();
					}
					words.push_back(std::string(1, sen[i])); // Добавляем текущий разделитель
				}
				else {
					word += sen[i]; // Добавляем к слову, если это не разделитель
				}
			}
			else {
				// Если пробел и слово не пустое, добавляем его в вектор
				if (!word.empty()) {
					words.push_back(word);
					word.clear();
				}
			}
		}

		// Добавляем последнее слово, если оно есть
		if (!word.empty()) {
			words.push_back(word);
		}

		return words;
		};





	std::string wstr(str);
	std::vector<std::string> array = getArray(wstr);


	std::string buff;

	std::stack<std::pair<std::list<IT::Entry>, std::string>> idEntryStack;

	std::pair<std::list<IT::Entry>, std::string> globalEntryList;
	globalEntryList.second = "GLOBAL";
	
	idEntryStack.push(globalEntryList);

	std::vector<FST::FST*> fst_vector;

	fst_vector.push_back(&fst_integer);
	fst_vector.push_back(&fst_string);
	fst_vector.push_back(&fst_function);
	fst_vector.push_back(&fst_symbol);
	fst_vector.push_back(&fst_byte);
	fst_vector.push_back(&fst_declare);
	fst_vector.push_back(&fst_return);
	fst_vector.push_back(&fst_print);
	fst_vector.push_back(&fst_writeint);
	fst_vector.push_back(&fst_writeln);
	fst_vector.push_back(&fst_for);
	fst_vector.push_back(&fst_main);
	fst_vector.push_back(&fst_semicolon);
	fst_vector.push_back(&fst_equally);
	fst_vector.push_back(&fst_comma);
	fst_vector.push_back(&fst_leftbrace);
	fst_vector.push_back(&fst_bracelet);
	fst_vector.push_back(&fst_lefthesis);
	fst_vector.push_back(&fst_righthesis);
	fst_vector.push_back(&fst_plus);
	fst_vector.push_back(&fst_minus);
	fst_vector.push_back(&fst_star);
	fst_vector.push_back(&fst_dirslash);
	fst_vector.push_back(&fst_equallyequally);
	fst_vector.push_back(&fst_notequally);
	fst_vector.push_back(&fst_greater);
	fst_vector.push_back(&fst_less);
	fst_vector.push_back(&fst_greaterOrEqual);
	fst_vector.push_back(&fst_lessOrEqual);
	fst_vector.push_back(&fst_id);
	fst_vector.push_back(&fst_integerLiteral);
	fst_vector.push_back(&fst_stringLiteral);
	fst_vector.push_back(&fst_symbolLiteral);

	int iteration = 0;
	int i = 0;
	int lineNumber = 1;
	int lineIndex = 1;
	for (std::string word : array) {
		LT::Entry ltentry = *(new LT::Entry());
		IT::Entry itentry = *(new IT::Entry());
		ltentry.idxTI = LT_TI_NULLIDX;
		ltentry.operation = ltentry.NOT_OPERATOR;
		for (auto fst : fst_vector) {
			fst->string = (char*)word.c_str();
			fst->position = -1;
			fst->rstates[0] = 0;
		}
		if (word == "\n") {
			lineIndex = 0;
			buff += '\n';
			lineNumber++;
			i--;
		}
		else if (execute(fst_integer)) {
			buff += LEX_INTEGER;
		}
		else if (execute(fst_string)) {
			buff += LEX_STRING;
		}
		else if (execute(fst_symbol)) {
			buff += LEX_INTEGER;
		}
		else if (execute(fst_byte)) {
			buff += LEX_STRING;
		}
		else if (execute(fst_function)) {
			buff += LEX_FUNCTION;
		}
		else if (execute(fst_declare)) {
			buff += LEX_DECLARE;
		}
		else if (execute(fst_return)) {
			buff += LEX_RETURN;
		}
		else if (execute(fst_print)) {
			buff += LEX_PRINT;
		}
		else if (execute(fst_writeint)) {
			buff += LEX_PRINT;
		}
		else if (execute(fst_writeln)) {
			buff += LEX_PRINT;
		}
		else if (execute(fst_for)) { 
			buff += LEX_FOR;
		}
		else if (execute(fst_main)) {
			buff += LEX_MAIN;
		}
		else if (execute(fst_semicolon)) {
			buff += LEX_SEMICOLON;
		}
		else if (execute(fst_comma)) {
			buff += LEX_COMMA;
		}
		else if (execute(fst_leftbrace)) {
			buff += LEX_LEFTBRACE;
			// добавление суффикса и параметров к области видимости
 			int j = iteration;
			if (lextable.table[lextable.size - 1].lexema == LEX_RIGHTHESIS) {
				for (;j >= 0 ; j--) {
					if (array[j] == "main") {
						j--;
						break;
					}
					else if (array[j] == "function") {
						break;
					}
					else if (array[j] == "for") {
						break;
					}
				}
				if (j < 0) {
					throw ERROR_THROW(0);
				}
			} 

			std::pair<std::list<IT::Entry>, std::string> newList;
			if (array[j] != "for") {
				newList.second = array[j + 1];
			}
			else {
				newList.second = array[j];
			}
			idEntryStack.push(newList);
			//for (int j = idtable.size - 1; j >= 0 && idtable.table[j].idtype == IT::P; j--) {
			//	idEntryStack.top().first.push_back(idtable.table[j]);
			//}
			if (lextable.table[i - 1].lexema == LEX_RIGHTHESIS) {
				for (int j = i - 1; j >= 0 && lextable.table[j].lexema != LEX_LEFTHESIS; j--) {
					if (lextable.table[j].lexema == LEX_ID && lextable.table[j - 1].lexema == LEX_INTEGER) {
						idEntryStack.top().first.push_back(idtable.table[LT::GetEntry(lextable, j + 1).idxTI]);
					}
				}

			}

		}
		else if (execute(fst_bracelet)) {
			buff += LEX_BRACELET;
			// проверка на объявление переменных с одинаковыми названиями в локальной области видимости
			std::stack<std::pair<std::list<IT::Entry>, std::string>> copyStack(idEntryStack);
			while (!copyStack.empty()) {
				std::pair<std::list<IT::Entry>, std::string> list = copyStack.top();
				for (std::list<IT::Entry>::iterator it1 = list.first.begin(); it1 != list.first.end(); ++it1) {
					std::list<IT::Entry>::iterator it2 = it1;
					++it2;
					while (it2 != list.first.end()) {
						if (it1->id == it2->id) {
							throw ERROR_THROW_IN(201, LT::GetEntry(lextable, it1->idxfirstLE + 1).sn, -1);
						}
						++it2;
					}
				}
				copyStack.pop(); 
			}
			idEntryStack.pop();
			if (idEntryStack.size() == 1) {
				idEntryStack.top().second = "GLOBAL";
			}
			ltentry.operation = ltentry.FIRST;
		}
		else if (execute(fst_lefthesis)) {
			buff += LEX_LEFTHESIS;
			ltentry.operation = ltentry.FIRST;
		}
		else if (execute(fst_righthesis)) {
			buff += LEX_RIGHTHESIS;
			ltentry.operation = ltentry.FIRST;
		}
		else if (execute(fst_plus)) {
			buff += LEX_OPERATOR;
			ltentry.operation = ltentry.SECOND;
		}
		else if (execute(fst_minus)) {
			if (LT::GetEntry(lextable, i).lexema == LEX_ID || LT::GetEntry(lextable, i).lexema == LEX_LITERAL) {
				buff += LEX_OPERATOR;
				ltentry.operation = ltentry.SECOND;
			}
			else {
				buff += LEX_UNARY_MINUS;
				ltentry.operation = ltentry.ZERO;
			}
		}
		else if (execute(fst_star)) {
			buff += LEX_OPERATOR;
			ltentry.operation = ltentry.THIRD;
		}
		else if (execute(fst_dirslash)) {
			buff += LEX_OPERATOR;
			ltentry.operation = ltentry.THIRD;
		}
		else if (execute(fst_equally)) {
			buff += LEX_EQUALLY;
		}
		else if (execute(fst_equallyequally)) {
			buff += LEX_COMPRASION_OPERATOR;
			}
		else if (execute(fst_notequally)) {
			buff += LEX_COMPRASION_OPERATOR;
			}
		else if (execute(fst_greater)) {
			buff += LEX_COMPRASION_OPERATOR;
		}
		else if (execute(fst_less)) {
			buff += LEX_COMPRASION_OPERATOR;
			}
		else if (execute(fst_greaterOrEqual)) {
			buff += LEX_COMPRASION_OPERATOR;
			}
		else if (execute(fst_lessOrEqual)) {
			buff += LEX_COMPRASION_OPERATOR;
			}
		else if (execute(fst_id)) {
			if (word.length() > MAX_ID_LENGTH) {
				throw ERROR_THROW_IN(200, lineNumber, lineIndex)
			}

			bool isSignature = false;
			// Проверка на сигнатуру
			if (i >= 4 && (LT::GetEntry(lextable, i - 3).lexema == LEX_FUNCTION || LT::GetEntry(lextable, i - 1).lexema == LEX_COMMA)) {
				int index = i - 1;
				while (index > 0 && LT::GetEntry(lextable, index + 1).lexema != LEX_FUNCTION) { index--; }
				if (index >= 2 && LT::GetEntry(lextable, index - 1).lexema == LEX_DECLARE) {
					isSignature = true;
				}
			}

			bool isFind = false;
			if (!isSignature) {
			// присвоение индекса первого вхождения индентификаторам, которые были уже объявлены
			if (i > 0 && LT::GetEntry(lextable, i - 1).lexema != LEX_DECLARE && LT::GetEntry(lextable, i).lexema != LEX_FUNCTION)
			{
				std::stack<std::pair<std::list<IT::Entry>, std::string>> copyStack(idEntryStack);
				while (!copyStack.empty() && !isFind) {
					std::pair<std::list<IT::Entry>, std::string> list = copyStack.top();
					for (std::list<IT::Entry>::iterator it = list.first.begin(); it != list.first.end(); ++it) {
						if (word == it->id
							&& (LT::GetEntry(lextable, it->idxfirstLE - 1).lexema == LEX_DECLARE
								|| it->idtype == IT::P
								|| LT::GetEntry(lextable, it->idxfirstLE).lexema == LEX_FUNCTION))
						{
							ltentry.idxTI = LT::GetEntry(lextable, it->idxfirstLE + 1).idxTI;
							isFind = true;
							break;
						}
					}
					copyStack.pop();
				}
			}
			}
			if (!isFind)
			{
				bool isInitializationed = false;
				// Проверка локальной области видимости
				std::list<IT::Entry> entryList = idEntryStack.top().first;
				std::list<IT::Entry>::iterator findid = entryList.begin();
				if (!isSignature) {
					for (; findid != entryList.end(); findid++) {
						if (i > 1 && findid->id == word && LT::GetEntry(lextable, i - 1).lexema != LEX_DECLARE
							&& LT::GetEntry(lextable, findid->idxfirstLE - 1).lexema == LEX_DECLARE
							|| findid->id == word && findid->idtype == IT::P) {
							break;
						}
					}
				}

				if (findid == entryList.end() || isSignature) {
					itentry.sufix = idEntryStack.top().second;
					ltentry.idxTI = idtable.size;
					if (i >= 2 && LT::GetEntry(lextable, i - 1).lexema == LEX_DECLARE) {
						itentry.idtype = IT::V;
						if (LT::GetEntry(lextable, i).stringLexema == "integer") {
							itentry.iddatatype = IT::INT;
						}
						else if (LT::GetEntry(lextable, i).stringLexema == "string") {
							itentry.iddatatype = IT::STR;
						}
						else if (LT::GetEntry(lextable, i).stringLexema == "byte") {
							itentry.iddatatype = IT::BYTE;
						}
						else if (LT::GetEntry(lextable, i).stringLexema == "symbol") {
							itentry.iddatatype = IT::CHR;
						}
						else {
							throw ERROR_THROW(107)
						}
						isInitializationed = true;
					}

					else if (i >= 2 && LT::GetEntry(lextable, i).lexema == LEX_FUNCTION) {
						itentry.idtype = IT::F;
						if (LT::GetEntry(lextable, i - 1).stringLexema == "integer") {
							itentry.iddatatype = IT::INT;
						}
						else if (LT::GetEntry(lextable, i - 1).stringLexema == "string") {
							itentry.iddatatype = IT::STR;
						}
						else if (LT::GetEntry(lextable, i).stringLexema == "byte") {
							itentry.iddatatype = IT::BYTE;
						}
						else if (LT::GetEntry(lextable, i).stringLexema == "symbol") {
							itentry.iddatatype = IT::CHR;
						}
						else {
							throw ERROR_THROW(107)
						}
						isInitializationed = true;

					}
					else if (i >= 4) {
						if (LT::GetEntry(lextable, i - 3).lexema == LEX_FUNCTION || LT::GetEntry(lextable, i - 1).lexema == LEX_COMMA) {
							int index = i;
							for (; index >= 0 && LT::GetEntry(lextable, index).lexema != LEX_FUNCTION; index--) {}
							itentry.sufix = LT::GetEntry(lextable, index + 1).stringLexema;
							itentry.idtype = IT::P;
							if (LT::GetEntry(lextable, i).stringLexema == "integer") {
								itentry.iddatatype = IT::INT;
							}
							else if (LT::GetEntry(lextable, i).stringLexema == "string") {
								itentry.iddatatype = IT::STR;
							}
							else if (LT::GetEntry(lextable, i).stringLexema == "byte") {
								itentry.iddatatype = IT::BYTE;
							}
							else if (LT::GetEntry(lextable, i).stringLexema == "symbol") {
								itentry.iddatatype = IT::CHR;
							}
							else {
								throw ERROR_THROW(107)
							}
							isInitializationed = true;
						}
					}
					if (isInitializationed) {
						itentry.idxfirstLE = i;
						itentry.id = word;
						itentry.scope = idEntryStack.size();
						if (itentry.idtype != IT::P) {
							idEntryStack.top().first.push_back(itentry);
						}
						IT::Add(idtable, itentry);
					}
					else {
						throw ERROR_THROW_IN(202, lineNumber, lineIndex)
					}
				}
			}
			buff += LEX_ID;
		}

		else if (execute(fst_integerLiteral)) {
			ltentry.idxTI = idtable.size;
			itentry.idtype = IT::L;
 			itentry.idxfirstLE = i;
			if (LT::GetEntry(lextable, i).lexema != LEX_UNARY_MINUS) {
				if (word.length() > 2 && word[0] == '0' && word[1] == 'o') {
					std::string newStr = word.substr(2);
					if (newStr.length() <= 9) {
						long long num = stoll(newStr, nullptr, 8);
						if (num <= 255) {
							itentry.value.vbyte = num;
							itentry.iddatatype = IT::BYTE;
						}
						else if (num <= INT_MAX) {
							itentry.value.vint = num;
							itentry.iddatatype = IT::INT;
						}
						else {
							itentry.value.vint = INT_MAX;
							itentry.iddatatype = IT::INT;
						}
					}
					else {
						itentry.value.vint = INT_MAX;
						itentry.iddatatype = IT::INT;
					}
				}
				else {
					if (word.length() <= 9) {
						long long num = stoll(word);
						if (num <= 255) {
							itentry.value.vbyte = num;
							itentry.iddatatype = IT::BYTE;
						}
						else if (num <= INT_MAX) {
							itentry.value.vint = num;
							itentry.iddatatype = IT::INT;
						}
						else {
							itentry.value.vint = INT_MAX;
							itentry.iddatatype = IT::INT;
						}
					}
					else {
						itentry.value.vint = INT_MAX;
						itentry.iddatatype = IT::INT;
					}
				}
				itentry.id = word;
			}
			else {
				if (word.length() > 3 && word[0] == '0' && word[1] == 'o') {
					std::string newStr = "-";
					newStr += word.substr(2);
					if (newStr.length() <= 10) {
						long long num = stoll(newStr, nullptr, 8);
						if (num >= INT_MIN) {
							itentry.value.vint = num;
							itentry.iddatatype = IT::INT;
						}
						else {
							itentry.value.vint = INT_MIN;
							itentry.iddatatype = IT::INT;
						}
					}
					else {
						itentry.value.vint = INT_MIN;
						itentry.iddatatype = IT::INT;
					}
				}
				else {
					if (word.length() <= 10) {
						long long num = stoll(word);
						if (num >= INT_MIN) {
							itentry.value.vint = num;
							itentry.iddatatype = IT::INT;
						}
						else {
							itentry.value.vint = INT_MIN;
							itentry.iddatatype = IT::INT;
						}
					}
					else {
						itentry.value.vint = INT_MIN;
						itentry.iddatatype = IT::INT;
					}
				}
				itentry.id = "-" + word;
			}
			itentry.sufix = idEntryStack.top().second;
			itentry.literalNum = ++idtable.literalsCount;
			itentry.scope = idEntryStack.size();
			IT::Add(idtable, itentry);
			buff += LEX_LITERAL;
		}
		else if (execute(fst_stringLiteral)) {
			if (LT::GetEntry(lextable, i).lexema != LEX_UNARY_MINUS) {
				ltentry.idxTI = idtable.size;
				itentry.id = word;
				itentry.idtype = IT::L;
				itentry.idxfirstLE = i;
				itentry.value.vstr.str = word.substr(1, word.length() - 2);
				if (itentry.id.size() > MAX_LITERAL_LENGTH) {
					throw ERROR_THROW_IN(203, lineNumber, lineIndex)
				}
				itentry.value.vstr.len = itentry.id.size();
				itentry.iddatatype = IT::STR;
				itentry.sufix = idEntryStack.top().second;
				itentry.literalNum = ++idtable.literalsCount;
				itentry.scope = idEntryStack.size();
				IT::Add(idtable, itentry);
				buff += LEX_LITERAL;
			}
			else {
				throw ERROR_THROW_IN(208, lineNumber, lineIndex)
			}
		}
		else if (execute(fst_symbolLiteral)) {
			if (LT::GetEntry(lextable, i).lexema != LEX_UNARY_MINUS) {
			ltentry.idxTI = idtable.size;
			itentry.id = word;
			itentry.idtype = IT::L;
			itentry.idxfirstLE = i;
			itentry.value.vbyte = word[1];
			itentry.iddatatype = IT::CHR;
			itentry.sufix = idEntryStack.top().second;
			itentry.literalNum = ++idtable.literalsCount;
			itentry.scope = idEntryStack.size();
			IT::Add(idtable, itentry);
			buff += LEX_LITERAL;
			}
			else {
				throw ERROR_THROW_IN(208, lineNumber, lineIndex)
			}
		}
		if (buff[buff.length() - 1] != '\n') {
			ltentry.lexema = buff[buff.length() - 1];
			ltentry.stringLexema = word;
			ltentry.sn = lineNumber;
			LT::Add(lextable, ltentry);
		}
		i++;
		iteration++;
		lineIndex += word.size() + 1;
	}
	LT::Entry lastEntry = LT::Entry('$', lineNumber, -1, "$");
	LT::Add(lextable, lastEntry);
	return buff;
}