#ifndef LIKELIHOODDIRECTIONEVENTACTION_HH
#define LIKELIHOODDIRECTIONEVENTACTION_HH
// c++ STL
#include <memory>
// self introduced library
#include "VEventAction.hh"
#include "VEvent.hh"
#include "LikelihoodDirectionRunAction.hh"

class LikelihoodDirectionEventAction : public VEventAction
{
public:
  LikelihoodDirectionEventAction(std::shared_ptr<LikelihoodDirectionRunAction> action)
  {
    likelihooddirectionrunaction = action;
  }
  virtual ~LikelihoodDirectionEventAction()
  {
  }
  void BeginOfEventAction(std::shared_ptr<VEvent>){};
  void EndOfEventAction(std::shared_ptr<VEvent> event);
private:
  std::shared_ptr<LikelihoodDirectionRunAction> likelihooddirectionrunaction = nullptr;
};

#endif
