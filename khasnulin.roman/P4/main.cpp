#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <istream>

namespace khasnulin
{

  namespace ErrMessages
  {
    const char *bad_alloc = "Failed to allocate dynamic memory for the input data.";
  }
  const size_t eng_alpabet_size = 26;

  size_t min(size_t lhs, size_t rhs);

  bool get_skip_ws_state(std::istream &in);
  void set_no_ws_skip_stream_state(std::istream &in, bool skip_ws);
  void return_skip_ws_previous_state(std::istream &in, bool skip_ws);

  const size_t len_increment = 50;
  char *make_str(size_t size);

  char *get_resized_str(const char *str, size_t oldSize, size_t newSize);
  void resize_str(char *&str, size_t oldSize, size_t newSize);

  bool check_ensure_capacity(char *&str, size_t i, size_t &size);

  char *get_line(std::istream &in, size_t &size);

  char *get_line_with_ws(std::istream &in, size_t &size);

  bool is_symb_included(const char *str, size_t size, char symb);

  void fill_eng_alphabet(char *str);

  char *SHR_SYM(char *result, const char *origin_str, size_t size);

  char *UNI_TWO(char *result, const char *str1, size_t size1, const char *str2, size_t size2);
}

int main()
{
  size_t size;
  char *str = khasnulin::get_line_with_ws(std::cin, size);
  if (!str)
  {
    std::cerr << khasnulin::ErrMessages::bad_alloc << "\n";
    return 1;
  }

  const size_t new_str_size = khasnulin::eng_alpabet_size + 1;
  char new_str[new_str_size] = {};

  khasnulin::SHR_SYM(new_str, str, size);
  std::cout << new_str << "\n";

  const char str2[] = "def_";
  const size_t size2 = 4;

  char *uni_str = khasnulin::make_str(size + size2);
  if (!uni_str)
  {
    free(str);
    std::cerr << khasnulin::ErrMessages::bad_alloc << "\n";
    return 1;
  }

  khasnulin::UNI_TWO(uni_str, str, size, str2, size2);
  std::cout << uni_str << "\n";

  free(str);
}

bool khasnulin::get_skip_ws_state(std::istream &in)
{
  return in.flags() & std::ios_base::skipws;
}

void khasnulin::set_no_ws_skip_stream_state(std::istream &in, bool skip_ws)
{
  if (skip_ws)
  {
    in >> std::noskipws;
  }
}

void khasnulin::return_skip_ws_previous_state(std::istream &in, bool skip_ws)
{
  if (skip_ws)
  {
    in >> std::skipws;
  }
}

char *khasnulin::make_str(size_t size)
{
  return reinterpret_cast<char *>(malloc(sizeof(char) * size));
}

size_t khasnulin::min(size_t lhs, size_t rhs)
{
  return lhs < rhs ? lhs : rhs;
}

char *khasnulin::get_resized_str(const char *str, size_t oldSize, size_t newSize)
{
  char *newStr = make_str(newSize);
  if (!newStr)
  {
    return nullptr;
  }
  size_t minS = min(oldSize, newSize);
  for (size_t i = 0; i < minS; i++)

  {
    newStr[i] = str[i];
  }
  return newStr;
}

void khasnulin::resize_str(char *&str, size_t oldSize, size_t newSize)
{
  char *newStr = get_resized_str(str, oldSize, newSize);
  free(str);
  str = newStr;
}

bool khasnulin::check_ensure_capacity(char *&str, size_t i, size_t &size)
{
  if (i == size)
  {
    resize_str(str, size, size + len_increment);
    if (!str)
    {
      size = 0;
      return false;
    }
    size += len_increment;
  }
  return true;
}

char *khasnulin::get_line(std::istream &in, size_t &size)
{
  char *str = make_str(len_increment);
  if (!str)
  {
    size = 0;
    return nullptr;
  }

  size = len_increment;
  size_t i = 0;

  char ch;
  while (in >> ch && ch != '\n')
  {
    if (!check_ensure_capacity(str, i, size))
    {
      return nullptr;
    }
    str[i] = ch;
    i++;
  }
  resize_str(str, size, i + 1);
  if (!str)
  {
    size = 0;
    return nullptr;
  }
  size = i;
  str[i] = 0;
  return str;
}

char *khasnulin::get_line_with_ws(std::istream &in, size_t &size)
{
  bool skip_ws = get_skip_ws_state(in);
  set_no_ws_skip_stream_state(in, skip_ws);

  char *str = get_line(in, size);

  return_skip_ws_previous_state(in, skip_ws);
  return str;
}

void khasnulin::fill_eng_alphabet(char *str)
{
  char startSymb = 'a';
  for (size_t i = 0; i < eng_alpabet_size; i++)
  {
    str[i] = startSymb;
    startSymb++;
  }
}

bool khasnulin::is_symb_included(const char *str, size_t size, char symb)
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

char *khasnulin::SHR_SYM(char *result, const char *origin_str, size_t size)
{
  char eng_alhp[eng_alpabet_size + 1] = {};
  fill_eng_alphabet(eng_alhp);
  eng_alhp[eng_alpabet_size] = '\0';
  size_t new_str_len = 0;
  for (size_t i = 0; i < eng_alpabet_size; i++)
  {
    if (!is_symb_included(origin_str, size, eng_alhp[i]))
    {
      result[new_str_len] = eng_alhp[i];
      new_str_len++;
    }
  }
  result[new_str_len] = 0;
  return result;
}

char *khasnulin::UNI_TWO(char *result, const char *str1, size_t size1, const char *str2, size_t size2)
{
  size_t minS = min(size1, size2);
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
  return result;
}
