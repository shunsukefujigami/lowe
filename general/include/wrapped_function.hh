#ifndef WRAPPED_FUNCTION_HH
#define WRAPPED_FUNCTION_HH
#include <memory>
#include "runoption.hh"

class wrapped_function
{
  // this class supply wrapped function for the purpose of hide runoption

public:
  wrapped_function(std::shared_ptr<runoption> op);
  virtual ~wrapped_function(){};
  double goodness_minus(const double* a);
  double likelihood_direction_minus(const double* a);
  double goodness_x_f_direction_minus(const double* a);
private:
  std::shared_ptr<runoption> option;
};

#endif
