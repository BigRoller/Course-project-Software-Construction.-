#include "stdafx.h"
#include "CodeGeneration.h"

std::ofstream CG::CG::out(OUTPUT_PATH);
static std::vector<IT::Entry> local_procedures;
static std::vector<IT::Entry> extern_procedures;
static std::vector<LT::Entry> io_procedures;
static bool isMain = false;
static int flag_counter = 0;
static std::stack<int> flag_stack;

using namespace std;

void CG::GenerateCode(IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
{
	CG(idtable, lextable, mfst);

	if (!CG::out.is_open()) {
		throw ERROR_THROW_IN(99, -1, -1)
	}

	CG cg = *(new CG(idtable, lextable, mfst));

	CG::Head(cg);
	CG::Constants(cg);
	CG::Data(cg);
	CG::Main(cg);
	if (CG::out.is_open()) {
		CG::out.close();
	}
}

void CG::CG::Head(CG& cg)
{
	out << ".586\n";
	out << ".model flat, stdcall\n";
	out << "includelib kernel32.lib\n";
	out << "includelib libucrt.lib\n";
	out << "SetConsoleOutputCP PROTO : DWORD\n";
	out << "SetConsoleCP PROTO : DWORD\n";
		
	out << STANDART_LIB_PATH;
	out << "ExitProcess PROTO : DWORD\n";
	for (int i = 0; i < cg.lexT.size; i++) {
		if (cg.lexT.table[i].lexema == LEX_FUNCTION) {
			int k = i + 1;
			for (; cg.lexT.table[k].lexema != LEX_RIGHTHESIS; k++) {}
			if (cg.lexT.table[k + 1].lexema == LEX_LEFTBRACE) {
			local_procedures.push_back(IT::GetEntry(cg.idT, cg.lexT.table[i + 1].idxTI + 1));
			out << STRING_ID(i + 1) << " PROTO ";
			int j = i + 2;
			for (; cg.lexT.table[j].lexema != LEX_RIGHTHESIS; j++) {
				if (cg.lexT.table[j].lexema == LEX_ID) {
					if (IT::GetEntry(cg.idT, cg.lexT.table[j].idxTI).iddatatype == IT::BYTE
						|| IT::GetEntry(cg.idT, cg.lexT.table[j].idxTI).iddatatype == IT::CHR
						|| IT::GetEntry(cg.idT, cg.lexT.table[j].idxTI).iddatatype == IT::INT) {
						out << " : SDWORD";
					}
					else if (IT::GetEntry(cg.idT, cg.lexT.table[j].idxTI).iddatatype == IT::STR) {
						out << " : DWORD";
					}
					if (cg.lexT.table[j + 1].lexema != LEX_RIGHTHESIS) {
						out << ", ";
					}
				}
			}
			out << "\n";
			}
			else {
				bool flag = false;
				for (int j = 0; j < extern_procedures.size(); j++) {
					if (extern_procedures[j].id == cg.lexT.table[i + 1].stringLexema) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					extern_procedures.push_back(IT::GetEntry(cg.idT, cg.lexT.table[i + 1].idxTI + 1));
					out << "extern " << "__" << cg.lexT.table[i + 1].stringLexema << " : PROC\n";
				}
			}
		}
		else if (cg.lexT.table[i].lexema == LEX_PRINT) {
			bool flag = false;
			for (int j = 0; j < io_procedures.size(); j++) {
				if (io_procedures[j].stringLexema == cg.lexT.table[i].stringLexema) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				io_procedures.push_back(cg.lexT.table[i]);
				out << "extern " << "__" << cg.lexT.table[i].stringLexema << " : PROC\n";
			}
		}
	}
}

void CG::CG::Constants(CG& cg)
{
	out << "\n.stack 4096\n";
	out << ".const\n";
	out << CONST_ZERO_DIVISION << " BYTE " << ZERO_DIVISION << ", 0\n";
	out << CONST_TYPE_OVERFLOW << " BYTE " << TYPE_OVERFLOW << ", 0\n";

	for (int i = 0; i < cg.idT.size; i++) {
		if (cg.idT.table[i].idtype == IT::L) {
			out << CHAR_LITERAL(cg.idT.table[i].idxfirstLE);
			if (cg.idT.table[i].iddatatype == IT::BYTE) {
				out << " SDWORD " << (int)cg.idT.table[i].value.vbyte << "\n";
			}
			else if (cg.idT.table[i].iddatatype == IT::CHR) {
				out << " SDWORD " << "\'" << cg.idT.table[i].value.vbyte << "\'" << "\n";
			}
			else if (cg.idT.table[i].iddatatype == IT::INT) {
				out << " SDWORD " << cg.idT.table[i].value.vint << "\n";
			}
			else if (cg.idT.table[i].iddatatype == IT::STR) {
				out << " BYTE " << "\"" << cg.idT.table[i].value.vstr.str << "\", 0\n";
			}
		}
	}
	out << "\n";
 }

void CG::CG::Data(CG& cg)
{
	out << ".data\n";
	for (int i = 0; i < cg.idT.size; i++) {
		if (cg.idT.table[i].idtype == IT::V) {
			out << cg.idT.table[i].sufix << "_" << cg.idT.table[i].id << "_" << cg.idT.table[i].scope;
			if (cg.idT.table[i].iddatatype == IT::BYTE) {
				out << " SDWORD " << int(cg.idT.table[i].value.vbyte) << "\n";
			}
			else if (cg.idT.table[i].iddatatype == IT::CHR) {
				out << " SDWORD " << "\'" << char(cg.idT.table[i].value.vbyte) << "\'" << "\n";
			}
			else if (cg.idT.table[i].iddatatype == IT::STR) {

				out << " BYTE ";
				if (cg.idT.table[i].value.vstr.str == " ") {
					out << "256 dup(0)" << "\n";
				}
			}
			else if (cg.idT.table[i].iddatatype == IT::INT) {
				out << " SDWORD " << cg.idT.table[i].value.vint << "\n";;
			}
		}
	}
	out << "\n";
}			

void CG::CG::WriteExpression(CG& cg, int k, int& index, char* buff)
{
	stack<LT::Entry> stack;
	static auto writeIDAndLiterals = [&](std::stack<LT::Entry>&stack, int num, char* buff, int& index) {
		for (int i = 0; i < num; i++) {
			if (!stack.empty()) {
				if (stack.top().lexema == LEX_LITERAL) {
					if (IT::GetEntry(cg.idT, stack.top().idxTI + 1).iddatatype == IT::STR) {
						
						index += GEN1(buff, EXPR_STRING, ("l" + to_string(IT::GetEntry(cg.idT, stack.top().idxTI + 1).literalNum)).c_str(), index);
					}
					else {
						index += GEN1(buff, EXPR_INT, CHAR_LITERAL(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
						index += GEN1(buff, EXPR_EAX, CHAR_LITERAL(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
					}
				}
				else if (stack.top().lexema == LEX_ID && IT::GetEntry(cg.idT, stack.top().idxTI + 1).idtype != IT::F) {
					if (IT::GetEntry(cg.idT, stack.top().idxTI + 1).iddatatype == IT::STR) {
						if (IT::GetEntry(cg.idT, stack.top().idxTI + 1).idtype == IT::P) {
							index += GEN1(buff, EXPR_INT, CHAR_ID_PARM(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
							index += GEN1(buff, EXPR_EAX, CHAR_ID_PARM(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
						}
						else {
							index += GEN1(buff, EXPR_STRING, CHAR_ID(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
						}
					}
					else {
						if (IT::GetEntry(cg.idT, stack.top().idxTI + 1).idtype == IT::P) {
							index += GEN1(buff, EXPR_INT, CHAR_ID_PARM(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
							index += GEN1(buff, EXPR_EAX, CHAR_ID_PARM(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
						}
						else {
							index += GEN1(buff, EXPR_INT, CHAR_ID(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
							index += GEN1(buff, EXPR_EAX, CHAR_ID(IT::GetEntry(cg.idT, stack.top().idxTI + 1).idxfirstLE), index);
						}

					}
				}
				stack.pop();
			}
		}
		};

	for (int q = k + 1; cg.lexT.table[q].lexema != LEX_SEMICOLON; q++) {
		if ((cg.lexT.table[q].lexema == LEX_LITERAL || cg.lexT.table[q].lexema == LEX_ID)) {
			stack.push(cg.lexT.table[q]);
		}
		else if (cg.lexT.table[q].lexema == LEX_OPERATOR) {
			writeIDAndLiterals(stack, 2, buff, index);

			if (cg.lexT.table[q].stringLexema == "*") {
				index += GEN0(buff, EXPR_INT_MUL, index);
			}
			else if (cg.lexT.table[q].stringLexema == "+") {
				index += GEN0(buff, EXPR_INT_PLUS, index);
			}
			else if (cg.lexT.table[q].stringLexema == "-") {
				index += GEN0(buff, EXPR_INT_MINUS, index);
			}
			else if (cg.lexT.table[q].stringLexema == "/") {
				index += GEN0(buff, EXPR_INT_DIV, index);
			}
		}
		else if (cg.lexT.table[q].lexema == LEX_COMPRASION_OPERATOR) {
			writeIDAndLiterals(stack, 2, buff, index);
			if (cg.lexT.table[q].stringLexema == "<=") {
				index += GEN0(buff, EXPR_LE(flag_stack.top(), ), index);
			}
			else if (cg.lexT.table[q].stringLexema == "<") {
				index += GEN0(buff, EXPR_L(flag_stack.top()), index);
			}
			else if (cg.lexT.table[q].stringLexema == ">=") {
				index += GEN0(buff, EXPR_GE(flag_stack.top()), index);
			}
			else if (cg.lexT.table[q].stringLexema == ">") {
				index += GEN0(buff, EXPR_G(flag_stack.top()), index);
			}
			else if (cg.lexT.table[q].stringLexema == "==") {
				index += GEN0(buff, EXPR_E(flag_stack.top()), index);
			}
			else if (cg.lexT.table[q].stringLexema == "!=") {
				index += GEN0(buff, EXPR_NE(flag_stack.top()), index);
			}
		}
		else if (cg.lexT.table[q].lexema == LEX_UNARY_MINUS) {
			if (IT::GetEntry(cg.idT, cg.lexT.table[q - 1].idxTI + 1).idtype != IT::L) { ////////////////////////////
				writeIDAndLiterals(stack, 1, buff, index);
				index += GEN0(buff, EXPR_NEG, index);
			}
		}
		else if (cg.lexT.table[q].lexema == CALL_FUNCTION) {
			std::stack<LT::Entry> exportStack;
			bool flag = false;
			for (int j = 0; j < extern_procedures.size(); j++) {
				if (extern_procedures[j].id == cg.lexT.table[q - cg.lexT.table[q].operation - 1].stringLexema) {
					flag = true;
					break;
				}
			}
			if (flag) {
				writeIDAndLiterals(stack, cg.lexT.table[q].operation, buff, index);
				if (!stack.empty()) stack.pop();
				index += GEN1(buff, EXPR_CALL, ("__" + cg.lexT.table[q - cg.lexT.table[q].operation - 1].stringLexema).c_str(), index);
			}
			else {
				while (!stack.empty()) {
					exportStack.push(stack.top());
					stack.pop();
				}
				exportStack.pop();
				writeIDAndLiterals(exportStack, cg.lexT.table[q].operation, buff, index);
				index += GEN1(buff, EXPR_CALL, CHAR_ID(q - cg.lexT.table[q].operation - 1), index);
			}
		}
	}
	if (!stack.empty()) {
		writeIDAndLiterals(stack, 1, buff, index);
	}
}


void CG::CG::Code(CG& cg, int j)
{
	static int loop_counter = 0;
	for (int k = j + 1; cg.lexT.table[k].lexema != LEX_BRACELET; k++) {
		char* buff = new char[MAX_EXPRESSION_LENGTH] {0};
		int index = 0;
		if (cg.lexT.table[k].lexema == LEX_EQUALLY) {
			WriteExpression(cg, k, index, buff);
			if (IT::GetEntry(cg.idT, cg.lexT.table[k - 1].idxTI + 1).iddatatype == IT::STR) {
				index += GEN1(buff, EXPR_STRING_E(loop_counter), CHAR_ID(k - 1), index);
				loop_counter++;
			}
			else {
				if (IT::GetEntry(cg.idT, cg.lexT.table[k - 1].idxTI + 1).iddatatype == IT::BYTE
						|| IT::GetEntry(cg.idT, cg.lexT.table[k - 1].idxTI + 1).iddatatype == IT::CHR) {
					index += GEN0(buff, EXPR_CHECK_BYTE_TP, index);
				}
				else if (IT::GetEntry(cg.idT, cg.lexT.table[k - 1].idxTI + 1).iddatatype == IT::INT) {
					index += GEN0(buff, EXPR_CHECK_INT_TP, index);
				}
				index += GEN1(buff, EXPR_INT_E, CHAR_ID(k - 1), index);
			}
			out << buff;
		}
		else if (cg.lexT.table[k].lexema == LEX_RETURN) {
			WriteExpression(cg, k, index, buff);
			out << buff;
			if (IT::GetEntry(cg.idT, cg.lexT.table[k + 1].idxTI + 1).iddatatype == IT::STR) {
				if (IT::GetEntry(cg.idT, cg.lexT.table[k + 1].idxTI + 1).idtype == IT::L) {
					out << "mov eax, OFFSET " << CHAR_LITERAL(k + 1) << "\n";
				}
				else {
					out << "mov eax, OFFSET " << CHAR_ID(k + 1) << "\n";
				}
			}
			else {
				if (IT::GetEntry(cg.idT, cg.lexT.table[k + 1].idxTI).idtype == IT::L) {
					out << "mov eax, " << CHAR_LITERAL(k + 1) << "\n";
				}
				else {
					out << "mov eax, " << CHAR_ID(k + 1) << "\n";
				}
			}
			if (!isMain) {
				out << "ret\n";
			}
		}
		else if (cg.lexT.table[k].lexema == LEX_PRINT) {
			WriteExpression(cg, k, index, buff);
			out << buff;
			out << "call __" << cg.lexT.table[k].stringLexema << "\n";
		}
		else if (cg.lexT.table[k].lexema == LEX_FOR) {
			flag_stack.push(flag_counter);
			WriteExpression(cg, k + 2, index, buff);
			if (IT::GetEntry(cg.idT, cg.lexT.table[k + 2].idxTI + 1).iddatatype == IT::STR) {
				index += GEN1(buff, EXPR_STRING_E(loop_counter), CHAR_ID(k - 1), index);
				loop_counter++;
			}
			else {
				if (IT::GetEntry(cg.idT, cg.lexT.table[k + 2].idxTI + 1).iddatatype == IT::BYTE
					|| IT::GetEntry(cg.idT, cg.lexT.table[k + 2].idxTI + 1).iddatatype == IT::CHR) {
					index += GEN0(buff, EXPR_CHECK_BYTE_TP, index);
				}
				else if (IT::GetEntry(cg.idT, cg.lexT.table[k + 2].idxTI + 1).iddatatype == IT::INT) {
					index += GEN0(buff, EXPR_CHECK_INT_TP, index);
				}
				index += GEN1(buff, EXPR_INT_E, CHAR_ID(k + 2), index);
			}
			out << buff;
			delete buff;
			index = 0;
			buff = new char[MAX_EXPRESSION_LENGTH] {0};
			int second = k + 1;
			while (cg.lexT.table[second].lexema != LEX_SEMICOLON) { second++; }
			int third = second + 1;
			while (cg.lexT.table[third].lexema != LEX_SEMICOLON) { third++; }
			int body = third + 1;
			while (cg.lexT.table[body].lexema != LEX_SEMICOLON) { body++; }
			WriteExpression(cg, second, index, buff);
			out << buff;
			delete buff;
			index = 0;
			buff = new char[MAX_EXPRESSION_LENGTH] {0};
			out << "FLAG" << flag_stack.top() << ":\n";
			flag_counter++;
			Code(cg, body);
			WriteExpression(cg, third + 1, index, buff);
			if (IT::GetEntry(cg.idT, cg.lexT.table[third + 1].idxTI + 1).iddatatype == IT::STR) {
				index += GEN1(buff, EXPR_STRING_E(loop_counter), CHAR_ID(third + 1), index);
				loop_counter++;
			}
			else {
				if (IT::GetEntry(cg.idT, cg.lexT.table[third + 1].idxTI + 1).iddatatype == IT::BYTE
					|| IT::GetEntry(cg.idT, cg.lexT.table[third + 1].idxTI + 1).iddatatype == IT::CHR) {
					index += GEN0(buff, EXPR_CHECK_BYTE_TP, index);
				}
				else if (IT::GetEntry(cg.idT, cg.lexT.table[third + 1].idxTI + 1).iddatatype == IT::INT) {
					index += GEN0(buff, EXPR_CHECK_INT_TP, index);
				}
				index += GEN1(buff, EXPR_INT_E, CHAR_ID(third + 1), index);
			}
			WriteExpression(cg, second, index, buff);
			out << buff;
			out << "FOR_END" << flag_stack.top() << ":\n";
			delete buff;
			int i = body + 1;
			for (; cg.lexT.table[i].lexema != LEX_BRACELET; i++) {}
			k = i; 
			flag_stack.pop();
		}
	}
}

void CG::CG::Main(CG& cg)
{
	out << ".code\n";
	out << ERROR_PREFIX << CONST_ZERO_DIVISION << ":\n";
	out << "push OFFSET " << CONST_ZERO_DIVISION << "\n";
	out << "call " << STANDART_OUTPUT_LN << "\n";
	out << "push -1\n";
	out << "call ExitProcess\n";

	out << ERROR_PREFIX << CONST_TYPE_OVERFLOW << ":\n";
	out << "push OFFSET " << CONST_TYPE_OVERFLOW << "\n";
	out << "call " << STANDART_OUTPUT_LN << "\n";
	out << "push -1\n";
	out << "call ExitProcess\n\n";


	for (int i = 0; i < local_procedures.size(); i++) {
		out << local_procedures[i].sufix + "_" + local_procedures[i].id + "_" + to_string(local_procedures[i].scope) << " PROC ";
		int j = local_procedures[i].idxfirstLE;
		for (int k = j + 1; cg.lexT.table[k].lexema != LEX_RIGHTHESIS; k++) {
			if (cg.lexT.table[k].lexema == LEX_ID) {
				out << STRING_ID(k) + PARM_SUFFIX << " : ";
				if (IT::GetEntry(cg.idT, cg.lexT.table[k].idxTI + 1).iddatatype == IT::BYTE
					|| IT::GetEntry(cg.idT, cg.lexT.table[k].idxTI + 1).iddatatype == IT::INT
					|| IT::GetEntry(cg.idT, cg.lexT.table[k].idxTI + 1).iddatatype == IT::CHR) {
					out << "SDWORD";
				}
				else if (IT::GetEntry(cg.idT, cg.lexT.table[k].idxTI + 1).iddatatype == IT::STR) {
					out << "DWORD";
				}
				if (cg.lexT.table[k + 1].lexema != LEX_RIGHTHESIS) {
					out << ", ";
				}
			}
		}
		out << "\n";
		for (; cg.lexT.table[j].lexema != LEX_LEFTBRACE; j++) {}
		Code(cg, j);

		out << local_procedures[i].sufix + "_" + local_procedures[i].id + "_" + to_string(local_procedures[i].scope) << " ENDP\n\n";
	}
	out << "main PROC\n";
	out << "push 1251d\n";
	out << "call SetConsoleOutputCP\n";
	out << "push 1251d\n";
	out << "call SetConsoleCP\n";
	isMain = true;
	int begin = 0;
	for (; cg.lexT.table[begin].lexema != LEX_MAIN; begin++) {}
	Code(cg, begin);
	out << "call ExitProcess\n";
	out << "main ENDP\n";
	out << "end main\n";
}