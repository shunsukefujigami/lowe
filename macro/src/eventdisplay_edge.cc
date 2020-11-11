// c++ STL
#include <memory>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TArc.h>
#include <TPave.h>
#include <TCanvas.h>

// self-intrduced library
#include "/home/fujigami/retro/lowe/source/macro/include/eventdisplay_edge.hh"
#include "/home/fujigami/retro/lowe/source/include/general/constants.hh"

void eventdisplay_edge(TCanvas* c1,Detectortype type)
{
  double R;
  double L;
  if(type == SK){
    R = SKRadius;
    L = SKLength;
  }
  else if(type == HK){
    R = HKRadius;
    L = HKLength;
  }
  TArc* a1 = new TArc(0.,R + L/2.,R);
  TArc* a2 = new TArc(0.,-R - L/2.,R);
  TPave* p1 = new TPave(-PI*R,-L/2.,PI*R,L/2.);
  a1->SetFillStyle(0);
  a2->SetFillStyle(0);
  p1->SetFillStyle(0);
  a1->Draw("same");
  a2->Draw("same");
  p1->Draw("same");
}
