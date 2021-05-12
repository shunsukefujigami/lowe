#ifndef _ANALIZEMANAGER_HH
#define _ANALIZEMANAGER_HH
// STL
#include <vector>
#include <map>

// ROOT
#include <TObject.h>
#include <TH1D.h>
#include <TH2D.h>
// self
#include "FileManager.hh"
#include "AnalizeFile.hh"

class AnalizeManager : public TObject
{
public:
  AnalizeManager();
  virtual ~AnalizeManager()
  {
  }
  void cpFileList(FileManager* manager,std::string filelistname);
  void SetData();
  //  std::vector<std::string> filelistname;
  std::map<std::string,std::vector<AnalizeFile>> listoffilelist;
  static bool GetValue(AnalizeFile manager,std::string valueload,std::string valuetype,double& value,int ievent);
  void SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent=0);
  void SetTH1DEvent(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname);
  void SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname);
  void PrintFilename();
  ClassDef(AnalizeManager,1)
};


#endif
