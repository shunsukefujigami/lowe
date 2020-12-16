// c++ STL
#include <iostream>
// self-introduced library
#include "VLoop1Manager.hh"
#include "VLoop1.hh"

VLoop1Manager::VLoop1Manager()
{
}

VLoop1Manager::~VLoop1Manager()
{
}

void VLoop1Manager::SetParameters()
{
  loop2manager->SetParameters();
}

void VLoop1Manager::DoProcess(VLoop1* loop1)
{
  currentloop1 = loop1;
  loop1action->BeginOfLoop1Action(currentloop1);
  Doloop();
  loop1action->EndOfLoop1Action(currentloop1);
}

