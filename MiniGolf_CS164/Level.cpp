#include "Level.h"
#include "Tile.h"
#include "CommonUtils.h"
#include "Tee.h"
#include "MatrixObject.h"
#include "Ball.h"

#include <iostream>
#include <sstream>

using namespace std;

unsigned char Level::Initialize()
{
  // Initialize Tee and Cup pointers

  return STATUS_OK;
}

unsigned char Level::DeInitialize()
{
  // Delete Tee and Cup pointers
  Delete(&_name);

  return STATUS_OK;
}

unsigned char Level::PostLoad()
{
  vector<vector<unsigned int> *> *neighborInts = new vector<vector<unsigned int> *>;

  for (unsigned int i = 0; i < _tiles.size(); ++i)
  {
    neighborInts->push_back(_tiles.at(i)->GetNeighborIds());
  }

  unsigned int numTiles = neighborInts->size();
  for (unsigned int i = 0; i < numTiles; i++)
  {
    unsigned int numNeighbors = neighborInts->at(i)->size();
    vector<Tile*> *neighbors = new vector<Tile*>;
    for (unsigned int j = 0; j < numNeighbors; j++)
    {
      unsigned int tileid = neighborInts->at(i)->at(j);
      neighbors->push_back(tileid == 0 ? 0 : _tiles.at(tileid - 1));
    }
    _tiles.at(i)->SetNeighbors(neighbors);
    _tiles.at(i)->PostLoad();
  }

  _ball = new Ball;
  _ball->Initialize();
  _ball->CurrentTile(_tiles.at(_tee->GetTile()));
  _ball->Matrix()->Position(*_tee->GetMatrix()->Position() + glm::vec3(0.f, .05f, 0.f));
  _ball->Matrix()->Scale(0.05);
  _ball->DirectionMatrix()->Scale(0.25f);

  return STATUS_OK;
}

void Level::ReadName(char* name)
{
  _name = new string(name);
}

void Level::ReadPar(char* par)
{
#pragma warning( suppress : 4996 )
  sscanf(par, "%d", &_par);
}

void Level::ReadTile(char* tile)
{
  Tile *t = new Tile;
  t->Initialize();

  t->ReadTile(tile);

  _tiles.push_back(t);
}

void Level::ReadTee(char* tee)
{
  std::stringstream ss(tee);
  
  glm::vec3 pos;
  unsigned int tileid;

  ss >> tileid >> pos.x >> pos.y >> pos.z;

  _tee = new Tee;
  _tee->Initialize();
  _tee->SetTile(tileid - 1);

  // Load Renderable for circle
  // Scale appropriately
  // Position according to the stringstream
  Renderable *r = new Renderable;
  r->Initialize();
  Renderable::Color(glm::vec4(0.f, 0.f, 1.f, 1.f));
  r->LoadFromFile("Models/circle.obj");
  r->PostLoad();
  _tee->SetRenderable(r);
  
  _tee->GetMatrix()->Position(pos + glm::vec3(0.f, .01f, 0.f));
  _tee->GetMatrix()->Scale(0.075f);
}

// Same as the Tee, except the Cup is marked as the goal
void Level::ReadCup(char* cup)
{
  std::stringstream ss(cup);

  glm::vec3 pos;
  unsigned int tileid;

  ss >> tileid >> pos.x >> pos.y >> pos.z;
  _cup = new Tee;
  _cup->Initialize();
  _cup->SetTile(tileid - 1);

  Renderable *r = new Renderable;
  r->Initialize();
  Renderable::Color(glm::vec4(1.f, 0.f, 1.f, 1.f));
  r->LoadFromFile("Models/circle.obj");
  r->PostLoad();
  _cup->SetRenderable(r);

  _cup->GetMatrix()->Position(pos + glm::vec3(0.f, .01f, 0.f));
  _cup->GetMatrix()->Scale(0.075f);
  _cup->SetGoal(true);
}

void Level::Render(Camera *c, Shader *s)
{
  glUniform4fv(s->ambient, 1, (GLfloat*) &_ambientColor);
  glUniform3fv(s->sun, 1, (GLfloat*) &_lightSourceDirection);
  glUniformMatrix4fv(s->mat_modelTransform, 1, GL_FALSE, (GLfloat*) &glm::mat4());

  std::vector<Tile*>::iterator it = _tiles.begin(), end = _tiles.end();

  for (; it != end; ++it)
  {
    (*it)->Render(c, s);
  }

  _ball->Render(c, s);
  _tee->Render(c, s);
  _cup->Render(c, s);
}

void Level::Tick(double t)
{
  _tee->Tick(t);
  _cup->Tick(t);
  _ball->Tick(t);
}

Ball *Level::GetBall()
{
  return _ball;
}