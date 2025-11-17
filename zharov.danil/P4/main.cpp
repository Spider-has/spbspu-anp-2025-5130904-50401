#include <iostream>
#include <iomanip>
#include <cctype>

namespace zharov
{
  char ** splitLine(char * str, const char sep);
  char * getLine(std::istream & in, size_t size, size_t k, size_t & len, const char end);
  void extend(char ** str, size_t old_size, size_t new_size);
  char * LatRmv(const char * str, char * res);
  char * ShtSym(const char * str, char * res);
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
  char * res_1 = new char[len + 1];
  char * res_2 = new char[27];
  try {
    res_1 = zharov::LatRmv(str, res_1);
    res_2 = zharov::ShtSym(str, res_2);
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

void zharov::extend(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size+1];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = (* str)[i];
  }
  delete[] * str;
  * str = new_str;
}

char ** splitLine(char * str, const char sep, size_t size, size_t step, size_t & len)
{
  char ** arr_str = new char * [size];
  bool is_last_space = true; 
  size_t c = 0;
  size_t i = 0;
  size_t start_i = 0;
  for (; str[i] != '\0'; ++i) {
    if (str[i] == sep) {
      if (!is_last_space) {
        char * new_str = new char[i - start_i + 1];
        for (size_t j = 0; j < i - start_i; ++j) {
          new_str[j] = str[start_i + j];
        }
        arr_str[c] = new_str;
        ++c;
        is_last_space = true;
      }
      start_i = i + 1;
    } else {
      is_last_space = false;
    }
  }
  if (str[i-1] != sep) {
    char * new_str = new char[i - start_i + 1];
    for (size_t j = 0; j < i - start_i; ++j) {
      new_str[j] = str[start_i + j];
    }
    arr_str[c] = new_str;
    ++c;
  }


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
        zharov::extend(& str, size, size + k);
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

char * zharov::LatRmv(const char * str, char * res)
{
  size_t c = 0;
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (!isalpha(str[i])) {
      res[c] = str[i];
      ++c;
    }
  }
  res[c] = '\0';
  return res;
}

char * zharov::ShtSym(const char * str, char * res)
{
  bool found = false;
  size_t c = 0;
  for (char letter = 'a'; letter <= 'z'; letter++){
    for (size_t i = 0; str[i] != '\0'; ++i) {
      if (letter == (str[i])) {
        found = true;
        break;
      }
    }
    if (!found) {
      res[c] = letter;
      ++c;
    }
    found = false;
  }
  res[c] = '\0';
  return res;
}
