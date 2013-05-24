#include "NewLevel.h"

#include <fstream>

/// Utilities
#include "CommonUtils.h"

unsigned char NewLevel::Initialize()
{
  _tiles = new std::vector<NewRenderable*>;
  _ambient = new glm::vec4;
  _lightSourceDirection = new glm::vec3;

  return STATUS_OK;
}

unsigned char NewLevel::DeInitialize()
{
  Delete(&_tiles);

  return STATUS_OK;
}

unsigned char NewLevel::LoadFromFile(std::string filename)
{
  std::ifstream fin(filename.c_str());
	char c;
	unsigned short id, edges;

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
        std::vector<glm::vec3> *vertices = new std::vector<glm::vec3>;

				// Read the vertices of the Mesh: Tile's are NOT loaded through the *.obj format
				for(int i = 0; i < edges; i++)
				{
          glm::vec3 vertex;

					fin >> vertex.x >> vertex.y >> vertex.z;

          vertices->push_back(vertex);
				}

        m->LoadFromData(vertices);
        m->PostLoad();

        NewRenderable *renderable = new NewRenderable;
        renderable->Initialize();
        renderable->SetMesh(m);
        NewRenderable::Color(glm::vec4(0.f, 1.f, 0.f, 1.f));
        renderable->PostLoad();

        _tiles->push_back(renderable);

				//r->Init(vertData, edges);
				//r->TileInit();

        /* Bind 'renderable' to a Tile */

				// ACQUIRE NEIGHBORS THROUGH POINTERS RELATIVE TO THE TILE!
        // IN OTHER WORDS: MAKE THE TILE OBJECT BEFORE THIS, AND CREATE ADJACENCY LISTS
        // AFTER TILES ARE MADE
        /*
				for (int i = 0; i < edges; i++)
				{
					fin >> id;
					if (!r->SetNeighbor(i, id))
					{
						// Log error
						return 0x4;
					}
				}
        */
				//r->Finalize();

				//tiles.push_back(r);
			}
			else if (c == 'e') // Is the word 'tee'?
			{
				fin.get(c); // chomp the 'e'
        glm::vec3 teePos;
				fin >> _tee >> teePos.x >> teePos.y >> teePos.z;

        Mesh *m = new Mesh;
        m->Initialize();

        std::vector<glm::vec3> *vertices = new std::vector<glm::vec3>;

				//Renderable* r = new Renderable;
				//glm::vec3* vertData = new glm::vec3[4];
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

      std::vector<glm::vec3> *vertices = new std::vector<glm::vec3>;

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