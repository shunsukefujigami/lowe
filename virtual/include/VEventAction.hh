#ifndef VEVENTACTION_HH
#define VEVENTACTION_HH
// c++ STL
#include <memory>
// self-introduced library
#include "VEvent.hh"

class VEventAction
{
public:
  VEventAction(){};
  virtual ~VEventAction(){};
  virtual void BeginOfEventAction(std::shared_ptr<VEvent> event);
  virtual void EndOfEventAction(std::shared_ptr<VEvent> event);
};

#endif
