// c++ STL
#include <iostream>

// self-introduced library
#include "RunManager.hh"

RunManager::RunManager()
{}

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
  runaction->BeginOfRunAction(run);
  for(int i_event = 0;i_event < Nevent; i_event++)
    {
      std::cout << "event" << i_event << " start" << std::endl;
      ProcessOneEvent(i_event);
      std::cout << "event" << i_event << " end" << std::endl;
    }
  runaction->EndOfRunAction(run);
}

void RunManager::ProcessOneEvent(int i_event)
{
  currentevent = new VEvent();
  currentevent->SetEventID(i_event);
  eventmanager->ProcessOneEvent(currentevent);
  delete currentevent;
}

