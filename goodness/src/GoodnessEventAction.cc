// ROOT library
#include <TTree.h>
#include <TLorentzVector.h>
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>
// self-introduced library
#include "GoodnessEventAction.hh"
#include "GoodnessRunAction.hh"
#include "GoodnessEvent.hh"
#include "goodness_data.hh"
#include "AnalizedData.hh"

GoodnessEventAction::GoodnessEventAction(GoodnessRunAction* goodnessrunaction_in)
  :goodnessrunaction(goodnessrunaction_in)
{}

void GoodnessEventAction::BeginOfEventAction()
{
}


void GoodnessEventAction::EndOfEventAction(const GoodnessEvent* goodnessevent)
{
  goodness_data data;
  data.Setgoodness(goodnessevent->Getgoodness());
  CLHEP::HepLorentzVector vector = goodnessevent->Get4Vector();
  double x = vector.x();
  double y = vector.y();
  double z = vector.z();
  double t = vector.t();
  TLorentzVector vec(x,y,z,t);
  data.Set4Vector(vec);
  goodness_data* datain = GetRunAction()->GetgoodnessData();
  datain->Setdata(data);
  TTree* tree = GetRunAction()->GetTTree();
  tree->Fill();
}
