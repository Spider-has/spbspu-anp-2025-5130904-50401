#include "file_array.hpp"
#include <iostream>
#include <fstream>
#include "variants.hpp"

std::istream& kuznetsov::initMatr(std::istream& input, int* mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; input && i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

int kuznetsov::processMatrix(std::istream& input, int* mtx, size_t rows, size_t cols, const char* out)
{
  initMatr(input, mtx, rows, cols);
  if (input.eof()) {
    std::cerr << "Not enough elements for matrix\n";
    return 1;
  } else if (input.fail()) {
    std::cerr << "Bad read\n";
    return 2;
  }

  int res1 = getCntColNsm(mtx, rows, cols);
  int res2 = getCntLocMax(mtx, rows, cols);

  std::ofstream output(out);
  output << res1 << '\n';
  output << res2 << '\n';

  return 0;
}

