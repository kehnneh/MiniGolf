#pragma once

/// STL | GLM stuff
#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>

/// My stuff
#include "Mesh.h"
#include "Shader.h"

//
// No functionality for texturing is provided. It is unnecessary.
//
class Renderable
{
private:
  // (U, V) coordinates for each vertex in the Mesh
  // std::vector<glm::vec2> *_textureData;
  std::vector<glm::vec4> *_colorData;
  
  Mesh *_mesh;

  GLenum _drawMode;

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
      _mesh(0),
      _drawMode(GL_TRIANGLES)
  {}

  ~Renderable()
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
   * Loads the data from a WaveFront *.obj file, creating a mesh to render
   * in addition to setting the correct OpenGL draw mode
   */
  unsigned char LoadFromFile(std::string filename);

  /*
   * Does nothing (yet)
   */
  unsigned char PostLoad();

  /*
   * Sets the Mesh of this renderable to the given Mesh
   */
  void SetMesh(Mesh *m);

  /*
   * Sets the color of the NEXT renderable to call GenerateColors(), i.e. PostLoad()
   */
  static unsigned char Color(glm::vec4 const & color);

  /*
   * Sets the draw mode of this renderable to the specified mode
   */
  unsigned char DrawMode(GLenum mode);

  static void UseShader(Shader* shader);

  /*
   * Copies data from the CPU and pushes it to the GPU
   */
  void Render();

  /*
   * Returns the Mesh object that the renderable draws
   */
  Mesh const * GetMesh() const;

  /*
   * Returns the color of the renderable
   */
  glm::vec4 const * Color() const;
};

