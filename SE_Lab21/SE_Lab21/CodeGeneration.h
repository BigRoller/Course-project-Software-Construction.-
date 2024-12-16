#pragma once
#include "IT.h"
#include "LT.h"
#include "MFST.h"
#include "Error.h"

#include <fstream>
#include <vector>

#define OUTPUT_PATH "C:\\Users\\glora\\Desktop\\Ëàáû ÊÏÎ\\SE_Lab21\\SE_Lab21\\Asm.asm\\Asm.asm"
#define LIB_PATH "C:\\Users\\glora\\Desktop\\Ëàáû ÊÏÎ\\SE_Lab21\\SE_Lab21\\Debug\\Standart_lib.lib"
#define STANDART_LIB_PATH ("includelib \"" + (string)LIB_PATH + "\"\n").c_str()

#define STRING_ID(i) IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).sufix + "_" + IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).id + "_" + std::to_string(IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).scope)
#define CHAR_ID(i) (IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).sufix + "_" + IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).id + "_" + std::to_string(IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).scope)).c_str()
#define CHAR_ID_PARM(i) (IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).sufix + "_" + IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).id + "_" + std::to_string(IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).scope) + PARM_SUFFIX).c_str()
#define STRING_ID_PARM(i) IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).sufix + "_" + IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).id + "_" + std::to_string(IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).scope) + PARM_SUFFIX
#define CHAR_LITERAL(i) ("l" + to_string(IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).literalNum)).c_str()
#define CHAR_LITERAL_PARM(i) ("l" + to_string(IT::GetEntry(cg.idT, cg.lexT.table[i].idxTI + 1).literalNum) + PARM_SUFFIX).c_str()

#define MAX_EXPRESSION_LENGTH 1024
#define PARM_SUFFIX "_parm"
 
#define EXPR_INT			"push %s\n"
#define EXPR_EAX			"mov eax, %s\n"
#define EXPR_STRING		"push OFFSET %s \n"
#define EXPR_INT_E		"pop %s \n"
#define EXPR_STRING_E(idx) ("\
pop esi\n\
mov edi, offset %s\n\
copy_loop" + to_string(idx) + ":\n\
mov al, [esi]\n\
mov[edi], al\n\
inc esi\n\
inc edi\n\
cmp al, 0\n\
jne copy_loop" + to_string(idx) +  "\n").c_str()


#define EXPR_INT_PLUS "\
pop eax\n\
pop ebx\n\
add eax, ebx\n\
push eax\n"

#define EXPR_INT_MINUS "\
pop eax\n\
pop ebx\n\
sub eax, ebx\n\
push eax\n"

#define EXPR_INT_MUL	"\
pop eax\n\
pop ebx\n\
imul eax, ebx\n\
push eax\n"

#define EXPR_INT_DIV	"\
pop eax\n\
pop ebx\n\
cmp ebx, 0\n\
jz ERROR_ZERO_DIVISION\n\
div ebx\n\
push eax\n"

#define EXPR_GE(idx) ("\
pop eax\n\
pop ebx\n\
cmp eax, ebx\n\
jae FLAG" + to_string(idx) + "\n" +\
"jl FOR_END" + to_string(idx) + "\n").c_str()

#define EXPR_LE(idx) ("\
pop eax\n\
pop ebx\n\
cmp eax, ebx\n\
jbe FLAG" + to_string(idx) + "\n" +\
"jg FOR_END" + to_string(idx) + "\n").c_str()

#define EXPR_G(idx) ("\
pop eax\n\
pop ebx\n\
cmp eax, ebx\n\
jg FLAG" + to_string(idx) + "\n" +\
"jbe FOR_END" + to_string(idx) + "\n").c_str()

#define EXPR_L(idx) ("\
pop eax\n\
pop ebx\n\
cmp eax, ebx\n\
jb FLAG" + to_string(idx) + "\n" +\
"jae FOR_END" + to_string(idx) + "\n").c_str()

#define EXPR_E(idx) ("\
pop eax\n\
pop ebx\n\
cmp eax, ebx\n\
je FLAG" + to_string(idx) + "\n" +\
"jne FOR_END" + to_string(idx) + "\n").c_str()

#define EXPR_NE(idx) ("\
pop eax\n\
pop ebx\n\
cmp eax, ebx\n\
jne FLAG" + to_string(idx) + "\n" +\
"je FOR_END" + to_string(idx) + "\n").c_str()


#define EXPR_CALL			"call %s \npush eax\n"
#define EXPR_NEG      "pop eax\nneg eax\n push eax\n"

#define GEN1(b, tmpl, var, index) sprintf_s(b + index, MAX_EXPRESSION_LENGTH - index, tmpl, var)
#define GEN0(b, tmpl, index)			sprintf_s(b + index, MAX_EXPRESSION_LENGTH - index, tmpl)

#define ERROR_PREFIX "ERROR_"
#define TYPE_OVERFLOW "\"type overflow\""
#define ZERO_DIVISION "\"zero division\""

#define STANDART_OUTPUT_LN "__writeline"
#define STANDART_OUTPUT "__write"

#define CONST_ZERO_DIVISION "ZERO_DIVISION"
#define CONST_TYPE_OVERFLOW "TYPE_OVERFLOW"

#define EXPR_CHECK_BYTE_TP "cmp eax, 256\njg ERROR_TYPE_OVERFLOW\ncmp eax, 0\njl ERROR_TYPE_OVERFLOW\n"
#define EXPR_CHECK_INT_TP	"cmp eax, 2147483647\njg ERROR_TYPE_OVERFLOW\ncmp eax, -2147483648\n jl ERROR_TYPE_OVERFLOW\n"

namespace CG
{
	struct CG
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		MFST::Mfst mfst;
		static std::ofstream out;
		
		CG(IT::IdTable idtable, LT::LexTable lextable, MFST::Mfst mfst)
		{
			lexT = lextable;
			idT = idtable;
			this->mfst = mfst;
		}

		static void Head(CG&);
		static void Constants(CG&);
		static void Data(CG&);
		static void Code(CG&, int);
		static void Main(CG&);
		static void WriteExpression(CG&, int, int&, char*);
	};
	
	void GenerateCode(IT::IdTable, LT::LexTable, MFST::Mfst);

}