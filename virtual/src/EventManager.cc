// self-introduced library
#include "EventManager.hh"
#include "VEvent.hh"

EventManager::EventManager()
{
  if(feventmanager)
    {
      std::cout << "Error! EventManager constructed twice." << std::endl;
      throw "EventManager::EventManager()";
    }
  feventmanager = this;
}

EventManager::~EventManager()
{
}

void EventManager::SetParameters()
{
  loop1manager->SetParameters();
}

void EventManager::ProcessOneEvent(std::shared_ptr<VEvent> event)
{
  currentevent = event;
  if(eventaction)
    eventaction->BeginOfEventAction(currentevent);
  Doprocess();
  if(eventaction)
    eventaction->EndOfEventAction(currentevent);
}

