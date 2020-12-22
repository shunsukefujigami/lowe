// c++ STL
#include <iostream>
// self-introduced library
#include "VLoop1Manager.hh"
#include "VLoop1.hh"

VLoop1Manager::VLoop1Manager()
{
  if(floop1manager)
    {
      std::cout << "Error! Loop1Manager constructed twice." << std::endl;
      throw "VLoop1Manager::VLoop1Manager()";
    }
}

VLoop1Manager::~VLoop1Manager()
{
}

void VLoop1Manager::SetParameters()
{
  loop2manager->SetParameters();
}

void VLoop1Manager::DoProcess(std::shared_ptr<VLoop1> loop1)
{
  currentloop1 = loop1;
  if(loop1action)
    loop1action->BeginOfLoop1Action(currentloop1);
  Doloop();
  if(loop1action)
    loop1action->EndOfLoop1Action(currentloop1);
}

