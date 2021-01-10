// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
// self-introduced library
#include "config.hh"
#include "AngleRange.hh"
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionCalculateManager.hh"
#include "OneLikelihoodDirectionCalculateManager.hh"
#include "LikelihoodDirectionRunAction.hh"
#include "LikelihoodDirectionEventAction.hh"
#include "likelihood.hh"
#include "fdirection.hh"
#include "afunction.hh"

int main()
{
  try
    {
      std::shared_ptr<LikelihoodDirectionManager> likelihooddirectionmanager = std::make_shared<LikelihoodDirectionManager>(Getchar("INFILEGOODNESS"));
      std::shared_ptr<LikelihoodDirectionEventManager> likelihooddirectioneventmanager = std::make_shared<LikelihoodDirectionEventManager>();
      std::shared_ptr<LikelihoodDirectionCalculateManager> likelihooddirectioncalculatemanager = std::make_shared<LikelihoodDirectionCalculateManager>();
      std::shared_ptr<OneLikelihoodDirectionCalculateManager> onelikelihooddirectioncalculatemanager = std::make_shared<OneLikelihoodDirectionCalculateManager>(Getchar("ONELIKELIHOODDIRECTIONCALCULATETYPE"));
      likelihooddirectionmanager->SetProcessManager();
      likelihooddirectioneventmanager->SetProcessManager();
      likelihooddirectioncalculatemanager->SetProcessManager();
      onelikelihooddirectioncalculatemanager->SetProcessManager();
      likelihooddirectionmanager->SetNextManager(likelihooddirectioneventmanager);
      likelihooddirectioneventmanager->SetNextManager(likelihooddirectioncalculatemanager);
      likelihooddirectioncalculatemanager->SetNextManager(onelikelihooddirectioncalculatemanager);
      AngleRange range = GetAngleRange();
      likelihooddirectioneventmanager->SetAngleRange(range);
      std::shared_ptr<likelihood> likelihoodfuncnoretro = std::make_shared<likelihoodnoretro>();
      std::shared_ptr<likelihood> likelihoodfunconretro = std::make_shared<likelihoodonretro>();
      std::shared_ptr<fdirection> fdirectionfuncnoretro = std::make_shared<fdirbydatanoretro>();
      std::shared_ptr<fdirection> fdirectionfunconretro = std::make_shared<fdirbydataonretro>();
      std::shared_ptr<afunction> afunctionnoretro = std::make_shared<afuncprototype>();
      std::shared_ptr<afunction> afunctiononretro = std::make_shared<afuncprototype>();
      onelikelihooddirectioncalculatemanager->Setlikelihoodfuncnoretro(likelihoodfuncnoretro);
      onelikelihooddirectioncalculatemanager->Setlikelihoodfunconretro(likelihoodfunconretro);
      onelikelihooddirectioncalculatemanager->Setfdirectionnoretro(fdirectionfuncnoretro);
      onelikelihooddirectioncalculatemanager->Setfdirectiononretro(fdirectionfunconretro);
      onelikelihooddirectioncalculatemanager->Setafunctionnoretro(afunctionnoretro);
      onelikelihooddirectioncalculatemanager->Setafunctiononretro(afunctiononretro);
      onelikelihooddirectioncalculatemanager->SetParameters();
      std::shared_ptr<LikelihoodDirectionRunAction> likelihooddirectionrunaction = std::make_shared<LikelihoodDirectionRunAction>(Getchar("OUTFILE"),Getchar("INFILEGOODNESS"));
      likelihooddirectionmanager->SetAction(likelihooddirectionrunaction);
      std::shared_ptr<LikelihoodDirectionEventAction> likelihooddirectioneventaction = std::make_shared<LikelihoodDirectionEventAction>(likelihooddirectionrunaction);
      likelihooddirectioneventmanager->SetAction(likelihooddirectioneventaction);
      std::shared_ptr<Process> process = std::make_shared<Process>();
      likelihooddirectionmanager->SetProcess(process);
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
