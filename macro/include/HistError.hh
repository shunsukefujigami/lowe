#ifndef HISTERROR_HH
#define HISTERROR_HH
// ROOT library
#include <TH1D.h>

// self-introduced library
#include "FileList.hh"

class HistError : public TH1D
{
public:
  HistError();
  HistError(FileList* list,const char* paraname_in,const char* name,const char* title,int num,double min,double max,double width,int numorig_in,double minorig_in,double maxorig_in,double widthorig_in);
  virtual ~HistError(){};
private:
  FileList filelist;
  void fillloop(int i,double iter);
  const char* paraname;
  int numorig;
  double minorig;
  double maxorig;
  double widthorig;
public:
  ClassDef(HistError,1)
};

#endif
