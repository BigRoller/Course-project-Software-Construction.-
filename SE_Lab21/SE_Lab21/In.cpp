#include "stdafx.h"
#include <locale>
#include <codecvt>
#include <fstream>
#include "In.h"
#include "Error.h"

In::IN_ In::getin(wchar_t infile[])
{
	int table[IN_MAX_LEN_TEXT] = IN_CODE_TABLE;

	std::ifstream file_output(infile);

	std::string line;

	if (file_output.is_open()) {
		IN_ temp = *(new IN_(0, 1, 0));
		temp.text = new char[IN_MAX_LEN_TEXT];
		int j = 0;
		while (!file_output.eof()) {
			std::getline(file_output, line);
			for (int i = 0; i < line.length(); i++, j++) {
				if (table[line[i]] == IN_::F) {
					throw ERROR_THROW_IN(111, temp.lines, i + 1);
				}
				if (temp.size >= IN_MAX_LEN_TEXT - 1) {
					throw ERROR_THROW(102)
				}
				if (table[line[i]] == IN_::I) {
					temp.ignor++;
					j--;
					continue;
				}
				else {
					temp.text[j] = line[i];
					temp.size++;
					continue;
				}
			}
			temp.lines++;
			temp.text[j++] = '\n';
			temp.size++;
		}
		temp.text[--j] = '\0';
		temp.size--;
		temp.lines--;
		file_output.close();
		return temp;
	}
	else {
		throw ERROR_THROW(110);
	}
}