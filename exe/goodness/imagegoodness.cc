// c++ STL
#include <iostream>
#include <vector>

// ROOT library
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1D.h>

// self-introduced library
#include "config.hh"
#include "CSearch_range.hh"

int main()
{
  Config_goodness_image config;
  TFile* f_onretro = new TFile(config.infile_onretro);
  TChain* chain_onretro = (TChain*)f_onretro->Get(config.chainname_onretro);
  TFile* f_noretro = new TFile(config.infile_noretro);
  TChain* chain_noretro = (TChain*)f_noretro->Get(config.chainname_noretro);
  TFile* f_compare = new TFile(config.infile_compare);
  TChain* chain_compare = (TChain*)f_compare->Get(config.chainname_compare);
  CSearch_range range = config.range;
  TH1D* hx_noretro = new TH1D("hx_noretro","max x;max x;# of event",range.GetXNum(),range.GetXmin() - range.GetXwidth()/2.,range.GetXmax() + range.GetXwidth()/2.);
  TH1D* hx_onretro = new TH1D("hx_onretro","max x;max x;# of event",range.GetXNum(),range.GetXmin() - range.GetXwidth()/2.,range.GetXmax() + range.GetXwidth()/2.);
  TH1D* hy_noretro = new TH1D("hy_noretro","max y;max y;# of event",range.GetYNum(),range.GetYmin() - range.GetYwidth()/2.,range.GetYmax() + range.GetYwidth()/2.);
  TH1D* hy_onretro = new TH1D("hy_onretro","max y;max y;# of event",range.GetYNum(),range.GetYmin() - range.GetYwidth()/2.,range.GetYmax() + range.GetYwidth()/2.);
  TH1D* hz_noretro = new TH1D("hz_noretro","max z;max z;# of event",range.GetZNum(),range.GetZmin() - range.GetZwidth()/2.,range.GetZmax() + range.GetZwidth()/2.);
  TH1D* hz_onretro = new TH1D("hz_onretro","max z;max z;# of event",range.GetZNum(),range.GetZmin() - range.GetZwidth()/2.,range.GetZmax() + range.GetZwidth()/2.);
  TH1D* hx_compare = new TH1D("hx_compare","max x;max x;# of event",range.GetXNum(),range.GetXmin() - range.GetXwidth()/2.,range.GetXmax() + range.GetXwidth()/2.);
  TH1D* hy_compare = new TH1D("hy_compare","max y;max y;# of event",range.GetYNum(),range.GetYmin() - range.GetYwidth()/2.,range.GetYmax() + range.GetYwidth()/2.);
  TH1D* hz_compare = new TH1D("hz_compare","max z;max z;# of event",range.GetZNum(),range.GetZmin() - range.GetZwidth()/2.,range.GetZmax() + range.GetZwidth()/2.);
  hx_onretro->SetStats(0);
  hx_onretro->SetLineColor(4);
  hx_noretro->SetStats(0);
  hx_noretro->SetLineColor(2);
  hy_onretro->SetStats(0);
  hy_onretro->SetLineColor(4);
  hy_noretro->SetStats(0);
  hy_noretro->SetLineColor(2);
  hz_onretro->SetStats(0);
  hz_onretro->SetLineColor(4);
  hz_noretro->SetStats(0);
  hz_noretro->SetLineColor(2);
  hx_compare->SetStats(0);
  hx_compare->SetLineColor(8);
  hy_compare->SetStats(0);
  hy_compare->SetLineColor(8);
  hz_compare->SetStats(0);
  hz_compare->SetLineColor(8);
  chain_onretro->Draw("max_x>>hx_onretro","ncherenkovdigihits != 0");
  chain_noretro->Draw("max_x>>hx_noretro","ncherenkovdigihits != 0");
  chain_onretro->Draw("max_y>>hy_onretro","ncherenkovdigihits != 0");
  chain_noretro->Draw("max_y>>hy_noretro","ncherenkovdigihits != 0");
  chain_onretro->Draw("max_z>>hz_onretro","ncherenkovdigihits != 0");
  chain_noretro->Draw("max_z>>hz_noretro","ncherenkovdigihits != 0");
  chain_compare->Draw("max_x>>hx_compare","ncherenkovdigihits != 0");
  chain_compare->Draw("max_y>>hy_compare","ncherenkovdigihits != 0");
  chain_compare->Draw("max_z>>hz_compare","ncherenkovdigihits != 0");
  double binmax_xonretro = hx_onretro->GetBinContent(hx_onretro->GetMaximumBin());
  double binmax_xnoretro = hx_noretro->GetBinContent(hx_noretro->GetMaximumBin());
  double binmax_xcompare = hx_compare->GetBinContent(hx_compare->GetMaximumBin());
  double binmax_yonretro = hy_onretro->GetBinContent(hy_onretro->GetMaximumBin());
  double binmax_ynoretro = hy_noretro->GetBinContent(hy_noretro->GetMaximumBin());
  double binmax_ycompare = hy_compare->GetBinContent(hy_compare->GetMaximumBin());
  double binmax_zonretro = hz_onretro->GetBinContent(hz_onretro->GetMaximumBin());
  double binmax_znoretro = hz_noretro->GetBinContent(hz_noretro->GetMaximumBin());
  double binmax_zcompare = hz_compare->GetBinContent(hz_compare->GetMaximumBin());
  std::vector<double> vbinmax_x;
  vbinmax_x.push_back(binmax_xonretro);
  vbinmax_x.push_back(binmax_xnoretro);
  vbinmax_x.push_back(binmax_xcompare);
  double binmax_x = 0;
  for(auto& elemx : vbinmax_x){
    if(elemx > binmax_x){
      binmax_x = elemx;
    }
  }

  std::vector<double> vbinmax_y;
  vbinmax_y.push_back(binmax_yonretro);
  vbinmax_y.push_back(binmax_ynoretro);
  vbinmax_y.push_back(binmax_ycompare);
  double binmax_y = 0;
  for(auto& elemy : vbinmax_y){
    if(elemy > binmax_y){
      binmax_y = elemy;
    }
  }

  std::vector<double> vbinmax_z;
  vbinmax_z.push_back(binmax_zonretro);
  vbinmax_z.push_back(binmax_znoretro);
  vbinmax_z.push_back(binmax_zcompare);
  double binmax_z = 0;
  for(auto& elemz : vbinmax_z){
    if(elemz > binmax_z){
      binmax_z = elemz;
    }
  }

  hx_onretro->GetYaxis()->SetRangeUser(0.,binmax_x + 100.);
  hy_onretro->GetYaxis()->SetRangeUser(0.,binmax_y + 100.);
  hz_onretro->GetYaxis()->SetRangeUser(0.,binmax_z + 100.);
  TCanvas* c2 = new TCanvas("c2","c2");
  chain_onretro->Draw("max_x>>hx_onretro","ncherenkovdigihits != 0");
  chain_noretro->Draw("max_x>>hx_noretro","ncherenkovdigihits != 0","same");
  chain_compare->Draw("max_x>>hx_compare","ncherenkovdigihits != 0","same");
  c2->SaveAs(config.outfile_x);
  chain_onretro->Draw("max_y>>hy_onretro","ncherenkovdigihits != 0");
  chain_noretro->Draw("max_y>>hy_noretro","ncherenkovdigihits != 0","same");
  chain_compare->Draw("max_y>>hy_compare","ncherenkovdigihits != 0","same");
  c2->SaveAs(config.outfile_y);
  chain_onretro->Draw("max_z>>hz_onretro","ncherenkovdigihits != 0");
  chain_noretro->Draw("max_z>>hz_noretro","ncherenkovdigihits != 0","same");
  chain_compare->Draw("max_z>>hz_compare","ncherenkovdigihits != 0","same");
  c2->SaveAs(config.outfile_z);
  delete c2;
  delete hx_noretro;
  delete hx_onretro;
  delete hx_compare;
  delete hy_noretro;
  delete hy_onretro;
  delete hy_compare;
  delete hz_noretro;
  delete hz_onretro;
  delete hz_compare;
  delete f_noretro;
  delete f_onretro;
  delete f_compare;
  return 0;
}
