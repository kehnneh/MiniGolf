#include "Level.h"
#include "Renderable.h"
#include "Camera.h"
#include "Shader.h"

void Level::DeInit()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i])
		{
			delete tiles[i];
		}
	}
}

void Level::Render(Camera* camera, Shader* shader)
{	
	for (std::vector<Renderable*>::iterator it = others.begin(); it != others.end(); ++it)
	{
		(*it)->Tick();
	}

  _ball->Tick(0.0);
  _ball->Render(camera);

  glUniform4fv(shader->ambient, 1, (GLfloat*) &ambientLight);
	glUniform3fv(shader->sun, 1, (GLfloat*) &lightDir);

	for (std::vector<Renderable*>::iterator it = tiles.begin(); it != tiles.end(); ++it)
	{
		(*it)->Render(camera);
		((Tile*)(*it))->RenderBorders(camera);
	}

	for (std::vector<Renderable*>::iterator it = others.begin(); it != others.end(); ++it)
	{
		(*it)->Render(camera);
	}
}

bool Level::Init(std::string filename)
{
	std::ifstream fin(filename.c_str());
	char c;
	unsigned short id, edges;

	if(fin.fail()) {
		// Log failure to open file
		return false;
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
				Tile* r = new Tile(id);

				fin >> edges;
				glm::vec3* vertData = new glm::vec3[edges];

				// Read vertices from the file and push to the Tile's vertex array
				for(int i = 0; i < edges; i++)
				{
					fin >> vertData[i].x
						>> vertData[i].y
						>> vertData[i].z;
				}

				r->Init(vertData, edges);
				r->TileInit();

				// Here, we're using id for the neighbor's id
				for (int i = 0; i < edges; i++)
				{
					fin >> id;
					if (!r->SetNeighbor(i, id))
					{
						// Log error
						return false;
					}
				}

				r->Finalize();

				tiles.push_back(r);
			}
			else if (c == 'e') // Is the word 'tee'?
			{
				fin.get(c); // chomp the 'e'
				fin >> teeId >> teePos.x >> teePos.y >> teePos.z;

				Renderable* r = new Renderable;
				glm::vec3* vertData = new glm::vec3[4];

				vertData[3].x = teePos.x + 0.1f;
				vertData[3].y = teePos.y + 0.01f;
				vertData[3].z = teePos.z + 0.1f;

				vertData[2].x = teePos.x - 0.1f;
				vertData[2].y = teePos.y + 0.01f;
				vertData[2].z = teePos.z + 0.1f;

				vertData[1].x = teePos.x - 0.1f;
				vertData[1].y = teePos.y + 0.01f;
				vertData[1].z = teePos.z - 0.1f;

				vertData[0].x = teePos.x + 0.1f;
				vertData[0].y = teePos.y + 0.01f;
				vertData[0].z = teePos.z - 0.1f;

				if (!r->Init(vertData, 4))
				{
					// log error
					return false;
				}

				r->GenerateColor(glm::vec4(.0f, .0f, .0f, 1.f));
				others.push_back(r);
			} 
		} // End 't' 
		else if (c == 'c') // If we read in 'cup'...
		{ 
			fin.get(c); fin.get(c); // Chomp the 'up'
			fin >> cupId >> cupPos.x >> cupPos.y >> cupPos.z;

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
				return false;
			}

			r->GenerateColor(glm::vec4(.0f, .0f, .0f, 1.f));
			others.push_back(r);
		} // End 'cup'
		fin.get(c);
	}

	fin.close();

	// Load the golf ball!
  _ball = new Golfball;
  
  if (!_ball->Init())
  {
    return false;
  }
  _ball->Position(teePos + glm::vec3(0.f, 0.05f, 0.f));
  _ball->Scale(0.05f);
  _ball->SetTile((Tile *)tiles[teeId]);

	return true;
}

