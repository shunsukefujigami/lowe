// c++ STL
#include <iostream>

// self-introduced library
#include "GoodnessParameters.hh"


GoodnessParameters::GoodnessParameters():goodnessfunctiontype(GoodnessFunctionType::normal),onegoodnessfunctiontype(OneGoodnessFunctionType::no_retro),sigma(5.)
{
}

GoodnessParameters::~GoodnessParameters()
{
}

void GoodnessParameters::Print()
{
  if(goodnessfunctiontype == GoodnessFunctionType::normal)
    {
      std::cout << "GoodnessFunctionType = normal" << std::endl;
    }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::no_retro)
    {
      std::cout << "OneGoodnessFunctionType = no_retro" << std::endl;
    }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::sum)
    {
      std::cout << "OneGoodnessFunctionType = sum" << std::endl;
    }
  if(onegoodnessfunctiontype == OneGoodnessFunctionType::compare)
    {
      std::cout << "OneGoodnessFunctionType = compare" << std::endl;
    }
  std::cout << "sigma = " << sigma << "(ns)" << std::endl;
  range->Printrange();
}

