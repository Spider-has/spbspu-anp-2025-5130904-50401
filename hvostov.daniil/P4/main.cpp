#include <iostream>
#include <iomanip>
namespace hvostov {
  char * getLine(std::istream & in, size_t & size, size_t extansion);
  char * extendStr(char * str, size_t & size, size_t new_size);
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
  std::cout << str;
}
