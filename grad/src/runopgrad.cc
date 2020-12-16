// c++ STL
#include <map>
#include <functional>
#include <cstring>

// WCSim library
#include "WCSimRootGeom.hh"
#include "WCSimRootEvent.hh"

// self-introduced library
#include "runopgrad.hh"
#include "grad_data.hh"
#include "loopgrad.hh"

std::map<std::string,std::function<double(grad_data)>> runopgrad::funcmap
{ { "kari", grad_data::function } };
std::function<double(grad_data)> runopgrad::func = runopgrad::funcmap.at("kari");

std::map<std::string,std::function<grad_data(grad_data)>> runopgrad::loopfuncmap
{ { "kari", loopgrad } };

std::function<grad_data(grad_data)> runopgrad::loopfunc = runopgrad::loopfuncmap.at("kari");
WCSimRootGeom* runopgrad::wcsimrootgeom = nullptr;
WCSimRootTrigger* runopgrad::wcsimroottrigger = nullptr;
