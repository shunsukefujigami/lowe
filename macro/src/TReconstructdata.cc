#include "TReconstructdata.hh"

ClassImp(TReconstructdata)

ClassImp(TReconstructhit)

TReconstructdata::TReconstructdata()
{
}

TReconstructdata::~TReconstructdata()
{
}

void TReconstructdata::addhit(int hittype)
{
  TReconstructhit hit(hittype);
  fhit.push_back(hit);
}

TReconstructhit& TReconstructdata::Gethit(int i)
{
  return fhit[i];
}

void TReconstructdata::Setdata(TReconstructdata data)
{
  vector = data.Get4Vector();
  direction = data.Getdirection();
  energy = data.Getenergy();
  goodness = data.Getgoodness();
  likelihood = data.Getlikelihood();
  likelihoodonretro = data.Getlikelihoodonretro();
  likelihoodnoretro = data.Getlikelihoodnoretro();
  fhit = data.Getvhit();
}

