//malloc/free
//CNT-LOC-MAX
//LFT-BOT-CLK

/*
3 2 3
2 5 2 
3 2 3 
2 5 2 
3 2 3
*/
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
  

  matrix readMtx(std::istream & in) {
    matrix mtx;
    in >> mtx.rows >> mtx.cols;

    int * nums = reinterpret_cast< int * >(malloc(mtx.rows * mtx.cols * sizeof(int)));

    if (!nums) {
      std::cerr << "malloc error";
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
    int res = 0;

    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        if ((i != 0 || i != rows) && (j != 0 || j != cols)) {
          int num = mtx[i*rows + j];
          bool isLocMax = (num > mtx[(i+1)*rows + j]);
          isLocMax = isLocMax || (num > mtx[(i-1)*rows + j]);
          isLocMax = isLocMax || (num > mtx[(i)*rows + (j-1)]);
          isLocMax = isLocMax || (num > mtx[(i)*rows + (j+1)]);
          isLocMax = isLocMax || (num > mtx[(i+1)*rows + (j+1)]);
          isLocMax = isLocMax || (num > mtx[(i+1)*rows + (j-1)]);
          isLocMax = isLocMax || (num > mtx[(i-1)*rows + (j+1)]);
          isLocMax = isLocMax || (num > mtx[(i-1)*rows + (j-1)]);
          res+=isLocMax;
        }
      }
    }

    return res;
  }

  int lftBotClk(int ** mtx, size_t rows, size_t cols) {
    
  }

}

int main() {

}