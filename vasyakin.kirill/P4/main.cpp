#include <iostream>
#include <cstddef>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <limits>
namespace vasyakin
{
  size_t stringLength(const char* str);
  void cutLetters(const char* str, char* str1);
  void excludeCharsFromSecond(const char* str1, const char* str2, char* result);
  size_t extend(char*& a, size_t k, size_t k1);
  size_t getline(std::istream& input, size_t& k, char*& str);
  const size_t MAX = std::numeric_limits< size_t >::max();
}
size_t vasyakin::stringLength(const char* str)
{
  size_t count = 0;
  while(str[count] != '\0')
  {
    count++;
  }
  return count + 1;
}
int main()
{
  return 0;
}