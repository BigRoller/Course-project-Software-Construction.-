#include "stdafx.h"
#include "Out.h"
#include "Error.h"

#include <fstream>

void Out::getout(wchar_t fileOut[], char str[])
{
  std::string wstr;
  int strCounter = 2;

  {
    static auto lambda = [&wstr](int num) {
      std::string wnum = std::to_string(num);
      if (num < 10) {
        wstr += "0" + wnum + " ";
      }
      else {
        wstr += wnum + " ";
      } 
      };

    lambda(1);  // Нумерация строк начинается с 1
    wstr += str[0];
    for (int i = 1; str[i] != '\0'; i++) {
      if (i >= 1 && str[i - 1] == '\n' && str[i] != '\n') {
        lambda(strCounter++);
      }
      if (i >= 1 && (str[i - 1] != ' ' || str[i] != ' ') && (str[i - 1] != '\n' || str[i] != '\n')) {
        wstr += str[i];
      }
    }
  }

  std::ofstream file(fileOut);
  if (!file.is_open()) {
    throw ERROR_THROW(101);
  }
  file << wstr;
  file.close();
  return;
}
