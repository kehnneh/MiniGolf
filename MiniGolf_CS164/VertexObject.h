#pragma once

#include <glm\glm.hpp>

#define VEC_VERTEX 0x1
#define VEC_DIRECTION 0x2

#define _SIMD_OPS_VEC

#ifdef _SIMD_OPS_VEC
  #define GLM_SIMD_ENABLE_XYZW_UNION
  #include <glm\gtx\simd_vec4.hpp>

  #include "AlignedAllocationPolicy.h"

  typedef glm::simdVec4 Vec4;
#else
  #include <glm\core\type_vec4.hpp>

  typedef glm::vec4 Vec4;
#endif

/// Vector manipulation class. Supports both standard (slow) vector operations as well as SIMD (fast) vector operations.
#ifdef _SIMD_OPS_VEC
class VertexObject : public AlignedAllocationPolicy<16>
#else
class VertexObject
#endif
{
private:
  Vec4 *_vec;
  glm::vec3 *_vert;

  /**
   * Flags are mutually exclusive. Value is either VEC_VERTEX or VEC_DIRECTION, error otherwise
   */
  unsigned char _flags;

public:
  VertexObject() :
    _vert(0),
    _vec(0),
    _flags(VEC_VERTEX)
  {}
  ~VertexObject()
  {}

  void Init();
  void DeInit();

  float Length() const;

  void Normalize();

  // Rotate
  void Rotate(float pitch, float yaw, float roll);

  // Position Incrementers
  void Increment(float x, float y, float z);
  void IncX(float x);
  void IncY(float y);
  void IncZ(float z);

  // Position Setters
  void Set(float x, float y, float z);
  const glm::vec3 *Vertex() const;
};
