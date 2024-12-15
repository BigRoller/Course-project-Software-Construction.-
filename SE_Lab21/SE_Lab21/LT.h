#pragma once
#define LEXEMA_FIXSIZE		 1
#define LT_MAXSIZE				 4096
#define LT_TI_NULLIDX			 0Xffffffff
#define LEX_MAIN           'm'
#define LEX_INTEGER				 't'
#define LEX_STRING				 't'
#define LEX_ID						 'i'
#define LEX_LITERAL				 'l'
#define LEX_FUNCTION			 'f'
#define LEX_DECLARE				 'd'
#define LEX_RETURN				 'r'
#define LEX_PRINT					 'p'
#define LEX_FOR						 'z'
#define LEX_SEMICOLON			 ';'
#define LEX_COMMA					 ','
#define LEX_LEFTBRACE			 '{'
#define LEX_BRACELET			 '}'
#define LEX_LEFTHESIS		   '('
#define LEX_RIGHTHESIS		 ')'
#define LEX_OPERATOR			 'v'
#define LEX_UNARY_MINUS		 '-'
#define LEX_COMPRASION_OPERATOR 'g'
#define LEX_EQUALLY							 '='
#define LEX_LEFT_SQUARE_BRACKET  '['
#define LEX_RIGHT_SQUARE_BRACKET ']'
#define CALL_FUNCTION '@'

namespace LT
{
	struct Entry
	{
		char lexema;
		std::string stringLexema;
		int sn; // номер строки в исходном файле
		int idxTI; // индекс в таблице индентификаторов
		short operation;
		int scope;
		enum OPERATION_RANG {
			NOT_OPERATOR = -1,
			ZERO = 0,
			FIRST,
			SECOND,
			THIRD,
			FOURTH
		};
		Entry(char ch, int num) {
			lexema = ch;
			sn = num;
			idxTI = LT_TI_NULLIDX;
			scope = 0;
		}
		Entry(char ch, int num, short op, std::string strLex) {
			lexema = ch;
			sn = num;
			operation = op;
			stringLexema = strLex;
			idxTI = LT_TI_NULLIDX;
			scope = 0;
		}
		Entry(){}
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	LexTable Create(
		int size
	);

	void Add(
		LexTable& lextable,
		Entry& entry
	);

	Entry GetEntry(
		LexTable& lextable,
		int n
	);

	void Delete(LexTable& lextable);
}