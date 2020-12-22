#ifndef EVENTMANAGER_HH
#define EVENTMANAGER_HH
// c++ STL
#include <memory>
// self-introduced library
#include "VEvent.hh"
#include "VEventAction.hh"
#include "VLoop1Action.hh"
#include "VLoop2Action.hh"
#include "VLoop1Manager.hh"

class EventManager
{
public:
  static EventManager* GetEventManager()
  {
    return feventmanager;
  }
private:
  static EventManager* feventmanager;
public:
  EventManager();
  virtual ~EventManager();
  virtual void SetParameters();
  virtual void ProcessOneEvent(std::shared_ptr<VEvent> event);
  virtual void Doprocess() = 0;
  void SetEventAction(std::shared_ptr<VEventAction> action)
  {
    eventaction = action;
  }
  void SetLoop1Action(std::shared_ptr<VLoop1Action> action)
  {
    loop1manager->SetLoop1Action(action);
  }
  void SetLoop2Action(std::shared_ptr<VLoop2Action> action)
  {
    loop1manager->SetLoop2Action(action);
  }
protected:
  std::shared_ptr<VEventAction> eventaction = nullptr;
  std::shared_ptr<VEvent> currentevent = nullptr;
  std::shared_ptr<VLoop1Manager> loop1manager = nullptr;
};

#endif
