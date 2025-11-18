#include <iostream>
// #include <iomanip>
#include <cctype>

namespace zubarev
{
  using s_t = size_t;
  s_t getline(std::istream& in, char* data, s_t size);
  void push_back(char** arr, s_t& size, char value);
  char* getline(std::istream& in, s_t& s);
  std::ostream& outputMatrix(std::ostream& out, const char* const str, const s_t size);
  size_t strlen(const char* s);
  int inputUNI_TWO();
  bool inStr(const char* const str, const s_t size, const char let);
  int inputSHR_SYM();
} // namespace zubarev

int main()
{
  namespace zub = zubarev;
  zub::inputUNI_TWO();
  zub::inputSHR_SYM();
}

void zubarev::push_back(char** arr, s_t& size, char value)
{
  char* newArr = nullptr;
  try {
    newArr = new char[size + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
  }
  for (s_t i = 0; i < size; i++) {
    newArr[i] = (*arr)[i];
  }
  newArr[size] = value;
  delete[] *arr;
  *arr = newArr;
  size = size + 1;
}

char* zubarev::getline(std::istream& in, s_t& s)
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

std::ostream& zubarev::outputMatrix(std::ostream& out, const char* const str, const s_t size)
{
  for (s_t i = 0; i < size; ++i) {
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

int zubarev::inputUNI_TWO()
{
  const char* secondStr = "def_";
  size_t secondSize = strlen(secondStr);
  size_t mainSize = 0;

  char* mainStr = getline(std::cin, mainSize);
  if (!mainStr) {
    return 1;
  }

  size_t itogSize = secondSize + mainSize;
  char* itogStr = nullptr;

  try {
    itogStr = new char[itogSize + 1];
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed for square matrix\n";
    return 1;
  }

  s_t countMain = 0, countSecond = 0, count = 0;

  while (countMain < mainSize || countSecond < secondSize) {
    if (countMain < mainSize)
      itogStr[count++] = mainStr[countMain++];

    if (countSecond < secondSize)
      itogStr[count++] = secondStr[countSecond++];
  }

  itogStr[count] = '\0';

  outputMatrix(std::cout, itogStr, itogSize - 1);
  delete[] mainStr;
  delete[] itogStr;
  return 0;
}

bool zubarev::inStr(const char* const str, const s_t size, const char let)
{
  for (s_t i = 0; i < size; ++i) {
    if (std::tolower(str[i]) == std::tolower(let)) {
      return true;
    }
  }
  return false;
}

int zubarev::inputSHR_SYM()
{
  const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
  const s_t alpSize = strlen(alphabet);

  s_t size = 0;
  char* mainStr = getline(std::cin, size);
  if (!mainStr) {
    mainStr = nullptr;
    size = 0;
  }

  s_t itogSize = 0;
  char* itogStr = nullptr;

  for (s_t i = 0; i < alpSize; ++i) {
    if (!(inStr(mainStr, size, alphabet[i]))) {
      push_back(&itogStr, itogSize, alphabet[i]);
    }
  }

  push_back(&itogStr, itogSize, '\0');

  outputMatrix(std::cout, itogStr, itogSize);
  delete[] mainStr;
  delete[] itogStr;
  return 0;
}
