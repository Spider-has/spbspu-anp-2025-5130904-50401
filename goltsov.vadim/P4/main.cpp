#include <iostream>
#include <iomanip>

namespace goltsov
{
  void increase_size(char** str, size_t & size);
  void reduce_size(char** str, size_t & size);
  char* SPC_RMV(char* str, size_t size, size_t& new_size);
  void getstr(std::istream & in, char** str, size_t & size);
  int HAS_SAM(char* el1, char* el2, size_t size);
}

int main()
{
  char* el1 = nullptr;
  size_t size1 = 0;
  char* el2 = nullptr;
  size_t size2 = 0;
  try
  {
    goltsov::increase_size(&el1, size1);
    goltsov::increase_size(&el2, size2);
  }
  catch(const std::bad_alloc &e)
  {
    delete[] el1;
    delete[] el2;
    return 1;
  }

  goltsov::getstr(std::cin, &el1, size1);
  goltsov::getstr(std::cin, &el2, size2);

  int has_sam = goltsov::HAS_SAM(el1, el2, size1 > size2 ? size2 : size1);

  char str[10] = " a  a d  ";
  size_t size = 10;

  size_t new_size = 0;
  char* new_str = goltsov::SPC_RMV(str, size, new_size);

  std::cout << has_sam << '\n';
  std::cout << new_str << '\n';
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

char* goltsov::SPC_RMV(char* str, size_t size, size_t& new_size)
{
  char* new_str = nullptr;
  increase_size(&new_str, new_size);

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

void goltsov::getstr(std::istream & in, char** str, size_t & size)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }

  char a = '\0';
  while (std::cin >> a && a != ' ' && a != '\n')
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

int goltsov::HAS_SAM(char* el1, char* el2, size_t size)
{
  for (size_t i = 0; i + 1 < size; ++i)
  {
    for (size_t j = 0; j+1 < size; ++j)
    {
      if (el1[i] == el2[j])
      {
        return 1;
      }
    }
  }
  return 0;
}
