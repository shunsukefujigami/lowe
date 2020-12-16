#include <memory>
#include "wrapped_function.hh"
#include <TLorentzVector.h>
#include "goodness_given_4Vector.hh"
#include "likelihood_direction.hh"
#include "runoption.hh"

wrapped_function::wrapped_function(std::shared_ptr<runoption> op)
 :option(op)
{}

double wrapped_function::goodness_minus(const double* a)
{
  TLorentzVector vector(a[0],a[1],a[2],a[3]);
  return -goodness_given_4Vector(vector,option);
}

double wrapped_function::likelihood_direction_minus(const double* a)
{
  TLorentzVector vector(a[0],a[1],a[2],a[3]);
  return -((option->lfunc)(vector,a[4],a[5],option));
}

double wrapped_function::goodness_x_f_direction_minus(const double* a)
{
  TLorentzVector vector(a[0],a[1],a[2],a[3]);
  return -((option->gffunc)(vector,a[4],a[5],option));
}
