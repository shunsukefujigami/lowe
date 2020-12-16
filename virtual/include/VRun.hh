#ifndef VRUN_HH
#define VRUN_HH

class VRun
{
public:
  VRun()
  {
  }
  virtual ~VRun()
  {
  }
  int GetnumberOfEvent()
  {
    return numberofevent;
  }
  void SetnumberOfEvent(int n)
  {
    numberofevent = n;
  }
private:
  int numberofevent;
};

#endif
