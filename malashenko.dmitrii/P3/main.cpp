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

  int cntLocMax(int ** mtx, size_t rows, size_t cols) {
    int res = 0;

    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        if ((i != 0 || i != rows) && (j != 0 || j != cols)) {
          int num = mtx[i][j];
          bool isLocMax = (num > mtx[i+1][j]);
          isLocMax = isLocMax || (num > mtx[i-1][j]);
          isLocMax = isLocMax || (num > mtx[i][j-1]);
          isLocMax = isLocMax || (num > mtx[i][j+1]);
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