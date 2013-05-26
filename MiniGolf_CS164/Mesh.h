#pragma once

/// STL includes
#include <string>
#include <vector>

/// GLMath includes
#include <glm\glm.hpp>

struct Triangle {
  glm::vec3 *vertexData[3];
  glm::vec3 *normalData[3];
  //glm::vec4 *colorData[3];
};

class Mesh
{
private:
  std::vector<glm::vec3> *_vertexData;
  std::vector<glm::vec3> *_normalData;
  std::vector<unsigned int> *_indexData;
  //std::vector<glm::vec4> *_colorData;
  std::vector<Triangle*> *_triangleData;

  /*
   * Populates _triangleData
   */
  unsigned char GenerateTriangles();

  /*
   * Populates _normalData
   */
  unsigned char GenerateNormals();

  /*
   * Populates _indexData
   */
  unsigned char GenerateIndices();
  /*
   * Populates _colorData
   */
  //unsigned char GenerateColors();

public:
  Mesh() :
      _vertexData(0),
      _normalData(0),
      _indexData(0),
      //_colorData(0),
      _triangleData(0)
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
   * Loads a mesh from a WaveFront *.obj file. Populates _vertexData
   */
  unsigned char LoadFromFile(std::string filename);

  /*
   * Loads a mesh from the given set of vertices. Populates _vertexData
   */
  unsigned char LoadFromData(std::vector<glm::vec3> *vertices);

  /*
   * Triangulates vertices, calculates normals and colors
   */
  unsigned char PostLoad();

  /*
   * Returns the Mesh's vertex data
   */
  std::vector<glm::vec3> const & VertexData() const;

  /*
   * Returns the Mesh's normal data
   */
  std::vector<glm::vec3> const & NormalData() const;

  /*
   * Returns the Mesh's polygonal index data
   */
  std::vector<unsigned int> const & IndexData() const;

  /*
   * Creates and returns a new Vertical-Quad mesh from the given two base points
   */
  static Mesh* VerticalQuad(glm::vec3 const & vb1, glm::vec3 const & vb2);

  /*
   * This assigns the color which GenerateColors will assign to the Mesh
   */
  //static void PrepareColor(glm::vec4 const & col);
};

