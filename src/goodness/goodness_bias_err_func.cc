// c++ STL
#include <memory>
#include <functional>

// ROOT library
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>

// self-introduced library
#include "CSearch_range.hh"
#include "goodness_bias_err_func.hh"

void goodness_bias_err_fit(TH1D* hbias,TH1D* herr,TTree* tree,CSearch_range rangemin,double xvertex,int i,axis a){
  std::unique_ptr<TH1D> hfit { setup_hist(a,rangemin,xvertex) };
  std::unique_ptr<TCanvas> c1 { new TCanvas("c1","c1") };
  double vertex;
  switch(a)
    {
    case x:
      tree->Draw("max_x>>hfit","ncherenkovdigihits != 0");
      std::cout << "x draw" << std::endl;
      vertex = xvertex;
      break;
    case y:
      tree->Draw("max_y>>hfit","ncherenkovdigihits != 0");
      std::cout << "y draw" << std::endl;
      vertex = rangemin.GetYcentral();
      break;
    case z:
      tree->Draw("max_z>>hfit","ncherenkovdigihits != 0");
      std::cout << "z draw" << std::endl;
      vertex = rangemin.GetZcentral();
      break;
    }
  std::unique_ptr<TF1> f { new TF1("f","[0]*exp(-0.5*pow((x-[1])/[2],2))",hfit->GetXaxis()->GetXmin(),hfit->GetXaxis()->GetXmax())};
  f->SetParameters(100.,vertex,100.);
  hfit->Fit("f");
  double bias = f->GetParameter(1) - vertex;
  double biaserr = f->GetParError(1);
  double err = f->GetParameter(2);
  double errerr = f->GetParError(2);
    hbias->Fill(xvertex,bias);
    hbias->SetBinError(i+1,biaserr);
    herr->Fill(xvertex,err);
    herr->SetBinError(i+1,errerr);
}

std::unique_ptr<TH1D> setup_hist(axis a,CSearch_range rangemin,double xvertex){
 int hnum;
 double hmin;
 double hmax;
 switch(a)
   {
   case x:
     hnum = rangemin.GetXNum();
     hmin = xvertex - rangemin.GetXallwidth()/2.;
     hmax = xvertex + rangemin.GetXallwidth()/2.;
     break;
   case y:
     hnum = rangemin.GetYNum();
     hmin = rangemin.GetYmin();
     hmax = rangemin.GetYmax();
     break;
   case z:
     hnum = rangemin.GetZNum();
     hmin = rangemin.GetZmin();
     hmax = rangemin.GetZmax();
     break;
   }
 std::unique_ptr<TH1D> hfit { new TH1D("hfit","",hnum,hmin,hmax) };
 return hfit;
}
