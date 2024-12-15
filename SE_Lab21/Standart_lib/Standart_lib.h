#pragma once
#include <iostream>
#include <string>

extern "C"
{
  int __strlen(char*);

  char* __substr(const char*, int, int);

  void __free_buffer(char*);

  void __write(char*);

  void __writeint(int);

  void __writeline(char*);

  int __stoi(char*);

}