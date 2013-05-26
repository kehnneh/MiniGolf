#include "Level.h"
#include "Renderable.h"
#include "MatrixObject.h"

#include <fstream>

using namespace std;

/// Utilities
#include "CommonUtils.h"

unsigned char Level::Initialize()
{
  _tiles = new vector<Tile*>;
  _ambient = new glm::vec4;
  _lightSourceDirection = new glm::vec3;

  return STATUS_OK;
}

unsigned char Level::DeInitialize()
{
  Delete(&_tiles);
  Delete(&_ambient);
  Delete(&_lightSourceDirection);

  return STATUS_OK;
}

// IMPORTANT: Tiles in the level filed are specified in sequential order!
// accumulate neighbor lists of unsigned ints, then search the accumulated Tiles to extract their pointers
unsigned char Level::LoadFromFile(string filename)
{
  ifstream fin(filename.c_str());
	char c;
	unsigned short id, edges;
  vector<vector<unsigned int> *> neighborIntList;

  glm::vec3 teePos, cupPos;

	if(fin.fail()) {
		// Log failure to open file
		return 0x2;
	}

	fin.get(c);

	while(!fin.eof())
	{
		// If we read in 't'...
		if(c == 't')
		{
			fin.get(c);

			if (c == 'i') // Is the word 'tile'?
			{
				fin.get(c); fin.get(c); // chomp the 'le'

				fin >> id;
        Mesh* m = new Mesh;
        m->Initialize();

				fin >> edges;
        vector<glm::vec3> *vertices = new vector<glm::vec3>;

				// Read the vertices of the Mesh: Tile's are NOT loaded through the *.obj format
				for(int i = 0; i < edges; i++)
				{
          glm::vec3 vertex;
					fin >> vertex.x >> vertex.y >> vertex.z;
          vertices->push_back(vertex);
				}

        m->LoadFromData(vertices);
        m->DrawMode(GL_TRIANGLES);
        m->PostLoad();

        Renderable::Color(glm::vec4(0.f, 1.f, 0.f, 1.f));
        Renderable *renderable = new Renderable;
        renderable->Initialize();
        renderable->SetMesh(m);
        renderable->PostLoad();

        Tile* tile = new Tile;
        tile->Initialize();
        tile->SetRenderable(renderable);

        _tiles->push_back(tile);

        // Acquire a list of unsigned ints of the neighbors from the file. To be sorted through later
        vector<unsigned int> *neighbors = new vector<unsigned int>;
				for (int i = 0; i < edges; i++)
				{
					fin >> id;
					neighbors->push_back(id);
				}
        
        neighborIntList.push_back(neighbors);
			}
			else if (c == 'e') // Is the word 'tee'?
			{
				fin.get(c); // chomp the 'e'
				fin >> _tee >> teePos.x >> teePos.y >> teePos.z;

        Mesh *m = new Mesh;
        m->Initialize();

        vector<glm::vec3> *vertices = new vector<glm::vec3>;

        vertices->push_back(teePos + glm::vec3(.1f, .01f, .1f));
        vertices->push_back(teePos + glm::vec3(-.1f, .01f, .1f));
        vertices->push_back(teePos + glm::vec3(-.1f, .01f, -.1f));
        vertices->push_back(teePos + glm::vec3(.1f, .01f, -.1f));

        m->LoadFromData(vertices);
        m->DrawMode(GL_TRIANGLES);
        m->PostLoad();

        Renderable *renderable = new Renderable;
        renderable->Initialize();
        renderable->SetMesh(m);
        Renderable::Color(glm::vec4(1.f, 1.f, 1.f, 1.f));
        renderable->PostLoad();

        // Make Tee object!
			} 
		} // End 't' 
		else if (c == 'c') // If we read in 'cup'...
		{ 
      // Create a cup object
			fin.get(c); fin.get(c); // Chomp the 'up'
			fin >> _cup >> cupPos.x >> cupPos.y >> cupPos.z;

      Mesh *m = new Mesh;
      m->Initialize();

      vector<glm::vec3> *vertices = new vector<glm::vec3>;

			//Renderable* r = new Renderable;
			//glm::vec3* vertData = new glm::vec3[4];
      vertices->push_back(cupPos + glm::vec3(.1f, .01f, .1f));
      vertices->push_back(cupPos + glm::vec3(-.1f, .01f, .1f));
      vertices->push_back(cupPos + glm::vec3(-.1f, .01f, -.1f));
      vertices->push_back(cupPos + glm::vec3(.1f, .01f, -.1f));

      m->LoadFromData(vertices);
      m->DrawMode(GL_TRIANGLES);
      m->PostLoad();

      Renderable *renderable = new Renderable;
      renderable->Initialize();
      renderable->SetMesh(m);
      Renderable::Color(glm::vec4(0.f, 0.f, 0.f, 1.f));
      renderable->PostLoad();
      // Make cup object!

      /*
			Renderable* r = new Renderable;
			glm::vec3* vertData = new glm::vec3[4];

			vertData[3].x = cupPos.x + 0.1f;
			vertData[3].y = cupPos.y + 0.01f;
			vertData[3].z = cupPos.z + 0.1f;

			vertData[2].x = cupPos.x - 0.1f;
			vertData[2].y = cupPos.y + 0.01f;
			vertData[2].z = cupPos.z + 0.1f;

			vertData[1].x = cupPos.x - 0.1f;
			vertData[1].y = cupPos.y + 0.01f;
			vertData[1].z = cupPos.z - 0.1f;

			vertData[0].x = cupPos.x + 0.1f;
			vertData[0].y = cupPos.y + 0.01f;
			vertData[0].z = cupPos.z - 0.1f;

			if (!r->Init(vertData, 4))
			{
				// log error
				return 0x10;
			}

			r->GenerateColor(glm::vec4(.0f, .0f, .0f, 1.f));
			others.push_back(r);
      */
		} // End 'cup'
		fin.get(c);
	}

	fin.close();

  unsigned int numTiles = neighborIntList.size();
  for (unsigned int i = 0; i < numTiles; i++)
  {
    unsigned int numNeighbors = neighborIntList.at(i)->size();
    vector<Tile*> *neighbors = new vector<Tile*>;
    for (unsigned int j = 0; j < numNeighbors; j++)
    {
      unsigned int tileid = neighborIntList.at(i)->at(j);
      neighbors->push_back(tileid == 0 ? 0 : _tiles->at(tileid - 1));
    }
    _tiles->at(i)->SetNeighbors(neighbors);
    _tiles->at(i)->PostLoad();
  }

  Renderable *ballobj = new Renderable;
  Renderable::Color(glm::vec4(1.f, 1.f, 1.f, 1.f));
  ballobj->Initialize();
  ballobj->LoadFromFile("Models/golfball.obj");
  ballobj->PostLoad();

  _ball = new Ball;
  _ball->Initialize();
  _ball->CurrentTile(_tiles->at(_tee));
  _ball->SetRenderable(ballobj);

  MatrixObject* ballMat = _ball->Matrix();
  ballMat->Position(teePos + glm::vec3(0.f, .05f, 0.f));
  ballMat->Scale(0.05);

  MatrixObject* arrowMat = _ball->DirectionMatrix();
  arrowMat->Scale(0.25f);
  //arrowMat->Position(*ballMat->Position());

	return STATUS_OK;
}

unsigned char Level::PostLoad()
{
  // Make the golfball and put it in the tile with the tee!

  _lightSourceDirection = &glm::vec3(-1.f, 1.f, -1.f);
  _ambient = &glm::vec4(.2f, .2f, .2f, 1.f);

  return STATUS_OK; // double check the values of the above vecNs
}

unsigned char Level::Tick(double t)
{
  _ball->Tick(t);

  return STATUS_OK;
}

unsigned char Level::Render(Camera *camera, Shader *shader)
{
  glUniform4fv(shader->ambient, 1, (GLfloat*) _ambient);
	glUniform3fv(shader->sun, 1, (GLfloat*) _lightSourceDirection);
  glUniformMatrix4fv(shader->mat_modelTransform, 1, GL_FALSE, (GLfloat *) &glm::mat4());

  vector<Tile*>::iterator it = _tiles->begin(), end = _tiles->end();
  
  for (; it != end; ++it)
  {
    (*it)->Render(camera, shader);
  }

  // Render the ball, tee, and hole
  _ball->Render(camera, shader);

  return STATUS_OK;
}

Ball *Level::GetBall()
{
  return _ball;
}