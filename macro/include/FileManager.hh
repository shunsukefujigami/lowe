#ifndef FILEMANAGER_HH
#define FILEMANAGER_HH

// c++ STL
#include <vector>
#include <string>

// ROOT
#include <TObject.h>

// self
#include "AnalizeFile.hh"

class FileManager : public TObject
{
public:
  FileManager();
  virtual ~FileManager(){};
  void SetAllFile();
  void printfilelist();
  void reflectNarrowDownTag();
  void printselectedfile();
  bool isexistsamefile();
  bool isexistsamefile(AnalizeFile file);
  std::vector<AnalizeFile> allfile;
  std::vector<AnalizeFile> selectedfile;
  std::vector<AnalizeTag> narrowdowntag;
  static std::string directory;
  ClassDef(FileManager,1)
};
  

#endif
