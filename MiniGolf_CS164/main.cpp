#include "Kengine.h"
#include "Mesh.h"

int main(int argc, char** argv)
{
	// Initialize engine
	Kengine *k = new Kengine;

	if (!k->Init(argc, argv)) return 2;

	k->Run();

	return 0;
}