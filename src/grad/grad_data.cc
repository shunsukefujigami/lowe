// c++ STL
#include <cmath>

// ROOT library
#include <TLorentzVector.h>

// self-introduced library
#include "grad_data.hh"

grad_data::grad_data()
  :x(0.),y(0.),z(0.),t(0.),theta(0.),phi(0.)
{}

grad_data::grad_data(TLorentzVector vector,double theta,double phi)
  :x(vector.X()),y(vector.Y()),z(vector.Z()),t(vector.T()),theta(theta),phi(phi)
{}

grad_data::grad_data(double x,double y,double z,double t,double theta,double phi)
  :x(x),y(y),z(z),t(t),theta(theta),phi(phi)
{}

grad_data::grad_data(const grad_data& data)
  :x(data.X()),y(data.Y()),z(data.Z()),t(data.T()),theta(data.Theta()),phi(data.Phi())
{}

grad_data grad_data::operator + (grad_data const & right) const
{
  return grad_data(x + right.X(),y + right.Y(),z + right.Z(),t + right.T(),theta + right.Theta() , phi + right.Phi());
}

grad_data grad_data::operator - (grad_data const & right) const
{
  return grad_data(x - right.X(),y - right.Y(),z - right.Z(),t - right.T(),theta - right.Theta() , phi - right.Phi());
}

grad_data& grad_data::operator += (grad_data const & right)
{
  x+= right.X();
  y+= right.Y();
  z+= right.Z();
  t+= right.T();
  theta+= right.Theta();
  phi+= right.Phi();
  return *this;
}

grad_data& grad_data::operator -= (grad_data const & right)
{
  x-= right.X();
  y-= right.Y();
  z-= right.Z();
  t-= right.T();
  theta-= right.Theta();
  phi-= right.Phi();
  return *this;
}

grad_data grad_data::operator * (double a) const
{
  return grad_data(a*x,a*y,a*z,a*t,a*theta,a*phi);
}

bool grad_data::operator == (grad_data const & right) const
{
  return (( x == right.X()) && (y == right.Y()) && (z == right.Z()) && (t == right.T()) && (theta == right.Theta()) && (phi == right.Phi()));
}
bool grad_data::operator != (grad_data const & right) const
{
  return !((*this) == right);
}

double grad_data::X() const
{
  return x;
}

double grad_data::Y() const
{
  return y;
}

double grad_data::Z() const
{
  return z;
}

double grad_data::T() const
{
  return t;
}

double grad_data::Theta() const
{
  return theta;
}

double grad_data::CosTheta() const
{
  return std::cos(theta);
}

double grad_data::Phi() const
{
  return phi;
}

grad_data& grad_data::plusX(double x_in)
{
  x += x_in;
  return *this;
}

grad_data& grad_data::plusY(double y_in)
{
  y += y_in;
  return *this;
}

grad_data& grad_data::plusZ(double z_in)
{
  z += z_in;
  return *this;
}

grad_data& grad_data::plusT(double t_in)
{
  t += t_in;
  return *this;
}

grad_data& grad_data::plusTheta(double theta_in)
{
  theta += theta_in;
  return *this;
}
grad_data& grad_data::plusPhi(double phi_in)
{
  phi += phi_in;
  return *this;
}
double grad_data::function(grad_data data)
{
  return 0; // temporary
};

grad_data grad_data::gradfunction(std::function<double(grad_data)> func,grad_data data)
{
  double dx = 1e-8;
  double dy = 1e-8;
  double dz = 1e-8;
  double dt = 1e-8;
  double dtheta = 1e-8;
  double dphi = 1e-8;
  double dfdx = (func(data.plusX(dx)) - func(data))/dx;
  double dfdy = (func(data.plusY(dy)) - func(data))/dy;
  double dfdz = (func(data.plusZ(dz)) - func(data))/dz;
  double dfdt = (func(data.plusT(dt)) - func(data))/dt;
  double dfdtheta = (func(data.plusTheta(dtheta)) - func(data))/dtheta;
  double dfdphi = (func(data.plusPhi(dphi)) - func(data))/dphi;
  return grad_data(dfdx,dfdy,dfdz,dfdt,dfdtheta,dfdphi);
}

bool grad_data::nequalzero(grad_data error) const
{
  if(x < error.X() && x > -error.X() && y < error.Y() && y > -error.Y() && z < error.Z() && z > -error.Z() && t < error.T() && t > -error.T() && theta < error.Theta() && theta > -error.Theta() && phi < error.Phi() && phi > -error.Phi())
    {
      return true;
    }
  else
    {
      return false;
    }
}
