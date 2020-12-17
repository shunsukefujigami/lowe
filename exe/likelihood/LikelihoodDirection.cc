// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
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
      std::shared_ptr<LikelihoodDirectionParameters> likelihooddirectionparameters = std::make_shared<LikelihoodDirectionParameters>();
      likelihooddirectionparameters->SetOneLikelihoodDirectionCalculateType(GetEnum<OneLikelihoodDirectionCalculateType>("ONELIKELIHOODDIRECTIONCALCULATETYPE"));
      likelihooddirectionparameters->SetFDirFuncNoretroType(GetEnum<FDirFuncNoretroType>("FDIRFUNCNORETROTYPE"));
      likelihooddirectionparameters->SetFDirFuncOnretroType(GetEnum<FDirFuncOnretroType>("FDIRFUNCONRETROTYPE"));
      likelihooddirectionparameters->SetAFuncNoretroType(GetEnum<AFuncNoretroType>("AFUNCNORETROTYPE"));
      likelihooddirectionparameters->SetAFuncOnretroType(GetEnum<AFuncOnretroType>("AFUNCONRETROTYPE"));
      AngleRange range = GetAngleRange();
      likelihooddirectionparameters->SetAngleRange(range);
      std::unique_ptr<LikelihoodDirectionManager> likelihooddirectionmanager(new LikelihoodDirectionManager(Getchar("INFILEDATA"),Getchar("INFILEGOODNESS")));
      likelihooddirectionmanager->SetVParameters(likelihooddirectionparameters);
      std::shared_ptr<LikelihoodDirectionRunAction> likelihooddirectionrunaction = std::make_shared<LikelihoodDirectionRunAction>(Getchar("OUTFILE"));
      likelihooddirectionmanager->SetRunAction(likelihooddirectionrunaction);
      std::shared_ptr<LikelihoodDirectionEventAction> likelihooddirectioneventaction = std::make_shared<LikelihoodDirectionEventAction>(likelihooddirectionrunaction);
      likelihooddirectionmanager->SetEventAction(likelihooddirectioneventaction);
      likelihooddirectionmanager->SetParameters();

      likelihooddirectionmanager->Run(Getint("NEVENTS"));
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
