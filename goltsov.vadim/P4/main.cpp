#include <iostream>
#include <iomanip>

namespace goltsov
{
  void increase_size(char** str, size_t& size);
  void reduce_size(char** str, size_t& size);
  void getline(std::istream& in, char** str, size_t& size);
  char* SPC_RMV(char* str, size_t size, size_t& new_size);
  void getstr(std::istream& in, char** str, size_t& size);
  int HAS_SAM(char* el1, char* el2, size_t size);
}

int main()
{
  char* str = nullptr;
  size_t size = 0;
  try
  {
    goltsov::increase_size(& str, size);
  }
  catch(const std::bad_alloc &e)
  {
    delete[] str;
    return 1;
  }

  goltsov::getline(std::cin, & str, size);

  if (std::cin.eof())
  {
    return 1;
  }

  size_t new_size = 0;
  char* new_str = goltsov::SPC_RMV(str, size, new_size);

  char my_str[4] = "abs";
  size_t my_size = 4;

  int has_sam = goltsov::HAS_SAM(str, my_str, (size < my_size ? size : my_size));

  std::cout << "Expects output (return 0) with second string " << "\"" << my_str << "\"" << ": " << has_sam << '\n';
  std::cout << "Expects output (return 0): " << new_str << '\n';

  delete[] str;
  delete[] new_str;

  return 0;
}

void goltsov::increase_size(char** str, size_t& size)
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

void goltsov::reduce_size(char** str, size_t& size)
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

void goltsov::getline(std::istream& in, char** str, size_t& size)
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

  if (in.eof())
  {
    return;
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
