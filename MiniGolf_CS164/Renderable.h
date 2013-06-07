#pragma once

// STL | GLM stuff
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>

// My stuff
#include "Mesh.h"
#include "Shader.h"

//
// No functionality for texturing is provided. It is unnecessary.
//
/// Defines an object that can be rendered
class Renderable
{
private:
  // (U, V) coordinates for each vertex in the Mesh
  // std::vector<glm::vec2> *_textureData;
  std::vector<glm::vec4> *_colorData;
  
  Mesh *_mesh;

  /*
   * Populates _colorData. Not necessary for a mesh, and not necessary if there is a texture
   * associated with the renderable.
   */
  unsigned char GenerateColors();

  template <typename T>
  void BindBuffer(
    GLenum target, // GL_ARRAY_BUFFER
    GLuint buffer, // shader->vertexBuffer
    std::vector<T> const & data, // the actual data you want to use
    int size,
    GLenum usage, // GL_DYNAMIC_DRAW
    GLint attarr // shader->vertex **TYPE MISMATCH IN GLEW! data is returned as a GLint but this function wants a GLuint!
  );

public:
  Renderable() :
      _colorData(0),
      // _textureData(0),
      _mesh(0)
  {}

  ~Renderable()
  {}

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();

  /// Loads the data from a WaveFront *.obj file, creating a mesh to render in addition to setting the correct OpenGL draw mode
  unsigned char LoadFromFile(std::string filename);

  /// Generates colors for the mesh based on the last static call to Color
  unsigned char PostLoad();

  /// Assigns the mesh associated with this Renderable
  void SetMesh(Mesh *m);

  /// Sets the color of the NEXT renderable to call GenerateColors(), i.e. PostLoad()
  static unsigned char Color(glm::vec4 const & color);

  /// Sets the global shader to use when drawing Renderables
  static void UseShader(Shader* shader);

  /// Copies data from the CPU and pushes it to the GPU
  void Render();

  /// Returns the Mesh object that the renderable draws
  Mesh *GetMesh();

  /// Returns the color of the renderable
  glm::vec4 const * Color() const;
};

