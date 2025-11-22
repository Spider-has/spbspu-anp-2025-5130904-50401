#include <iostream>
#include <iomanip>

namespace hvostov {
  char * getLine(std::istream & in, size_t & size, size_t extansion);
  char * extendStr(char * str, size_t & size, size_t new_size);
  void strConcatCharByChar(char * buffer, char * str1, char * str2);
}

char * hvostov::extendStr(char * str, size_t & size, size_t new_size)
{
  char * new_str = new char[new_size];
  for (size_t i = 0; i < size; i++) {
    new_str[i] = str[i];
  }
  delete[] str;
  size = new_size;
  return new_str;
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
        str = hvostov::extendStr(str, size, size + extansion + 1);
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
  if (str1[i / 2] == '\0') {
    size_t diff = i - i / 2;
    for (; str2[i - diff] != '\0'; i++) {
      buffer[i] = str2[i - diff];
    }
  } else {
    size_t diff = i - i / 2;
    for (; str1[i - diff] != '\0'; i++) {
      buffer[i] = str1[i - diff];
    }
  }
  buffer[i+1] = '\0';
}

int main()
{
  char * str = nullptr;
  size_t size = 10, extansion = 5;
  try {
    str = hvostov::getLine(std::cin, size, extansion);
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    delete[] str;
    return 1;
  }
  char str2[] = "qwerty12345";
  size_t size2 = 11;
  char * result = new char[size+size2+1];
  hvostov::strConcatCharByChar(result, str, str2);
  std::cout << result;
}
