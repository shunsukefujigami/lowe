#ifndef VLOOP1ACTION_HH
#define VLOOP1ACTION_HH

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
  virtual void BeginOfLoop1Action(VLoop1* loop1);
  
  virtual void EndOfLoop1Action(VLoop1* loop1);
  
};


#endif
