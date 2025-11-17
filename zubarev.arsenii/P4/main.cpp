// new/delete	UNI-TWO	SHR-SYM
#include <iostream>
#include <iomanip>
#include <cctype>
using s_t = size_t;
s_t getline(std::istream& in, char* data, s_t size)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  s_t i = 0;
  for (; in && i < size; ++i) {
    in >> data[i];
  }
  data[i] = 0;
  if (is_skipws) {
    in >> std::skipws;
  }
  return i;
}
void push_back(char** arr, s_t& size, char value)
{
  size = size + 1;
  char* newArr = new char[size];
  for (int i = 0; i < size - 1; i++) {
    newArr[i] = (*arr)[i];
  }
  newArr[size - 1] = value;
  delete[] *arr;
  *arr = newArr;
}

char* getline(std::istream& in, s_t& s)
{
  char let;
  char* data = new char[0];

  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  while (true) {
    in >> let;
    if (let == '\n') {
      break;
    }
    push_back(&data, s, let);
  }
  let = '\0';
  push_back(&data, s, let);

  if (is_skipws) {
    in >> std::skipws;
  }

  return data;
}
std::ostream& outputMatrix(std::ostream& out, const char* const str, const s_t size)
{
  for (s_t i = 0; i < size; ++i) {
    out << str[i];
  }
  std::cout << '\n';
  return out;
}
size_t strlen(const char* s)
{
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}
void inputUNI_TWO()
{
  const char* secondStr = "def_";
  size_t secondSize = strlen(secondStr);
  size_t mainSize = 0;

  char* mainStr = getline(std::cin, mainSize);
  size_t itogSize = secondSize + mainSize;
  char* itogStr = new char[itogSize + 1];
  s_t countMain = 0, countSecond = 0, count = 0;

  while (countMain < mainSize || countSecond < secondSize) {
    if (countMain < mainSize)
      itogStr[count++] = mainStr[countMain++];

    if (countSecond < secondSize)
      itogStr[count++] = secondStr[countSecond++];
  }

  itogStr[count] = '\0';

  outputMatrix(std::cout, itogStr, itogSize);
}

bool inStr(const char* const str, const s_t size, const char let)
{
  for (int i = 0; i < size; ++i) {
    if (tolower(str[i]) == let) {
      return true;
    }
  }
  return false;
}
void inputSHR_SYM()
{
  const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
  ;
  const s_t alpSize = strlen(alphabet);

  s_t size = 0;
  char* mainStr = getline(std::cin, size);

  s_t itogSize = 0;
  char* itogStr = new char[0];
  for (s_t i = 0; i < alpSize; ++i) {
    if (!(inStr(mainStr, size, alphabet[i]))) {
      push_back(&itogStr, itogSize, alphabet[i]);
    }
  }

  push_back(&itogStr, itogSize, '\0');
  // itogStr[count] = '\0';

  outputMatrix(std::cout, itogStr, itogSize);
}

int main()
{
  inputUNI_TWO();
  inputSHR_SYM();
}
