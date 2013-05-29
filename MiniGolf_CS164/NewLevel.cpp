#include "NewLevel.h"
#include "Tile.h"
#include "CommonUtils.h"

#include <iostream>

unsigned char NewLevel::Initialize()
{
  // Initialize Tee and Cup pointers

  return STATUS_OK;
}

unsigned char NewLevel::DeInitialize()
{
  // Delete Tee and Cup pointers
  Delete(&_name);

  return STATUS_OK;
}

void NewLevel::ReadName(char* name)
{
  _name = new std::string(name);
}

void NewLevel::ReadPar(char* par)
{
#pragma warning( suppress : 4996 )
  if (sscanf(par, "%d", _par) < 1)
  {
    // What happened?
  }
}

void NewLevel::ReadTile(char* tile)
{
  Tile *t = new Tile;
  t->Initialize();

  t->ReadTile(tile);

  /*
  unsigned int edges;
  char data[1024];
  sscanf(tile, "%*d %d %s", &edges, data);

  std::string fmt;
  for (unsigned int i = 0; i < edges; i++)
  {
    fmt += "%f %f %f ";
  }
  for (unsigned int i = 0; i < edges; i++)
  {
    fmt += i == edges - 1 ? "%d" : "%d ";
  }

  std::cout << fmt << std::endl;
  */
}

void NewLevel::ReadTee(char*)
{

}

void NewLevel::ReadCup(char*)
{

}