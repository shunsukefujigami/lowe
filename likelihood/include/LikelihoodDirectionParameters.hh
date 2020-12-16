#ifndef LIKELIHOODDIRECTIONPARAMETERS_HH
#define LIKELIHOODDIRECTIONPARAMETERS_HH

// self-introduced library
#include "VParameters.hh"
#include "AngleRange.hh"
#include "EnumManager.hh"

ENUM(OneLikelihoodDirectionCalculateType,noretro,onretro,sum);

ENUM(FDirFuncNoretroType,prototype,bydata);

ENUM(FDirFuncOnretroType,prototype,bydata);

ENUM(AFuncOnretroType,prototype);

ENUM(AFuncNoretroType,prototype);

class LikelihoodDirectionParameters :public VParameters
{
public:
  LikelihoodDirectionParameters(){}
  virtual ~LikelihoodDirectionParameters()
  {
  }
  OneLikelihoodDirectionCalculateType::type GetOneLikelihoodDirectionCalculateType() const 
  {
    return onelikelihooddirectioncalculatetype;
  }
  void SetOneLikelihoodDirectionCalculateType(OneLikelihoodDirectionCalculateType::type type)
  {
    onelikelihooddirectioncalculatetype = type;
  }
  FDirFuncNoretroType::type GetFDirFuncNoretroType() const
  {
    return fdirfuncnoretrotype;
  }
  void SetFDirFuncNoretroType(FDirFuncNoretroType::type type)
  {
    fdirfuncnoretrotype = type;
  }
  FDirFuncOnretroType::type GetFDirFuncOnretroType() const
  {
    return fdirfunconretrotype;
  }
  void SetFDirFuncOnretroType(FDirFuncOnretroType::type type)
  {
    fdirfunconretrotype = type;
  }
  
  AFuncOnretroType::type GetAFuncOnretroType() const 
  {
    return afunconretrotype;
  }
  void SetAFuncOnretroType(AFuncOnretroType::type type)
  {
    afunconretrotype = type;
  }

  AFuncNoretroType::type GetAFuncNoretroType() const
  {
    return afuncnoretrotype;
  }

  void SetAFuncNoretroType(AFuncNoretroType::type type)
  {
    afuncnoretrotype = type;
  }

  AngleRange GetAngleRange() const
  {
    return range;
  }
  void SetAngleRange(AngleRange ran)
  {
    range = ran;
  }
  
private:
  OneLikelihoodDirectionCalculateType::type onelikelihooddirectioncalculatetype;
  FDirFuncNoretroType::type fdirfuncnoretrotype;
  FDirFuncOnretroType::type fdirfunconretrotype;
  AFuncOnretroType::type afunconretrotype;
  AFuncNoretroType::type afuncnoretrotype;
  AngleRange range;
};
  
#endif
