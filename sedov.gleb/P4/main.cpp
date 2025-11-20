#include <iostream>
#include <cstddef>
#include <iomanip>
#include <memory>

namespace sedov
{
  char * extend(char * a, size_t k, size_t d);
  char * getline(std::istream & in, size_t s & s);
}

int main()
{
  size_t size = 0;
  char * str1 = reinterpret_cast< char * >(malloc(sizeof(char)));
  str1 = sedov::getline(std::cin, size);
  if (str1 == nullptr)
  {
    std::cerr << "Bad alloc\n";
    return 1;
  }
  std::cout << str1 << "\n";
  free(str1);
  return 0;
}

char * sedov::extend(char * a, size_t k, size_t d)
{
  char * newArray = reinterpret_cast< char * >(malloc(sizeof(char) * d));
  if (newArray != nullptr)
  {
    for (size_t i = 0; i < k; ++i)
    {
      newArray[i] = a[i];
    }
    free(a);
  }
  return newArray;
}

char * sedov::getline(std::istream & in, size_t & s)
{
  char * str = reinterpret_cast< char * >(malloc(sizeof(char)));
  if (str == nullptr)
  {
    return str;
  }
  str[0] = '\0';
  s = 0;
  bool isSkipWs = in.flags() & std::ios_base::skipws;
  if (isSkipWs)
  {
    in >> std::noskipws;
  }
  char t = 0;
  while (in >> t && t != '\n')
  {
    str = extend(str, s, s + 2);
    if (str == nullptr)
    {
      if (isSkipWs)
      {
        in >> std::skipws;
      }
      return str;
    }
    str[s] = t;
    str[s + 1] = '\0';
    ++s;
  }
  if (isSkipWs)
  {
    in >> std::skipws;
  }
  return str;
}
