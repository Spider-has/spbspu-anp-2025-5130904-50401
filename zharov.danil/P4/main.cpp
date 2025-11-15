#include <iostream>
#include <iomanip>

namespace zharov
{
  char * getline(std::istream & in, size_t size, size_t k, size_t & len, const char end);
  void extension(char * str, size_t old_size, size_t new_size);
}

int main()
{
  char * str = new char[6];
  size_t size = 5;

  std::cin >>std::noskipws;

  for (size_t i = 0; i < size; ++i) {
    std::cin >> str[i];
  }

  std::cout << str << "\n";
}

void zharov::extension(char * str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size+1];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = str[i];
  }
  delete[] str;
  str = new_str;
  delete new_str;
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
      extension(str, size, size + k);
      size += k;
    }
  }
  str[len] = '\0';
  
  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}