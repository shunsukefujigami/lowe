#ifndef VRUNACTION_HH
#define VRUNACTION_HH

// self-introduced library
#include "VRun.hh"

class VRunAction
{
public:
  VRunAction(){};
  virtual ~VRunAction(){};
  virtual void BeginOfRunAction(VRun* run);
  
  virtual void EndOfRunAction(VRun* run);
  
};


#endif
