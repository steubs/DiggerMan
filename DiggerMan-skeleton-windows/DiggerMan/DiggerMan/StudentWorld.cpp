#include "StudentWorld.h"
#include <cstdlib>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	addDirt();
    
	m_diggerman = new DiggerMan(this, IMID_PLAYER, 30, 60);
	//m_protestorTest = new HardcoreProtestor(this, IMID_HARD_CORE_PROTESTER, 55, 60);//just for testing protestor functions, will be deleted later
	//m_protestorTest2 = new RegularProtestor(this, IMID_PROTESTER, 50, 60);//just for testing protestor functions, will be deleted later
	addBoulders();
	addGoldNuggets();
	addBarrel();
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

	removeDead();
	
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
	int c = 0;
	while (c < i) {
		int x = rand() % 60;
		int y = rand() % 56;
		if (actors.empty()) {
			if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4) && y > 20)
			{
				actors.push_back(new Boulder(this, IMID_BOULDER, x, y));
				c++;
				for (int j = 0; j < 4; j++) {
					dirtarr[x + j][y]->setVisible(false);
					dirtarr[x + j][y + 1]->setVisible(false);
					dirtarr[x + j][y + 2]->setVisible(false);
					dirtarr[x + j][y + 3]->setVisible(false);
					dirtarr[x + j][y]->setAlive(false);
					dirtarr[x + j][y + 1]->setAlive(false);
					dirtarr[x + j][y + 2]->setAlive(false);
					dirtarr[x + j][y + 3]->setAlive(false);
				}
			}
		}
		else
		{
			if (checkDistance(x, y) && y > 20) {
				if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4) && y > 20)
				{
					actors.push_back(new Boulder(this, IMID_BOULDER, x, y));
					c++;
					for (int j = 0; j < 4; j++) {
						dirtarr[x + j][y]->setVisible(false);
						dirtarr[x + j][y + 1]->setVisible(false);
						dirtarr[x + j][y + 2]->setVisible(false);
						dirtarr[x + j][y + 3]->setVisible(false);
						dirtarr[x + j][y]->setAlive(false);
						dirtarr[x + j][y + 1]->setAlive(false);
						dirtarr[x + j][y + 2]->setAlive(false);
						dirtarr[x + j][y + 3]->setAlive(false);
					}
				}
			}
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
		for (unsigned int j = 0; j < actors.size();j++) {//checking all the other actors before creating
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

void StudentWorld::isClose(int key) {
	int x;
	int y;
	if (key == 1) {
		for (unsigned int i = 0; i < actors.size(); i++) {
			if (typeid(*actors[i]) == typeid(Oil) /* || typeid(*actors[i]) == typeid(Gold)*/) {
				x = actors[i]->getX();
				y = actors[i]->getY();
				int digX = m_diggerman->getX();
				int digY = m_diggerman->getY();
				if (x = digX) {//the parameter for when the diggerman is next to this is too big for me to write cause im tired
					//no matter the direction, if the diggerman is next to it
					actors[i]->setVisible(true);
					//return true;
				}
			}
		}
	}
	else if (key == 2) {
		for (unsigned int i = 0; i < actors.size(); i++) {
			if (typeid(*actors[i]) == typeid(GoldNugget)) {
				x = actors[i]->getX();
				y = actors[i]->getY();
				int digX = m_diggerman->getX();
				int digY = m_diggerman->getY();
				double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
				if (SR <= 4.0) {
					actors[i]->setVisible(true);
				}
				else if (SR > 4.0) {
					actors[i]->setVisible(false);
				}
			}
		}
	}
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
	int gold = getGold();
	//int sonar = getPlayerSonarChargeCount();
	int barrelsLeft = getBarrels();
	int score = getScore();

    string s = "Lvl: " + to_string(level) + " " + "Lives: " + to_string(lives) + " " + "Hlth: " + to_string(health) + "%" + " Gld: " + to_string(gold) + " Oil Left: " + to_string(barrelsLeft) + " Scr: " + to_string(score);
	setGameStatText(s);

}

void StudentWorld::removeDead(){
	for (auto it = actors.begin(); it != actors.end() ; ){
		if (!(*it)->getAlive())
			it = actors.erase(it);
		else
			++it;
	}
}




void StudentWorld::addGoldNuggets() {
	int current_level = getLevel();
	int G = max(5 - current_level / 2, 2);
	int c = 0;
	while (c < G)
	{
		int x = rand() % 60;
		int y = rand() % 56;
		if (actors.empty())
		{
			if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4))// y only has to be > 20 for boulders
			{
				actors.push_back(new GoldNugget(this, IMID_GOLD, x, y));
                m_gold++;
				c++;
			}
		}
		else
		{
			if (checkDistance(x, y)) { // y only has to be > 20 for boulders
				if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4))// y only has to be > 20 for boulders
				{
					actors.push_back(new GoldNugget(this, IMID_GOLD, x, y));
                    m_gold++;
					c++;
				}
			}
		}
	}
}
void StudentWorld::addBarrel() {
	int current_level = getLevel();
	int i = min(current_level + 2, 18);
	int c = 0;
	while (c < i) {
		int x = rand() % 60;
		int y = rand() % 56;
		if (actors.empty()) {
			if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4))// y only has to be > 20 for boulders
			{
				actors.push_back(new Oil(this, IMID_BARREL, x, y));
				m_barrels++;
				c++;
			}
		}
		else
		{
			if (checkDistance(x, y)) { // y only has to be > 20 for boulders
				if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4))// y only has to be > 20 for boulders
				{
					actors.push_back(new Oil(this, IMID_BARREL, x, y));
					m_barrels++;
					c++;
				}
			}
		}
	}
}
bool StudentWorld::checkDistance(int x, int y) {
	bool flag = false;
	for (auto it = actors.begin(); it != actors.end(); it++)
	{
		double S = pow(abs((*it)->getX() - x), 2) + pow(abs((*it)->getY() - y), 2);
		double SR = pow(S, 0.5);
		if (SR >= 6.0)
			flag = true;
		else 
		{
			flag = false;
			break;
		}
	}
	return flag;
}
void StudentWorld::pickGold_diggerman() {
	int x;
	int y;
	for (unsigned int i = 0; i < actors.size(); i++) {
		if (typeid(*actors[i]) == typeid(GoldNugget)) {
			x = actors[i]->getX();
			y = actors[i]->getY();
			int digX = m_diggerman->getX();
			int digY = m_diggerman->getY();
			double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
			if (SR <= 3.0) {
				actors[i]->setVisible(false);
				actors[i]->setAlive(false);
				increaseScore(10);
				playSound(SOUND_GOT_GOODIE);
			}
		}
	}
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
