#include <iostream>
#include <cctype>
#include <iomanip>


namespace kuznetsov {
  char* getLine(std::istream& in, size_t& i);
  void extend(char** str, size_t oldSize, size_t newSize);
  void removeVow(char* buff, const char* str);
  int checkSeqSym(const char* str);
}

int main()
{
  namespace kuz = kuznetsov;
  size_t size = 0;
  char* str = nullptr;

  str = kuz::getLine(std::cin, size);
  if (!std::cin) {
    delete[] str;
    return 1;
  }

  char* buffer = nullptr;
  try {
     buffer = new char[size]{};
  } catch (const std::bad_alloc& e) {
    delete[] str;
    std::cerr << "Bad alloc buffer\n";
    return 2;
  }

  kuz::removeVow(buffer, str);

  std::cout << buffer << '\n';
  std::cout << kuz::checkSeqSym(str) << '\n';

  delete[] buffer;
  delete[] str;
}

char* kuznetsov::getLine(std::istream& in, size_t& size)
{
  char* buff = new char[8];
  size_t i = 8;
  size_t s = 0;
  bool is_skinws = in.flags() & std::ios::skipws;
  if (is_skinws) {
    in >> std::noskipws;
  }
  while (in >> buff[s] && buff[s] != '\n') {
    if (s + 4 >= i) {
      try {
        extend(&buff, i, i + 8);
      } catch (const std::bad_alloc&) {
        delete[] buff;
        throw;
      }
      i += 8;
    }
    ++s;
  }
  size = s;
  buff[s] = '\0';
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

void kuznetsov::removeVow(char* buff, const char* str)
{
  char vow[] = "aeiou";
  size_t nextPast = 0;
  for (size_t i = 0; *(str + i) != '\0'; ++i ) {
    size_t j = 0;
    for (; j < 5; ++j) {
      if (tolower(str[i]) == vow[j]) {
        break;
      }
    }
    if (j == 5) {
      buff[nextPast] = str[i];
      nextPast++;
    }
  }
}

int kuznetsov::checkSeqSym(const char* str)
{
  for (size_t i = 1; str[i] != '\n'; ++i) {
    if (str[i-1] == str[i]) {
      return 1;
    }
  }
  return 0;
}

