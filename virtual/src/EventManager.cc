// self-introduced library
#include "EventManager.hh"
#include "VEvent.hh"

EventManager::EventManager()
{
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

