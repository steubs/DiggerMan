#include "StudentWorld.h"
#include <string>
#include "Actor.h"
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
			if (i <= 33 && i >= 30 && j <= 59 && j >= 8)//(Sharon)this is the mine shaft around the middle (josh) changed size of mineshaft to fit with spec p16
			{
				continue;
			}
			//(Sharon)create and put dirt objects in a container.
			dirt.push_back(new Dirt(this, IMID_DIRT, i, j));
		}
	}
	//DiggerMan MUST be first object in actors_
	actors_.push_back(new DiggerMan(this, IMID_PLAYER, 30, 60));


	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	actors_[0]->doSomething();
	int index = 0;
	for (std::vector<Dirt*>::iterator it = dirt.begin(); it != dirt.end(); ++it,index++)
	{ 
		if (actors_[0]->getX() == dirt[index]->getX() &&
			actors_[0]->getY() == dirt[index]->getY())
			
			dirt[index]->setVisible(false);
	}
	return GWSTATUS_CONTINUE_GAME;//(Sharon) chose continue game to see the dirt 
	/*This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.*/
	/*decLives();*/
	//return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
	delete this;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
