#include <iostream>
int main()
{
  int* a = new int(0);
  int b = 0;
  std::cout << "address of *a is " << a << std::endl;
  std::cout << "address of b is " << &b << std::endl;
  delete a;
  return 0;
}

  
