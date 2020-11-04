#include "Math/Functor.h"
#include <functional>

double function(const double* a,bool b){
  return a[0];
}

class wrapped_function_test
{
public:
  wrapped_function_test(bool b);
  virtual ~wrapped_function_test(){};
  double f(const double* a);
private:
  bool b;
};

wrapped_function_test::wrapped_function_test(bool b)
  : b(b){}

double wrapped_function_test::f(const double* a){
  return function(a,b);
}

int main(){
  wrapped_function_test func(true);
  //  std::function<double(double*)> func = std::bind(function,std::placeholders::_1,b);
  ROOT::Math::Functor f(&func,&wrapped_function_test::f,1);
  return 0;
}
