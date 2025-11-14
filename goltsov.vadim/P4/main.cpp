#include <iostream>
#include <iomanip>

namespace goltsov
{
  void increase_size(char** str, size_t & size);
  void reduce_size(char** str, size_t & size);
  void getline(std::istream & in, char** str, size_t & size);
  char* SPC_RMV(char* str, size_t size, size_t& new_size);
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

  size_t new_size = 0;
  char* new_str = goltsov::SPC_RMV(str, size, new_size);
  
  std::cout << new_str << '\n';
  std::cout << new_size << '\n';
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

void goltsov::reduce_size(char** str, size_t & size)
{
  --size;
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

char* goltsov::SPC_RMV(char* str, size_t size, size_t& new_size)
{
  char* new_str = nullptr;
  increase_size(& new_str, new_size);
  
  size_t i = 0;
  while (str[i] == ' ')
  {
    ++i;
  }
  if (str[i] == '\0')
  {
    new_str[new_size - 1] = '\0';
    return new_str;
  }
  new_str[new_size - 1] = str[i];
  increase_size(& new_str, new_size);
  ++i;

  for (; i + 1 < size; ++i)
  {
    if (!(str[i] == ' ' && new_str[new_size - 2] == ' '))
    {
      new_str[new_size - 1] = str[i];
      increase_size(& new_str, new_size);
    }
  }
  if (new_str[new_size - 2] == ' ')
  {
    reduce_size(& new_str, new_size);
  }
  new_str[new_size - 1] = '\0';
  return new_str;
}