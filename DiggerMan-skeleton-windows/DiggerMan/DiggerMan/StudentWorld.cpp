#include "StudentWorld.h"
#include <string>
#include <cstdlib>
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
			dirtarr[i][j] = new Dirt(this, IMID_DIRT, i, j);
			if (i <= 33 && i >= 30 && j <= 60 && j >= 8)//(Sharon)this is the mine shaft around the middle (josh) changed size of mineshaft to fit with spec p16
			{
				dirtarr[i][j]->setVisible(false);
				dirtarr[i][j]->setAlive(false);
			}
			//(Sharon)create and put dirt objects in a container.
        }
    }
    m_diggerman = new DiggerMan(this, IMID_PLAYER, 30, 60);
	for (int i = 0; i < 3/*(however many boulders per level)*/; i++) {
		int x=33;//make these in the mine shaft just to get into the while loop
		int y=60;
		while (x <= 33 && x >= 30 && y <= 60 && y >= 8)//if the values are in the original mine shaft, generate more numbers
		{
			x = rand() % 60;
			y = rand() % 60;
			//should probably check if theres already a boulder here
		}
		actors.push_back(new Boulder(this, IMID_BOULDER, x, y));//randomly placed boulders
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_diggerman->doSomething();
	for (int i = 0; i < actors.size();i++)
	{
		actors[i]->doSomething();
		//i think in theory if all the different actors have different dosomethings this should work but idk
	}
    return GWSTATUS_CONTINUE_GAME;
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
