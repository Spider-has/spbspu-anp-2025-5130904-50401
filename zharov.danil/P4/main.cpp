#include <iostream>
#include <iomanip>

namespace zharov
{
  char * getline(std::istream & in, size_t size, size_t k, size_t & len, const char end);
  void extension(char *& str, size_t old_size, size_t new_size);
}

int main()
{
  size_t size = 10;
  size_t k = 5;
  size_t len = 0;
  const char end = '\n';
  char * str = nullptr;
  try {
    str = zharov::getline(std::cin, size, k, len, end);
    if (!std::cin) {
      delete[] str;
      std::cerr << "Bad enter\n";
      return 1;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "Bad alloc\n";
    return 1;
  }

  std::cout << str << "\n";
  delete[] str;
}

void zharov::extension(char *& str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size+1];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = str[i];
  }
  delete[] str;
  str = new_str;
}

char * zharov::getline(std::istream & in, size_t size, size_t k, size_t & len, char end)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char * str = new char[size + 1];
  char sym = ' ';
  while (in >> sym && sym != end) {
    str[len] = sym;
    ++len;
    if (size == len) {
      zharov::extension(str, size, size + k);
      size += k;
    }
  }
  str[len] = '\0';
  
  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}