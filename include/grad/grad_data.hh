#ifndef GRAD_DATA_HH
#define GRAD_DATA_HH
// c++ STL
#include <functional>

// ROOT library
#include <TLorentzVector.h>

class grad_data
{
  // class for the self-making gradient minimize analize
public:
  grad_data();
  grad_data(TLorentzVector vector,double theta,double phi);
  grad_data(double x,double y,double z,double t,double theta,double phi);
  grad_data(const grad_data& data);
  virtual ~grad_data(){};
  grad_data operator + (grad_data const & right) const;
  grad_data operator - (grad_data const & right) const;
  grad_data& operator += (grad_data const & right);
  grad_data& operator -= (grad_data const & right);
  grad_data operator * (double a) const;
  bool operator == (grad_data const & right) const;
  bool operator != (grad_data const & right) const;
  double X() const;
  double Y() const;
  double Z() const;
  double T() const;
  double Theta() const;
  double CosTheta() const;
  double Phi() const;
  grad_data& plusX(double x);
  grad_data& plusY(double y);
  grad_data& plusZ(double z);
  grad_data& plusT(double t);
  grad_data& plusTheta(double theta);
  grad_data& plusPhi(double phi);
  static double function(grad_data data);
  static grad_data gradfunction(std::function<double(grad_data)> func,grad_data data);
  bool nequalzero(grad_data error) const;
private:
  double x;
  double y;
  double z;
  double t;
  double theta;
  double phi;
};

#endif
