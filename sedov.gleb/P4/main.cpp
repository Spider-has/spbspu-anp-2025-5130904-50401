#include <iostream>
#include <cstddef>
#include <iomanip>
#include <memory>
#include <cctype>

namespace sedov
{
  char * extend(char * a, size_t k, size_t d);
  char * getline(std::istream & in, size_t & s);
  size_t getDifLat(const char * a, size_t s);
  size_t getCountOfVowels(const char * a, size_t s);
  void getRmvVow(const char * a, size_t s, char * str);
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

size_t sedov::getDifLat(const char * a, size_t s)
{
  size_t arrOfAlpha[52] = {0};
  for (size_t i = 0; i < s; ++i)
  {
    char ind = a[i];
    if (ind >= 'a' && ind <= 'z')
    {
      arrOfAlpha[ind - 'a']++;
    }
    else if (ind >= 'A' && ind <= 'Z')
    {
      arrOfAlpha[ind - 'A' + 26]++;
    }
  }
  size_t count = 0;
  for (size_t i = 0; i < 52; ++i)
  {
    if (arrOfAlpha[i])
    {
      count++;
    }
  }
  return count;
}

size_t sedov::getCountOfVowels(const char * a, size_t s)
{
  size_t count = 0;
  for (size_t i = 0; i < s; ++i)
  {
    char ind = a[i];
    char lInd = std::tolower(ind);
    if (lInd == 'a' || lInd == 'e' || lInd == 'i' || lInd == 'o' || lInd == 'u' || lInd == 'y')
    {
      count++;
    }
  }
  return count;
}

void sedov::getRmvVow(const char * a, size_t s, char * str)
{
  size_t count = 0;
  for (size_t i = 0; i < s; ++i)
  {
    char ind = a[i];
    char lInd = std::tolower(ind);
    if (lInd != 'a' && lInd != 'e' && lInd != 'i' && lInd != 'o' && lInd != 'u' && lInd != 'y')
    {
      str[count] = a[i];
      ++count;
    }
  }
  str[count] = '\0';
}
