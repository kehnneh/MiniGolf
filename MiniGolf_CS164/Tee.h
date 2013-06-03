#pragma once

class MatrixObject;
class Renderable;
class Camera;
class Shader;

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

  unsigned char Initialize();

  unsigned char DeInitialize();
  
  void SetRenderable(Renderable *renderable);

  void SetMatrix(MatrixObject *m);

  MatrixObject *GetMatrix();

  float GetRadius();

  void SetRadius(float radius);

  void SetGoal(bool goal);

  void SetTile(unsigned int id);
  
  unsigned int GetTile();

  void Render(Camera *camera, Shader *shader);

  void Tick(double dt);
};

