int abc(int &a, int b, const int &c)
{
  return a + b + c;
}

int main()
{
  int a = 1;
  const int &b = 2;
  int &c = a;
  abc(c, b, c);
}