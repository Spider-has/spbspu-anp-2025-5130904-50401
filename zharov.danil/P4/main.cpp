#include <iostream>
#include <iomanip>
#include <cctype>

namespace zharov
{
  char * getLine(std::istream & in, size_t size, size_t k, size_t & len, const char end);
  void extend(char *& str, size_t old_size, size_t new_size);
  char * LatRmv(const char * str, size_t len);
  char * ShtSym(const char * str, size_t len);
}

int main()
{
  size_t size = 10;
  size_t k = 5;
  size_t len = 0;
  const char end = '\n';
  char * str = nullptr;
  try {
    str = zharov::getLine(std::cin, size, k, len, end);
    if (!std::cin) {
      delete[] str;
      std::cerr << "Bad enter\n";
      return 1;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "Bad alloc\n";
    return 1;
  }
  char * res_1 = nullptr;
  char * res_2 = nullptr;
  try {
    res_1 = zharov::LatRmv(str, len);
    res_2 = zharov::ShtSym(str,len);
  } catch(const std::bad_alloc &) {
    delete[] str;
    delete[] res_1;
    std::cerr << "Bad alloc\n";
    return 1;
  }
  std::cout << "LAT-RMV: " << res_1 << "\n";
  std::cout << "SHT_SYM: " << res_2 << "\n";
  delete[] res_1;
  delete[] res_2;
  delete[] str;
}

void zharov::extend(char *& str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size+1];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = str[i];
  }
  delete[] str;
  str = new_str;
}

char * zharov::getLine(std::istream & in, size_t size, size_t k, size_t & len, char end)
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
      try {
        zharov::extend(str, size, size + k);
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
      size += k;
    }
  }
  str[len] = '\0';

  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}

char * zharov::LatRmv(const char * str, size_t len)
{
  char * new_str = new char[len+1];
  size_t c = 0;
  for (size_t i = 0; i < len; ++i) {
    if (!isalpha(str[i])) {
      new_str[c] = str[i];
      ++c;
    }
  }
  new_str[c] = '\0';
  return new_str;
}

char * zharov::ShtSym(const char * str, size_t len)
{
  char * new_str = new char[27];
  bool found = false;
  size_t c = 0;
  for (char letter = 'a'; letter <= 'z'; letter++){
    for (size_t i = 0; i < len; ++i) {
      if (letter == (str[i])) {
        found = true;
        break;
      }
    }
    if (!found) {
      new_str[c] = letter;
      ++c;
    }
    found = false;
  }
  new_str[c] = '\0';
  return new_str;
}
