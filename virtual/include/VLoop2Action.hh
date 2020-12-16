#ifndef VLOOP2ACTION_HH
#define VLOOP2ACTION_HH

// self-introduced library
#include "VLoop2.hh"

class VLoop2Action
{
public:
  VLoop2Action()
  {
  }
  virtual ~VLoop2Action()
  {
  }
  virtual void BeginOfLoop2Action(VLoop2* loop2);
  
  virtual void EndOfLoop2Action(VLoop2* loop2);
  
};


#endif
