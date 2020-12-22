#ifndef RUNMANAGER_HH
#define RUNMANAGER_HH
// c++ STL
#include <memory>
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
  static RunManager* GetRunManager()
  {
    return frunmanager;
  }
private:
  static RunManager* frunmanager;
public:
  RunManager();
  virtual ~RunManager();
  void Run(int Nevent);
  virtual void SetParameters();
  virtual void ProcessOneEvent(int i_event);
  std::shared_ptr<VParameters> GetParameters()
  {
    return parameters;
  }
  void SetVParameters(std::shared_ptr<VParameters> para)
  {
    parameters = para;
  }
  void SetRunAction(std::shared_ptr<VRunAction> action)
  {
    runaction = action;
  }
  void SetEventAction(std::shared_ptr<VEventAction> action)
  {
    eventmanager->SetEventAction(action);
    eventaction = action;
  }
  void SetLoop1Action(std::shared_ptr<VLoop1Action> action)
  {
    eventmanager->SetLoop1Action(action);
    loop1action = action;
  }
  void SetLoop2Action(std::shared_ptr<VLoop2Action> action)
  {
    eventmanager->SetLoop2Action(action);
    loop2action = action;
  }
protected:
  std::unique_ptr<EventManager> eventmanager = nullptr;
  std::shared_ptr<VParameters> parameters = nullptr;
  std::shared_ptr<VRunAction> runaction = nullptr;
  std::shared_ptr<VEventAction> eventaction = nullptr;
  std::shared_ptr<VLoop1Action> loop1action = nullptr;
  std::shared_ptr<VLoop2Action> loop2action = nullptr;
  std::shared_ptr<VRun> run = nullptr;
  std::shared_ptr<VEvent> currentevent = nullptr;
  int Nevents;
};

#endif
