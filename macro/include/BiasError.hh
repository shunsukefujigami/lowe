#ifndef BIASERROR_HH
#define BIASERROR_HH

class BiasError
{
public:
  BiasError(){}
  virtual ~BiasError()
  {
  }
  
  double bias;
  double biaserror;
  double error;
  double errorerror;
};

#endif
