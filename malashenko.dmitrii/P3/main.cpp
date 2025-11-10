//malloc/free
//CNT-LOC-MAX
//LFT-BOT-CLK
#include <iostream>
#include <cstddef>
#include <memory>
#include <fstream>

namespace malasenko {

  struct matrix {
    size_t rows;
    size_t cols;
    int * nums;
  };

  std::ostream & outMtx(std::ostream & out, const int* matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        out << matrix[i * cols + j] << " ";
      }
    }
    return out;
  }

  matrix readMtx(std::istream & in) {
    matrix mtx;
    in >> mtx.rows >> mtx.cols;
    int * nums = reinterpret_cast< int * >(malloc(mtx.rows * mtx.cols * sizeof(int)));
    if (!nums) {
      std::cerr << "malloc error\n";
      mtx.nums = nullptr;
      return mtx;
    }
    for (size_t i = 0; i < mtx.rows * mtx.cols; ++i) {
      in >> nums[i];
    }
    mtx.nums = nums;
    return mtx;
  }

  int cntLocMax(int * mtx, size_t rows, size_t cols) {
    if (rows <= 2 || cols <= 2) {
      return 0;
    }
    int res = 0;
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        if ((i != 0 && i != (rows-1)) && (j != 0 && j != (cols-1))) {
          int num = mtx[i * cols + j];
          bool isLocMax = true;
          for (int i_ind = -1; i_ind < 2; ++i_ind) {
            for (int j_ind = -1; j_ind < 2; ++j_ind) {
              if (i_ind != 0 && j_ind != 0) {
                if (num <= mtx[(i + i_ind) * cols + (j + j_ind)]) {
                  isLocMax = false;
                }
              }
            }
          }
          res+=isLocMax;
        }
      }
    }
    return res;
  }

  void lftBotClk(int * mtx, size_t rows, size_t cols) {
    if (cols <= 0 || rows <= 0) {
      return;
    }
    size_t total = rows * cols;
    size_t i = rows - 1, j = 0;
    size_t step = 0, cnt = 0;
    size_t top = 0,  botom = rows - 1, left = 0, right = cols - 1;
    while (cnt != total) {
      while (i > top && cnt < total) {
        mtx[i * cols + j] -= ++step;
        cnt++;
        i--;
      }
      left++;
      while (j < right && cnt < total) {
        mtx[i * cols + j] -= ++step;
        cnt++;
        j++;
      }
      top++;
      while (i < botom && cnt < total) {
        mtx[i * cols + j] -= ++step;
        cnt++;
        i++;
      }
      right--;
      while (j > left && cnt < total) {
        mtx[i * cols + j] -= ++step;
        cnt++;
        j--;
      }
      botom--;
    }
  }
}


int main(int argc, char ** argv) {
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  
  try {
    if (std::stoi(argv[1]) != 2 && std::stoi(argv[1]) != 1){
      std::cerr << "Wrong arguments" << "\n";
      return 1;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  namespace mal = malasenko;

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Problem with input file opening\n";
    return 1;
  }

  mal::matrix mtx;
  try {
    mtx = mal::readMtx(input);
  } catch (const std::exception &) {
    std::cerr << "Problem with file reading\n";
    return 2;
  }

  input.close();

  size_t rows = mtx.rows;
  size_t cols = mtx.cols;
  int * nums = mtx.nums;

  if (!nums) {
    std::cerr << "Problem with matrix\n";
    free(nums);
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Problem with output file opening\n";
    free(nums);
    return 1;
  }

  output << mal::cntLocMax(nums, rows, cols) << ' ';
  mal::lftBotClk(nums, rows, cols);
  mal::outMtx(output, nums, rows, cols);

  free(nums);
  return 0;
}
