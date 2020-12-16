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

void EventManager::ProcessOneEvent(VEvent* event)
{
  currentevent = event;
  eventaction->BeginOfEventAction(currentevent);
  Doprocess();
  eventaction->EndOfEventAction(currentevent);
}

