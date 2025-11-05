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
        if ((i != 0 && i != (rows-1)) && (j != 0 && j != (cols-1))) {
          int num = mtx[i * cols + j];
          bool isLocMax = 0;
          for (int i_ind = -1; i_ind <= 1; ++i_ind) {
            for (int j_ind = -1; j_ind <= 1; ++j_ind) {
              if (i_ind != 0 && j_ind != 0) {
                isLocMax = isLocMax || (num > mtx[(i + i_ind) * cols + (j + j_ind)]);
              }
            }
          }
          res+=isLocMax;
        }
      }
    }

    return res;
  }

  int lftBotClk(int * mtx, size_t rows, size_t cols) {
    if (cols == 0 || rows == 0) return;

    size_t total = rows * cols;
    int i = rows - 1, j = 0;
    int step = 0, cnt = 0;

    int top = 0,  botom = rows - 1, left = 0, right = cols - 1;

      
    while (cnt != total) {
      while (i > top && cnt < total) {
        step++;
        mtx[i * cols + j] -= step;
        cnt++;
        i--; 
      }
      left++;
        
      while (j < right && cnt < total) {
        step++;
        mtx[i * cols + j] -= step;
        cnt++;
        j++; 
      }
      top++;

      while (i < botom && cnt < total) {
        step++;
        mtx[i * cols + j] -= step;
        cnt++;
        i++; 
      }
      right--;
      
      while (j > left && cnt < total) {
        step++;
        mtx[i * cols + j] -= step;
        cnt++;
        j--; 
      }
      botom--;
    }
  }

}


int main(int argc, char ** argv) {
  if (argc < 4) {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  }
  try {
    int _ = std::stoi(argv[1]);
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "First parameter is not a number" << "\n";
    return 1;
  }

  if ((argv[1] != "2") && (argv[1] != "1")) {
    std::cerr << "Wrong arguments" << "\n";
    return 1;
  } 

    
  namespace mal = malasenko;
  
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Problem with input file opening" << "\n";
    return 1;
  }

  mal::matrix mtx = mal::readMtx(input);
  input.close();

  size_t rows = mtx.rows;
  size_t cols = mtx.cols;
  int * nums = mtx.nums;

  if (!nums) {
    std::cerr << "Problem with matrix" << "\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Problem with output file opening" << "\n";
    return 1;
  }
  output << mal::cntLocMax(nums, rows, cols);
  mal::lftBotClk(nums, rows, cols);
  output << nums;

  free(nums);

  return 0;
}