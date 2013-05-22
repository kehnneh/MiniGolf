#include "Kengine.h"
#include "Mesh.h"

int main(int argc, char** argv)
{
	// Initialize engine
	Kengine *k = new Kengine;

	//if (!k->Init(argc, argv)) return 2;

	//k->Run();

  Mesh *m = new Mesh;
  m->Initialize();
  m->LoadFromFile("Models/golfball.obj");

	return 0;
}