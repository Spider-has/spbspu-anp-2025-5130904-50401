#include <iostream>
#include <iomanip>
#include <cctype>

namespace zharov
{
  char ** splitLine(char * str, const char sep, size_t size, size_t step, size_t & len);
  void extendArr(char *** str, size_t old_size, size_t new_size);
  char * getLine(std::istream & in, size_t size, size_t step, size_t & len, const char end);
  void extendStr(char ** str, size_t old_size, size_t new_size);
  char * LatRmv(const char * str, char * res);
  char * ShtSym(const char * str, char * res);
  void destroyArr(char ** arr, size_t len);
}

int main()
{
  size_t size = 10;
  size_t step = 5;
  size_t len = 0;
  const char end = '\0';
  char * str = nullptr;
  try {
    str = zharov::getLine(std::cin, size, step, len, end);
    if (std::cin.bad()) {
      delete[] str;
      std::cerr << "Bad enter\n";
      return 1;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "Bad alloc\n";
    return 1;
  }

  char ** arr_str = nullptr;
  size_t len_arr = 0;
  const char sep = '\n';
  try {
    arr_str = zharov::splitLine(str, sep, size, step, len_arr);
  } catch (const std::bad_alloc &) {
    delete[] str;
    std::cerr << "Bad alloc\n";
    return 1;
  }

  std::cout << '\n';
  for (size_t i = 0; i < len_arr; ++i) {
    char * line = arr_str[i];
    size_t c = 0;
    while (line[c] != '\0') {
      ++c;
    }
    char * res_1 = new char[c + 1];
    try {
      res_1 = zharov::LatRmv(line, res_1);
    } catch(const std::bad_alloc &) {
      delete[] line;
      delete[] res_1;
      std::cerr << "Bad alloc\n";
      return 1;
    }
    std::cout << "LAT-RMV №" << i + 1 << ": " << res_1 << "\n";
    delete[] res_1;
  }
  std::cout << '\n';
  for (size_t i = 0; i < len_arr; ++i) {
    char * line = arr_str[i];
    char * res_2 = new char[27];
    try {
      res_2 = zharov::ShtSym(line, res_2);
    } catch(const std::bad_alloc &) {
      delete[] line;
      delete[] res_2;
      std::cerr << "Bad alloc\n";
      return 1;
    }
    std::cout << "SHT_SYM №" << i + 1 << ": " << res_2 << "\n";
    delete[] res_2;
  }

  zharov::destroyArr(arr_str, len_arr);
  delete[] str;
}

void zharov::destroyArr(char ** arr, size_t len)
{
  for (size_t i = 0; i < len; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

void zharov::extendStr(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = (* str)[i];
  }
  delete[] * str;
  * str = new_str;
}

void zharov::extendArr(char *** arr_str, size_t old_size, size_t new_size)
{
  char ** new_arr = new char * [new_size];
  for (size_t i = 0; i < old_size; ++i) {
    new_arr[i] = (* arr_str)[i];
  }
  zharov::destroyArr(* arr_str, old_size);
  * arr_str = new_arr;
}

char ** zharov::splitLine(char * str, const char sep, size_t size, size_t step, size_t & len)
{
  char ** arr_str = new char * [size];
  bool is_last_space = true;
  size_t i = 0;
  size_t start_i = 0;
  for (; str[i] != '\0'; ++i) {
    if (len == size) {
      try {
        zharov::extendArr(& arr_str, size, size + step);
      } catch (const std::bad_alloc &) {
        zharov::destroyArr(arr_str, len);
      }
      size += step;
    }

    if (str[i] == sep) {
      if (!is_last_space) {
        char * new_str = nullptr;
        try {
          new_str = new char[i - start_i + 1];
        } catch (const std::bad_alloc &) {
          zharov::destroyArr(arr_str, len);
        }
        for (size_t j = 0; j < i - start_i; ++j) {
          new_str[j] = str[start_i + j];
        }
        arr_str[len] = new_str;
        ++len;
        is_last_space = true;
      }
      start_i = i + 1;
    } else {
      is_last_space = false;
    }
  }
  if (str[i-1] != sep) {
    char * new_str = nullptr;
    try {
      new_str = new char[i - start_i + 1];
    } catch (const std::bad_alloc &) {
      zharov::destroyArr(arr_str, len);
    }
    for (size_t j = 0; j < i - start_i; ++j) {
      new_str[j] = str[start_i + j];
    }
    arr_str[len] = new_str;
    ++len;
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
  while (in >> sym && sym != end && !in.eof()) {
    str[len] = sym;
    ++len;
    if (size == len) {
      try {
        zharov::extendStr(& str, size, size + step + 1);
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
      size += step;
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
