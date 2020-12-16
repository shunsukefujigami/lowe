#ifndef VEVENTACTION_HH
#define VEVENTACTION_HH

// self-introduced library
#include "VEvent.hh"

class VEventAction
{
public:
  VEventAction(){};
  virtual ~VEventAction(){};
  virtual void BeginOfEventAction(VEvent* event);
  virtual void EndOfEventAction(VEvent* event);
};

#endif
