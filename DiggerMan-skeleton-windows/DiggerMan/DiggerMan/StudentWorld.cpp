#include "StudentWorld.h"
#include <string>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	for (int i = 0; i < 61; i++)
	{
		vector < Dirt*> temp;
		for (int j = 0; j < 60; j++)
		{
			if (i <= 33 && i >= 30 && j <= 59 && j >= 8)//(Sharon)this is the mine shaft around the middle (josh) changed size of mineshaft to fit with spec p16
			{
				continue;
			}
			//(Sharon)create and put dirt objects in a container.
			temp.push_back(new Dirt(this, IMID_DIRT, i, j));
		}
		dirt.push_back(temp);
	}
	//DiggerMan MUST be first object in actors_
	actors_.push_back(new DiggerMan(this, IMID_PLAYER, 30, 60));
	actors_.push_back(new Boulders(this, IMID_BOULDER, 15, 25));
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	actors_[0]->doSomething();
	actors_[1]->doSomething();
	int index = 0;
	for (std::vector<vector<Dirt*>>::iterator it = dirt.begin(); it != dirt.end(); ++it, index++) {
		int x = actors_[0]->getX();
		int y = actors_[0]->getY();
		dirt.at(x).at(y)->setVisible(false);
	}// this is not working, i am still working on it. This is just showing you guys what i am trying to do.
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
vector<vector<Dirt*>> StudentWorld::getDirt() {
	return dirt;
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
