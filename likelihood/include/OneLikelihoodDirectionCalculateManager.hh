#ifndef ONELIKELIHOODDIRECTIONCALCULATEMANAGER_HH
#define ONELIKELIHOODDIRECTIONCALCULATEMANAGER_HH

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "VLoop2Manager.hh"
#include "LikelihoodDirectionParameters.hh"

class OneLikelihoodDirectionCalculateManager : public VLoop2Manager
{
public:
  OneLikelihoodDirectionCalculateManager();
  virtual ~OneLikelihoodDirectionCalculateManager();
  void SetParameters();
  void Doloop();
  void OneLikelihoodDirectionOnretro();
  void OneLikelihoodDirectionNoretro();
  void OneLikelihoodDirectionSum();
  double distance_position_pmt() const;
  double distance_position_retro() const;
  double distance_fly_retro() const;
  double tof(double distance) const;
  double tof_no_retro() const;
  double tof_on_retro() const;
  void SetLikelihood(double l)
  {
    onelikelihood = l;
  }
  double GetLikelihood()
  {
    return onelikelihood;
  }
    void SetHitTime(double t){ hittime = t;}
  double GetHitTime() const { return hittime;}
  void SetPMTPosition(const CLHEP::Hep3Vector& position){ pmtposition = position;}
  CLHEP::Hep3Vector GetPMTPosition() const { return pmtposition;}
  CLHEP::HepLorentzVector GetVertex() const { return fitted4vector;}
  double GetWCradius() const { return WCradius; }
  void SetWCradius(double WCradius_in)
  {
    WCradius = WCradius_in;
  }

  double GetWClength() const 
  {
    return WClength;
  }

  void SetWClength(double WClength_in)
  {
    WClength = WClength_in;
  }
  void Setup();
  double theta_i_func();
  double fdirprototypenoretro() const;
  double fdirbydatanoretro() const;
  double fdirprototypeonretro() const;
  double fdirbydataonretro() const;
  double afuncprototype() const
  {
    return 1.;
  }
  
  
  void SetHit(WCSimRootCherenkovDigiHit* h)
  {
    hit = h;
  }
  
private:
  WCSimRootGeom* wcsimrootgeom = nullptr;
  WCSimRootCherenkovDigiHit* hit = nullptr;
  WCSimRootPMT pmt;
  CLHEP::Hep3Vector pmtposition;
  CLHEP::Hep3Vector hminusv;
  double theta_dir_i;
  double costheta_dir_i;
  double theta_i;
  double hittime;
  CLHEP::HepLorentzVector fitted4vector;
  double onelikelihood;
  double WCradius;
  double WClength;
  OneLikelihoodDirectionCalculateType::type onelikelihooddirectioncalculatetype;
  FDirFuncNoretroType::type fdirfuncnoretrotype;
  AFuncNoretroType::type afuncnoretrotype;
  FDirFuncOnretroType::type fdirfunconretrotype;
  AFuncOnretroType::type afunconretrotype;
};

#endif
