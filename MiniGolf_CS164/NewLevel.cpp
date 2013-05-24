#include "NewLevel.h"
#include "NewRenderable.h"

#include <fstream>

using namespace std;

/// Utilities
#include "CommonUtils.h"

unsigned char NewLevel::Initialize()
{
  _tiles = new vector<NewTile*>;
  _ambient = new glm::vec4;
  _lightSourceDirection = new glm::vec3;

  return STATUS_OK;
}

unsigned char NewLevel::DeInitialize()
{
  Delete(&_tiles);
  Delete(&_ambient);
  Delete(&_lightSourceDirection);

  return STATUS_OK;
}

// IMPORTANT: Tiles in the level filed are specified in sequential order!
// accumulate neighbor lists of unsigned ints, then search the accumulated Tiles to extract their pointers
unsigned char NewLevel::LoadFromFile(string filename)
{
  ifstream fin(filename.c_str());
	char c;
	unsigned short id, edges;
  vector<vector<unsigned int> *> neighborIntList;

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
        m->PostLoad();

        NewRenderable::Color(glm::vec4(0.f, 1.f, 0.f, 1.f));
        NewRenderable *renderable = new NewRenderable;
        renderable->Initialize();
        renderable->SetMesh(m);
        renderable->PostLoad();

        NewTile* tile = new NewTile;
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
        glm::vec3 teePos;
				fin >> _tee >> teePos.x >> teePos.y >> teePos.z;

        Mesh *m = new Mesh;
        m->Initialize();

        vector<glm::vec3> *vertices = new vector<glm::vec3>;

        vertices->push_back(teePos + glm::vec3(.1f, .01f, .1f));
        vertices->push_back(teePos + glm::vec3(-.1f, .01f, .1f));
        vertices->push_back(teePos + glm::vec3(-.1f, .01f, -.1f));
        vertices->push_back(teePos + glm::vec3(.1f, .01f, -.1f));

        m->LoadFromData(vertices);
        m->PostLoad();

        NewRenderable *renderable = new NewRenderable;
        renderable->Initialize();
        renderable->SetMesh(m);
        NewRenderable::Color(glm::vec4(1.f, 1.f, 1.f, 1.f));
        renderable->PostLoad();

        // Make Tee object!
			} 
		} // End 't' 
		else if (c == 'c') // If we read in 'cup'...
		{ 
      // Create a cup object
      glm::vec3 cupPos;
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
      m->PostLoad();

      NewRenderable *renderable = new NewRenderable;
      renderable->Initialize();
      renderable->SetMesh(m);
      NewRenderable::Color(glm::vec4(0.f, 0.f, 0.f, 1.f));
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
    vector<NewTile*> *neighbors = new vector<NewTile*>;
    for (unsigned int j = 0; j < numNeighbors; j++)
    {
      unsigned int tileid = neighborIntList.at(i)->at(j);
      neighbors->push_back(_tiles->at(tileid == 0 ? 0 : tileid - 1));
    }
    _tiles->at(i)->SetNeighbors(neighbors);
    _tiles->at(i)->PostLoad();
  }

  /*
	// Load the golf ball!
  _ball = new Golfball;
  
  if (!_ball->Init())
  {
    return false;
  }
  _ball->Position(teePos + glm::vec3(0.f, 0.05f, 0.f));
  _ball->Scale(0.05f);
  _ball->SetTile((Tile *)tiles[teeId]);
  */

	return STATUS_OK;
}

unsigned char NewLevel::PostLoad()
{
  // Make the golfball and put it in the tile with the tee!

  _lightSourceDirection = &glm::vec3(-1.f, 1.f, -1.f);
  _ambient = &glm::vec4(.2f, .2f, .2f, 1.f);

  return STATUS_OK; // double check the values of the above vecNs
}

unsigned char NewLevel::Tick(double t)
{

  return STATUS_OK;
}