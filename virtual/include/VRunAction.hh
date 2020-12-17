#ifndef VRUNACTION_HH
#define VRUNACTION_HH
// c++ STL
#include <memory>
// self-introduced library
#include "VRun.hh"

class VRunAction
{
public:
  VRunAction(){};
  virtual ~VRunAction(){};
  virtual void BeginOfRunAction(std::shared_ptr<VRun> run);
  
  virtual void EndOfRunAction(std::shared_ptr<VRun> run);
  
};


#endif
