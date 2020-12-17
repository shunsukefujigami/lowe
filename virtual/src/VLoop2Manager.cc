// self-introduced library
#include "VLoop2Manager.hh"

VLoop2Manager::VLoop2Manager()
{
}

VLoop2Manager::~VLoop2Manager()
{
   
}

void VLoop2Manager::SetParameters()
{
}

void VLoop2Manager::DoProcess(std::shared_ptr<VLoop2> loop2)
{
  currentloop2 = loop2;
  if(loop2action)
    loop2action->BeginOfLoop2Action(currentloop2);
  Doloop();
  if(loop2action)
    loop2action->EndOfLoop2Action(currentloop2);
}


