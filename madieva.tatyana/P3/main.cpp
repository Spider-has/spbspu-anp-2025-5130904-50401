#include <iostream>
#include <fstream>
namespace madieva
{
  const size_t max_static_size = 10000;
  int * create_array(char number, size_t rows, size_t cols) {
    if (number == '1') {
      if (rows * cols > max_static_size) {
        throw std::bad_alloc();
      }
      static int array[max_static_size] = {};
      return array;
    }
    else {
      return new int[rows * cols];
    }
  }
  void free_array(int * array, char number) {
    if (number ==  '2') {
      delete []array;
    }
  }
  bool read_matrix(std::ifstream& input, size_t rows, size_t cols, int * array)
  {
    for (size_t i = 0; i < rows * cols; i++) {
      input >> array[i];
      if (input.fail()) {
        return false;
      }
    }
    return true;
  }
  void change_in_spiral(int * matrix, size_t rows, size_t cols) {
    size_t top = 0;
    size_t left = 0;
    size_t bottom = rows - 1;
    size_t right = cols - 1;
    int subtraction = 1;
    matrix[bottom * cols + left] -= subtraction;
    while (left <= right && top <= bottom) {
      for (size_t i =  bottom; i > top; --i) {
        matrix[i * cols + left] -= subtraction;
        subtraction++;
      }
      if (left == right) {
        break;
      }
      for (size_t i =  left; i < right; ++i) {
        matrix[top * cols + i] -= subtraction;
        subtraction++;
      }
      if (bottom == top) {
        break;
      }
      for (size_t i =  top + 1; i <=  bottom; ++i) {
        matrix[i * cols + right] -= subtraction;
        subtraction++;
      }
      if (left + 1 == right) {
        break;
      }
      for (size_t i =  right; i > left; --i) {
        matrix[bottom * cols + i] -= subtraction;
        subtraction++;
      }
      right--;
      left++;
      top++;
      bottom--;
    }
  }
 }

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (argv[1][0] < '0' || argv[1][0] > '9') {
    std::cerr << "First parameter us not a number\n";
    return 1;
  }
  if (argv[1][0] != '1' && argv[1][0] != '2') {
    std::cerr << "First pharameter is out of range\n";
    return 1;
  }
  const char* arg = argv[1];
  const char* inputFile = argv[2];
  const char* outputFile = argv[3];


  std::ifstream input(inputFile);
  if (!input.is_open()) {
    std::cerr << "Error when opening input file\n";
    return 2;
  }
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (input.fail()) {
    std::cerr << "Irregular matrix size\n";
    return 2;
  }
  if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0)) {
    std::cerr << "Irregular matrix size\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    std::ofstream output(outputFile);
    output << 0 << 0 << "\n"; 
    return 0;
}
  int* matrix = nullptr;
  try {
    matrix = madieva::create_array(arg[0], rows, cols);
  } catch (const std::bad_alloc& e) {
    std::cerr << "Out of memory\n";
    return 2;
  }
  if (!madieva::read_matrix) {
    std::cerr << "Error reading matrix\n";
    madieva::free_array(matrix, arg[1]);
    return 2;
  }
  input.close();
  madieva::free_array(matrix, arg[0]);
  return 0;
}

