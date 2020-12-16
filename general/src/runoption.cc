// c++ STL
#include <map>
#include <functional>
#include <string>
#include <iostream>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "runoption.hh"
#include "goodness_given_4Vector.hh"
#include "one_goodness.hh"
#include "f_direction.hh"
#include "acceptance_pmt.hh"
#include "likelihood_direction.hh"
#include "goodness_x_f_direction.hh"

/*void runoption::SetTypeofrun(std::string nameoftype){
  type = nameoftype;
}

auto runoption::GetVariable(std::string nameofvariable){
  auto option = runoption::Getrunoption();
  return option.GetVariable(nameofvariable);
}

auto runoption::Getrunoption(){
  if(type == "goodness")
    return runop_g;
  else{
    std::cerr << "invalid name of type" << std::endl;
    throw "runoption::Getrunoption()";
  }
}

std::string runoption::type = "default"

using GFunc = decltype(goodness_given_4Vector);
using OGFunc = decltype(one_goodness_no_retro);

auto runoption_goodness::GetVariable(std::string nameofvariable){
  if(nameofvariable == "gfuncmap")
    return gfuncmap;
  else if(nameofvariable == "ogfuncmap")
    return ogfuncmap;
  else if(nameofvariable == "gfunc")
    return gfunc;
  else if(nameofvariable == "ogfunc")
    return ogfunc;
  else if(nameofvariable == "sigma")
    return sigma;
  else if(nameofvariable == "wcsimrootgeom")
    return wcsimrootgeom;
  else if(nameofvariable == "wcsimroottrigger")
    return wcsimroottrigger;
  else if(nameofvariable == "offset")
    return offset;
  else{
    std::cout << "invalid name of variable" << std::endl;
    throw "runoption_goodness::GetVariable()";
  }
}
*/
runoption::runoption()
  :gfuncmap{{ "normal",goodness_given_4Vector }}
  ,ogfuncmap{{ "no_retro",one_goodness_no_retro },
  { "on_retro",one_goodness_on_retro },
  { "sum", one_goodness_sum },
  { "compare", one_goodness_compare }}
  ,f_dirfuncmap{{ "prototype_noretro",f_direction_prototype_noretro }
  ,{"prototype_onretro",f_direction_prototype_onretro }
  ,{"bydata_noretro",f_direction_bydata_noretro}
  ,{"bydata_onretro",f_direction_bydata_onretro}}
  ,afuncmap{{ "prototype",acceptance_pmt_prototype}}
  ,lfuncmap{{ "no_retro",likelihood_direction_noretro}
  ,{ "on_retro",likelihood_direction_onretro}
  ,{ "sum",likelihood_direction_sum}}
  ,gffuncmap{{ "no_retro",goodness_x_f_direction_noretro }
  ,{ "on_retro",goodness_x_f_direction_onretro }
  ,{ "sum", goodness_x_f_direction_sum }}
  ,gfunc(gfuncmap.at("normal"))
  ,ogfunc(ogfuncmap.at("sum"))
  ,ogfunc_noretro(ogfuncmap.at("no_retro"))
  ,ogfunc_onretro(ogfuncmap.at("on_retro"))
  ,f_dirfunc_noretro(f_dirfuncmap.at("prototype_noretro"))
  ,f_dirfunc_onretro(f_dirfuncmap.at("prototype_onretro"))
  ,afunc(afuncmap.at("prototype"))
  ,lfunc(lfuncmap.at("no_retro"))
  ,gffunc(gffuncmap.at("no_retro"))
  ,gffunc_noretro(gffuncmap.at("no_retro"))
  ,gffunc_onretro(gffuncmap.at("on_retro"))
  ,gfuncname("normal")
  ,ogfuncname("sum")
  ,ogfunc_noretroname("no_retro")
  ,ogfunc_onretroname("on_retro")
  ,f_dirfunc_noretroname("prototype_noretro")
  ,f_dirfunc_onretroname("prototype_onretro")
  ,afuncname("prototype")
  ,lfuncname("no_retro")
  ,gffuncname("no_retro")
  ,gffunc_noretroname("no_retro")
  ,gffunc_onretroname("on_retro")
  ,sigma(5.)
  ,wcsimrootgeom(nullptr)
  ,wcsimroottrigger(nullptr)
  ,offset(950.)
  {}

runoption::runoption(WCSimRootGeom* wcsimrootgeom,WCSimRootTrigger* wcsimroottrigger)
  :gfuncmap{{ "normal",goodness_given_4Vector }}
  ,ogfuncmap{{ "no_retro",one_goodness_no_retro },
  { "on_retro",one_goodness_on_retro },
  { "sum", one_goodness_sum },
  { "compare", one_goodness_compare }}
 ,f_dirfuncmap{{ "prototype_noretro",f_direction_prototype_noretro },
  {"prototype_onretro",f_direction_prototype_onretro }
  ,{"bydata_noretro",f_direction_bydata_noretro}
  ,{"bydata_onretro",f_direction_bydata_onretro}}
  ,afuncmap{{ "prototype",acceptance_pmt_prototype}}
  ,lfuncmap{{ "no_retro",likelihood_direction_noretro}
  ,{ "on_retro",likelihood_direction_onretro}
  ,{ "sum",likelihood_direction_sum}}
  ,gffuncmap{{ "no_retro",goodness_x_f_direction_noretro }
  ,{ "on_retro",goodness_x_f_direction_onretro }
  ,{ "sum", goodness_x_f_direction_sum }}
  ,gfunc(gfuncmap.at("normal"))
  ,ogfunc(ogfuncmap.at("sum"))
  ,ogfunc_noretro(ogfuncmap.at("no_retro"))
  ,ogfunc_onretro(ogfuncmap.at("on_retro"))
  ,f_dirfunc_noretro(f_dirfuncmap.at("prototype_noretro"))
  ,f_dirfunc_onretro(f_dirfuncmap.at("prototype_onretro"))
  ,afunc(afuncmap.at("prototype"))
  ,lfunc(lfuncmap.at("no_retro"))
  ,gffunc(gffuncmap.at("no_retro"))
  ,gffunc_noretro(gffuncmap.at("no_retro"))
  ,gffunc_onretro(gffuncmap.at("on_retro"))
  ,gfuncname("normal")
  ,ogfuncname("sum")
  ,ogfunc_noretroname("no_retro")
  ,ogfunc_onretroname("on_retro")
  ,f_dirfunc_noretroname("prototype_noretro")
  ,f_dirfunc_onretroname("prototype_onretro")
  ,afuncname("prototype")
  ,lfuncname("no_retro")
  ,gffuncname("no_retro")
  ,gffunc_noretroname("no_retro")
  ,gffunc_onretroname("on_retro")
  ,sigma(5.)
  ,wcsimrootgeom(wcsimrootgeom)
  ,wcsimroottrigger(wcsimroottrigger)
  ,offset(950.)
  {}

runoption::runoption(WCSimRootGeom* wcsimrootgeom)
  :gfuncmap{{ "normal",goodness_given_4Vector }}
  ,ogfuncmap{{ "no_retro",one_goodness_no_retro },
  { "on_retro",one_goodness_on_retro },
  { "sum", one_goodness_sum },
  { "compare", one_goodness_compare }}
 ,f_dirfuncmap{{ "prototype_noretro",f_direction_prototype_noretro },
  {"prototype_onretro",f_direction_prototype_onretro }
  ,{"bydata_noretro",f_direction_bydata_noretro}
  ,{"bydata_onretro",f_direction_bydata_onretro}}
  ,afuncmap{{ "prototype",acceptance_pmt_prototype}}
  ,lfuncmap{{ "no_retro",likelihood_direction_noretro}
  ,{ "on_retro",likelihood_direction_onretro}
  ,{ "sum",likelihood_direction_sum}}
  ,gffuncmap{{ "no_retro",goodness_x_f_direction_noretro }
  ,{ "on_retro",goodness_x_f_direction_onretro }
  ,{ "sum", goodness_x_f_direction_sum }}
  ,gfunc(gfuncmap.at("normal"))
  ,ogfunc(ogfuncmap.at("sum"))
  ,ogfunc_noretro(ogfuncmap.at("no_retro"))
  ,ogfunc_onretro(ogfuncmap.at("on_retro"))
  ,f_dirfunc_noretro(f_dirfuncmap.at("prototype_noretro"))
  ,f_dirfunc_onretro(f_dirfuncmap.at("prototype_onretro"))
  ,afunc(afuncmap.at("prototype"))
  ,lfunc(lfuncmap.at("no_retro"))
  ,gffunc(gffuncmap.at("no_retro"))
  ,gffunc_noretro(gffuncmap.at("no_retro"))
  ,gffunc_onretro(gffuncmap.at("on_retro"))
  ,gfuncname("normal")
  ,ogfuncname("sum")
  ,ogfunc_noretroname("no_retro")
  ,ogfunc_onretroname("on_retro")
  ,f_dirfunc_noretroname("prototype_noretro")
  ,f_dirfunc_onretroname("prototype_onretro")
  ,afuncname("prototype")
  ,lfuncname("no_retro")
  ,gffuncname("no_retro")
  ,gffunc_noretroname("no_retro")
  ,gffunc_onretroname("on_retro")
  ,sigma(5.)
  ,wcsimrootgeom(wcsimrootgeom)
  ,wcsimroottrigger(nullptr)
  ,offset(950.)
  {}

void runoption::SetVariable(std::string valtype,std::string valname)
{
  if( valtype == "gfunc" ){
    if( valname == "normal" ){
      gfunc = gfuncmap.at("normal");
    }
    else{
      std::cout << "invalid valuename in gfunc" << std::endl;
      throw "runoption::SetVariable";
    }
    gfuncname = valname;
  }
  else if( valtype == "ogfunc" ){
    if( valname == "no_retro" ){
      ogfunc = ogfuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      ogfunc = ogfuncmap.at("on_retro");
    }
    else if( valname == "sum"){
      ogfunc = ogfuncmap.at("sum");
    }
    else if( valname == "compare"){
      ogfunc = ogfuncmap.at("compare");
    }
    else{
      std::cout << "invalid valuename in ogfunc" << std::endl;
      throw "runoption::SetVariable";
    }
    ogfuncname = valname;
  }
  else if( valtype == "ogfunc_noretro" ){
    if( valname == "no_retro" ){
      ogfunc_noretro = ogfuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      ogfunc_noretro = ogfuncmap.at("on_retro");
    }
    else if( valname == "sum"){
      ogfunc_noretro = ogfuncmap.at("sum");
    }
    else if( valname == "compare"){
      ogfunc_noretro = ogfuncmap.at("compare");
    }
    else{
      std::cout << "invalid valuename in ogfunc_noretro" << std::endl;
      throw "runoption::SetVariable";
    }
    ogfunc_noretroname = valname;
  }
  else if( valtype == "ogfunc_onretro" ){
    if( valname == "no_retro" ){
      ogfunc_onretro = ogfuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      ogfunc_onretro = ogfuncmap.at("on_retro");
    }
    else if( valname == "sum"){
      ogfunc_onretro = ogfuncmap.at("sum");
    }
    else if( valname == "compare"){
      ogfunc_onretro = ogfuncmap.at("compare");
    }
    else{
      std::cout << "invalid valuename in ogfunc_onretro" << std::endl;
      throw "runoption::SetVariable";
    }
    ogfunc_onretroname = valname;
  }
  else if( valtype == "f_dirfunc_noretro" ){
    if( valname == "prototype_noretro"){
      f_dirfunc_noretro = f_dirfuncmap.at("prototype_noretro");
    }
    else if( valname == "prototype_onretro"){
      f_dirfunc_noretro = f_dirfuncmap.at("prototype_onretro");
    }
    else if( valname == "bydata_noretro"){
      f_dirfunc_noretro = f_dirfuncmap.at("bydata_noretro");
    }
    else if( valname == "bydata_onretro"){
      f_dirfunc_onretro = f_dirfuncmap.at("bydata_onretro");
    }
    else{
      std::cout << "invalid valuename in f_dirfunc_noretro" << std::endl;
      throw "runoption::SetVariable";
    }
    f_dirfunc_noretroname = valname;
  }
  else if( valtype == "f_dirfunc_onretro" ){
    if( valname == "prototype_noretro"){
      f_dirfunc_onretro = f_dirfuncmap.at("prototype_noretro");
    }
    else if( valname == "prototype_onretro"){
      f_dirfunc_onretro = f_dirfuncmap.at("prototype_onretro");
    }
    else{
      std::cout << "invalid valuename in f_dirfunc_onretro" << std::endl;
      throw "runoption::SetVariable";
    }
    f_dirfunc_onretroname = valname;
  }
  else if( valtype == "afunc" ){
    if( valname == "prototype" ){
      afunc = afuncmap.at("prototype");
    }
    else{
      std::cout << "invalid valuename in afunc" << std::endl;
      throw "runoption::SetVariable";
    }
    afuncname = valname;
  }
  else if( valtype == "lfunc" ){
    if( valname == "no_retro"){
      lfunc = lfuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      lfunc = lfuncmap.at("on_retro");
    }
    else if( valname == "sum"){
      lfunc = lfuncmap.at("sum");
    }
    else{
      std::cout << "invalid valuename in lfunc" << std::endl;
      throw "runoption::SetVariable";
    }
    lfuncname = valname;
  }
  else if( valtype == "gffunc" ){
    if( valname == "no_retro"){
      gffunc = gffuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      gffunc = gffuncmap.at("on_retro");
    }
    else if( valname == "sum" ){
      gffunc = gffuncmap.at("sum");
    }
    else{
      std::cout << "invalid valuename in gffunc" << std::endl;
      throw "runoption::SetVariable";
    }
    gffuncname = valname;
  }
  else if( valtype == "gffunc_noretro" ){
    if( valname == "no_retro"){
      gffunc_noretro = gffuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      gffunc_noretro = gffuncmap.at("on_retro");
    }
    else if( valname == "sum" ){
      gffunc_noretro = gffuncmap.at("sum");
    }
    else{
      std::cout << "invalid valuename in gffunc_noretro" << std::endl;
      throw "runoption::SetVariable";
    }
    gffunc_noretroname = valname;
  }
  else if( valtype == "gffunc_onretro" ){
    if( valname == "no_retro"){
      gffunc_onretro = gffuncmap.at("no_retro");
    }
    else if( valname == "on_retro"){
      gffunc_onretro = gffuncmap.at("on_retro");
    }
    else if( valname == "sum" ){
      gffunc_onretro = gffuncmap.at("sum");
    }
    else{
      std::cout << "invalid valuename in gffunc_onretro" << std::endl;
      throw "runoption::SetVariable";
    }
    gffunc_onretroname = valname;
  }
  else{
    std::cout << "invalid valuetype" << std::endl;
    throw "runoption::SetVariable";
  }
}

void runoption::SetVariable(const char* valtype,const char* valname){
  std::string s_valtype = valtype;
  std::string s_valname = valname;
  SetVariable(s_valtype,s_valname);
}

void runoption::Print(){
  std::cout << "gfunc = " << gfuncname << std::endl;
  std::cout << "ogfunc = " << ogfuncname << std::endl;
  std::cout << "ogfunc_noretro = " << ogfunc_noretroname << std::endl;
  std::cout << "ogfunc_onretro = " << ogfunc_onretroname << std::endl;
  std::cout << "f_dirfunc_noretro = " << f_dirfunc_noretroname << std::endl;
  std::cout << "f_dirfunc_onretro = " << f_dirfunc_onretroname << std::endl;
  std::cout << "afunc = " << afuncname << std::endl;
  std::cout << "lfunc = " << lfuncname << std::endl;
  std::cout << "gffunc = " << gffuncname << std::endl;
  std::cout << "gffunc_noretro = " << gffunc_noretroname << std::endl;
  std::cout << "gffunc_onretro = " << gffunc_onretroname << std::endl;
  std::cout << "sigma = " << sigma << "ns" << std::endl;
  if(wcsimrootgeom == nullptr){
    std::cout << "wcsimrootgeom = nullptr" << std::endl;
  }
  else{
    std::cout << "wcsimrootgeom is not nullptr" << std::endl;
  }
  if(wcsimroottrigger == nullptr){
    std::cout << "wcsimroottrigger = nullptr" << std::endl;
  }
  else{
    std::cout << "wcsimroottrigger is not nullptr" << std::endl;
  }
  std::cout << "offset = " << offset << "ns" << std::endl;
}
/*runoption::runoption(const runoption& option) noexcept
:gfuncmap(option.gfuncmap)
  ,ogfuncmap(option.ogfuncmap)
  ,gfunc(option.gfunc)
  ,ogfunc(option.ogfunc)
  ,sigma(option.sigma)
  ,wcsimrootgeom( new WCSimRootGeom( *(option.wcsimrootgeom)))
  ,wcsimroottrigger( new WCSimRootTrigger( *(option.wcsimroottrigger)))
{}
*/
runoption::~runoption(){
  //  delete wcsimrootgeom;
  //  delete wcsimroottrigger;
}

