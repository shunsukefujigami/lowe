// c++ STL
#include <iostream>
#include <stdexcept>
#include <memory>
// self-introduced library
#include "config.hh"
#include "GoodnessMinimizeManager.hh"
#include "GoodnessMinimizeEventManager.hh"
#include "fsumgoodness.hh"


int main()
{
  try
    {
      std::shared_ptr<GoodnessMinimizeManager> goodnessminimizemanager = std::make_shared<GoodnessMinimizeManager>(Getchar("INFILELIKELIHOOD"));
      std::shared_ptr<GoodnessMinimizeEventManager> goodnessminimizeeventmanager = std::make_shared<GoodnessMinimizeEventManager>();
      goodnessminimizemanager->SetProcessManager();
      goodnessminimizeeventmanager->SetProcessManager();
      goodnessminimizemanager->SetNextManager(goodnessminimizeeventmanager);
      goodnessminimizeeventmanager->Setmaxfunctioncalls(Getint("MAXFUNCTIONCALLS"));
      goodnessminimizeeventmanager->Setmaxiterations(Getint("MAXITERATIONS"));
      goodnessminimizeeventmanager->Settolerance(Getdouble("TOLERANCE"));
      int nvar = 6;
      double step[nvar] = {Getdouble("STEPX"),Getdouble("STEPY"),Getdouble("STEPZ"),Getdouble("STEPT"),Getdouble("STEPCOSTHETA"),Getdouble("STEPPHI")};
      double lower[nvar] = {Getdouble("LOWERX"),Getdouble("LOWERY"),Getdouble("LOWERZ"),Getdouble("LOWERT"),Getdouble("LOWERCOSTHETA"),Getdouble("LOWERPHI")};
      double upper[nvar] = {Getdouble("UPPERX"),Getdouble("UPPERY"),Getdouble("UPPERZ"),Getdouble("UPPERT"),Getdouble("UPPERCOSTHETA"),Getdouble("UPPERPHI")};
      goodnessminimizeeventmanager->Setstep(step);
      goodnessminimizeeventmanager->Setlower(lower);
      goodnessminimizeeventmanager->Setupper(upper);
      //      std::shared_ptr<fsumgoodnesssum> sumgoodnesssum = std::make_shared<fsumgoodnesssum>();
      fsumgoodnesssum* sumgoodnesssum = new fsumgoodnesssum();
      sumgoodnesssum->Setsigma(Getdouble("SIGMA"));
      sumgoodnesssum->Setsigmaangle(Getdouble("SIGMAANGLE"));
      sumgoodnesssum->Setonretrocorrection(Getdouble("ONRETROCORRECTION"));
      goodnessminimizeeventmanager->Setfsumgoodness(sumgoodnesssum);
      std::shared_ptr<Process> process = std::make_shared<Process>();
      goodnessminimizemanager->SetProcess(process);
      goodnessminimizemanager->Run(Getint("NEVENTS"));
      delete sumgoodnesssum;
    }
  catch(const char* str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  catch(std::out_of_range&)
    {
      std::cout << "exception std::out_of_range&" << std::endl;
    }
  return 0;
}

      
      
	
