#ifndef VLOOP1MANAGER_HH
#define VLOOP1MANAGER_HH
// c++ STL
#include <memory>
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
  virtual void DoProcess(std::shared_ptr<VLoop1> loop1);
  virtual void Doloop() = 0;
  void SetLoop1Action(std::shared_ptr<VLoop1Action> action)
  {
    loop1action = action;
  }
  void SetLoop2Action(std::shared_ptr<VLoop2Action> action)
  {
    loop2manager->SetLoop2Action(action);
  }
protected:
  std::shared_ptr<VLoop1Action> loop1action = nullptr;
  std::shared_ptr<VLoop1> currentloop1 = nullptr;
  std::shared_ptr<VLoop2Manager> loop2manager = nullptr;
};

#endif
