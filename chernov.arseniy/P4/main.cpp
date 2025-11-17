#include <iostream>
#include <iomanip>
#include <memory>

namespace chernov {
  void resize(char ** str, size_t old_size, size_t new_size);
  char * getline(std::istream & in, size_t & size);

}

void chernov::resize(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = reinterpret_cast< char * >(malloc(sizeof(char) * new_size)){};
  if (new_str == nullptr) {
    throw std::bad_alloc("badAllocError");
  }
  size_t size = std::min(old_size, new_size);
  for (size_t i = 0; i < size; ++i) {
    new_str[i] = (*str)[i];
  }
  free(*str);
  *str = new_str;
}

char * chernov::getline(std::istream & in, size_t & size)
{
  bool is_skipws = in.flag() & std::ios_base::skipws;
  if (is_skipws) {
    is >> std::noskipws;
  }
  size_t batch_size = 10;
  size_t str_size = 0, i = 0;
  char * str = nullptr;
  while (in) {
    if (i == str_size) {
      chernov::resize(&str, str_size, str_size + batch_size);
      str_size += batch_size;
    }
    char ch = 0;
    in >> ch;
    if (ch == '\n') {
      break;
    }
    str[i] = ch;
    ++i;
  }
  if (in.fail()) {
    throw std::runtime_error("inputError");
  }
  str[i] = 0;
  size = i;
  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}

int main()
{}
