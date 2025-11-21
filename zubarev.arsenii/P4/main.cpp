#include <iostream>
#include <iomanip>
#include <cctype>

namespace zubarev
{
  size_t getline(std::istream& in, char* data, size_t size);
  void push_back(char** arr, size_t& size, char value);
  char* getline(std::istream& in, size_t& s);
  std::ostream& outputMatrix(std::ostream& out, const char* const str, const size_t size);
  size_t strlen(const char* s);
  int inputUNI_TWO(const char* const mainStr, size_t mainSize);
  bool inStr(const char* const str, const size_t size, const char let);
  int inputUNI_TWO(const char* mainStr, size_t mainSize);
  void solveUNI_TWO(const char* mainStr, size_t mainSize, char* finalStr);
  int inputSHR_SYM(const char* const mainStr, size_t mainSize);
  void solveSHR_SYM(const char* const mainStr, size_t mainSize, char* buf, size_t bufSize);
}

int main()
{
  namespace zub = zubarev;
  size_t mainSize = 0;
  char* mainStr = zub::getline(std::cin, mainSize);
  if (!mainStr) {
    std::cerr << "Input wrong\n";
    return 1;
  }
  zub::inputUNI_TWO(mainStr, mainSize);
  zub::inputSHR_SYM(mainStr, mainSize);
  delete[] mainStr;
}

void zubarev::push_back(char** arr, size_t& size, char value)
{
  char* newArr = nullptr;
  try {
    newArr = new char[size + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
  }
  for (size_t i = 0; i < size; i++) {
    newArr[i] = (*arr)[i];
  }
  newArr[size] = value;
  delete[] *arr;
  *arr = newArr;
  size = size + 1;
}

char* zubarev::getline(std::istream& in, size_t& s)
{
  char let;
  char* data = nullptr;

  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  while (true) {
    in >> let;
    if (!in) {
      return nullptr;
    }
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

std::ostream& zubarev::outputMatrix(std::ostream& out, const char* const str, const size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    out << str[i];
  }
  std::cout << '\n';
  return out;
}

size_t zubarev::strlen(const char* s)
{
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

int zubarev::inputUNI_TWO(const char* mainStr, size_t mainSize)
{
  const char* secondStr = "def_";
  size_t secondSize = strlen(secondStr);

  size_t finalSize = secondSize + mainSize + 1;
  char* finalStr = nullptr;

  try {
    finalStr = new char[finalSize + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
    return 1;
  }
  solveUNI_TWO(mainStr, mainSize, finalStr);
  outputMatrix(std::cout, finalStr, finalSize - 1);
  delete[] finalStr;
  return 0;
}

void zubarev::solveUNI_TWO(const char* mainStr, size_t mainSize, char* finalStr)
{
  const char* secondStr = "def_";
  size_t secondSize = strlen(secondStr);

  size_t countMain = 0, countSecond = 0;

  while (countMain < mainSize || countSecond < secondSize) {
    if (countMain < mainSize)
      *(finalStr++) = *(mainStr++);
    countMain++;
    if (countSecond < secondSize)
      *(finalStr++) = *(secondStr++);
    countSecond++;
  }
  *finalStr = '\0';
}

bool zubarev::inStr(const char* const str, const size_t size, const char let)
{
  for (size_t i = 0; i < size; ++i) {
    if (std::tolower(str[i]) == std::tolower(let)) {
      return true;
    }
  }
  return false;
}
int zubarev::inputSHR_SYM(const char* const mainStr, size_t mainSize)
{
  size_t itogSize = 0;
  char* itogStr = nullptr;
  try {
    itogStr = new char[itogSize + 1];
    itogSize = 28;
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
    return 1;
  }

  solveSHR_SYM(mainStr, mainSize, itogStr, itogSize);
  outputMatrix(std::cout, itogStr, itogSize);
  delete[] itogStr;
  return 0;
}

void zubarev::solveSHR_SYM(const char* const mainStr, size_t mainSize, char* buf, size_t bufSize)
{
  const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
  const size_t alpSize = strlen(alphabet);

  size_t tempSize = 0;

  for (const char* i = alphabet; i < alphabet + alpSize; ++i) {
    if (!(inStr(mainStr, mainSize, *i))) {
      *(buf++) = *i;
    }
  }
  *buf = '\0';
}
