#ifndef EVENTMANAGER_HH
#define EVENTMANAGER_HH

#include "VEvent.hh"
#include "VEventAction.hh"
#include "VLoop1Action.hh"
#include "VLoop2Action.hh"
#include "VLoop1Manager.hh"

class EventManager
{
public:
  EventManager();
  virtual ~EventManager();
  virtual void SetParameters();
  virtual void ProcessOneEvent(VEvent* event);
  virtual void Doprocess() = 0;
  void SetLoop1Manager(VLoop1Manager* manager)
  {
    loop1manager = manager;
  }
  void SetLoop2Manager(VLoop2Manager* manager)
  {
    loop1manager->SetLoop2Manager(manager);
  }
  
  void SetEventAction(VEventAction* action)
  {
    eventaction = action;
  }
  void SetLoop1Action(VLoop1Action* action)
  {
    loop1manager->SetLoop1Action(action);
  }
  void SetLoop2Action(VLoop2Action* action)
  {
    loop1manager->SetLoop2Action(action);
  }
protected:
  VEventAction* eventaction = nullptr;
  VEvent* currentevent = nullptr;
  VLoop1Manager* loop1manager = nullptr;
};

#endif
