#include "StudentWorld.h"
#include <cstdlib>
#include "Actor.h"
#include <algorithm>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	addDirt();
    
	m_diggerman = new DiggerMan(this, IMID_PLAYER, 30, 60);

	addBoulders();
	
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setDisplayText();

	removeDead(actors);

    m_diggerman->doSomething();

	
	for (unsigned int i = 0; i < actors.size();i++)
	{
		actors[i]->doSomething();
		
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

void StudentWorld::addBoulders(){
	
	int current_level = getLevel();
	int i = min((current_level/2) + 2, 7); // number of boulders to be added as listed by specs
	int CHECKX = -1;
	int CHECKY = -1;
	double SR = 6.0;

	for (int n = 0; n < i; )
	{
		int x = rand() % 60;
		int y = rand() % 56;
		if (x != CHECKX && y != CHECKY)
		{
			if (CHECKX != -1 && CHECKY != 1) {
				double S = pow(abs(CHECKX - x), 2) + pow(abs(CHECKY - y), 2);
				SR = pow(S, 0.5);
			}
			if (SR >= 6.0 && y > 20) // y must be greater than 20, listed in specs
			{
				if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4)) 
				{
					actors.push_back(new Boulder(this, IMID_BOULDER, x, y));
					for (int j = 0; j < 4; j++)
					{
						dirtarr[x + j][y]->setVisible(false);
						dirtarr[x + j][y + 1]->setVisible(false);
						dirtarr[x + j][y + 2]->setVisible(false);
						dirtarr[x + j][y + 3]->setVisible(false);
						dirtarr[x + j][y]->setAlive(false);
						dirtarr[x + j][y + 1]->setAlive(false);
						dirtarr[x + j][y + 2]->setAlive(false);
						dirtarr[x + j][y + 3]->setAlive(false);
					}
					CHECKX = x;
					CHECKY = y;
					n++;
				}
				else
					continue;
			}
		}
	}
	
}

void StudentWorld::addDirt(){

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

}

bool StudentWorld::checkUnder(Boulder* b){
		
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

void StudentWorld::removeDead(vector<Actor*>& actor){

	for (auto it = actor.begin(); it != actor.end() ; ){

		if (!(*it)->getAlive())
			it = actor.erase(it);
		else
			++it;

	}

}

bool StudentWorld::isThere(){

	int x = m_diggerman->getX();
	int y = m_diggerman->getY();

	for (unsigned int i = 0; i < actors.size(); i++){
		if (typeid(*(actors[i])) == typeid(Boulder)){
			if (m_diggerman->getDirection() == GraphObject::Direction::left){
				if ((x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY()) ||
					(x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY() + 1) ||
					(x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY() + 2) ||
					(x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY() + 3) ||
					(x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY() - 1) ||
					(x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY() - 2) ||
					(x - 1 == actors[i]->getX() + 3 &&
					y == actors[i]->getY() - 3))
					return true;

				else
					continue;
			}
			else if (m_diggerman->getDirection() == GraphObject::Direction::right){
				if ((x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY()) ||
					(x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY() + 1) ||
					(x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY() + 2) ||
					(x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY() + 3) ||
					(x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY() - 1) ||
					(x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY() - 2) ||
					(x + 4 == actors[i]->getX()  &&
					y == actors[i]->getY() - 3))
					return true;

				else
					continue;

			}
			else if (m_diggerman->getDirection() == GraphObject::Direction::down){
				if ((x - 3 == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x - 2 == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x - 1 == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x  == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x + 1 == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x + 2 == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x + 3 == actors[i]->getX() &&
					y == actors[i]->getY() + 4))
					return true;

				else
					continue;
		
			}
			else if(m_diggerman->getDirection() == GraphObject::Direction::up){
				if ((x - 3 == actors[i]->getX() &&
					y + 4 == actors[i]->getY()) ||
					(x - 2 == actors[i]->getX() &&
					y + 4 == actors[i]->getY()) ||
					(x - 1 == actors[i]->getX() &&
					y + 4 == actors[i]->getY()) ||
					(x == actors[i]->getX() &&
					y + 4 == actors[i]->getY()) ||
					(x + 1 == actors[i]->getX() &&
					y + 4 == actors[i]->getY()) ||
					(x + 2 == actors[i]->getX() &&
					y + 4 == actors[i]->getY()) ||
					(x + 3 == actors[i]->getX() &&
					y + 4 == actors[i]->getY()))
					return true;

				else
					continue;

			}
		}

		else
			continue;
	}

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

void StudentWorld::setDisplayText(){

	int level = getLevel();
	int lives = getLives();
	int health = m_diggerman->getHealth();
	//int squirts = getSquirtsLeftInSquirtGun();
	//int gold = getPlayerGoldCount();
	//int sonar = getPlayerSonarChargeCount();
	//int barrelsLeft = getNumberOfBarrelsRemainingToBePickedUp();
	int score = getScore();

	string s = "Lvl: " + to_string(level) + " " + "Lives: " + to_string(lives) + " " + "Hlth: " + to_string(health) + "%";
	setGameStatText(s);

}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
