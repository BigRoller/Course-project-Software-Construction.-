#include "stdafx.h"
#include <cwchar>    

#include "Error.h"
#include "Parm.h"
#include "Out.h"
#include "Log.h"
#include "In.h"
#include "Lexer.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
#include "MFST.h"
#include "PolishNotation.h"
#include "SA.h"
#include "CodeGeneration.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
 {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  setlocale(LC_CTYPE, "Ru");
  Log::LOG log = Log::INITLOG;
  try 
  {
    Parm::PARM parm = Parm::getparm(argc, argv);
    log = Log::getlog(parm.log);
    Log::WriteLine(log, (char*)"Тест:", (char*)" без ошибок \n", "");
    Log::WriteLine(log, (wchar_t*)L"Тест:", (wchar_t*)L" без ошибок \n", L"");
    Log::Writelog(log);
    Log::WriteParm(log, parm);
    In::IN_ in = In::getin(parm.in);
    Log::WriteIn(log, in); 
    Out::getout(parm.out, in.text);
    
    LT::LexTable lextable = LT::Create(300);
		IT::IdTable idtable = IT::Create(50);

		std::string code = GetLexAndIdTable(lextable, idtable, in.text);
    Log::WriteLine(log, (char*)"Лексический анализ:", (char*)" без ошибок \n", "");

		Log::WriteLexTable(log, code);

		Log::WriteIdTable(log, idtable);

		MFST::Mfst mfst(lextable, GRB::getGreibach(), log);
    Log::WriteLine(log, (char*)"Дерево разбора:\n", "");
		mfst.start(log);

		mfst.savededucation();
		mfst.printrules(log);

    SA::performSemanticAnalysis(lextable, idtable);
    Log::WriteLine(log, (char*)"Семантический анализ:", (char*)" без ошибок \n", "");

    Log::WriteLine(log, (char*)"Преобразование выражений в ПОЛИЗ:\n", "");
    PN::PolishNotation(lextable, idtable);
    Log::WriteAfterPN(log, lextable);

    CG::GenerateCode(idtable, lextable, mfst);
      
    LT::Delete(lextable);
    IT::Delete(idtable);

		Log::Close(log);
    cout << "Программа завершена успешно" << endl;
  }
  catch (Error::ERROR_ e)
  {
    Log::WriteError(log, e);
    cout << "Ошибка " << e.id << ": " << e.message << ", строка " << e.inext.line << ", позиция " << e.inext.col << "\n";
  }

  system("pause");
  return 0;
}