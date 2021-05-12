// STL
#include <iterator>
#include <algorithm>
#include <iostream>
// ROOT
#include <TPython.h>
#include <TH1D.h>
#include <TVector3.h>
// self
#include "AnalizeManager.hh"

ClassImp(AnalizeManager)
AnalizeManager::AnalizeManager()
{
}


void AnalizeManager::cpFileList(FileManager* manager,std::string filelistname)
{
  //  (*this).filelistname.push_back(filelistname);
  listoffilelist.insert(std::make_pair(filelistname,manager->selectedfile));
}

void AnalizeManager::SetData()
{
  for(auto iter = listoffilelist.begin();iter != listoffilelist.end();iter++)
    {
      TPython::Exec("filelist = {}");
      for(auto iter2 = (*iter).second.begin(); iter2 != (*iter).second.end();iter2++)
	{
	  std::string filenameroot = (*iter2).fileroot;
	  TPython::Exec(("filelist['" + filenameroot + "'] = macro.filemanager('" + filenameroot + "')").c_str());
	}
      TPython::Exec(("macro.filemanager.filedictofdict['" + (*iter).first + "'] = filelist").c_str());
    }
}


bool AnalizeManager::GetValue(AnalizeFile manager,std::string valueload,std::string valuetype,double& value,int ievent)
{
  if(valueload == "number")
    {
      value = 1.;
      return true;
    }
  int valueint = 0;
  std::string bvalue = "init";
  if(valuetype == "int")
	{
	  if(manager.GetTagint(valueload,valueint))
	    {
	      value = (double)valueint;
	      return true;
	    }
	}
  else if(valuetype == "double")
	{
	  if(manager.GetTagdouble(valueload,value))
	    {
	      return true;
	    }
	}
  else
    {
    }
  TPython::Exec(("value = f.GetValue('" + valueload + "'," + std::to_string(ievent) + ")").c_str());
  const char* cbvalue = TPython::Eval("value[1]");
  bvalue = cbvalue;
  value = (double)TPython::Eval("value[0]");
  if(bvalue == "true")
    return true;
  if(valueload == "distance_true_reconstructedbygoodness")
    {
      TPython::Exec(("truex = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(0)'," + std::to_string(ievent) + ")").c_str());
      TPython::Exec(("truey = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(1)'," + std::to_string(ievent) + ")").c_str());
      TPython::Exec(("truez = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetVtx(2)'," + std::to_string(ievent) +")").c_str());
      TPython::Exec("truevec = ROOT.TVector3(truex[0],truey[0],truez[0])");
      TPython::Exec(("reconstructvec = f.GetValue('goodnessT.reconstructdata.Get3Position()'," + std::to_string(ievent) + ")").c_str());
      value = TPython::Eval("(truevec - reconstructvec[0]).Mag()");
      return true;
    }
  if(valueload == "truecostheta")
    {
      double truedirx = TPython::Exec(("f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetDir(0)'," + std::to_string(ievent) + ")[0]").c_str());
      double truediry = TPython::Eval(("f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetDir(1)'," + std::to_string(ievent) + ")[0]").c_str());
      double truedirz = TPython::Eval(("f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetDir(2)'," + std::to_string(ievent) + ")[0]").c_str());
      TVector3 dir(truedirx,truediry,truedirz);
      value = dir.CosTheta();
      return true;
    }
  if(valueload == "truephi")
    {
      double truedirx = TPython::Eval(("f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetDir(0)'," + std::to_string(ievent) + ")[0]").c_str());
      double truediry = TPython::Eval(("f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetDir(1)'," + std::to_string(ievent) + ")[0]").c_str());
      double truedirz = TPython::Eval(("f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetTracks().At(0).GetDir(2)'," + std::to_string(ievent) + ")[0]").c_str());
      TVector3 dir(truedirx,truediry,truedirz);
      value = dir.Phi();
      return true;
    } 
  return false;
}


void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());

      double x = 0.;
      double value = 0.;
      if(!GetValue((*iterin),xaxis,xaxistype,x,ievent))
	    {
	      std::cout << "invalid input!" << std::endl;
	      throw "void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)";
	    }
      if(!GetValue((*iterin),valueaxis,valueaxistype,value,ievent))
	    {
	      std::cout << "invalid input!" << std::endl;
	      throw "void AnalizeManager::SetTH1D(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname,int ievent)";
	    }
      h1->Fill(x,value);
    }
}

void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
      int nevent = TPython::Eval("f.GetNeventmax()");
      for(int ievent = 0;ievent != nevent;ievent++)
	{
	  TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
	  int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
	  if(ncherenkovdigihits != 0)
	    {
	      double x = 0.;
	      double value = 0.;
	      if(!GetValue((*iterin),xaxis,xaxistype,x,ievent))
		{
		  std::cout << "invalid input!" << std::endl;
		  throw "void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		}
	      if(!GetValue((*iterin),valueaxis,valueaxistype,value,ievent))
		{
		  std::cout << "invalid input!" << std::endl;
		  throw "void AnalizeManager::SetTH1DEvent(TH1D* h1,std::string xaxis,std::string xaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		} 
	      h1->Fill(x,value);
	    }
	}
    }
}

void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)
{
  auto iter = listoffilelist.at(flistname);
  for(auto iterin = iter.begin();iterin != iter.end();iterin++)
    {
      TPython::Exec(("f = macro.filemanager.filedictofdict['" + flistname + "']['" + (*iterin).fileroot + "']").c_str());
      int nevent = TPython::Eval("f.GetNeventmax()");
      for(int ievent = 0;ievent != nevent;ievent++)
	{
	  TPython::Exec(("Ncherenkovdigihits = f.GetValue('wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()'," + std::to_string(ievent) + ")").c_str());
	  int ncherenkovdigihits = TPython::Eval("Ncherenkovdigihits[0]");
	  if(ncherenkovdigihits != 0)
	    {
	      double x = 0.;
	      double y = 0.;
	      double value = 0.;
	      if(!GetValue((*iterin),xaxis,xaxistype,x,ievent))
		{
		  std::cout << "invalid input!" << std::endl;
		  throw "void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		}
	      if(!GetValue((*iterin),yaxis,yaxistype,y,ievent))
		{
		  std::cout << "invalid input!" << std::endl;
		  throw "void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		}
	      
	      if(!GetValue((*iterin),valueaxis,valueaxistype,value,ievent))
		{
		  std::cout << "invalid input!" << std::endl;
		  throw "void AnalizeManager::SetTH2DEvent(TH2D* h,std::string xaxis,std::string xaxistype,std::string yaxis,std::string yaxistype,std::string valueaxis,std::string valueaxistype,std::string flistname)";
		} 
	      h->Fill(x,y,value);
	    }
	}
    }
}

void AnalizeManager::PrintFilename()
{
  TPython::Exec("print macro.filemanager.filecictofdict.keys()");
}

