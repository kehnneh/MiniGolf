#include <fstream>
#include <iostream>

#include "Mesh.h"
#include "CommonUtils.h"

unsigned char Mesh::Initialize()
{
  _triangles = new std::vector<Triangle*>;

  return 0x1; /// OK
}

unsigned char Mesh::DeInitialize()
{
  DeleteVector(&_triangles);

  return 0x1; /// OK
}

unsigned char Mesh::LoadFromFile(std::string filename)
{
  std::ifstream fileIn;

  // Properly open the file for reading
  fileIn.open(filename.c_str());
  if (fileIn.fail())
  {
    return 0x2;
  }

  // Read the data from the file in a large switch

  return 0x1;
}