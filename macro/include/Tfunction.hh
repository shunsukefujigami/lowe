#ifndef TFUNCTION_HH
#define TFUNCTION_HH

#include <TObject.h>

class Tfunction : public TObject
{
public:
  Tfunction()
  {
  }
  virtual ~Tfunction(){};
  virtual double returnvalue() = 0;
  ClassDef(Tfunction,1)
};

#endif
  
