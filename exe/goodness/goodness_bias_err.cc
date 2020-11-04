// c++ STL
#include <vector>
#include <cmath>
#include <memory>
#include <string>
#include <sstream>

// ROOT library
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TF1.h>

// self-introduced library
#include "CSearch_range.hh"
#include "config.hh"
#include "goodness_bias_err_func.hh"

int main(){
  Config_goodness_bias_err config;
  int xnum = config.xnum;
  CSearch_range rangemin = config.rangemin;
  double xvermin = rangemin.GetXcentral();
  double xvermax = xvermin + (xnum-1)*config.xverwidth;
  double xhistmin = xvermin - config.xverwidth/2;
  double xhistmax = xvermax + config.xverwidth/2;
  TH1D* hxbiasnoretro = new TH1D("hxbiasnoretro","xbias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hybiasnoretro = new TH1D("hybiasnoretro","ybias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hzbiasnoretro = new TH1D("hzbiasnoretro","zbias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hxerrnoretro = new TH1D("hxerrnoretro","xerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hyerrnoretro = new TH1D("hyerrnoretro","yerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hzerrnoretro = new TH1D("hzerrnoretro","zerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hxbiasonretro = new TH1D("hxbiasonretro","xbias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hybiasonretro = new TH1D("hybiasonretro","ybias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hzbiasonretro = new TH1D("hzbiasonretro","zbias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hxerronretro = new TH1D("hxerronretro","xerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hyerronretro = new TH1D("hyerronretro","yerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hzerronretro = new TH1D("hzerronretro","zerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  /*  TH1D* hxbiascompare = new TH1D("hxbiascompare","xbias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hybiascompare = new TH1D("hybiascompare","ybias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hzbiascompare = new TH1D("hzbiascompare","zbias;x(cm);bias(cm)",xnum,xhistmin,xhistmax);
  TH1D* hxerrcompare = new TH1D("hxerrcompare","xerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hyerrcompare = new TH1D("hyerrcompare","yerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);
  TH1D* hzerrcompare = new TH1D("hzerrcompare","zerr;x(cm);err(cm)",xnum,xhistmin,xhistmax);*/

  double xvertex = xvermin;
  for( int i = 0; i < xnum ; i++, xvertex += config.xverwidth )
    {
      std::stringstream ssinfile_onretro;
      ssinfile_onretro << config.infilehead_onretro << xvertex << config.infiletail;
      std::unique_ptr<TFile> f_onretro { new TFile( ssinfile_onretro.str().c_str())};
      std::stringstream sstree_onretro;
      if(xvertex < 0){
	sstree_onretro << config.intreehead_onretro << "minus" << std::abs(xvertex) << config.intreetail;
      }
      else{
	sstree_onretro << config.intreehead_onretro << xvertex << config.intreetail;
      }
      TTree* tree_onretro = (TTree*)f_onretro->Get(sstree_onretro.str().c_str());
      std::cout << sstree_onretro.str() << std::endl;

      std::stringstream ssinfile_noretro;
      ssinfile_noretro << config.infilehead_noretro << xvertex << config.infiletail;
      std::unique_ptr<TFile> f_noretro { new TFile( ssinfile_noretro.str().c_str())};
      std::stringstream sstree_noretro;
      if(xvertex < 0){
	sstree_noretro << config.intreehead_noretro << "minus" << std::abs(xvertex) << config.intreetail;
      }
      else{
	sstree_noretro << config.intreehead_noretro << xvertex << config.intreetail;
      }
      TTree* tree_noretro = (TTree*)f_noretro->Get(sstree_noretro.str().c_str());

      /*      std::stringstream ssinfile_compare;
      ssinfile_compare << infilehead_compare << xvertex << infiletail;
      std::unique_ptr<TFile> f_compare { new TFile( ssinfile_compare.str().c_str())};
      std::stringstream sstree_compare;
      if(xvertex < 0){
	sstree_compare << intreehead_compare << "minus" << std::abs(xvertex) << intreetail;
      }
      else{
	sstree_compare << intreehead_compare << xvertex << intreetail;
      }
      TTree* tree_compare = (TTree*)f_compare->Get(sstree_compare.str().c_str());
      */
      goodness_bias_err_fit(hxbiasnoretro,hxerrnoretro,tree_noretro,rangemin,xvertex,i,x);
      goodness_bias_err_fit(hybiasnoretro,hyerrnoretro,tree_noretro,rangemin,xvertex,i,y);
      goodness_bias_err_fit(hzbiasnoretro,hzerrnoretro,tree_noretro,rangemin,xvertex,i,z);
      goodness_bias_err_fit(hxbiasonretro,hxerronretro,tree_onretro,rangemin,xvertex,i,x);
      goodness_bias_err_fit(hybiasonretro,hyerronretro,tree_onretro,rangemin,xvertex,i,y);
      goodness_bias_err_fit(hzbiasonretro,hzerronretro,tree_onretro,rangemin,xvertex,i,z);
      /*      goodness_bias_err_fit(hxbiascompare,hxerrcompare,tree_compare,rangemin,xvertex,i,x);
      goodness_bias_err_fit(hybiascompare,hyerrcompare,tree_compare,rangemin,xvertex,i,y);
      goodness_bias_err_fit(hzbiascompare,hzerrcompare,tree_compare,rangemin,xvertex,i,z); */

    }

  std::unique_ptr<TCanvas> c1 { new TCanvas("c1","c1")};
  hxbiasonretro->SetLineColor(4);
  hxbiasonretro->GetYaxis()->SetRangeUser(-80.,80.);
  hxbiasonretro->SetStats(0);
  hybiasonretro->SetLineColor(4);
  hybiasonretro->SetStats(0);
  hzbiasonretro->SetLineColor(4);
  hzbiasonretro->SetStats(0);
  hxerronretro->GetYaxis()->SetRangeUser(0.,200.);
  hxerronretro->SetLineColor(4);
  hxerronretro->SetStats(0);
  hyerronretro->GetYaxis()->SetRangeUser(0.,150.);
  hyerronretro->SetLineColor(4);
  hyerronretro->SetStats(0);
  hzerronretro->GetYaxis()->SetRangeUser(0.,150.);
  hzerronretro->SetLineColor(4);
  hzerronretro->SetStats(0);
  hxbiasnoretro->SetLineColor(2);
  hxbiasnoretro->SetStats(0);
  hybiasnoretro->SetLineColor(2);
  hybiasnoretro->SetStats(0);
  hzbiasnoretro->SetLineColor(2);
  hzbiasnoretro->SetStats(0);
  hxerrnoretro->SetLineColor(2);
  hxerrnoretro->SetStats(0);
  hyerrnoretro->SetLineColor(2);
  hyerrnoretro->SetStats(0);
  hzerrnoretro->SetLineColor(2);
  hzerrnoretro->SetStats(0);
  /*  hxbiascompare->SetLineColor(2);
  hxbiascompare->SetStats(0);
  hybiascompare->SetLineColor(9);
  hybiascompare->SetStats(0);
  hzbiascompare->SetLineColor(9);
  hzbiascompare->SetStats(0);
  hxerrcompare->SetLineColor(9);
  hxerrcompare->SetStats(0);
  hyerrcompare->SetLineColor(9);
  hyerrcompare->SetStats(0);
  hzerrcompare->SetLineColor(9);
  hzerrcompare->SetStats(0); */
  hxbiasonretro->Draw();
  hxbiasnoretro->Draw("same");
  //  hxbiascompare->Draw("same");
  c1->SaveAs(config.outfile_x_bias);
  hybiasonretro->Draw();
  hybiasnoretro->Draw("same");
  //  hxbiascompare->Draw("same");
  c1->SaveAs(config.outfile_y_bias);
  hzbiasonretro->Draw();
  hzbiasnoretro->Draw("same");
  //  hzbiascompare->Draw("same");
  c1->SaveAs(config.outfile_z_bias);
  hxerronretro->Draw();
  hxerrnoretro->Draw("same");
  //  hxerrcompare->Draw("same");
  c1->SaveAs(config.outfile_x_err);
  hyerronretro->Draw();
  hyerrnoretro->Draw("same");
  //  hyerrcompare->Draw("same");
  c1->SaveAs(config.outfile_y_err);
  hzerronretro->Draw();
  hzerrnoretro->Draw("same");
  //  hzerrcompare->Draw("same");
  c1->SaveAs(config.outfile_z_err);
  return 0;
}


