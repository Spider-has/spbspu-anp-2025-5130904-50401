#include <iostream>
#include <iomanip>
#include <memory>

namespace chernov {
  char * getline(std::istream & in, size_t & size);

}

char * chernov::getline(std::istream & in, size_t & size)
{
  bool is_skipws = in.flag() & std::ios_base::skipws;
  if (is_skipws) {
    is >> std::noskipws;
  }
  size_t batch_size = 100;
  size_t str_size = batch_size, i = 0;
  char * str = reinterpret_cast< int * >(malloc(sizeof(char) * str_size));

  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
}

int main()
{}
