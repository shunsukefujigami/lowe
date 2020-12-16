#ifndef RUNMANAGER_HH
#define RUNMANAGER_HH

// self-introduced library
#include "VParameters.hh"
#include "EventManager.hh"
#include "VRunAction.hh"
#include "VEventAction.hh"
#include "VLoop1Action.hh"
#include "VLoop2Action.hh"

class RunManager
{
public:
  RunManager();
  virtual ~RunManager();
  void Run(int Nevent);
  virtual void SetParameters();
  virtual void ProcessOneEvent(int i_event);
  void SetEventManager(EventManager* manager)
  {
    eventmanager = manager;
  }
  void SetLoop1Manager(VLoop1Manager* manager)
  {
    eventmanager->SetLoop1Manager(manager);
  }
  void SetLoop2Manager(VLoop2Manager* manager)
  {
    eventmanager->SetLoop2Manager(manager);
  }
  
  VParameters* GetParameters()
  {
    return parameters;
  }
  void SetVParameters(VParameters* para)
  {
    parameters = para;
  }
  void SetRunAction(VRunAction* action)
  {
    runaction = action;
  }
  void SetEventAction(VEventAction* action)
  {
    eventmanager->SetEventAction(action);
  }
  void SetLoop1Action(VLoop1Action* action)
  {
    eventmanager->SetLoop1Action(action);
  }
  void SetLoop2Action(VLoop2Action* action)
  {
    eventmanager->SetLoop2Action(action);
  }
protected:
  EventManager* eventmanager = nullptr;
  VParameters* parameters = nullptr;
  VRunAction* runaction = nullptr;
  VEventAction* eventaction = nullptr;
  VLoop1Action* loop1action = nullptr;
  VLoop2Action* loop2action = nullptr;
  VRun* run = nullptr;
  VEvent* currentevent = nullptr;
  int Nevents;
};

#endif
