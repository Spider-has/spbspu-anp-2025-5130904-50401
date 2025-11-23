#include <iostream>
#include <iomanip>
#include <cctype>

namespace hvostov {
  char * getLine(std::istream & in, size_t & size, size_t extansion);
  void extendStr(char ** str, size_t & size, size_t new_size);
  void strConcatCharByChar(char * buffer, char * str1, char * str2);
  void concatRemainders(char * str1, char * str2, size_t & i);
  size_t countAlphaCharacters(char * str);
}

int main()
{
  char * str = nullptr;
  size_t size = 10, extansion = 5;
  try {
    str = hvostov::getLine(std::cin, size, extansion);
    if (!std::cin) {
      std::cerr << "Problems with input!\n";
      delete[] str;
      return 1;
    }
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    delete[] str;
    return 1;
  }
  char str2[] = "qwerty12345";
  size_t size2 = 11;
  char * result = nullptr;
  try {
    result = new char[size+size2+1];
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  hvostov::strConcatCharByChar(result, str, str2);
  size_t counter = hvostov::countAlphaCharacters(result);
  std::cout << result << "\n";
  std::cout << counter << "\n";
  delete[] str;
  return 0;
}

char * hvostov::getLine(std::istream & in, size_t & size, size_t extansion)
{
  char * str = new char[size + 1];
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  size_t i = 0;
  char a = 'a';
  while (in >> a && a != '\n') {
    if (i == size) {
      try {
        hvostov::extendStr(& str, size, size + extansion + 1);
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
    }
    str[i] = a;
    i++;
  }
  str[i] = '\0';
  size = i;
  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}

void hvostov::extendStr(char ** str, size_t & size, size_t new_size)
{
  char * new_str = new char[new_size];
  for (size_t i = 0; i < size; i++) {
    new_str[i] = (* str)[i];
  }
  delete[] * str;
  size = new_size;
  * str = new_str;
}

void hvostov::strConcatCharByChar(char * buffer, char * str1, char * str2)
{
  size_t i = 0;
  for (; str1[i / 2] != '\0' && str2[i / 2] != '\0'; i++) {
    if (i % 2 == 0) {
      buffer[i] = str1[i / 2];
    } else {
      buffer[i] = str2[i / 2];
    }
  }
  char * remainder_str = str1[i / 2] == '\0' ? str2 : str1;
  hvostov::concatRemainders(buffer, remainder_str, i);
  buffer[i] = '\0';
}

void hvostov::concatRemainders(char * str1, char * str2, size_t & i)
{
  size_t diff = i - i / 2;
  for (; str2[i - diff] != '\0'; i++) {
    str1[i] = str2[i - diff];
  }
}

size_t hvostov::countAlphaCharacters(char * str)
{
  size_t counter = 0;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      counter++;
    }
  }
  return counter;
}
