// c++ STL
#include <iostream>
#include <stdexcept>

// self-introduced library
#include "config.hh"
#include "CSearch_range.hh"
#include "GoodnessParameters.hh"
#include "GoodnessManager.hh"
#include "GoodnessRunAction.hh"

int main()
{
  try
    { 
      GoodnessParameters* goodnessparameters = new GoodnessParameters();
      goodnessparameters->SetGoodnessLoop4VectorType(GetEnum<GoodnessLoop4VectorType>("GOODNESSLOOP4VECTORTYPE"));
      goodnessparameters->SetGoodnessFunctionType(GetEnum<GoodnessFunctionType>("GOODNESSFUNCTIONTYPE"));
      goodnessparameters->SetOneGoodnessFunctionType(GetEnum<OneGoodnessFunctionType>("ONEGOODNESSFUNCTIONTYPE"));
      goodnessparameters->Setsigma(Getdouble("SIGMA"));
      CSearch_range range = GetCSearch_range();
      goodnessparameters->SetSearch_range(&range);
      goodnessparameters->Print();
      GoodnessManager* goodnessmanager = new GoodnessManager(Getchar("INFILE"));
      goodnessmanager->SetGoodnessParameters(goodnessparameters);
      GoodnessRunAction* goodnessrunaction = new GoodnessRunAction(Getchar("OUTFILE"));
      goodnessmanager->SetGoodnessRunAction(goodnessrunaction);
      goodnessmanager->SetGoodnessEventAction(new GoodnessEventAction(goodnessrunaction));
      goodnessmanager->SetGoodnessCalculateAction(new GoodnessCalculateAction());
      goodnessmanager->SetOneGoodnessCalculateAction(new OneGoodnessCalculateAction());
      goodnessmanager->SetParameters();
      
      goodnessmanager->Run(Getint("NEVENTS"));
      delete goodnessmanager;
    }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  catch(std::out_of_range&)
    {
      std::cout << "exception std::out_of_range" << std::endl;
    }
  return 0;
}

