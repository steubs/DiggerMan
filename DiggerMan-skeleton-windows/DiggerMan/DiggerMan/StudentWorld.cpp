#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (i <= 33 && i >= 30 && j <= 59 && j >= 4)//(Sharon)this is the mine shaft around the middle (josh) changed size of mineshaft to fit with spec p16
			{
				continue;
			}
			//(Sharon)create and put dirt objects in a container.
			dirt.push_back(new Dirt(IMID_DIRT, i, j));
		}
	}
	actors_.push_back(new DiggerMan(IMID_PLAYER, 30, 60));


	return GWSTATUS_CONTINUE_GAME;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
