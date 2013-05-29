#include "LevelManager.h"

#include "CommonUtils.h"
#include <fstream>

#include "FileHandle.h"
#include "NewLevel.h"

using namespace std;

static const unsigned int MAX_FUNC_SIZE = 11,
  MAX_PARAM_SIZE = 1024 - MAX_FUNC_SIZE;

static map<string, LevelManager::levelCallback> __levelFuncMap;
static map<string, LevelManager::levelMgrCallback> __levelMgrFuncMap;

void LevelManager::InitializeCourse(char* params)
{
  size_t paramLen = strlen(params);
  char *name = new char[paramLen + 1];
#pragma warning( suppress : 4996 )
  sscanf(params, "\"%[^\"] %d", name, _holeCount);
  _courseName = name;
  delete name;
}

void LevelManager::CreateLevel(char*)
{
  NewLevel *l = new NewLevel;
  l->Initialize();
  _levels->push_back(l);
}

void LevelManager::FinalizeLevel(char*)
{
  unsigned int level = _levels->size() - 1;
  //_levels->at(level)->PostLoad();
}

unsigned char LevelManager::Initialize()
{
  _levels = new std::vector<NewLevel*>;

  __levelMgrFuncMap["course"] = &LevelManager::InitializeCourse;
  __levelMgrFuncMap["begin_hole"] = &LevelManager::CreateLevel;
  __levelMgrFuncMap["end_hold"] = &LevelManager::FinalizeLevel;

  __levelFuncMap["name"] = &NewLevel::ReadName;
  __levelFuncMap["par"] = &NewLevel::ReadPar;
  __levelFuncMap["tile"] = &NewLevel::ReadTile;
  __levelFuncMap["tee"] = &NewLevel::ReadTee;
  __levelFuncMap["cup"] = &NewLevel::ReadCup;

  return STATUS_OK;
}

unsigned char LevelManager::DeInitialize()
{
  //DeleteVectorPtrs(&_levels);

  return STATUS_OK;
}

template <typename K, typename T>
unsigned char LevelManager::ExecuteCallback(map<K, void (T::*)(char*)> const & m, K key, char* params, T* t)
{
  map<string, void (T::*)(char*)>::const_iterator iter = m.find(key);

  if (iter != m.end())
  {
    (t->*(*iter).second)(params);
    return STATUS_OK;
  }

  return 0x2;
}

unsigned char LevelManager::LoadLevels()
{
  FileHandle f;

  if (f.Open("Holes/course.db") != STATUS_OK)
  {
    return 0x2; // Failed to open file
  }

  char func[MAX_FUNC_SIZE], params[MAX_PARAM_SIZE];

  while(!f.eof())
  {
    f.ReadLine('\n', func, params);
    const string funcStr(func);

    if (ExecuteCallback(__levelMgrFuncMap, funcStr, params, this) == STATUS_OK)
    {
      continue;
    }
    else if (ExecuteCallback(__levelFuncMap, funcStr, params, _levels->at(_levels->size() - 1)) == STATUS_OK)
    {
      continue;
    }

    // If this gets hit, then either the function specified in the file
    // was incorrect, or there is no registered callback for that
    // particular function
    return 0x4;
  }

  f.Close();

  return STATUS_OK;
}

void LevelManager::PlayLevel(unsigned int level)
{

}