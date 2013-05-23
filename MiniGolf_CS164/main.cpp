#include "Kengine.h"
#include "Mesh.h"

int main(int argc, char** argv)
{
	// Initialize engine
	Kengine *k = new Kengine;

	//if (!k->Init(argc, argv)) return 2;

	//k->Run();

  Mesh *m = new Mesh;
  if (m->Initialize() != 0x1)
  {
    return 1;
  }

  if (m->LoadFromFile("Models/golfball.obj") != 0x1)
  {
    return 2;
  }

  if (m->PostLoad() != 0x1)
  {
    return 3;
  }

	return 0;
}