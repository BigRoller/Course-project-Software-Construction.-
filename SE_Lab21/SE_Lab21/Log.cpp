#include "stdafx.h"
#include "Log.h"

Log::LOG Log::getlog(wchar_t logfile[])
{
	LOG log;
	log.stream = new std::ofstream;
	wcscpy_s(log.logfile, logfile);
	log.stream->open(logfile);
	if (!log.stream->is_open()) {
		throw ERROR_THROW(112);
	}
	else {
		return log;
	}
}

void Log::WriteLine(LOG log, char* c, ...)
{
	char** p = &c;
	char buffer[256] = "";
	char temp[256];
	while (*p != "") {
		strcpy(temp, *p++);
		strncat(buffer, temp, sizeof(temp) + sizeof(buffer));
	}
	*(log.stream) << buffer;

	return;
}

void Log::WriteLine(LOG log, wchar_t* c, ...)
{
	wchar_t** p = &c;
	wchar_t buffer[256] = L"";
	wchar_t temp[256];
	while (*p != L"") {
		wcscpy(temp, *p++);
		wcsncat(buffer, temp, sizeof(temp) + sizeof(buffer));
	}
	char str[256];
	wcstombs(str, buffer, sizeof(str));
	str[sizeof(str) - 1] = '\0';
	*(log.stream) << str;

	return;
}

void Log::Writelog(LOG log)
{
	char buffer1[256];
	char buffer2[256];
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	strftime(buffer2, sizeof(buffer2), "%d.%m.%Y", now);
	strftime(buffer1, sizeof(buffer1), "%T", now);
	*(log.stream) << " - - - -  Протокол  - - - - - " << buffer1 << '\t' << buffer2 << "\n";
	return;
}

void Log::WriteParm(LOG log, Parm::PARM parm)
{
	char buf[80];
	*(log.stream) << " - - - Параметры - - - - " << "\n";
	wcstombs(buf, parm.log, sizeof(buf));
	*(log.stream) << "-log: " << buf << "\n";
	wcstombs(buf, parm.out, sizeof(buf));
	*(log.stream) << "-out: " << buf << "\n";
	wcstombs(buf, parm.in, sizeof(buf));
	*(log.stream) << "-in: " << buf << "\n";
	return;
}

void Log::WriteIn(LOG log, In::IN_ in)
{
	*(log.stream) << " - - - Исходные данные - - - - " << "\n";
	*(log.stream) << "Количество символов: " << in.size << "\n";
	*(log.stream) << "Проигнорировано: " << in.ignor << "\n";
	*(log.stream) << "Количество строк: " << in.lines << "\n";
	return;
}

void Log::WriteLexTable(Log::LOG log, std::string str)
{ 
		std::string buffer;
	int strCounter = 2;

	{
		auto lambda = [&buffer, &strCounter](int num, int pos) {
			std::string wnum = std::to_string(num);
			strCounter < 11 ? buffer += "0" + wnum + " " : buffer += wnum + " ";
			};

		lambda(1, 0);
		for (int i = 0; i < str.size(); i++) {
			if (i > 0 && str[i - 1] == '\n') {
				lambda(strCounter++, i);
			}
			if (str[i] != L' ' || str[i + 1] != L' ') { 
				buffer += str[i];
			}
		}
	}
	*(log.stream) << "\n - - - Таблица лексем - - - - " << "\n";
	*(log.stream) << buffer << "\n";
	return;
}

void Log::WriteIdTable(Log::LOG log, IT::IdTable idTable)
{
	static int width = 25;
	static int maxStringLength = 18;
	*(log.stream) << "\n\n - - - Таблица идентификаторов - - - - " << "\n";
	*(log.stream) << std::left << std::setw(width) << "Функция"
		<< std::setw(width) << "Имя идентификатора"
		<< std::setw(width) << "Тип данных"
		<< std::setw(width) << "Значение"
		<< std::setw(width) << "Длина строки"
		<< std::setw(width) << "Тип идентификатора"
		<< std::setw(width) << "Индекс первого вхождения"
		<< std::endl;

	for (int i = 0; i < idTable.size; i++) {
		*(log.stream) << std::left << std::setw(width) << idTable.table[i].sufix;
		if (idTable.table[i].id.size() <= maxStringLength) {
			*(log.stream) << std::left << std::setw(width) << idTable.table[i].id.c_str();
		}
		else {
			*(log.stream) << std::left << std::setw(width) << idTable.table[i].id.substr(0, maxStringLength) + "...\"";
		}
		if (idTable.table[i].iddatatype == IT::INT) {
			*(log.stream) << std::left << std::setw(width) << "integer"
				<< std::setw(width) << idTable.table[i].value.vint
				<< std::setw(width) << " ";
		}
		else if (idTable.table[i].iddatatype == IT::STR) {
			if (idTable.table[i].id.size() <= maxStringLength) {
				*(log.stream) << std::left << std::setw(width) << "string"
					<< std::setw(width) << idTable.table[i].value.vstr.str
					<< std::setw(width) << (int)idTable.table[i].value.vstr.len;
			}
			else {
				*(log.stream) << std::left << std::setw(width) << "string"
					<< std::setw(width) << idTable.table[i].value.vstr.str.substr(0, maxStringLength - 1) + "..."
					<< std::setw(width) << (int)idTable.table[i].value.vstr.len;
			}
		}
		else if (idTable.table[i].iddatatype == IT::CHR) {
			*(log.stream) << std::left << std::setw(width) << "symbol"
				<< std::setw(width) << idTable.table[i].value.vbyte
				<< std::setw(width) << " ";
		}
		else if (idTable.table[i].iddatatype == IT::BYTE) {
			*(log.stream) << std::left << std::setw(width) << "byte"
				<< std::setw(width) << (int)idTable.table[i].value.vbyte
				<< std::setw(width) << " ";
		}

		if (idTable.table[i].idtype == 1) {
			*(log.stream) << std::left << std::setw(width) << "переменная";
		}
		else if (idTable.table[i].idtype == 2) {
			*(log.stream) << std::left << std::setw(width) << "функция";
		}
		else if (idTable.table[i].idtype == 3) {
			*(log.stream) << std::left << std::setw(width) << "параметр";
		}
		else if (idTable.table[i].idtype == 4) {
			*(log.stream) << std::left << std::setw(width) << "литерал";
		}

		if (idTable.table[i].idxfirstLE != 0xffffffff) {
			*(log.stream) << idTable.table[i].idxfirstLE << "\n";
		}
	}
}


void Log::WriteError(LOG log, Error::ERROR_ error)
{
	if (log.stream == NULL) {
		log.stream = new std::ofstream;
	}
 	if (!log.stream->is_open()) {
		std::cout << error.message << std::endl;
	}
	else {
		*(log.stream) << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << "\n";
 	}
}

void Log::WriteAfterPN(LOG log, LT::LexTable lextable)
{	
	for (int i = 0; i < lextable.size; i++) {
		*(log.stream) << lextable.table[i].lexema;
	}
	*(log.stream) << "\n";
}

void Log::Close(LOG log)
{
	log.stream->close();
	return;
}