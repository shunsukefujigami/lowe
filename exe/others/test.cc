#include <iostream>
#include <TCanvas.h>
#include "MultiRunAnalizeManager.hh"
int main()
{
  MultiRunAnalizeManager* mram = new MultiRunAnalizeManager();
  mram->SetBasefile("~/store/goodnessfile/SIG5GTcGSRn_21_-600_50_21_-500_50_21_-500_50_300_-300_1GEN10000DETskPePOSf_-100_0_0DIRf_0_0Ef_5RorRFtz_0.0_20_60RSnsTT24TW200TPR-400TPO950DR4.2AFNfEN10000.root");
  mram->SetAllfile();
  std::vector<std::string> exclusionname;
  exclusionname.push_back("RFtrmax");
  mram->SetComparefile(exclusionname);
  TH1D* h1 = new TH1D("","",11,-0.05,1.05);
  mram->GetTH1D(h1,"tzmaxreflectivity","xerrorbygoodness");
  TCanvas* c1 = new TCanvas();
  h1->Draw();
  c1->SaveAs("/home/fujigami/retro/lowe/picture/2021January/xerror.png");
  delete c1;
  delete h1;
  delete mram;
  return 0;
}

  
