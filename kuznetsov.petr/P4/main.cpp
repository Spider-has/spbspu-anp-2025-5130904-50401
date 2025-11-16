#include <iostream>
#include <cctype>
#include <iomanip>
#include <cstring>

namespace kuznetsov {
  char* getLine(std::istream& in, size_t& size);
  void extend(char** str, size_t oldSize, size_t newSize);
}

// new/delete	RMV-VOW	SEQ-SYM
int main()
{

}

char* kuznetsov::getLine(std::istream& in, size_t& size)
{
  char* buff = new char[8];
  bool is_skinws = in.flags() & std::ios::skipws;
  if (is_skinws) {
    in >> std::noskipws;
  }
  size_t i = 0;
  while ( in >> buff[i] && i < size) {
    ++i;
  }

  buff[i] = '\0';

  if (is_skinws) {
    in >> std::skipws;
  }

  return buff;
}

void kuznetsov::extend(char** str, size_t oldSize, size_t newSize)
{
  char* extendedStr = new char[newSize];
  for (size_t i = 0; i < oldSize; ++i) {
    extendedStr[i] = (*str)[i];
  }
  for (size_t i = oldSize; i < newSize; ++i) {
    extendedStr[i] = 0;
  }
  delete[] *str;
  *str = extendedStr;
}

