#ifndef VLOOP1MANAGER_HH
#define VLOOP1MANAGER_HH

// self-introduced library
#include "VLoop1Action.hh"
#include "VLoop2Action.hh"
#include "VLoop1.hh"
#include "VLoop2Manager.hh"

class VLoop1Manager
{
public:
  VLoop1Manager();
  virtual ~VLoop1Manager();
  virtual void SetParameters();
  virtual void DoProcess(VLoop1* loop1);
  virtual void Doloop() = 0;
  void SetLoop2Manager(VLoop2Manager* manager)
  {
    loop2manager = manager;
  }
  
  void SetLoop1Action(VLoop1Action* action)
  {
    loop1action = action;
  }
  void SetLoop2Action(VLoop2Action* action)
  {
    loop2manager->SetLoop2Action(action);
  }
protected:
  VLoop1Action* loop1action = nullptr;
  VLoop1* currentloop1 = nullptr;
  VLoop2Manager* loop2manager = nullptr;
};

#endif
