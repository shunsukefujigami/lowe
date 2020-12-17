#ifndef VLOOP2ACTION_HH
#define VLOOP2ACTION_HH
// c++ STL
#include <memory>
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
  virtual void BeginOfLoop2Action(std::shared_ptr<VLoop2> loop2);
  
  virtual void EndOfLoop2Action(std::shared_ptr<VLoop2> loop2);
  
};


#endif
