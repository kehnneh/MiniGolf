#include <fstream>
#include <iostream>

#include <glm\gtx\normal.hpp>

#include "Mesh.h"
#include "CommonUtils.h"

glm::vec4 color(0.f, 0.f, 0.f, 0.f);

unsigned char Mesh::Initialize()
{
  _vertexData = new std::vector<glm::vec3>;
  _normalData = new std::vector<glm::vec3>;
  _indexData = new std::vector<unsigned int>;
  //_colorData = new std::vector<glm::vec4>;
  _triangleData = new std::vector<Triangle*>;

  return STATUS_OK;
}

unsigned char Mesh::DeInitialize()
{
  DeleteVectorPtrs(&_triangleData);
  //Delete(&_colorData);
  Delete(&_indexData);
  Delete(&_normalData);
  Delete(&_vertexData);

  return STATUS_OK;
}

unsigned char Mesh::LoadFromFile(std::string filename)
{
  std::ifstream fileIn;
  char c;

  // Properly open the file for reading
  fileIn.open(filename.c_str());
  if (fileIn.fail())
  {
    return 0x2;
  }

  // Read the data from the file via a large switch
  

  while (!fileIn.eof())
  {
    fileIn.get(c);

    if (c == 'v')
    {
      glm::vec3 vertex;
      fileIn >> vertex.x >> vertex.y >> vertex.z;
      _vertexData->push_back(vertex);
    }
    else if (c == 'f')
    {
      unsigned int i;
      for (unsigned int j = 0; j < 3; j++)
      {
        fileIn >> i;
        _indexData->push_back(--i);
      }
    }

    while (c != '\n' && !fileIn.eof())
    {
      fileIn.get(c);
    }
  }

  fileIn.close();

  return STATUS_OK;
}

unsigned char Mesh::LoadFromData(std::vector<glm::vec3> *vertices)
{
  _vertexData = vertices;

  return STATUS_OK;
}

unsigned char Mesh::PostLoad()
{
  if (GenerateNormals() != STATUS_OK)
  {
    return 0x2;
  }
  /*
  if (GenerateColors() != STATUS_OK)
  {
    return 0x4;
  }
  */
  if (GenerateTriangles() != STATUS_OK)
  {
    return 0x4;
  }

  return STATUS_OK;
}

unsigned char Mesh::GenerateTriangles()
{
  unsigned int indices = _indexData->size();
  if (indices == 0)
  {
    // No data provided! This Mesh was probably created from LoadFromData,
    // which expects data to be organized properly for the following algorithm
    // to work properly.

    // Connect the 1st vertex to the 2nd and 3rd.
    // Connect the 1st vertex to the 4th and 5th. etc...
    indices = 3 * (_vertexData->size() - 2);
    unsigned int index = 1;
    for (unsigned int v = 0; v < indices; v += 3)
    {
      _indexData->push_back(0);
      _indexData->push_back(index++);
      _indexData->push_back(index);
    }
  }

  for (unsigned int v = 0; v < indices; v += 3)
  {
    Triangle* tri = new Triangle;
    memset(tri, 0, sizeof(Triangle));

    for (unsigned int i = 0; i < 3; i++)
    {
      tri->vertexData[i] = &_vertexData->at(_indexData->at(v + i));
      tri->normalData[i] = &_normalData->at(_indexData->at(v + i));
      //tri->colorData[i] = &_colorData->at(_indexData->at(v + i));
    }

    _triangleData->push_back(tri);
  }

  return STATUS_OK;
}

unsigned char Mesh::GenerateNormals()
{
  // Populate _normalData first, such that we can increment afterwards
  unsigned int vertices = _vertexData->size();

  for (unsigned int i = 0; i < vertices; i++)
  {
    _normalData->push_back(glm::vec3(0.f, 0.f, 0.f));
  }

  unsigned int indices = _indexData->size();

  for (unsigned int i = 0; i < indices; i += 3)
  {
    glm::vec3 normal = glm::triangleNormal(
      _vertexData->at(_indexData->at(i)),
      _vertexData->at(_indexData->at(i + 1)),
      _vertexData->at(_indexData->at(i + 2))
    );

    _normalData->at(_indexData->at(i)) += normal;
    _normalData->at(_indexData->at(i + 1)) += normal;
    _normalData->at(_indexData->at(i + 2)) += normal;
  }

  for (std::vector<glm::vec3>::iterator it = _normalData->begin(); it != _normalData->end(); ++it)
  {
    (*it) = glm::normalize(*it);
  }

  return STATUS_OK;
}

/*
unsigned char Mesh::GenerateColors()
{
  unsigned int vertices = _vertexData->size();
  for (unsigned int i = 0; i < vertices; i++)
  {
    _colorData->push_back(color);
  }

  return STATUS_OK;
}
*/

Mesh* Mesh::VerticalQuad(glm::vec3 const & vb1, glm::vec3 const & vb2)
{
  Mesh *m = new Mesh;

  std::vector<glm::vec3> *vertices = new std::vector<glm::vec3>;

  glm::vec3* quad = new glm::vec3[4];

  quad[0] = vb1;
  quad[0].y += .25f;

  quad[1] = vb2;
  quad[1].y += .25f;

  quad[2] = vb2;

  quad[3] = vb1;

  for (unsigned int i = 0; i < 4; i++)
  {
    vertices->push_back(quad[i]);
  }

  if (m->LoadFromData(vertices) != STATUS_OK)
  {
    return nullptr;
  }

  return m;
}

/*
void Mesh::PrepareColor(glm::vec4 const & col)
{
  color = col;
}
*/