#pragma once

/// STL | GLM stuff
#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>

/// My stuff
#include "Mesh.h"

/// Utilities
#include "CommonUtils.h"

//
// No functionality for texturing is provided. It is unnecessary.
//
class NewRenderable
{
private:
  // (U, V) coordinates for each vertex in the Mesh
  // std::vector<glm::vec2> *_textureData;
  glm::vec4 *_colorData;
  
  Mesh *_mesh;

  GLenum _drawMode;

  void BindBuffer(
    GLenum target, // GL_ARRAY_BUFFER
    GLuint buffer, // shader->vertexBuffer
    std::vector<glm::vec3> const & data, // the actual data you want to use
    GLenum usage, // GL_DYNAMIC_DRAW
    GLint attarr, // shader->vertex **TYPE MISMATCH IN GLEW! data is returned as a GLint but this function wants a GLuint!
    bool const & vertAttrib
  );

public:
  NewRenderable() :
      _colorData(0),
      // _textureData(0),
      _mesh(0),
      _drawMode(GL_TRIANGLES)
  {}

  ~NewRenderable()
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
   * Sets the color of this renderable to the given color
   */
  unsigned char Color(glm::vec4 const & color);

  unsigned char DrawMode(GLenum mode);

  void Render();

  Mesh const * GetMesh() const;

  glm::vec4 const * GetColor() const;
};

