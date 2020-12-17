#ifndef VLOOP2MANAGER_HH
#define VLOOP2MANAGER_HH
// c++ STL
#include <memory>
// self-introduced library
#include "VLoop2Action.hh"
#include "VLoop2.hh"

class VLoop2Manager
{
public:
  VLoop2Manager();
  virtual ~VLoop2Manager();
  virtual void SetParameters();
  virtual void DoProcess(std::shared_ptr<VLoop2> loop2);
  virtual void Doloop() = 0;
  void SetLoop2Action(std::shared_ptr<VLoop2Action> action)
  {
    loop2action = action;
  }
protected:
  std::shared_ptr<VLoop2Action> loop2action = nullptr;
  std::shared_ptr<VLoop2> currentloop2;
};


#endif
