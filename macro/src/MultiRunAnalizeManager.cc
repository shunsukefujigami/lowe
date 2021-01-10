// c++ STL
#include <iostream>
#include <cstring>
#include <dirent.h>
// self-introduced libarary
#include "MultiRunAnalizeManager.hh"
#include "OneRunAnalizeManager.hh"
#include "BiasError.hh"

ClassImp(MultiRunAnalizeManager)

MultiRunAnalizeManager::MultiRunAnalizeManager()
{
}


void MultiRunAnalizeManager::SetBasefile(const char* basefile)
{
  sbasefile = basefile;
  if(sbasefile.find("LSR") != std::string::npos)
    {
      mode = 2;
      std::cout << "set likelihood mode!" << std::endl;
      baselikelihoodparameters.Setpair(sbasefile);
      baselikelihoodparameters.SetValue();
    }
  else if(sbasefile.find("GSR") != std::string::npos)
    {
      mode = 1;
      std::cout << "set goodness mode!" << std::endl;
      basegoodnessparameters.Setpair(sbasefile);
      basegoodnessparameters.SetValue();
    }
  else if(sbasefile.find("DET") != std::string::npos)
    {
      mode = 0;
      std::cout << "set data mode!" << std::endl;
      basefileparameters.Setpair(sbasefile);
      basefileparameters.SetValue();
    }
  else
    {
      std::cout << "invalid file name!" << std::endl;
      throw "MultiRunAnalizeManager::SetComparefile(const char* file)";
    }
}

void MultiRunAnalizeManager::SetAllfile()
{
  std::string directory;
  if(mode == 0)
    directory = "/home/fujigami/store/datafile/";
  if(mode == 1)
    directory = "/home/fujigami/store/goodnessfile/";
  if(mode == 2)
    directory = "/home/fujigami/store/likelihoodfile/";
  DIR* dir;
  dir = opendir(directory.c_str());
  if(dir == NULL)
    {
      std::cout << "directory is not found";
      throw "void MultiRunAnalizeManager::SetComparefile(std::vector<std::string> vexclusionname)";
    }
  dirent* entry = readdir(dir);
  while(entry != NULL)
    {
      std::string sdname = entry->d_name;
      std::string fullpath = directory + sdname;
      if(fullpath.find("/.") == std::string::npos)
	{
	  if(mode == 0)
	    {
	      std::cout << fullpath << std::endl;
	      OneDataParameters odp;
	      odp.Setpair(fullpath);
	      odp.SetValue();
	      odp.PrintValue();
	      vdataparameters.push_back(odp);
	    }
	  if(mode == 1)
	    {
	      std::cout << fullpath << std::endl;
	      OneGoodnessParameters ogp;
	      ogp.Setpair(fullpath);
	      ogp.SetValue();
	      ogp.PrintValue();
	      vgoodnessparameters.push_back(ogp);
	    }
	  if(mode == 2)
	    {
	      std::cout << fullpath << std::endl;
	      OneLikelihoodParameters olp;
	      olp.Setpair(fullpath);
	      olp.SetValue();
	      olp.PrintValue();
	      vlikelihoodparameters.push_back(olp);
	    }
	  
	}
      entry = readdir(dir);
    }
}

void MultiRunAnalizeManager::SetComparefile(std::vector<std::string> vexclusionname)
{
  int number = 0;
  std::vector<std::string> vfile;
  if(mode == 0)
    {
      for(auto itr = vdataparameters.begin();itr != vdataparameters.end();itr++)
	{
	  if(basefileparameters.isEqual(*itr,vexclusionname))
	    {
	      number++;
	      vfile.push_back((*itr).Getfile());
	    }
	}
    }
  if(mode == 1)
    {
      for(auto itrg = vgoodnessparameters.begin();itrg != vgoodnessparameters.end();itrg++)
	{
	  if(basegoodnessparameters.isEqual(*itrg,vexclusionname))
	    {
	      number++;
	      vfile.push_back((*itrg).Getfile());
	    }
	}
    }
  if(mode == 2)
    {
      for(auto itrl = vlikelihoodparameters.begin();itrl != vlikelihoodparameters.end();itrl++)
	{
	  if(baselikelihoodparameters.isEqual(*itrl,vexclusionname))
	    {
	      number++;
	      vfile.push_back((*itrl).Getfile());
	    }
	}
    }
  vrunanalizemanager = std::vector<OneRunAnalizeManager>(number);
  size_t i = 0;
  for(auto itrf = vfile.begin();itrf != vfile.end();itrf++)
    {
      if(mode == 0)
	vrunanalizemanager.at(i).Setdatafile((*itrf).c_str());
      if(mode == 1)
	vrunanalizemanager.at(i).SetGoodnessfile((*itrf).c_str());
      if(mode == 2)
	vrunanalizemanager.at(i).SetLikelihoodfile((*itrf).c_str());
      i++;
    }
}

void MultiRunAnalizeManager::PrintAllfile()
{
  if(mode == 0)
    {
      for(auto itr = vdataparameters.begin();itr != vdataparameters.end();itr++)
	{
	  std::cout << (*itr).Getfile() << std::endl;
	}
    }
  if(mode == 1)
    {
      for(auto itrg = vgoodnessparameters.begin();itrg != vgoodnessparameters.end();itrg++)
	{
	  std::cout << (*itrg).Getfile() << std::endl;
	}
    }
  if(mode == 2)
    {
      for(auto itrl = vlikelihoodparameters.begin();itrl != vlikelihoodparameters.end();itrl++)
	{
	  std::cout << (*itrl).Getfile() << std::endl;
	}
    }
  
}

void MultiRunAnalizeManager::PrintComparefile()
{
  for(auto itr = vrunanalizemanager.begin();itr != vrunanalizemanager.end();itr++)
    {
      if(mode == 0)
	std::cout << (*itr).Getdatamanager()->GetDataParameters()->Getfile() << std::endl;
      if(mode == 1)
	std::cout << (*itr).Getgoodnessmanager()->GetGoodnessParameters()->Getfile() << std::endl;
      if(mode == 2)
	std::cout << (*itr).Getlikelihoodmanager()->GetLikelihoodParameters()->Getfile() << std::endl;
    }
}

MultiRunAnalizeManager::~MultiRunAnalizeManager()
{
}

TH1D MultiRunAnalizeManager::GetTH1D(int num,double min,double max,const char* xvar,const char* yvar,bool berror,const char* errorval)
{
  TH1D th1d("","",num,min,max);
  for(auto itr = vrunanalizemanager.begin();itr != vrunanalizemanager.end();itr++)
    {
      double xval = GetVariable(xvar,*itr);
      double yval = GetVariable(yvar,*itr);
      th1d.Fill(xval,yval);
      if(berror)
	{
	  int bin = th1d.FindBin(xval);
	  double yerror = GetVariable(errorval,*itr);
	  th1d.SetBinError(bin,yerror);
	}
      
    }
  return th1d;
}

double MultiRunAnalizeManager::GetVariable(const char* var,OneRunAnalizeManager& oram)
{
  std::string svar = var;
  if(svar == "tzmaxreflectivity")
    {
      return oram.Getdatamanager()->GetDataParameters()->trapezoidreflectivity;
    }
  if(svar == "fixedenergy")
    {
      return oram.Getdatamanager()->GetDataParameters()->fixedenergy;
    }
  if(svar == "triggerefficiency")
    {
      return oram.Getdatamanager()->GetEfficiency();
    }
  if(svar == "xbiasbygoodness")
    {
      BiasError xbiaserror = oram.GetXBiasErrorbygoodness();
      return xbiaserror.bias;
    }
  if(svar == "xbiaserrorbygoodness")
    {
      BiasError xbiaserror = oram.GetXBiasErrorbygoodness();
      return xbiaserror.biaserror;
    }
  if(svar == "xerrorbygoodness")
    {
      BiasError xbiaserror = oram.GetXBiasErrorbygoodness();
      return xbiaserror.error;
    }
  if(svar == "xerrorerrorbygoodness")
    {
      BiasError xbiaserror = oram.GetXBiasErrorbygoodness();
      return xbiaserror.errorerror;
    }
    if(svar == "ybiasbygoodness")
    {
      BiasError ybiaserror = oram.GetYBiasErrorbygoodness();
      return ybiaserror.bias;
    }
  if(svar == "ybiaserrorbygoodness")
    {
      BiasError ybiaserror = oram.GetYBiasErrorbygoodness();
      return ybiaserror.biaserror;
    }
  if(svar == "yerrorbygoodness")
    {
      BiasError ybiaserror = oram.GetYBiasErrorbygoodness();
      return ybiaserror.error;
    }
  if(svar == "yerrorerrorbygoodness")
    {
      BiasError ybiaserror = oram.GetYBiasErrorbygoodness();
      return ybiaserror.errorerror;
    }
    if(svar == "zbiasbygoodness")
    {
      BiasError zbiaserror = oram.GetZBiasErrorbygoodness();
      return zbiaserror.bias;
    }
  if(svar == "zbiaserrorbygoodness")
    {
      BiasError zbiaserror = oram.GetZBiasErrorbygoodness();
      return zbiaserror.biaserror;
    }
  if(svar == "zerrorbygoodness")
    {
      BiasError zbiaserror = oram.GetZBiasErrorbygoodness();
      return zbiaserror.error;
    }
  if(svar == "zerrorerrorbygoodness")
    {
      BiasError zbiaserror = oram.GetZBiasErrorbygoodness();
      return zbiaserror.errorerror;
    }
  if(svar == "angleerrrorbylikeliihood")
    {
      double angle = oram.angleerror1sigma();
      return angle;
    }
  
  std::cout << svar << " is invalid!" << std::endl;
  throw "double MultiRunAnalizeManager::GetVariable(const char* var,OneRunAnalizeManager oram)";
}
