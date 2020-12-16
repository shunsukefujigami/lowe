// ROOT library
#include <TLorentzVector.h>
// geant4-library
#include <CLHEP/Vector/LorentzVector.h>
// self-introduced library
#include "GoodnessEventManager.hh"
#include "GoodnessEvent.hh"
#include "GoodnessManager.hh"
#include "goodness_data.hh"
#include "GoodnessCalculated.hh"

GoodnessEventManager::GoodnessEventManager(){
  goodnesscalculatemanager = new GoodnessCalculateManager();
  }

GoodnessEventManager::~GoodnessEventManager()
{
  delete goodnesseventaction;
  
  if(goodnesscalculatemanager)
    {
      delete goodnesscalculatemanager;
    }
}

void GoodnessEventManager::SetParameters()
{
  range = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetSearch_range();
  goodnessloop4vectortype = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetGoodnessLoop4VectorType();
  goodnesscalculatemanager->SetParameters();
  
}

void GoodnessEventManager::ProcessOneEvent(GoodnessEvent* event)
{
  currentevent = event;
  wcsimroottrigger = GoodnessManager::GetGoodnessManager()->GetWCSimRootEvent()->GetTrigger(0);
  goodnesseventaction->BeginOfEventAction();
  if(goodnessloop4vectortype == GoodnessLoop4VectorType::normal)
    {
      Doloop();
    }
  if(goodnessloop4vectortype == GoodnessLoop4VectorType::True)
    {
      double x = wcsimroottrigger->GetVtx(0);
      double y = wcsimroottrigger->GetVtx(1);
      double z = wcsimroottrigger->GetVtx(2);
      double t = (-1)*wcsimroottrigger->GetTriggerTime();
      CLHEP::HepLorentzVector hvector(x,y,z,t);
      Doloopin(hvector);
    }
  
  std::cout << "currentevent->Getgoodness() is " << currentevent->Getgoodness() << std::endl;
  std::cout << "currentevent->Get4Vector().t() is " << currentevent->Get4Vector().t() << std::endl;
  
  goodnesseventaction->EndOfEventAction(currentevent);
}

void GoodnessEventManager::Doloop()
{
  double x = range->GetXmin();
  for( int i = 0; i < range->GetXNum() ; ++i , x += range->GetXwidth() )
    {
      double y = range->GetYmin();
      for( int j = 0 ; j < range->GetYNum() ; ++j , y += range->GetYwidth() )
	{
	  double z = range->GetZmin();
	  for(int k = 0; k < range->GetZNum() ; ++k , z += range->GetZwidth() )
	    {
	      double t = range->GetTmin();
	      for(int l = 0; l < range->GetTNum() ; ++l , t+= range->GetTwidth() )
		{
		  CLHEP::HepLorentzVector vector(x,y,z,t);
		  Doloopin(vector);
		}
	    }
	}
    }
}

void GoodnessEventManager::Doloopin(CLHEP::HepLorentzVector hvector)
{
  GoodnessCalculated* goodnesscalculated = new GoodnessCalculated();
  goodnesscalculated->SetLorentzVector(hvector);
  goodnesscalculatemanager->DoProcess(goodnesscalculated);
  double goodness = goodnesscalculated->GetGoodness();
  if(currentevent->Getgoodness() < goodness)
    {
      currentevent->Setgoodness(goodness);
      currentevent->Set4Vector(hvector);
    }
  delete goodnesscalculated;
}
