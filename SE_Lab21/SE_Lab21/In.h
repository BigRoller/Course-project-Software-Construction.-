#pragma once

//#define IN_MAX_LEN_TEXT 1024*1024  // maximum size of the text buffer = 1MB
#define IN_MAX_LEN_TEXT 2045  // maximum size of the text buffer = 1KB
#define IN_CODE_ENDL L'\n'

#define IN_CODE_TABLE {\
IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F,\
IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::F, IN_::F, IN_::F, IN_::F, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::F, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::F,\
IN_::F, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F,\
IN_::F, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::F, IN_::T, IN_::F, IN_::F,\
\
IN_::F, IN_::T, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F,\
IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F,\
IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::T, IN_::F, IN_::F, IN_::F,\
IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F, IN_::F,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T,\
IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T, IN_::T,\
}

namespace In
{
  struct IN_
  {
    enum { T = 1024, F = 2048, I = 4096 };
    int size;
    int lines;
    int ignor;
    char* text;
    wchar_t code[IN_MAX_LEN_TEXT];
    IN_(int Size, int Lines, int Ignor)
    {
    size = Size; 
    lines = Lines;
    ignor = Ignor;
    }
    IN_() {};
  };
  IN_ getin(wchar_t infile[]);
}