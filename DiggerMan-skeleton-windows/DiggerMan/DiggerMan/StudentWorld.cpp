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
		int x=34;//make these in the mine shaft just to get into the while loop
		int y=56;
		while (x <= 34 && x >= 26 && y <= 56 && y >= 4)//if the values are in the original mine shaft, generate more numbers
		{
			x = rand() % 60;
			y = rand() % 56;
			//should probably check if theres already a boulder here
			if (!dirtarr[x][y]->getAlive()) {//this doesnt quite work yet
				x = 34;
				y = 56;
			}
		}
		actors.push_back(new Boulder(this, IMID_BOULDER, x, y));//randomly placed boulders
		for (int j = 0;j < 4;j++)//i believe the dirt around the boulder should be gone 
		{
			dirtarr[x+j][y]->setVisible(false);
			dirtarr[x + j][y + 1]->setVisible(false);
			dirtarr[x + j][y + 2]->setVisible(false);
			dirtarr[x + j][y + 3]->setVisible(false);

			dirtarr[x + j][y]->setAlive(false);
			dirtarr[x + j][y + 1]->setAlive(false);
			dirtarr[x + j][y + 2]->setAlive(false);
			dirtarr[x + j][y + 3]->setAlive(false);
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_diggerman->doSomething();
	for (unsigned int i = 0; i < actors.size();i++)
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

bool StudentWorld::checkUnder(Boulder* b){

	//for (int i = 0; i < actors.size(); i++){
		
	if (typeid(*b) == typeid(Boulder)){
		int x = b->getX();
		int y = b->getY();
		if (!dirtarr[x][y - 1]->getAlive() && !dirtarr[x + 1][y - 1]->getAlive() && 
			!dirtarr[x + 2][y - 1]->getAlive() && !dirtarr[x + 3][y - 1]->getAlive())
			return true;
		else
			return false;
	}
	else
		return false;
}



void StudentWorld::removeDirt(){
	int x = m_diggerman->getX();
	int y = m_diggerman->getY();

	if (m_diggerman->getDirection() == GraphObject::Direction::left) {
		
		if (y == 59) {

			dirtarr[x][y]->setVisible(false);

			dirtarr[x][y]->setAlive(false);

		}
		else if (y == 58) {

			dirtarr[x][y]->setVisible(false);
			dirtarr[x][y + 1]->setVisible(false);

			dirtarr[x][y]->setAlive(false);
			dirtarr[x][y + 1]->setAlive(false);

		}
		else if (y == 57) {

			dirtarr[x][y]->setVisible(false);
			dirtarr[x][y + 1]->setVisible(false);
			dirtarr[x][y + 2]->setVisible(false);

			dirtarr[x][y]->setAlive(false);
			dirtarr[x][y + 1]->setAlive(false);
			dirtarr[x][y + 2]->setAlive(false);

		}
		else if (y < 57) {

			dirtarr[x][y]->setVisible(false);
			dirtarr[x][y + 1]->setVisible(false);
			dirtarr[x][y + 2]->setVisible(false);
			dirtarr[x][y + 3]->setVisible(false);

			dirtarr[x][y]->setAlive(false);
			dirtarr[x][y + 1]->setAlive(false);
			dirtarr[x][y + 2]->setAlive(false);
			dirtarr[x][y + 3]->setAlive(false);
		}
		
	}
	else if (m_diggerman->getDirection() == GraphObject::Direction::right)
	{
	
		if (y == 59) {

			dirtarr[x + 3][y]->setVisible(false);

			dirtarr[x + 3][y]->setAlive(false);

		}
		else if (y == 58) {

			dirtarr[x + 3][y]->setVisible(false);
			dirtarr[x + 3][y + 1]->setVisible(false);

			dirtarr[x + 3][y]->setAlive(false);
			dirtarr[x + 3][y + 1]->setAlive(false);

		}
		else if (y == 57) {

			dirtarr[x + 3][y]->setVisible(false);
			dirtarr[x + 3][y + 1]->setVisible(false);
			dirtarr[x + 3][y + 2]->setVisible(false);

			dirtarr[x + 3][y]->setAlive(false);
			dirtarr[x + 3][y + 1]->setAlive(false);
			dirtarr[x + 3][y + 2]->setAlive(false);

		}
		else if (y < 57) {

			dirtarr[x + 3][y]->setVisible(false);
			dirtarr[x + 3][y + 1]->setVisible(false);
			dirtarr[x + 3][y + 2]->setVisible(false);
			dirtarr[x + 3][y + 3]->setVisible(false);

			dirtarr[x + 3][y]->setAlive(false);
			dirtarr[x + 3][y + 1]->setAlive(false);
			dirtarr[x + 3][y + 2]->setAlive(false);
			dirtarr[x + 3][y + 3]->setAlive(false);
		}
	}
	else if (m_diggerman->getDirection() == GraphObject::Direction::up) {

		if (y < 57)
		{
			dirtarr[x][y + 3]->setVisible(false);
			dirtarr[x + 1][y + 3]->setVisible(false);
			dirtarr[x + 2][y + 3]->setVisible(false);
			dirtarr[x + 3][y + 3]->setVisible(false);

			dirtarr[x][y + 3]->setAlive(false);
			dirtarr[x + 1][y + 3]->setAlive(false);
			dirtarr[x + 2][y + 3]->setAlive(false);
			dirtarr[x + 3][y + 3]->setAlive(false);
		}
	}

	else if (m_diggerman->getDirection() == GraphObject::Direction::down) {

		dirtarr[x][y]->setVisible(false);
		dirtarr[x + 1][y]->setVisible(false);
		dirtarr[x + 2][y]->setVisible(false);
		dirtarr[x + 3][y]->setVisible(false);

		dirtarr[x][y]->setAlive(false);
		dirtarr[x + 1][y]->setAlive(false);
		dirtarr[x + 2][y]->setAlive(false);
		dirtarr[x + 3][y]->setAlive(false);

	}

	else
		return;

}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
