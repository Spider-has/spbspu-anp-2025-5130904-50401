#include <iostream>
#include <fstream>
namespace madieva
{

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
  if (argv[1] > 2 || argv[1] == 0) {
    std::cerr << "First pharameter is out of range\n";
    return 1;
  }
  if (argv[1] != 1 || argv != 2) {
    std::cerr << "First parameter us not a number\n";
  }
  
}
