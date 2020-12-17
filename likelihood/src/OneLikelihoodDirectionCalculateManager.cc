// c++ STL
#include <iostream>
#include <cmath>
#include <memory>
// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "OneLikelihoodDirectionCalculateManager.hh"
#include "OneLikelihoodDirectionCalculated.hh"
#include "LikelihoodDirectionManager.hh"
#include "constants.hh"

OneLikelihoodDirectionCalculateManager::OneLikelihoodDirectionCalculateManager()
{
  wcsimrootgeom = LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetWCSimRootGeom();
}

OneLikelihoodDirectionCalculateManager::~OneLikelihoodDirectionCalculateManager()
{
}

void OneLikelihoodDirectionCalculateManager::SetParameters()
{
  onelikelihooddirectioncalculatetype = (std::dynamic_pointer_cast<LikelihoodDirectionParameters>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters()))->GetOneLikelihoodDirectionCalculateType();
  fdirfuncnoretrotype = (std::dynamic_pointer_cast<LikelihoodDirectionParameters>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters()))->GetFDirFuncNoretroType();
  fdirfunconretrotype = (std::dynamic_pointer_cast<LikelihoodDirectionParameters>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters()))->GetFDirFuncOnretroType();
  afunconretrotype = (std::dynamic_pointer_cast<LikelihoodDirectionParameters>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters()))->GetAFuncOnretroType();
  afuncnoretrotype = (std::dynamic_pointer_cast<LikelihoodDirectionParameters>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters()))->GetAFuncNoretroType();
}

void OneLikelihoodDirectionCalculateManager::Doloop()
{
  Setup();
  if(onelikelihooddirectioncalculatetype == OneLikelihoodDirectionCalculateType::noretro)
    {
      OneLikelihoodDirectionNoretro();
    }
  if(onelikelihooddirectioncalculatetype == OneLikelihoodDirectionCalculateType::onretro)
    {
      OneLikelihoodDirectionOnretro();
    }
  if(onelikelihooddirectioncalculatetype == OneLikelihoodDirectionCalculateType::sum)
    {
      OneLikelihoodDirectionSum();
    }
}

void OneLikelihoodDirectionCalculateManager::Setup()
{
  hittime = hit->GetT();
  int tubeId = hit->GetTubeId();
  pmt = wcsimrootgeom->GetPMT(tubeId-1);
  double pmtX = pmt.GetPosition(0);
  double pmtY = pmt.GetPosition(1);
  double pmtZ = pmt.GetPosition(2);
  pmtposition.set(pmtX,pmtY,pmtZ); 
  hminusv = pmtposition - fitted4vector.vect();
  theta_dir_i = (std::dynamic_pointer_cast<OneLikelihoodDirectionCalculated>(currentloop2))->Get3Vector().angle(hminusv);
  theta_i = theta_i_func();
  costheta_dir_i = std::cos(theta_dir_i);
  fitted4vector = (std::dynamic_pointer_cast<OneLikelihoodDirectionCalculated>(currentloop2))->Getfitted4Vector();
}

double OneLikelihoodDirectionCalculateManager::theta_i_func()
{
  double orientX = pmt.GetOrientation(0);
  double orientY = pmt.GetOrientation(1);
  double orientZ = pmt.GetOrientation(2);
  CLHEP::Hep3Vector orientation(orientX,orientY,orientZ);
  return orientation.angle(-hminusv);
}

double OneLikelihoodDirectionCalculateManager::distance_position_pmt() const
{
  CLHEP::Hep3Vector position = fitted4vector.vect();
  CLHEP::Hep3Vector position_pmt = position - pmtposition;
  double d1 = std::sqrt(position_pmt*position_pmt);
  return d1;
}

double OneLikelihoodDirectionCalculateManager::distance_position_retro() const
{
  double positionX = fitted4vector.x();
  double positionY = fitted4vector.y();
  double positionZ = fitted4vector.z();
  double pmtX = pmtposition.x();
  double pmtY = pmtposition.y();
  double pmtZ = pmtposition.z();
  double half_WClength = WClength/2.;
  double a = (pmtX-positionX)*(pmtX-positionX)+(pmtY-positionY)*(pmtY-positionY);
  double b = positionX*(positionX-pmtX)+positionY*(positionY-pmtY);
  double c = positionX*positionX+positionY*positionY-WCradius*WCradius;
  double t;
  if(a != 0){
    t = (b-sqrt(b*b-a*c))/a;
  }
  else{
    t = -c/(2*b);
  }
  double z = positionZ + (pmtZ - positionZ)*t;
  if(-half_WClength < z && half_WClength > z){

}
  else if(z > half_WClength){
    t = (half_WClength - positionX)/(pmtZ-positionX);
    z = half_WClength;
  }
  else{
    t = (-half_WClength - positionX)/(pmtZ-positionX);
    z = - half_WClength;
  }
  double x = positionX + (pmtX-positionX)*t;
  double y = positionY + (pmtY-positionY)*t;
  double d2 = std::sqrt((positionX-x)*(positionX-x)+(positionY-y)*(positionY-y)+(positionZ-z)*(positionZ-z));
  return d2;
}

double OneLikelihoodDirectionCalculateManager::distance_fly_retro() const
{
  double d_position_pmt = distance_position_pmt();
  double d_position_retro = distance_position_retro();
  return (d_position_pmt + 2* d_position_retro);
}

double OneLikelihoodDirectionCalculateManager::tof_no_retro() const{
  double tof = hittime - offset - distance_position_pmt()/v_light_in_water;
  return tof;
}

double OneLikelihoodDirectionCalculateManager::tof(double distance) const
{
  double tof = hittime - offset - distance/v_light_in_water;
  return tof;
}


double OneLikelihoodDirectionCalculateManager::tof_on_retro() const{
  double tof = hittime - offset - distance_fly_retro()/v_light_in_water;
  return tof;
}

double OneLikelihoodDirectionCalculateManager::fdirprototypenoretro() const
{
  double a0 = 0.929027;
  double b0 = 4.69195;
  double a1 = 7.97348;
  double b1 = -0.310661;
  if(costheta_dir_i < 0.75){
    return (1 + a0 * (std::exp(b0 * (costheta_dir_i - 0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta_dir_i - 0.75 )) - 1));
  }
}

double OneLikelihoodDirectionCalculateManager::fdirprototypeonretro() const
{
  double a0 = 0.929027;
  double b0 = 4.69195;
  double a1 = 7.97348;
  double b1 = -0.310661;
  if(-costheta_dir_i < 0.75){
    return (1 + a0 * (std::exp(b0 * (-costheta_dir_i - 0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (-costheta_dir_i - 0.75 )) - 1));
  }
} 

double OneLikelihoodDirectionCalculateManager::fdirbydatanoretro() const
{
  double a0 = 0.97648;
  double b0 = 3.51958;
  double a1 = 0.88353;
  double b1 = -3.52407;
  if(costheta_dir_i < 0.75){
    return (1 + a0 * (std::exp(b0 * (costheta_dir_i -0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta_dir_i - 0.75 )) - 1));
  }
}

double OneLikelihoodDirectionCalculateManager::fdirbydataonretro() const
{
    double a0 = 1.55324;
  double b0 = 1.53637;
  double a1 = 0.75423;
  double b1 = -2.31295;
  if(costheta_dir_i < -0.75){
    return (1 + a0 * (std::exp(b0 * (costheta_dir_i +0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta_dir_i + 0.75 )) - 1));
  }
}

void OneLikelihoodDirectionCalculateManager::OneLikelihoodDirectionNoretro()
{
  double toferror = tof_no_retro() - fitted4vector.t();
  double likelihood;
  if(toferror > -20. && toferror < 20.)
    {
      double fdir;
      double afunc = 1.;
      if(fdirfuncnoretrotype == FDirFuncNoretroType::prototype)
	fdir = fdirprototypenoretro();
      if(fdirfuncnoretrotype == FDirFuncNoretroType::bydata)
	fdir = fdirbydatanoretro();
      if(afuncnoretrotype == AFuncNoretroType::prototype)
	afunc = afuncprototype();
      likelihood = (std::log(fdir))* std::cos(theta_i) / afunc;
    }
  else
    {
      likelihood = 0;
    }
  (std::dynamic_pointer_cast<OneLikelihoodDirectionCalculated>(currentloop2))->SetLikelihood(likelihood);
}

void OneLikelihoodDirectionCalculateManager::OneLikelihoodDirectionOnretro()
{
  double toferror = tof_on_retro() - fitted4vector.t();
  double likelihood;
  if(toferror > -20. && toferror < 20.)
    {
      double fdir;
      double afunc = 1.;
      if(fdirfunconretrotype == FDirFuncOnretroType::prototype)
	fdir = fdirprototypeonretro();
      if(fdirfunconretrotype == FDirFuncOnretroType::bydata)
	fdir = fdirbydataonretro();
      if(afunconretrotype == AFuncOnretroType::prototype)
	afunc = afuncprototype();
      likelihood = (std::log(fdir))* std::cos(theta_i) / afunc;
    }
  else
    {
      likelihood = 0;
    }
  (std::dynamic_pointer_cast<OneLikelihoodDirectionCalculated>(currentloop2))->SetLikelihood(likelihood);
}

void OneLikelihoodDirectionCalculateManager::OneLikelihoodDirectionSum()
{
  double d_position_pmt = distance_position_pmt();
  double d_position_retro = distance_position_retro();
  double d_fly_retro = d_position_pmt + 2* d_position_retro;
  double tofnoretro = tof(d_position_pmt);
  double tofonretro = tof(d_fly_retro);
  double likelihood = 0;
  double toferrornoretro = tofnoretro - fitted4vector.t();
  if(toferrornoretro > -20. && toferrornoretro < 20.)
    {
      double fdir;
      double afunc = 1.;
      if(fdirfuncnoretrotype == FDirFuncNoretroType::prototype)
	fdir = fdirprototypenoretro();
      if(fdirfuncnoretrotype == FDirFuncNoretroType::bydata)
	fdir = fdirbydatanoretro();
      if(afuncnoretrotype == AFuncNoretroType::prototype)
	afunc = afuncprototype();
      likelihood += (std::log(fdir))* std::cos(theta_i) / afunc;
    }
  double toferroronretro = tofonretro - fitted4vector.t();
  if(toferroronretro > -20. && toferroronretro < 20.)
    {
      double fdir;
      double afunc = 1.;
      if(fdirfunconretrotype == FDirFuncOnretroType::prototype)
	fdir = fdirprototypeonretro();
      if(fdirfunconretrotype == FDirFuncOnretroType::bydata)
	fdir = fdirbydataonretro();
      if(afuncnoretrotype == AFuncNoretroType::prototype)
	afunc = afuncprototype();
      likelihood += (std::log(fdir))* std::cos(theta_i) / afunc;
    }
  (std::dynamic_pointer_cast<OneLikelihoodDirectionCalculated>(currentloop2))->SetLikelihood(likelihood);
}

