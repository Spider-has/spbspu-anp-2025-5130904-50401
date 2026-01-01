#include <iostream>
#include <fstream>
#include <memory>
#include <cctype>
#include "file_array.hpp"

namespace kuznetsov {
  const size_t MAX_SIZE = 10'000;
}

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (!std::isdigit(argv[1][0])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t rows = 0, cols = 0;
  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Can't open file\n";
    return 2;
  }

  input >> rows >> cols;
  if (!input) {
    std::cerr << "Bad reading size\n";
    return 2;
  }
  int mtx[kuz::MAX_SIZE] {};
  int* mtrx = nullptr;
  int* mt = nullptr;
  if (argv[1][0] == '1') {
    mtrx = mtx;
  } else {
    mt = reinterpret_cast< int* >(malloc(sizeof(int) * rows * cols));
    if (mt == nullptr) {
      std::cerr << "Bad alloc\n";
      return 3;
    }
    mtrx = mt;
  }
  int statusExit = kuz::processMatrix(input, mtrx, rows, cols, argv[3]);
  free(mt);
  return statusExit;
}

