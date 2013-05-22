#pragma once

/// STL includes
#include <string>
#include <vector>

/// GLMath includes
#include <glm\glm.hpp>

struct Triangle {
  glm::vec3 vertexData[3];
  glm::vec3 normalData[3];
};

class Mesh
{
private:
  std::vector<Triangle*> *_triangles;

public:
  Mesh() :
      _triangles(0)
  {}

  ~Mesh()
  {}

  /*
   * Allocates memory
   */
  unsigned char Initialize();

  /*
   * Frees memory
   */
  unsigned char DeInitialize();

  /*
   * Loads a mesh from a WaveFront *.obj file
   */
  unsigned char LoadFromFile(std::string filename);
};

