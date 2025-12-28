#include <iostream>
#include <cctype>
#include <iomanip>


namespace kuznetsov {
  char* getLine(std::istream& in, size_t& size);
  char** getWords(std::istream& in, size_t& words, size_t** sizes, bool(*c)(char));
  void extend(char** str, size_t oldSize, size_t newSize);
  void extend(char*** arr, size_t old);
  void extend(size_t** arr, size_t old);
  void removeVow(char* buff, const char* str);
  int checkSeqSym(const char* str);
  bool isSpace(char t);
  void cut(char** str, size_t k);
  void deleting(char** arr, size_t k);
}

int main()
{
  namespace kuz = kuznetsov;
  size_t size = 0;
  char** str = nullptr;
  size_t* sizes = nullptr;

  str = kuz::getWords(std::cin, size, &sizes, kuz::isSpace);

  if (!std::cin) {
    delete[] str;
    return 1;
  }
  for (size_t i = 0; i < size; ++i) {
    char* buffer = nullptr;
    try {
      buffer = new char[sizes[i] + 1] {};
    } catch (const std::bad_alloc&) {
      delete[] sizes;
      kuz::deleting(str, size);
      std::cerr << "Bad alloc buffer\n";
      return 2;
    }

    kuz::removeVow(buffer, str[i]);
    std::cout << buffer << '\n';
    std::cout << kuz::checkSeqSym(str[i]) << '\n';

    delete[] buffer;
  }

  delete[] sizes;
  kuz::deleting(str, size);
}

void kuznetsov::cut(char** str, size_t k)
{
  char* arr = new char[k];
  for (size_t i = 0; i < k; ++i) {
    arr[i] = (*str)[i];
  }
  delete[] *str;
  *str = arr;
}

char* kuznetsov::getLine(std::istream& in, size_t& size)
{
  char* buff = new char[2] {};
  size_t blockSize = 1;
  size_t strLen = 0;
  bool isSkipws = in.flags() & std::ios::skipws;
  in >> std::noskipws;
  while (in >> buff[strLen++] && buff[strLen - 1] != '\n') {
    if (strLen == blockSize) {
      try {
        size_t newSize = blockSize +  blockSize / 2 + 1;
        extend(&buff, strLen, newSize + 1);
        blockSize = newSize;
      } catch (const std::bad_alloc&) {
        delete[] buff;
        throw;
      }
    }
  }
  strLen--;
  cut(&buff, strLen);
  size = strLen;
  buff[strLen] = '\0';
  if (isSkipws) {
    in >> std::skipws;
  }
  return buff;
}

bool kuznetsov::isSpace(char t)
{
  return std::isspace(t);
}

void kuznetsov::extend(char*** arr, size_t old)
{
  char** newArray = new char*[old + 1];
  for (size_t i = 0; i < old; ++i) {
    newArray[i] = (*arr)[i];
  }
  newArray[old] = nullptr;
  delete[] *arr;
  *arr = newArray;
}

void kuznetsov::extend(size_t** arr, size_t old)
{
  size_t* newArray = new size_t[old + 1];
  for (size_t i = 0; i < old; ++i) {
    newArray[i] = (*arr)[i];
  }
  delete[] *arr;
  *arr = newArray;
}

void kuznetsov::deleting(char** arr, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

char** kuznetsov::getWords(std::istream& in, size_t& words, size_t** sizes, bool(*spliter)(char))
{
  size_t strCount = 0;
  char** strArray = new char*[0];
  size_t* strLens = new size_t[0];
  bool isSkipws = in.flags() & std::ios::skipws;
  in >> std::noskipws;

  char* buff = nullptr;
  char t = '\0';
  try {
    while (t != '\n' && in ) {
      t = '\0';
      extend(&strArray, strCount);
      extend(&strLens, strCount);
      buff = new char[2];
      size_t strLen = 0;
      size_t blockSize = 1;
      while (!spliter(t) && in) {
        in >> t;
        buff[strLen++] = t;
        if (strLen == blockSize) {
          size_t newSize = blockSize +  blockSize / 2 + 1;
          extend(&buff, strLen, newSize + 1);
          blockSize = newSize;
        }
      }
      buff[strLen - 1] = '\0';
      cut(&buff, strLen);
      strArray[strCount] = buff;
      strLens[strCount] = strLen - 1;
      strCount++;
    }
  } catch (const std::bad_alloc&) {
    delete[] buff;
    delete[] strLens;
    deleting(strArray, strCount);
    throw;
  }

  if (isSkipws) {
    in >> std::skipws;
  }
  words = strCount;
  *sizes = strLens;
  return strArray;
}

void kuznetsov::extend(char** str, size_t oldSize, size_t newSize)
{
  char* extendedStr = new char[newSize];
  for (size_t i = 0; i < oldSize; ++i) {
    extendedStr[i] = (*str)[i];
  }
  for (size_t i = oldSize; i < newSize; ++i) {
    extendedStr[i] = 0;
  }
  delete[] *str;
  *str = extendedStr;
}

void kuznetsov::removeVow(char* buff, const char* str)
{
  char vow[] = "aeiou";
  size_t nextPast = 0;
  for (size_t i = 0; str[i] != '\0'; ++i ) {
    size_t j = 0;
    for (; j < 5; ++j) {
      if (tolower(str[i]) == vow[j]) {
        break;
      }
    }
    if (j == 5) {
      buff[nextPast] = str[i];
      nextPast++;
    }
  }
  buff[nextPast] = '\0';
}

int kuznetsov::checkSeqSym(const char* str)
{
  if (str[0] == '\0') {
    return 0;
  }
  for (size_t i = 1; str[i] != '\0'; ++i) {
    if (str[i - 1] == str[i]) {
      return 1;
    }
  }
  return 0;
}
