#pragma once

#include <gl\glew.h>

// STL includes
#include <string>
#include <vector>

// GLMath includes
#include <glm\glm.hpp>

/// Contains data about a particular triangle in the mesh
struct Triangle {
  glm::vec3 *vertexData[3];
  glm::vec3 *normalData[3];
};

/// Defines a Mesh that contains drawing data or collision data, depending on the usage
class Mesh
{
private:
  std::vector<glm::vec3> *_vertexData;
  std::vector<glm::vec3> *_normalData;
  std::vector<unsigned int> *_indexData;
  std::vector<Triangle*> *_triangleData;

  GLenum _drawMode;

  /// Generates Triangle struct data
  unsigned char GenerateTriangles();

  /// Generates normals for each vertex of the Mesh
  unsigned char GenerateNormals();

  /// Initializes the index data for the Mesh
  unsigned char GenerateIndices();

public:
  Mesh() :
      _vertexData(0),
      _normalData(0),
      _indexData(0),
      _triangleData(0),
      _drawMode(0)
  {}

  ~Mesh()
  {}

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Loads a mesh from a WaveFront *.obj file. Populates _vertexData
  unsigned char LoadFromFile(std::string filename);

  /// Loads a mesh from the given set of vertices. Populates _vertexData
  unsigned char LoadFromData(std::vector<glm::vec3> *vertices);

  /// Sets the normal data associated with this Mesh
  void SetNormalData(std::vector<glm::vec3> *normalData);

  /// Triangulates vertices, calculates normals and colors
  unsigned char PostLoad();

  /// Returns the Mesh's vertex data
  std::vector<glm::vec3> const & VertexData() const;

  /// Returns the Mesh's normal data
  std::vector<glm::vec3> const & NormalData() const;

  /// Returns the Mesh's polygonal index data
  std::vector<unsigned int> const & IndexData() const;

  /// Creates and returns a new Vertical-Quad mesh from the given two base points
  static Mesh* VerticalQuad(glm::vec3 const & vb1, glm::vec3 const & vb2);

  /// Sets the OpenGL drawing mode for this Mesh
  void DrawMode(GLenum drawMode);

  /// Returns the OpenGL drawing mode for this Mesh
  GLenum DrawMode();
};

