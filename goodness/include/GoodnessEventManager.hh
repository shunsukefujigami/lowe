#ifndef GOODNESSEVENTMANAGER_HH
#define GOODNESSEVENTMANAGER_HH
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>
// self-introduced library
#include "GoodnessEvent.hh"
#include "GoodnessEventAction.hh"
#include "GoodnessCalculateManager.hh"
#include "GoodnessParameters.hh"
#include "CSearch_range.hh"
class GoodnessEventManager
{
public:
  GoodnessEventManager();
  virtual ~GoodnessEventManager();
  void SetParameters();
  void ProcessOneEvent(GoodnessEvent* event);
  void Doloop();
  void Doloopin(CLHEP::HepLorentzVector hvector);
  void SetGoodnessEventAction(GoodnessEventAction* goodnesseventaction_in)
  {
    goodnesseventaction = goodnesseventaction_in;
  }
  void SetGoodnessCalculateAction(GoodnessCalculateAction* goodnesscalculateaction)
  {
    goodnesscalculatemanager->SetGoodnessCalculateAction(goodnesscalculateaction);
  }

  void SetOneGoodnessCalculateAction(OneGoodnessCalculateAction* onegoodnesscalculateaction)
  {
    goodnesscalculatemanager->SetOneGoodnessCalculateAction(onegoodnesscalculateaction);
  }
  
private:
  GoodnessEventAction* goodnesseventaction = nullptr;
  GoodnessEvent* currentevent = nullptr;
  GoodnessCalculateManager* goodnesscalculatemanager = nullptr;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
  GoodnessLoop4VectorType::type goodnessloop4vectortype;
  CSearch_range* range;
};

#endif
