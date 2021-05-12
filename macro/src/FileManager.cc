#include "FileManager.hh"
#include <dirent.h>
#include <iostream>
#include <string>

ClassImp(FileManager)

std::string FileManager::directory = "/raid1/kuzelab/fujigami/analizefile/";

FileManager::FileManager()
{
}

void FileManager::SetAllFile()
{
  DIR* dir;
  dir = opendir(directory.c_str());
  if(dir == NULL)
    {
      std::cout << "directory is not found";
      throw "void FileManager::SetAllFile()";
    }
  dirent* entry = readdir(dir);
  while(entry != NULL)
    {
      std::string sdname = entry->d_name;
      if(sdname.find(".csv") != std::string::npos)
	{
	  std::string fullpath = directory + sdname;
	  allfile.emplace_back(fullpath);
	}
      entry = readdir(dir);
    }
}

void FileManager::printfilelist()
{
  std::cout << "file name table" << std::endl;
  std::cout << "---------------------------------------------" << std::endl;
  for(auto iter = allfile.begin();iter != allfile.end();iter++)
    {
      std::cout << (*iter).filecsv << std::endl;
    }
  std::cout << "---------------------------------------------" << std::endl;
}

void FileManager::reflectNarrowDownTag()
{
  selectedfile.clear();
  std::vector<int> isselected(allfile.size(),1);
  for(auto itertag = narrowdowntag.begin();itertag != narrowdowntag.end();itertag++)
    {
      std::vector<int> isselectedone(allfile.size(),0);
      int i = 0;
      for(auto iterfile = allfile.begin();iterfile != allfile.end();iterfile++,i++)
	{
	  if((*iterfile).hasEqualTag((*itertag)))
	    isselectedone.at(i) = 1;
	}
      for(int k = 0;k != (int)allfile.size();k++)
	{
	  if(isselectedone.at(k) == 0)
	    {
	      isselected.at(k) = 0;
	    }
	  
	}
    }
  int j = 0;
  for(auto iter = allfile.begin();iter != allfile.end();iter++,j++)
    {
      if(isselected.at(j) == 1)
	{
	  selectedfile.emplace_back((*iter));
	}
    }
}

void FileManager::printselectedfile()
{
  std::cout << "selected file table" << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;
  for(auto iter = selectedfile.begin();iter != selectedfile.end();iter++)
    {
      std::cout << (*iter).filecsv << std::endl;
    }
  std::cout << "-----------------------------------------------------" << std::endl;
}

bool FileManager::isexistsamefile()
{
  for(auto iter = allfile.begin();iter != allfile.end();iter++)
    {
      for(auto iter2 = allfile.begin();iter2 != allfile.end();iter2++)
	{
	  if((*iter).filecsv != (*iter2).filecsv)
	    {
	      if((*iter) == (*iter2))
		return true;
	    }
	}
    }
  return false;
}

bool FileManager::isexistsamefile(AnalizeFile file)
{
  for(auto iter = allfile.begin();iter != allfile.end();iter++)
    {
      if((*iter).filecsv != file.filecsv)
	{
	  if((*iter) == file)
	    return true;
	}
    }
  return false;
}

