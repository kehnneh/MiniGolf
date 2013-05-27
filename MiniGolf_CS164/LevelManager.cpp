#include "LevelManager.h"

#include "CommonUtils.h"
#include <fstream>

unsigned char LevelManager::Initialize()
{
  _levels = new std::vector<Level*>;

  return STATUS_OK;
}

unsigned char LevelManager::DeInitialize()
{
  DeleteVectorPtrs(&_levels);

  return STATUS_OK;
}

unsigned char LevelManager::LoadLevels()
{
  std::fstream fin("Holes/course.db");

  if (fin.fail())
  {
    return 0x2;
  }

  char c;

  while(!fin.eof())
  {
    fin.get(c);

    // check the first character of the line
    if (c == 'c') // 'course' line
    {
      for (int i = 0; i < 5; i++)
        fin.get(c);

      fin >> _courseName;
    }
    else if (c == 'b') // 'begin_hole' line, does nothing
    {
      // chomp line 
    }
    else if (c == 'n') // 'name' line
    {
      for (int i = 0; i < 3; i++)
        fin.get(c);

      //NewLevel *l = new NewLevel;
      //l->Initialize();
      //fin >> l->levelName;
      
      fin.get(c);

    }
  }

  return STATUS_OK;
}

void LevelManager::PlayLevel(unsigned int level)
{

}