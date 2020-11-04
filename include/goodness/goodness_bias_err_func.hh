// c++ STL
#include <memory>

// ROOT library
#include <TH1D.h>
#include <TTree.h>

// self-introduced library
#include <CSearch_range.hh>

enum axis
  {
    x,y,z
  };

// this library is a group of function to use in bias and error analize in goodness search

void goodness_bias_err_fit(TH1D* hbias,TH1D* herr,TTree* tree,CSearch_range rangemin,double xvertex,int i,axis a);

// for each given histograms, bias one and error one, fill bias and error data. bias and error is getted by gaussian fitting.

std::unique_ptr<TH1D> setup_hist(axis a,CSearch_range rangemin,double xvertex);

// setting histogram function. correspond to each axis (x,y,z)
