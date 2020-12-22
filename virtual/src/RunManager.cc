// c++ STL
#include <iostream>

// self-introduced library
#include "RunManager.hh"

RunManager::RunManager()
{
  if(frunmanager)
    {
      std::cout << "Error! RunManager constructed twice." << std::endl;
      throw "RunManager::RunManager()";
    }
  frunmanager = this;
}

RunManager::~RunManager()
{
}



void RunManager::SetParameters()
{
  eventmanager->SetParameters();
}


void RunManager::Run(int Nevent)
{
  std::cout << Nevent << "event run start" << std::endl;
  if(runaction)
      runaction->BeginOfRunAction(run);
  for(int i_event = 0;i_event < Nevent; i_event++)
    {
      std::cout << "event" << i_event << " start" << std::endl;
      ProcessOneEvent(i_event);
      std::cout << "event" << i_event << " end" << std::endl;
    }
  if(runaction)
      runaction->EndOfRunAction(run);
}

void RunManager::ProcessOneEvent(int i_event)
{
  currentevent = std::make_shared<VEvent>();
  currentevent->SetEventID(i_event);
  eventmanager->ProcessOneEvent(currentevent);
}

