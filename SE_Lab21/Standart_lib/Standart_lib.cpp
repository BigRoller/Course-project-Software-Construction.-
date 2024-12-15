#include "Standart_lib.h"

extern "C"
{
  int __strlen(char* str)
  {
    return std::strlen(str);
  }

  char* __substr(const char* str, int firstIndex, int length) {
    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
      return nullptr;
    }

    int bufferIndex = 0;
    for (int i = firstIndex; i < firstIndex + length; i++) {
      buffer[bufferIndex++] = str[i];
    }
    buffer[bufferIndex] = '\0';
    return buffer;
  }

  void __free_buffer(char* buffer) {
    free(buffer);
  }
  void __write(char* str) {
    std::cout << str;
  }

  void __writeint(int num) {
    std::cout << num;
  }

  void __writeline(char* str) {
    std::cout << str << std::endl;
  }

  int __stoi(char* str) {

    int result = 0;
    bool isNegative = false;
    int i = 0;

    if (str[i] == '-') {
      isNegative = true;
      i++;
    }
    else if (str[i] == '+') {
      i++;
    }

    while (str[i] != '\0') {
      if (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
      }
      else {
        std::cerr << "Invalid character found: " << str[i] << std::endl;
        return 0;
      }
      i++;
    }

    if (isNegative) {
      result = -result;
    }

    return result;
  }

}