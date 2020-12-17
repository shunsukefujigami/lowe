#ifndef VLOOP1ACTION_HH
#define VLOOP1ACTION_HH
// c++ STL
#include <memory>
// self-introduced library
#include "VLoop1.hh"

class VLoop1Action
{
public:
  VLoop1Action()
  {
  }
  virtual ~VLoop1Action()
  {
  }
  virtual void BeginOfLoop1Action(std::shared_ptr<VLoop1> loop1);
  
  virtual void EndOfLoop1Action(std::shared_ptr<VLoop1> loop1);
  
};


#endif
