#include "FileList.hh"
#include "MultiRunAnalizeManager.hh"

int main()
{
  FileList* dfilelist = new FileList("/home/fujigami/retro/lowe/filelist/wcsim_on_retro_threshold24_electron_5MeV_10000event_minus100cm_reflectivity.txt",11);
  MultiRunAnalizeManager* mram = new MultiRunAnalizeManager(dfilelist,11);
  delete mram;
  delete dfilelist;
  return 0;
}

  
