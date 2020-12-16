#ifndef VLOOP2MANAGER_HH
#define VLOOP2MANAGER_HH

// self-introduced library
#include "VLoop2Action.hh"
#include "VLoop2.hh"

class VLoop2Manager
{
public:
  VLoop2Manager();
  virtual ~VLoop2Manager();
  virtual void SetParameters();
  virtual void DoProcess(VLoop2* loop2);
  virtual void Doloop() = 0;
  void SetLoop2Action(VLoop2Action* action)
  {
    loop2action = action;
  }
protected:
  VLoop2Action* loop2action = nullptr;
  VLoop2* currentloop2;
};


#endif
