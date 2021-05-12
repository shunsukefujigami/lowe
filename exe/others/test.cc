#include "FileManager.hh"
#include "AnalizeManager.hh"
#include <TPython.h>
#include <TH1D.h>
#include <TRint.h>
#include <exception>
#include <iostream>
#include <string>

int main(int argc,char** argv)
{
  try
    {
      TRint app("app",&argc,argv);
      TPython::Exec("import macro");
      FileManager* filemanager = new FileManager();
      filemanager->SetAllFile();
      AnalizeTag tag("ParticleEnergyFixedValue","double",5.);
      AnalizeTag tag2("GoodnessSigma","double",5.);
      filemanager->narrowdowntag.push_back(tag);
      filemanager->narrowdowntag.push_back(tag2);
      filemanager->reflectNarrowDownTag();
      AnalizeManager* manager = new AnalizeManager();
      manager->cpFileList(filemanager,"test");
      manager->SetData();
      TH1D* h2 = new TH1D("h2","",100,0.,100.);
      manager->SetTH1DEvent(h2,"wcsimT.wcsimrootevent.GetTrigger(0).GetNcherenkovdigihits()","int","number","int","test");
      h2->Draw();
      app.Run();
      delete h2;
      delete manager;
      delete filemanager;
    }
  catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  
  catch(std::string str)
    {
      std::cout << "Error in " << str << std::endl;
    }
  
  return 0;
}

  
