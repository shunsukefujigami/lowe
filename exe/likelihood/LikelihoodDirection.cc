// c++ STL
#include <iostream>
#include <stdexcept>

// self-introduced library
#include "config.hh"
#include "AngleRange.hh"
#include "LikelihoodDirectionParameters.hh"
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRunAction.hh"
#include "LikelihoodDirectionEventAction.hh"

int main()
{
  try
    {
      LikelihoodDirectionParameters* likelihooddirectionparameters = new LikelihoodDirectionParameters();
      likelihooddirectionparameters->SetOneLikelihoodDirectionCalculateType(GetEnum<OneLikelihoodDirectionCalculateType>("ONELIKELIHOODDIRECTIONCALCULATETYPE"));
      likelihooddirectionparameters->SetFDirFuncNoretroType(GetEnum<FDirFuncNoretroType>("FDIRFUNCNORETROTYPE"));
      likelihooddirectionparameters->SetFDirFuncOnretroType(GetEnum<FDirFuncOnretroType>("FDIRFUNCONRETROTYPE"));
      likelihooddirectionparameters->SetAFuncNoretroType(GetEnum<AFuncNoretroType>("AFUNCNORETROTYPE"));
      likelihooddirectionparameters->SetAFuncOnretroType(GetEnum<AFuncOnretroType>("AFUNCONRETROTYPE"));
      AngleRange range = GetAngleRange();
      likelihooddirectionparameters->SetAngleRange(range);
      LikelihoodDirectionManager* likelihooddirectionmanager = new LikelihoodDirectionManager(Getchar("INFILEDATA"),Getchar("INFILEGOODNESS"));
      likelihooddirectionmanager->SetVParameters(likelihooddirectionparameters);
      LikelihoodDirectionRunAction* likelihooddirectionrunaction = new LikelihoodDirectionRunAction(Getchar("OUTFILE"));
      likelihooddirectionmanager->SetRunAction(likelihooddirectionrunaction);
      LikelihoodDirectionEventAction* likelihooddirectioneventaction = new LikelihoodDirectionEventAction(likelihooddirectionrunaction);
      likelihooddirectionmanager->SetEventAction(likelihooddirectioneventaction);
      likelihooddirectionmanager->SetLoop1Action(new VLoop1Action());
      likelihooddirectionmanager->SetLoop2Action(new VLoop2Action());
      likelihooddirectionmanager->SetParameters();

      likelihooddirectionmanager->Run(Getint("NEVENTS"));
      delete likelihooddirectionmanager;
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
