#pragma once
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h";
#include "IT.h"
#include <time.h>
#include <fstream>
#include <iomanip>

namespace Log
{
  struct LOG
  {
    wchar_t logfile[PARM_MAX_SIZE];
    std::ofstream* stream;

  };

  static const LOG INITLOG = { L""};
  LOG getlog(wchar_t logfile[]); 

  void WriteLine(LOG log, char* c, ...); 
  void WriteLine(LOG log, wchar_t*c, ...);  
  void Writelog(LOG log);
  void WriteParm(LOG log, Parm::PARM parm);
  void WriteIn(LOG log, In::IN_ in); 
  void WriteError(LOG log, Error::ERROR_ error);
  void Close(LOG log);  
  void WriteLexTable(LOG log, std::string str);
  void WriteIdTable(LOG log, IT::IdTable idTable);
  void WriteAfterPN(LOG log, LT::LexTable lextable);
}