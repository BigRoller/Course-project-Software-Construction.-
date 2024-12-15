		#include "stdafx.h"
		#include "PolishNotation.h"

void PN::PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable) {
	std::stack<LT::Entry> operatorStack;
	for (int i = 0; i < lextable.size; i++) {

		if (lextable.table[i].lexema == LEX_EQUALLY 
			|| lextable.table[i].lexema == LEX_PRINT 
			|| lextable.table[i].lexema == LEX_RETURN 
			|| lextable.table[i].lexema == LEX_COMPRASION_OPERATOR) {

			int index = i;

			if (lextable.table[i].lexema == LEX_COMPRASION_OPERATOR) {
				index -= 2;
			}

			LT::LexTable array = LT::Create(MAX_TOKEN_COUNT);
			std::stack<short> commaStack;

			for (int j = index + 1; j < lextable.size && lextable.table[j].lexema != LEX_SEMICOLON; j++) {
				LT::Add(array, lextable.table[j]);
			}

			std::stack<LT::Entry> output;
			for (int j = 0; j < array.size; j++) {
				if (array.table[j].lexema == LEX_ID || array.table[j].lexema == LEX_LITERAL) {
					output.push(array.table[j]);
				}
				else if (array.table[j].lexema == LEX_OPERATOR || array.table[j].lexema == LEX_COMPRASION_OPERATOR) {
					while (!operatorStack.empty() && operatorStack.top().operation >= array.table[j].operation) {
						output.push(operatorStack.top());
						operatorStack.pop();
					}
					operatorStack.push(array.table[j]);
				}
				else if (array.table[j].lexema == LEX_LEFTHESIS) {
					operatorStack.push(array.table[j]);
					if (array.table[j - 1].lexema == LEX_ID) {
						commaStack.push(1);
					}
				}
				else if (array.table[j].lexema == LEX_RIGHTHESIS) {
					while (!operatorStack.empty() && operatorStack.top().lexema != LEX_LEFTHESIS) {
						output.push(operatorStack.top());
						operatorStack.pop();
					}
					if (!operatorStack.empty()) operatorStack.pop();
					if (!commaStack.empty()) { 
						output.push({ '@', lextable.table[index].sn, commaStack.top(), "@"});
						commaStack.pop();
					}	
				}
				else if (array.table[j].lexema == LEX_COMMA) {
					if (!commaStack.empty()) commaStack.top()++;
				}
				else if (array.table[j].lexema == LEX_UNARY_MINUS) {
					operatorStack.push(array.table[j]);
				}
			}

			while (!operatorStack.empty()) {
				output.push(operatorStack.top());
				operatorStack.pop();
			}

			int k = index + 1;
			int temp = k;

			std::vector<LT::Entry> buffer;
			while (!output.empty()) {
				buffer.push_back(output.top());
				output.pop();
			}

			while (!buffer.empty()) {
				lextable.table[k++] = buffer.back();
				buffer.pop_back();
			}

			lextable.table[k++] = { ';', lextable.table[k].sn, lextable.table[k].NOT_OPERATOR, ";"};

			for (; k < array.size + index + 2; k++) {
				lextable.table[k] = { '~', -1, -1, "~"};
			}

			for (int j = temp; lextable.table[j].lexema != LEX_SEMICOLON; j++) {
				if (lextable.table[j].lexema == LEX_LITERAL) {
					idtable.table[lextable.table[j].idxTI].idxfirstLE = j;
				}
			}
			i += array.size;
			LT::Delete(array);
		}
	}
}
