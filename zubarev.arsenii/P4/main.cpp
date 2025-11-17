//new/delete	UNI-TWO	SHR-SYM
#include <iostream>
#include <iomanip>
using s_t=size_t;
s_t getline(std::istream& in, char* data, s_t size)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  s_t i = 0;
  for (; in && i < size; ++i) {
    in >> data[i];
  }
  data[i] = 0;
  if (is_skipws) {
    in >> std::skipws;
  }
  return i;
}
void push_back(char **arr,s_t &size,char value) {
  size=size+1;
  char *newArr=new char[size];
  for (int i=0;i<size-1;i++) {
    newArr[i]=(*arr)[i];
  }
  newArr[size-1]=value;
  delete [] *arr;
  *arr=newArr;
}

char * getline(std::istream & in, s_t & s) {
  char let;
  char * data=new char[0];

  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  while (true) {
    in>>let;
    if (let=='\n') {
      break;
    }
    push_back(&data,s,let);
  }
  let='\0';
  push_back(&data,s,let);

  if (is_skipws) {
    in >> std::skipws;
  }

  return data;
}

void inputUNI_TWO() {

}

int main()
{
  s_t size=0;
  char * a=getline(std::cin,size);
  for (s_t i=0;i<size;++i) {
    std::cout<<a[i];
  }
  std::cout<<'\n';
  delete [] a;
  // "Hi!" → 'H' 'i' "!' o
  // char str[] = "!!!!!";
  // s_t str_size = 5;
  // s_t k = getline(std::cin, str, str_size);
  // std::cout << str << "\n";

}
