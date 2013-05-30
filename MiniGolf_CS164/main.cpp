#include "Kengine.h"
#include "LevelManager.h"

int main(int argc, char** argv)
{
	// Initialize engine
  /*
	Kengine *k = new Kengine;

	if (!k->Init(argc, argv)) return 2;

	k->Run();
  */
  
  LevelManager *levelMgr = new LevelManager;
  levelMgr->Initialize(); // can't fail yet
  if (levelMgr->LoadLevels() != 0x1)
  {
    return 1;
  }
  

	return 0;
}