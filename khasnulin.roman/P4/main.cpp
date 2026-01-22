#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <istream>

namespace khasnulin
{
  struct Line
  {
    char *str;
    size_t size;
    size_t capacity;
  };

  const size_t eng_alpabet_size = 26;

  bool getSkipWsState(std::istream &in);

  const size_t start_length = 10;
  const double capacity_coef = 1.5;
  char *makeStr(size_t size);
  Line *makeLine();
  Line **makeLines(size_t size);
  void clearLines(Line **lines, size_t size);
  void expandLines(Line ***lines, size_t size, size_t newSize);

  char *getResizedStr(const char *str, size_t oldSize, size_t newSize);

  using filter = bool (*)(char);
  char *getLine(std::istream &in, size_t &size, size_t &capacity, bool &eol, filter check);
  Line *buildLine(std::istream &in, bool &eol, filter check);
  bool isSpace(char ch);

  Line **getWordsFromLine(std::istream &in, size_t &size, filter check);
  void ensureCapacity(char **str, size_t &size, size_t &capacity);

  bool isSymbIncluded(const char *str, size_t size, char symb);

  void fillEngAlphabet(char *str);

  char *shrSym(char *result, const char *origin_str, size_t size);
  char *uniTwo(char *result, const char *str1, size_t size1, const char *str2, size_t size2);
}

int main()
{
  using namespace khasnulin;

  size_t size = 0;
  Line **lines = getWordsFromLine(std::cin, size, isSpace);
  if (!lines)
  {
    std::cerr << "Failed to allocate dynamic memory for the input data.\n";
    return 1;
  }

  if (lines[0]->size)
  {
    const size_t new_str_size = khasnulin::eng_alpabet_size + 1;
    char new_str[new_str_size] = {};

    for (size_t i = 0; i < size; ++i)
    {
      shrSym(new_str, lines[i]->str, lines[i]->size);
      std::cout << "[ SHR-SYM ] word: " << lines[i]->str << ", result: " << new_str << "\n";
    }

    const char str2[] = "def_";
    const size_t size2 = 4;
    char *uni_str = nullptr;

    for (size_t i = 0; i < size; ++i)
    {
      uni_str = makeStr(lines[i]->size + size2 + 1);
      if (!uni_str)
      {
        clearLines(lines, size);
        std::cerr << "Failed to allocate dynamic memory for the new string.\n";
        return 1;
      }

      uniTwo(uni_str, lines[i]->str, lines[i]->size, str2, size2);
      std::cout << "[ UNI-TWO ] string 1: " << lines[i]->str << ", string 2: " << str2
                << ", result: " << uni_str << "\n";
      free(uni_str);
    }

    clearLines(lines, size);
  }
  else
  {
    std::cerr << "Empty input error\n";
    clearLines(lines, size);
    return 1;
  }
}

bool khasnulin::isSpace(char ch)
{
  return ch == ' ';
}

bool khasnulin::getSkipWsState(std::istream &in)
{
  return in.flags() & std::ios_base::skipws;
}

char *khasnulin::makeStr(size_t size)
{
  return reinterpret_cast<char *>(malloc(sizeof(char) * size));
}

khasnulin::Line **khasnulin::makeLines(size_t size)
{
  return reinterpret_cast<Line **>(malloc(sizeof(struct Line *) * size));
}

khasnulin::Line *khasnulin::makeLine()
{
  return reinterpret_cast<Line *>(malloc(sizeof(struct Line)));
}

void khasnulin::clearLines(Line **lines, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    free(lines[i]->str);
    free(lines[i]);
  }
  free(lines);
}

void khasnulin::expandLines(Line ***lines, size_t size, size_t newSize)
{
  Line **newLines = makeLines(newSize);
  if (newLines)
  {
    for (size_t i = 0; i < size; ++i)
    {
      newLines[i] = (*lines)[i];
    }
    free(*lines);
  }
  *lines = newLines;
}

char *khasnulin::getResizedStr(const char *str, size_t oldSize, size_t newSize)
{
  char *newStr = makeStr(newSize);
  if (!newStr)
  {
    return nullptr;
  }
  size_t minS = std::min(oldSize, newSize);
  for (size_t i = 0; i < minS; i++)
  {
    newStr[i] = str[i];
  }
  return newStr;
}

char *khasnulin::getLine(std::istream &in, size_t &size, size_t &capacity, bool &eol, filter check)
{
  char *str = makeStr(start_length);
  if (!str)
  {
    capacity = 0;
    size = 0;
    return nullptr;
  }

  capacity = start_length;
  size = 0;
  char ch;
  while ((in >> ch) && !check(ch) && ch != '\n')
  {
    str[size] = ch;
    size++;
    ensureCapacity(&str, size, capacity);
    if (!str)
    {
      return nullptr;
    }
  }
  eol = (in.eof() || ch == '\n');
  str[size] = '\0';
  return str;
}

void khasnulin::ensureCapacity(char **str, size_t &size, size_t &capacity)
{
  if (size == capacity)
  {
    size_t new_capacity = capacity_coef * capacity;
    char *newStr = getResizedStr(*str, size, new_capacity);
    free(*str);
    if (!newStr)
    {
      capacity = 0;
      size = 0;
      *str = nullptr;
    }
    else
    {
      *str = newStr;
      capacity = new_capacity;
    }
  }
}

khasnulin::Line *khasnulin::buildLine(std::istream &in, bool &eol, filter check)
{
  size_t size;
  size_t capacity;
  char *str = getLine(in, size, capacity, eol, check);
  Line *line = makeLine();
  if (!str || !line)
  {
    free(line);
    free(str);
    return nullptr;
  }
  line->str = str;
  line->size = size;
  line->capacity = capacity;
  return line;
}

khasnulin::Line **khasnulin::getWordsFromLine(std::istream &in, size_t &size, filter check)
{
  bool skip_ws = getSkipWsState(in);
  if (skip_ws)
  {
    in >> std::noskipws;
  }

  Line **lines = nullptr;
  size_t lines_count = 0;

  bool eol = false;
  while (!eol)
  {
    Line *line = buildLine(in, eol, check);
    if (!line)
    {
      clearLines(lines, lines_count);
      return nullptr;
    }
    expandLines(&lines, lines_count, lines_count + 1);
    if (!lines)
    {
      free(line);
      clearLines(lines, lines_count);
      return nullptr;
    }
    lines[lines_count++] = line;
  }

  if (skip_ws)
  {
    in >> std::skipws;
  }
  size = lines_count;
  return lines;
}

void khasnulin::fillEngAlphabet(char *str)
{
  char startSymb = 'a';
  for (size_t i = 0; i < eng_alpabet_size; i++)
  {
    str[i] = startSymb;
    startSymb++;
  }
}

bool khasnulin::isSymbIncluded(const char *str, size_t size, char symb)
{
  for (size_t i = 0; i < size; i++)
  {
    if (std::tolower(str[i]) == std::tolower(symb))
    {
      return true;
    }
  }
  return false;
}

char *khasnulin::shrSym(char *result, const char *origin_str, size_t size)
{
  char eng_alhp[eng_alpabet_size + 1] = {};
  fillEngAlphabet(eng_alhp);
  eng_alhp[eng_alpabet_size] = '\0';
  size_t new_str_len = 0;
  for (size_t i = 0; i < eng_alpabet_size; i++)
  {
    if (!isSymbIncluded(origin_str, size, eng_alhp[i]))
    {
      result[new_str_len] = eng_alhp[i];
      new_str_len++;
    }
  }
  result[new_str_len] = '\0';
  return result;
}

char *khasnulin::uniTwo(char *result, const char *str1, size_t size1, const char *str2, size_t size2)
{
  size_t minS = std::min(size1, size2);
  for (size_t i = 0; i < minS; i++)
  {
    result[i * 2] = str1[i];
    result[i * 2 + 1] = str2[i];
  }
  const char *max_str = minS == size1 ? str2 : str1;
  size_t maxS = minS == size1 ? size2 : size1;
  size_t res_i = minS * 2;
  for (size_t i = minS; i < maxS; i++)
  {
    result[res_i] = max_str[i];
    res_i++;
  }
  result[res_i] = '\0';

  return result;
}
