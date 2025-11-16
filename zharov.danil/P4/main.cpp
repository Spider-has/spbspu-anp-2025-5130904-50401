#include <iostream>
#include <iomanip>
#include <cctype>

namespace zharov
{
  char ** getArrStr(std::istream & in, 
  size_t size_arr, size_t step_arr, size_t & len_arr, const char end_arr,
  size_t size, size_t step, const char end);
  char * getLine(std::istream & in, size_t size, size_t step, size_t & len, const char end);
  void extend(char ** str, size_t old_size, size_t new_size);
  char * LatRmv(const char * str, char * res);
  char * ShtSym(const char * str, char * res);
  void destroyArr(char ** arr, size_t len);
}

int main()
{
  size_t size_arr = 10;
  size_t step_arr = 5;
  size_t len_arr = 0;
  const char end_arr = '\n';
  size_t size = 10;
  size_t step = 5;
  const char end = ' ';
  char ** arr_str = nullptr;
  try {
    arr_str = zharov::getArrStr(std::cin, size_arr, step_arr, len_arr, end_arr, size, step, end);
    if (!std::cin) {
      zharov::destroyArr(arr_str, len_arr);
      std::cerr << "Bad enter\n";
      return 1;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "Bad alloc\n";
    return 1;
  }

  for (size_t i = 0; i < len_arr; ++i) {
    char * str = arr_str[i];
    size_t c = 0;
    while (str[c] != '\0') {
      ++c;
    }
    char * res_1 = new char[c + 1];
    try {
      res_1 = zharov::LatRmv(str, res_1);
    } catch(const std::bad_alloc &) {
      delete[] str;
      delete[] res_1;
      std::cerr << "Bad alloc\n";
      return 1;
    }
    std::cout << "LAT-RMV №" << i + 1 << ": " << res_1 << "\n";
    delete[] res_1;
  }
  std::cout << '\n';
  for (size_t i = 0; i < len_arr; ++i) {
    char * str = arr_str[i];
    char * res_2 = new char[27];
    try {
      res_2 = zharov::ShtSym(str, res_2);
    } catch(const std::bad_alloc &) {
      delete[] str;
      delete[] res_2;
      std::cerr << "Bad alloc\n";
      return 1;
    }
    std::cout << "SHT_SYM №" << i + 1 << ": " << res_2 << "\n";
    delete[] res_2;
  }
  
  zharov::destroyArr(arr_str, len_arr);
}

void zharov::destroyArr(char ** arr, size_t len)
{
  for (size_t i = 0; i < len; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

void zharov::extend(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size + 1];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = (* str)[i];
  }
  delete[] * str;
  * str = new_str;
}

char ** zharov::getArrStr(std::istream & in, 
  size_t size_arr, size_t step_arr, size_t & len_arr, const char end_arr,
  size_t size, size_t step, const char end)
{
  char ** arr_str = new char * [size_arr];
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char sym = ' ';
  while (in >> sym && sym != end_arr) {
    in.putback(sym);
    size_t str_len = 0;
    char * str = nullptr;
    try {
      str = zharov::getLine(in, size, step, str_len, end);
    } catch (const std::bad_alloc &) {
      zharov::destroyArr(arr_str, len_arr);
      throw;
    }
    if (str_len == 0) { 
      delete[] str;
      continue;
    }
    if (len_arr == size_arr) {
      char ** new_arr = nullptr;
      try {
        new_arr = new char*[size_arr + step_arr];
      } catch (const std::bad_alloc &) {
        zharov::destroyArr(arr_str, len_arr);
        throw;
      }
      for (size_t i = 0; i < len_arr; ++i) {
        new_arr[i] = arr_str[i];
      }
      delete[] arr_str;
      arr_str = new_arr;
      size_arr += step_arr;
    }
    arr_str[len_arr] = str;
    ++len_arr;
  }

  if (is_skipws) {
    in >> std::skipws;
  }
  return arr_str;
}

char * zharov::getLine(std::istream & in, size_t size, size_t step, size_t & len, char end)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char * str = new char[size + 1];
  char sym = ' ';
  while (in >> sym && sym != end && sym != '\n') {
    str[len] = sym;
    ++len;
    if (size == len) {
      try {
        zharov::extend(& str, size, size + step);
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
      size += step;
    }
  }
  if (sym == '\n') {
    in.putback(sym);
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
      if (letter == tolower((str[i]))) {
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
