// c++ STL
#include <cmath>

// self-introduced library
#include "grad_data.hh"
#include "runopgrad.hh"

grad_data loopgrad(grad_data first){
  grad_data data = first;
  double a = 1;
  double k = 0.1;
  grad_data error(1e-4,1e-4,1e-4,1e-4,1e-4,1e-4);

  for(int i = 1;true;i++)
      {
	double alpha = a*std::exp(-k*i);
	grad_data grad = grad_data::gradfunction(runopgrad::func,data);
	if( grad.nequalzero(error) )
	  {
	    break;
	  }
	data += (grad * alpha);
      }
  return data;
}
