#include <iostream>
#include <iomanip>

namespace goltsov
{
  void increase_size(char** str, size_t & size);
  void getline(std::istream & in, char** str, size_t & size);
}

int main()
{
  char* str = nullptr;
  size_t size = 0;
  try
  {
    goltsov::increase_size(&str, size);
  }
  catch(const std::bad_alloc &e)
  {
    delete[] str;
    return 1;
  }

  goltsov::getline(std::cin, &str, size);

  std::cout << str << '\n';
  std::cout << size << '\n';
  
}

void goltsov::increase_size(char** str, size_t & size)
{
  ++size;
  char* new_str = new char[size];
  for (size_t i = 0; i + 1 < size; ++i)
  {
    new_str[i] = str[0][i];
  }
  delete[] *str;
  *str = new_str;
}

void goltsov::getline(std::istream & in, char** str, size_t & size)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }

  char a = '\0';
  while (std::cin >> a && a != '\n')
  {
    str[0][size-1] = a;
    goltsov::increase_size(str, size);
  }
  
  str[0][size-1] = '\0';

  if (is_skipws)
  {
    in >> std::skipws;
  }
}