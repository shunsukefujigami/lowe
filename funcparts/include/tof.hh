#ifndef TOF_HH
#define TOF_HH

// c++ STL
#include <memory>


// self-introduced library
#include "hitinfo.hh"
#include "Reconstructdata.hh"
#include "distance_function.hh"
#include "constants.hh"
class tof : public function
{
public:
  tof(){};
  virtual ~tof(){};
  void SetHitInfo(hitinfo infoin)
  {
    info = infoin;
  }
  void SetReconstructdata(Reconstructdata datain)
  {
    data = datain;
  }
  void Setdistancefunction(std::shared_ptr<distance_function> dfunc)
  {
    this->dfunc = dfunc;
  }
  virtual double returnvalue()
  {
    dfunc->SetHitInfo(info);
    dfunc->SetReconstructdata(data);
    double tof = info.HitTime() - offset - dfunc->returnvalue()/v_light_in_water;
    return tof;
  }
  
private:
  hitinfo info;
  Reconstructdata data;
  std::shared_ptr<distance_function> dfunc;
};

#endif
