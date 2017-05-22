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

	Oil*oil = new Oil(this, IMID_BARREL, 0, 0);//create to use in function call
	//Gold*gold = new Gold(this, IMID_GOLD,0,0);
	addActors(oil);
	//addActors(gold);
	
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setDisplayText();

    m_diggerman->doSomething();

	for (unsigned int i = 0; i < actors.size();i++)
	{
		actors[i]->doSomething();
		if (getBarrels() == 0)
			return GWSTATUS_FINISHED_LEVEL;
		
	}

	removeDead(actors);
	
    return GWSTATUS_CONTINUE_GAME;

}

void StudentWorld::cleanUp()

{
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			delete dirtarr[i][j];
		}
	}

	
	delete getDiggerman();

	for (auto it = actors.begin(); it != actors.end(); ++it){
		delete *it;
	}
	actors.clear();
}

void StudentWorld::addBoulders() {
	int current_level = getLevel();
	int i = min((current_level / 2) + 2, 7); // number of boulders to be added as listed by specs
	double SR = 0;
	int x = rand() % 60;
	int y = rand() % 56;
	int CHECKX;
	int CHECKY;
	bool isThere = false;
	if (actors.empty()) {//(Sharon) since we have to check all the actors we have to initialize the first one if empty
		while (true)
		{
			if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4) && y > 20) {
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
				break;
			}
			x = rand() % 60;
			y = rand() % 56;
		}
		i--;
	}
	for (int n = 0; n < i; )//(Sharon) I really hope this works the same as before!
	{
		for (unsigned int j = 0; j < actors.size();j++) {//checking all the other actors before creating
			CHECKX = actors[j]->getX();
			CHECKY = actors[j]->getY();
			if (x != CHECKX && y != CHECKY)
			{
				if (CHECKX != -1 && CHECKY != 1) {//i don't really understand this line but i left it
					double S = pow(abs(CHECKX - x), 2) + pow(abs(CHECKY - y), 2);
					SR = pow(S, 0.5);
				}
				if (SR >= 6)
					isThere = false;//if the object is 6 spaces away then isThere is false
				else {
					isThere = true;//if even one of the current objects is not 6 spaces away, break this loop
					//and try again with different x and y values
					break;
				}
			}
			else //if checkx and checky are the current object's x and y
				isThere = true;
		}
		if (isThere == false && y > 20) // y must be greater than 20, listed in specs
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
				n++;
			}
		}
		x = rand() % 60;
		y = rand() % 56;
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

void StudentWorld::addActors(Actor *actor) {

	
	if (actor->getX() == 0 && actor->getY() == 0){
		actor->setAlive(false);
		actor->setVisible(false);
	}
	int current_level = getLevel();
	int i; //number of items
	double SR = 0;
	int x = rand() % 60;
	int y = rand() % 56;
	int CHECKX;
	int CHECKY;
	bool isThere = false;
	if (typeid(*actor) == typeid(Oil)) {
		i = min(current_level + 2, 18);
	}
	//if (typeid(*actor) == typeid(Gold)) {  this is to make this function viable for gold once its created
	//	i = max(5 - current_level / 2, 2);
	//}
	for (int n = 0; n < i; )
	{
		for (unsigned int j = 1; j < actors.size();j++) {//checking all the other actors before creating
			CHECKX = actors[j]->getX();
			CHECKY = actors[j]->getY();
			if (x != CHECKX && y != CHECKY)
			{
				if (CHECKX != -1 && CHECKY != 1) {
					double S = pow(abs(CHECKX - x), 2) + pow(abs(CHECKY - y), 2);
					SR = pow(S, 0.5);
				}
				if (SR >= 6)
					isThere = false;
				else {
					isThere = true;
					break;
				}
			}
			else
				isThere = true;
		}
		if (isThere == false && y > 0)
		{
			if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4))
			{
				if (typeid(*actor) == typeid(Oil)) {
					actors.push_back(new Oil(this, IMID_BARREL,x, y));
					m_barrels++;
				}
				/*if (typeid(*actor) == typeid(Gold)) {  this is to make this function viable for gold when its created
				actors.push_back(new Gold(this, IMID_GOLD, x, y));
				}*/
				n++;
			}
		}
		x = rand() % 60;
		y = rand() % 56;
	}

}

bool StudentWorld::isClose() {
	int x;
	int y;
	for (unsigned int i = 0; i < actors.size();i++) {
		if (typeid(*actors[i]) == typeid(Oil) /* || typeid(*actors[i]) == typeid(Gold)*/) {
			x = actors[i]->getX();
			y = actors[i]->getY();
			int digX = m_diggerman->getX();
			int digY = m_diggerman->getY();
			if (x=digX) {//the parameter for when the diggerman is next to this is too big for me to write cause im tired
				//no matter the direction, if the diggerman is next to it
				actors[i]->setVisible(true);
				return true;
			}
		}
	}
	return false;
}

void StudentWorld::isTouching() {
	int x;
	int y;
	for (unsigned int i = 0; i < actors.size();i++) {
		if (typeid(*actors[i]) == typeid(Oil) /* || typeid(*actors[i]) == typeid(Gold)*/) {
			x = actors[i]->getX();
			y = actors[i]->getY();
			int digX = m_diggerman->getX();
			int digY = m_diggerman->getY();
			if (x = digX) {//no matter the direction, if diggerman is 3 spaces away
				actors[i]->setVisible(false);
				actors[i]->setAlive(false);
				playSound(SOUND_FOUND_OIL);
				//increase player's points by 1000
				//if barrels left == 0 then level ends and go to the next lvl
			}
		}
	}
}

bool StudentWorld::isThere(){

	int x = m_diggerman->getX();
	int y = m_diggerman->getY();

	for (unsigned int i = 0; i < actors.size(); i++){
		if (typeid(*(actors[i])) == typeid(Boulder))
		{
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
		if (typeid(*(actors[i])) == typeid(Oil)) //|| gold
		{
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
					return false;
				if ((x + 4 == actors[i]->getX() &&
					y == actors[i]->getY()) ||
					(x + 4 == actors[i]->getX() &&
						y == actors[i]->getY() + 1) ||
						(x + 4 == actors[i]->getX() &&
							y == actors[i]->getY() + 2) ||
							(x + 4 == actors[i]->getX() &&
								y == actors[i]->getY() + 3) ||
								(x + 4 == actors[i]->getX() &&
									y == actors[i]->getY() - 1) ||
									(x + 4 == actors[i]->getX() &&
										y == actors[i]->getY() - 2) ||
										(x + 4 == actors[i]->getX() &&
											y == actors[i]->getY() - 3))
					return false;
				if ((x - 3 == actors[i]->getX() &&
					y == actors[i]->getY() + 4) ||
					(x - 2 == actors[i]->getX() &&
						y == actors[i]->getY() + 4) ||
						(x - 1 == actors[i]->getX() &&
							y == actors[i]->getY() + 4) ||
							(x == actors[i]->getX() &&
								y == actors[i]->getY() + 4) ||
								(x + 1 == actors[i]->getX() &&
									y == actors[i]->getY() + 4) ||
									(x + 2 == actors[i]->getX() &&
										y == actors[i]->getY() + 4) ||
										(x + 3 == actors[i]->getX() &&
											y == actors[i]->getY() + 4))
					return false;
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
					return false;
		}
	}
	return false;
}

void StudentWorld::addDirt() {
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

	string s = "Lvl: " + to_string(level) + " " + "Lives: " + to_string(lives) + " " + "Hlth: " + to_string(health) + "%" + " Scr: " + to_string(score);
	setGameStatText(s);

}

void StudentWorld::removeDead(vector<Actor*>& actor){

	for (auto it = actor.begin(); it != actor.end() ; ){

		if (!(*it)->getAlive())
			it = actor.erase(it);

		else
			++it;
	}

}

Actor* StudentWorld::getDiggerman(){

	return m_diggerman;

}

int StudentWorld::getBarrels(){
	
	return m_barrels;

}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
