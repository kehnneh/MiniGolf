#pragma once

class MatrixObject;
class Renderable;
class Camera;
class Shader;

/// Defines an entity used for either the Tee or the Cup in a Level
class Tee
{
private:
  unsigned int _tileid;

  MatrixObject *_transform;

  float _radius;

  Renderable *_renderable;

  bool _goal;

public:
  Tee() :
    _transform(0),
    _renderable(0),
    _radius(0.f),
    _goal(false),
    _tileid(-1)
  {}

  ~Tee()
  {}

  /// Performs data allocation
  unsigned char Initialize();

  /// Performs data deallocation
  unsigned char DeInitialize();
  
  /// Sets the renderable of the Tee to the specified renderable
  void SetRenderable(Renderable *renderable);

  /// Sets the matrix of the Tee to the specified matrix
  void SetMatrix(MatrixObject *m);

  /// Returns the matrix of the Tee
  MatrixObject *GetMatrix();

  /// Returns the radius of the Tee
  float GetRadius();

  /// Sets the radius of the Tee
  void SetRadius(float radius);

  /// Sets whether this Tee is actually a Cup or not
  void SetGoal(bool goal);

  /// Associates the Tee object with the specified Tile ID
  void SetTile(unsigned int id);
  
  /// Returns the associated Tile ID
  unsigned int GetTile();

  /// Renders the Tee object
  void Render(Camera *camera, Shader *shader);

  /// Updates the Tee's data (matrix)
  void Tick(double dt);
};

