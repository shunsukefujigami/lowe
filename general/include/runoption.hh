#ifndef RUNOPTION_HH
#define RUNOPTION_HH

// c++ STL
#include <string>
#include <map>
#include <functional>

// ROOT library
#include <TLorentzVector.h>

// WCSim library
#include "WCSimRootGeom.hh"
#include "WCSimRootEvent.hh"

// self-introduced library
#include "goodness_given_4Vector.hh"
#include "one_goodness.hh"
#include "f_direction.hh"
#include "acceptance_pmt.hh"
#include "likelihood_direction.hh"
#include "goodness_x_f_direction.hh"

class runoption
{
  // class for manage of run of program. Storage running option e.g. function type to use.

  using GFunc = decltype(goodness_given_4Vector);
  using OGFunc = decltype(one_goodness_no_retro);
  using f_dirFunc = decltype(f_direction_prototype_noretro);
  using aFunc = decltype(acceptance_pmt_prototype);
  using lFunc = decltype(likelihood_direction_noretro);
  using gfFunc = decltype(goodness_x_f_direction_noretro);
public:
  runoption();
  runoption(WCSimRootGeom* wcsimrootgeom,WCSimRootTrigger* wcsimroottrigger);
  runoption(WCSimRootGeom* wcsimrootgeom);
  //  runoption(const runoption&) noexcept;
  virtual ~runoption();
  void SetVariable(std::string valtype,std::string valname);
  void SetVariable(const char* valtype,const char* valname);
  void Print();
  std::map<std::string,std::function<GFunc>> gfuncmap;
  std::map<std::string,std::function<OGFunc>> ogfuncmap;
  std::map<std::string,std::function<f_dirFunc>> f_dirfuncmap;
  std::map<std::string,std::function<aFunc>> afuncmap;
  std::map<std::string,std::function<lFunc>> lfuncmap;
  std::map<std::string,std::function<gfFunc>> gffuncmap;
  std::function<GFunc> gfunc;
  std::function<OGFunc> ogfunc;
  std::function<OGFunc> ogfunc_noretro;
  std::function<OGFunc> ogfunc_onretro;
  std::function<f_dirFunc> f_dirfunc_noretro;
  std::function<f_dirFunc> f_dirfunc_onretro;
  std::function<aFunc> afunc;
  std::function<lFunc> lfunc;
  std::function<gfFunc> gffunc;
  std::function<gfFunc> gffunc_noretro;
  std::function<gfFunc> gffunc_onretro;
  std::string gfuncname;
  std::string ogfuncname;
  std::string ogfunc_noretroname;
  std::string ogfunc_onretroname;
  std::string f_dirfunc_noretroname;
  std::string f_dirfunc_onretroname;
  std::string afuncname;
  std::string lfuncname;
  std::string gffuncname;
  std::string gffunc_noretroname;
  std::string gffunc_onretroname;
  double sigma;
  WCSimRootGeom* wcsimrootgeom;
  WCSimRootTrigger* wcsimroottrigger;
  double offset;
};

/*
class runoption
{
public:
  runoption();
  virtual ~runoption(){};
  static void SetTypeofrun(std::string nameoftype);
  static auto GetVariable(std::string nameofvariable);
  static auto Getrunoption();
private:
  static std::string type;
  static runoption_goodness runop_g;
};
*/

#endif
