// c++ STL
#include <map>
#include <functional>
#include <cstring>

// WCSim library
#include "WCSimRootGeom.hh"
#include "WCSimRootEvent.hh"

// self-introduced library
#include "grad_data.hh"
class runopgrad
{
public:
  // botsu not using
  runopgrad(){};
  virtual ~runopgrad(){};
  static std::map<std::string,std::function<double(grad_data)>> funcmap;
  static std::function<double(grad_data)> func;
  static std::map<std::string,std::function<grad_data(grad_data)>> loopfuncmap;
  static std::function<grad_data(grad_data)> loopfunc;
  static WCSimRootGeom* wcsimrootgeom;
  static WCSimRootTrigger* wcsimroottrigger;
};
