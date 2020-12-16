#ifndef LIKELIHOODDIRECTIONEVENTACTION_HH
#define LIKELIHOODDIRECTIONEVENTACTION_HH

// self introduced library
#include "VEventAction.hh"
#include "VEvent.hh"
#include "LikelihoodDirectionRunAction.hh"

class LikelihoodDirectionEventAction : public VEventAction
{
public:
  LikelihoodDirectionEventAction(LikelihoodDirectionRunAction* action)
    :likelihooddirectionrunaction(action)
  {}
  virtual ~LikelihoodDirectionEventAction()
  {
  }
  void BeginOfEventAction(VEvent*){};
  void EndOfEventAction(VEvent* event);
private:
  LikelihoodDirectionRunAction* likelihooddirectionrunaction = nullptr;
};

#endif
