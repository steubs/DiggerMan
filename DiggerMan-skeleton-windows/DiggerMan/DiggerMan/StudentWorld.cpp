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
	addBoulders();
	addGoldNuggets();
	addBarrel();
	addProtestors();
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setDisplayText();
	addProtestors();
    m_diggerman->doSomething();
	for (unsigned int i = 0; i < actors.size(); i++)
	{
		actors[i]->doSomething();
		if (m_barrels == 0)
			return GWSTATUS_FINISHED_LEVEL;
		
	}
		if (!m_diggerman->getAlive()) {
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	int current_level = getLevel();
	int j = current_level * 25 + 300;
	if (1 == rand()% j) {//one in getLevel() * 25 + 300 chance to add these
		int add = rand() % 5;
		if (1 == add && sonarInMap == 0)//one in 5 chance
		{
			addSonarKit();
			sonarInMap++;//create one sonar kit at a time
		}
		else if (add > 1 && waterInMap==0) {// four in 5 chance
			addWater();
			waterInMap++;
		}
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
	m_barrels = 0; // fixes count when you die
	m_sonar = 1; // fixes count when you die
	tickCount = 0;
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

void StudentWorld::addProtestors()
{
	if (tickCount == 0) {
		actors.push_back(new RegularProtestor(this, IMID_PROTESTER, 60, 60));//all protestors added to 60,60
		m_protestors++;
	}//add first protestor at beginning of each level
	
	tickCount++;

	int current_level = getLevel();
	int ticksUntilAdd = max(25, 200 - current_level);//at least this many ticks before another protestor added
	int numProtestors = min(15, 2+(int)(current_level*1.5));
	if(tickCount==ticksUntilAdd && m_protestors<numProtestors){
		int G = current_level * 25 + 300;
		if (1==rand()%G)
			actors.push_back(new HardcoreProtestor(this, IMID_PROTESTER, 60, 60));
		//one in current_level * 25 + 300 chance it's a hardcore protestor(don't know if this works)
		actors.push_back(new RegularProtestor(this, IMID_PROTESTER, 60, 60));
		m_protestors++;
		tickCount = 1;
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
				c++;
			}
		}
		else
		{
			if (checkDistance(x, y)) { // y only has to be > 20 for boulders
				if (!(x <= 34 && x >= 26 && y <= 56 && y >= 4))// y only has to be > 20 for boulders
				{
					actors.push_back(new GoldNugget(this, IMID_GOLD, x, y));
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

void StudentWorld::addSonarKit() {
	actors.push_back(new Sonar(this, IMID_SONAR, 0, 60));//sonar kits are always added to 0,60
}

void StudentWorld::addWater() {
	int x = rand() % 60;
	int y = rand() % 56;
	while (dirtarr[x][y]->getAlive() || dirtarr[x][y + 1]->getAlive()
		|| dirtarr[x][y + 2]->getAlive() || dirtarr[x][y + 3]->getAlive()
		|| dirtarr[x + 1][y]->getAlive() || dirtarr[x + 1][y + 1]->getAlive()
		|| dirtarr[x + 1][y + 2]->getAlive() || dirtarr[x + 1][y + 3]->getAlive()
		|| dirtarr[x + 2][y]->getAlive() || dirtarr[x + 2][y + 1]->getAlive()
		|| dirtarr[x + 2][y + 2]->getAlive() || dirtarr[x + 2][y + 3]->getAlive()
		|| dirtarr[x + 3][y]->getAlive() || dirtarr[x + 3][y + 1]->getAlive()
		|| dirtarr[x + 3][y + 2]->getAlive() || dirtarr[x + 3][y + 3]->getAlive()) {
		x = rand() % 60;
		y = rand() % 56;
	}
		actors.push_back(new Water(this, IMID_WATER_POOL, x, y));
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

bool StudentWorld::checkDistance(int x, int y) {
	bool flag = false;
	for (auto it = actors.begin(); it != actors.end(); it++)
	{
		double S = pow(abs((*it)->getX() - x), 2) 
			+ pow(abs((*it)->getY() - y), 2);
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
	}
	return false;
}

bool StudentWorld::isBoulderThere() {
	for (unsigned int j = 0; j < actors.size(); j++)
	{
		if (typeid(*(actors[j])) == typeid(RegularProtestor) || typeid(*(actors[j])) == typeid(HardcoreProtestor))
		{	
			int x = actors[j]->getX();
			int y = actors[j]->getY();
			for (unsigned int i = 0; i < actors.size(); i++) {
				if (typeid(*(actors[i])) == typeid(Boulder))
				{
					if (actors[j]->getDirection() == GraphObject::Direction::left) {
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
					else if (actors[j]->getDirection() == GraphObject::Direction::right) {
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
							return true;
						else
							continue;
					}
					else if (actors[j]->getDirection() == GraphObject::Direction::down) {
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
							return true;
						else
							continue;
					}
					else if (actors[j]->getDirection() == GraphObject::Direction::up) {
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
			}
			return false;
		}
	}
}

void StudentWorld::addDirt() {
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			dirtarr[i][j] = new Dirt(this, IMID_DIRT, i, j);
			if (i <= 33 && i >= 30 && j <= 60 && j >= 8)
			{
				dirtarr[i][j]->setVisible(false);
				dirtarr[i][j]->setAlive(false);
			}
		}
	}
}

bool StudentWorld::removeDirt() {
	int x = m_diggerman->getX();
	int y = m_diggerman->getY();
	if (m_diggerman->getDirection() == GraphObject::Direction::left) {
		if (y == 59) {
			if (dirtarr[x][y]->getAlive()) {
				dirtarr[x][y]->setVisible(false);
				dirtarr[x][y]->setAlive(false);
				return true;
			}
		}
		else if (y == 58) {
			if (dirtarr[x][y]->getAlive()
				|| dirtarr[x][y + 1]->getAlive()) {
				dirtarr[x][y]->setVisible(false);
				dirtarr[x][y + 1]->setVisible(false);
				dirtarr[x][y]->setAlive(false);
				dirtarr[x][y + 1]->setAlive(false);
				return true;
			}
		}
		else if (y == 57) {
			if (dirtarr[x][y]->getAlive()
				|| dirtarr[x][y + 1]->getAlive()
				|| dirtarr[x][y + 2]->getAlive()) {
				dirtarr[x][y]->setVisible(false);
				dirtarr[x][y + 1]->setVisible(false);
				dirtarr[x][y + 2]->setVisible(false);
				dirtarr[x][y]->setAlive(false);
				dirtarr[x][y + 1]->setAlive(false);
				dirtarr[x][y + 2]->setAlive(false);
				return true;
			}
		}
		else if (y < 57) {
			if (dirtarr[x][y]->getAlive()
				|| dirtarr[x][y + 1]->getAlive()
				|| dirtarr[x][y + 2]->getAlive()
				|| dirtarr[x][y + 3]->getAlive()) {
				dirtarr[x][y]->setVisible(false);
				dirtarr[x][y + 1]->setVisible(false);
				dirtarr[x][y + 2]->setVisible(false);
				dirtarr[x][y + 3]->setVisible(false);
				dirtarr[x][y]->setAlive(false);
				dirtarr[x][y + 1]->setAlive(false);
				dirtarr[x][y + 2]->setAlive(false);
				dirtarr[x][y + 3]->setAlive(false);
				return true;
			}
		}
	}
	else if (m_diggerman->getDirection() == GraphObject::Direction::right)
	{
		if (y == 59) {
			if (dirtarr[x + 3][y]->getAlive()) {
				dirtarr[x + 3][y]->setVisible(false);
				dirtarr[x + 3][y]->setAlive(false);
				return true;
			}
		}
		else if (y == 58) {
			if (dirtarr[x + 3][y]->getAlive()
				|| dirtarr[x + 3][y + 1]->getAlive()) {
				dirtarr[x + 3][y]->setVisible(false);
				dirtarr[x + 3][y + 1]->setVisible(false);
				dirtarr[x + 3][y]->setAlive(false);
				dirtarr[x + 3][y + 1]->setAlive(false);
				return true;
			}
		}
		else if (y == 57) {
			if (dirtarr[x + 3][y]->getAlive()
				|| dirtarr[x + 3][y + 1]->getAlive()
				|| dirtarr[x + 3][y + 2]->getAlive()) {
				dirtarr[x + 3][y]->setVisible(false);
				dirtarr[x + 3][y + 1]->setVisible(false);
				dirtarr[x + 3][y + 2]->setVisible(false);
				dirtarr[x + 3][y]->setAlive(false);
				dirtarr[x + 3][y + 1]->setAlive(false);
				dirtarr[x + 3][y + 2]->setAlive(false);
				return true;
			}
		}
		else if (y < 57) {
			if (dirtarr[x + 3][y]->getAlive()
				|| dirtarr[x + 3][y + 1]->getAlive()
				|| dirtarr[x + 3][y + 2]->getAlive()
				|| dirtarr[x + 3][y + 3]->getAlive()) {
				dirtarr[x + 3][y]->setVisible(false);
				dirtarr[x + 3][y + 1]->setVisible(false);
				dirtarr[x + 3][y + 2]->setVisible(false);
				dirtarr[x + 3][y + 3]->setVisible(false);
				dirtarr[x + 3][y]->setAlive(false);
				dirtarr[x + 3][y + 1]->setAlive(false);
				dirtarr[x + 3][y + 2]->setAlive(false);
				dirtarr[x + 3][y + 3]->setAlive(false);
				return true;
			}
		}
	}
	else if (m_diggerman->getDirection() == GraphObject::Direction::up) {
		if (y < 57)
		{
			if (dirtarr[x][y + 3]->getAlive()
				|| dirtarr[x + 1][y + 3]->getAlive()
				|| dirtarr[x + 2][y + 3]->getAlive()
				|| dirtarr[x + 3][y + 3]->getAlive()) {
				dirtarr[x][y + 3]->setVisible(false);
				dirtarr[x + 1][y + 3]->setVisible(false);
				dirtarr[x + 2][y + 3]->setVisible(false);
				dirtarr[x + 3][y + 3]->setVisible(false);
				dirtarr[x][y + 3]->setAlive(false);
				dirtarr[x + 1][y + 3]->setAlive(false);
				dirtarr[x + 2][y + 3]->setAlive(false);
				dirtarr[x + 3][y + 3]->setAlive(false);
				return true;
			}
		}
	}
	else if (m_diggerman->getDirection() == GraphObject::Direction::down) {
		if (dirtarr[x][y]->getAlive()
			|| dirtarr[x + 1][y]->getAlive()
			|| dirtarr[x + 2][y]->getAlive()
			|| dirtarr[x + 3][y]->getAlive()) {
			dirtarr[x][y]->setVisible(false);
			dirtarr[x + 1][y]->setVisible(false);
			dirtarr[x + 2][y]->setVisible(false);
			dirtarr[x + 3][y]->setVisible(false);
			dirtarr[x][y]->setAlive(false);
			dirtarr[x + 1][y]->setAlive(false);
			dirtarr[x + 2][y]->setAlive(false);
			dirtarr[x + 3][y]->setAlive(false);
			return true;
		}
	}
	return false;
}

void StudentWorld::setDisplayText(){

	int level = getLevel();
	int lives = getLives();
	int health = m_diggerman->getHealth();
	int score = getScore();

    string s = "Lvl: " + to_string(level) + " Lives: " + to_string(lives) + " Hlth: " 
		+ to_string(health) + "%" + " Water: " + to_string(m_water) + " Gld: " + to_string(m_gold) 
		+ " Sonar: " + to_string(m_sonar) + " Oil Left: " + to_string(m_barrels) + " Scr: " + to_string(score);
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


void StudentWorld::setallVisible(){

    for(unsigned int i = 0; i < actors.size(); i++){
        int x = actors[i]->getX();
        int y = actors[i]->getY();
        int digX = getDiggerman()->getX();
        int digY = getDiggerman()->getY();
        double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);

		if (actors[i]->getAlive()) {
			if (SR <= 12)
				actors[i]->setVisible(true);
        }
    }
    return;
}
void StudentWorld::dropGold() {
	if (m_gold > 0) {
		int x = m_diggerman->getX();
		int y = m_diggerman->getY();
		GoldNugget *newG = new GoldNugget(this, IMID_GOLD, x, y);
		newG->setVisible(true);
		actors.push_back(newG);
		m_gold--;
	}
}
bool StudentWorld::pickUPPRO(int x, int y){
	//cout << "1" << endl;
	for (auto it = actors.begin(); it != actors.end(); it++){
		//cout << "2" << endl;
		if (typeid(**it) == typeid(RegularProtestor)){
			//cout << "13" << endl;
			int PX = (*it)->getX();
			int PY = (*it)->getY();
			double SR = pow((pow(abs(x - PX), 2) + pow(y - PY, 2)), 0.5);
			if (SR <= 3.0){
				//cout << "14" << endl;
				(*it)->setAlive(false);
				(*it)->setVisible(false);//these two lines are just there to test code
				return true;
			}
		}
	}
	return false;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
