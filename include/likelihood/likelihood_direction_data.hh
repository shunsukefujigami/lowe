#ifndef LIKELIHOOD_DIRECTION_DATA_HH
#define LIKELIHOOD_DIRECTION_DATA_HH

class l_dir_data
{
  // class for the storage of likelihood direction analisys data
public:
  l_dir_data();
  l_dir_data(double costheta,double phi,double likelihood);
  virtual ~l_dir_data(){};
  void SetL(double l) { likelihood = l;}
  void SetCosTheta(double costheta_in){ costheta = costheta_in;}
  void SetPhi(double phi_in){ phi = phi_in;}
  double GetL(){return likelihood;}
  double GetCosTheta(){return costheta;}
  double GetPhi(){ return phi;}
private:
  double likelihood;
  double costheta;
  double phi;
};

#endif
