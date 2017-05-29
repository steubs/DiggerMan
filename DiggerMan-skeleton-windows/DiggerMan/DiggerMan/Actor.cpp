#include "StudentWorld.h"
#include "Actor.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>


//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Actor::Actor(StudentWorld *p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :GraphObject(imageID, startX, startY, dir, size, depth), isAlive(true), world(p),health(100)
{
	setVisible(true);
	setAlive(true);
}

bool Actor::getAlive(){
	return isAlive;
}
void Actor::setAlive(bool Is){
	isAlive = Is;
}
StudentWorld *Actor::getWorld(){
	return world;
}
Actor::~Actor()
{
	
}
void Actor::doSomething()
{

}
void Actor::setHealth(int health_)
{
	health = health_;
}


//////////////////////////////////////////////////////////////  DIRT    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Dirt::Dirt(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	
}

Dirt::~Dirt()
{
	
}
void Dirt::doSomething()
{
	//doesn't do anything as said in specs.
}

//////////////////////////////////////////////////////////////  DIGGERMAN  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


DiggerMan::DiggerMan(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	
}

DiggerMan::~DiggerMan()
{
}
void DiggerMan::doSomething()
{
	
	int x = getX();
	int y = getY();
	int ch;
	if (getAlive()) {
		if (getWorld()->getKey(ch) == true) {
			switch (ch) {
			case KEY_PRESS_LEFT:
				if (getDirection() != left) {
					setDirection(left);
					break;
				}
				else {
					setDirection(left);
					if (x < 1)
						break;
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG); have to play this when digging through dirt
						moveTo(x - 1, y);
					}
					getWorld()->removeDirt();
					break;
				}
			case KEY_PRESS_RIGHT:
				if (getDirection() != right) {
					setDirection(right);
					break;
				}
				else {
					setDirection(right);
					if (x > 59)
						break;
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG);
						moveTo(x + 1, y);
					}
					getWorld()->removeDirt();
					break;
				}
			case KEY_PRESS_UP:
				if (getDirection() != up) {
					setDirection(up);
					break;
				}
				else {
					setDirection(up);
					if (y > 59)
						break;
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG);
						moveTo(x, y + 1);
					}
					getWorld()->removeDirt();
					break;
				}
			case KEY_PRESS_DOWN:
				if (getDirection() != down) {
					setDirection(down);
					break;
				}
				else {
					setDirection(down);
					if (y < 1)
						break;
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG);
						moveTo(x, y - 1);
					}
					getWorld()->removeDirt();
					break;
				}
            case 'z':
                if(getWorld()->getSonar() > 0){
                    getWorld()->setallVisible();
                    getWorld()->decSonar();
                }
                    break;
            case 'Z':
                if(getWorld()->getSonar() > 0){
                    getWorld()->setallVisible();
                    getWorld()->decSonar();
                }
                    break;
			}
		}
	}
	else
		return;

}
//////////////////////////////////////////////////////////////  BOULDER  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Boulder::Boulder(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),count(0),fell(false) {
	
}
Boulder::~Boulder(){
	
}
void Boulder::doSomething() {
	if (getAlive())
	{
		int x = getX();
		int y = getY(); 
		if (y == 0) {

			setVisible(false);
			setAlive(false);

		}
		if (y < 60 && y>0)//check under the boulder only if it's inside the map
		{
			if (getWorld()->checkUnder(this)) {
				count++;
				if (count >= 30) {//30 ticks have to pass before the boulder falls
					if (fell==false)//if this is the first time the boulder has moved at all
						getWorld()->playSound(SOUND_FALLING_ROCK);//play the sound once
					moveTo(x, y - 1);
					int BX = getWorld()->getDiggerman()->getX();
					int BY = getWorld()->getDiggerman()->getY();
					double SR = pow((pow(abs(x - BX), 2) + pow(y - BY, 2)), 0.5);
					if (SR <= 3.0) {
						getWorld()->getDiggerman()->setVisible(false);
						getWorld()->getDiggerman()->setAlive(false);
					}
					//getWorld()->BoulderHitDig();
					fell = true;//this also helps get rid of the boulder
				}
			}
			else if (fell == true){ //if the boulder has fallen
				setVisible(false);
				setAlive(false);
			}
			else
				return;
		}
	}
	else 
		return;
}
////////////////////////////////////////////////////////////// GoldNugget  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GoldNugget::GoldNugget(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth), pickUpProtestor(false), pickUpDiggerman(false)
{
	setVisible(false);
}
void GoldNugget::doSomething()
{
	if (getAlive())
	{
			int x = getX();
			int y = getY();
			int digX = getWorld()->getDiggerman()->getX();
			int digY = getWorld()->getDiggerman()->getY();
			double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
			if (SR <= 4.0 && !pickUpDiggerman) {
				pickUpDiggerman = true;
				setVisible(true);
				return;
			}
			else if (SR > 4.0)
				setVisible(false);
			if (SR <= 3.0 && pickUpDiggerman && (!pickUpProtestor)) {
				setVisible(true);
				setVisible(false);
				setAlive(false);
				getWorld()->increaseScore(10);
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->incGold();
				pickUpDiggerman = false;
			}
	}
	else
		return;
}
GoldNugget::~GoldNugget()
{
}


//////////////////////////////////////////////////////////////  OIL  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Oil::Oil(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),pick(false) {
	setVisible(false);
}

void Oil::doSomething() {
	if (getAlive())
	{
		//getWorld()->isClose();
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		if (SR <= 4.0 && !pick) {
			pick = true;
			setVisible(true);
			return;
		}
		else if (SR > 4.0) {
			setVisible(false);
			pick = false;
		}
		if (SR <= 3.0 &&pick) {
			setVisible(true);
			setVisible(false);
			setAlive(false);
			getWorld()->decBarrels();
			getWorld()->playSound(SOUND_FOUND_OIL);
			getWorld()->increaseScore(1000);
		}
	}
	else 
		return;
}
Oil::~Oil() {
	
}
//////////////////////////////////////////////////////////////  SONAR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sonar::Sonar(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	
}
void Sonar::doSomething() {
	if (getAlive()) {
		count++;
        int x = getX();
        int y = getY();
        int digX = getWorld()->getDiggerman()->getX();
        int digY = getWorld()->getDiggerman()->getY();
        double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
        int current_level = getWorld()->getLevel();
		int a = max(100, 300 - 10 * current_level);
		//int max = std::max(10,0);
        if(SR <= 3)
            
		if (count == a) {
			setVisible(false);
			setAlive(false);
			getWorld()->decSonarInMap();
		}
	}
	else return;
}

Sonar::~Sonar() {

}

//////////////////////////////////////////////////////////////  SQUIRT  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Squirt::Squirt(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {

}

void Squirt::doSomething() {

}

Squirt::~Squirt() {
	
}

////////////////////////////////////////////////////////////// PROTESTOR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RegularProtestor::RegularProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	leaveOilFieldState = false;
	setHealth(5);
}

void RegularProtestor::setLeaveOilFieldState(bool state)
{
	leaveOilFieldState = state;
}

void RegularProtestor::setHealth(int health_)
{
	health = health_;
}

bool RegularProtestor::getLeaveOilFieldState()
{
	return leaveOilFieldState;
}
void RegularProtestor::setTickCounter(int tickCounter_)
{
	tickCounter = tickCounter_;
}
void RegularProtestor::doSomething()
{
	
	if (!getAlive()) return;//return if not alive
	
	if (tickCounter > 0)
	{
		tickCounter--;//decriment tick
		return;
	}
	
	//protestor is alive and able to move, therefore tick countrer should be set back to the level's correct value max(0,3-lvl)
	setTickCounter(max(0, 3));//placehold value
	if (!getLeaveOilFieldState())//protester is moving freely
	{
		wander();
		numSquaresToMoveInCurrentDirection--;
	}
	else returnHome();
		

}

void RegularProtestor::wander()
{
	int x = getX();
	int y = getY();

	if (numSquaresToMoveInCurrentDirection <= 0)//we need to switch directions
	{
		direction_integer = rand() % 4;
		switchDirection(direction_integer);
		numSquaresToMoveInCurrentDirection = rand() % 58 + 6;
		//setNumSquaresToMoveInCurrentDirection((rand() % 58) + 6);
		return;
	}
	switch (direction_integer) {
		case 0:
			if (x < 1)
			{
				numSquaresToMoveInCurrentDirection = 0;//has hit a wall, switch directions and reset numSquaresTo...
				break;
			}
			if (!getWorld()->isThere())
				moveTo(x - 1, y);
			break;	
		case 1:
			if (x > 59)
			{
				numSquaresToMoveInCurrentDirection = 0;
				break;
			}
			if (!getWorld()->isThere())
				moveTo(x + 1, y);
			break;
		case 2:
			if (y > 59)
			{
				numSquaresToMoveInCurrentDirection = 0;
				break;
			}
			if (!getWorld()->isThere())
				moveTo(x, y + 1);
			break;
			
		case 3:
			if (y < 1)
			{
				numSquaresToMoveInCurrentDirection = 0;
				break;
			}
			if (!getWorld()->isThere())
				moveTo(x, y - 1);
			break;
			
	}
}

void RegularProtestor::switchDirection(int direction)
{
	switch (direction)
	{
	case 0:
		setDirection(left);
		break;
	case 1:
		setDirection(right);
		break;
	case 2:
		setDirection(up);
		break;
	case 3:
		setDirection(down);
		break;
	}
}


void RegularProtestor::returnHome()
{

}

RegularProtestor::~RegularProtestor()
{

}



////////////////////////////////////////////////////////////// HARDCORE PROTESTOR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HardcoreProtestor::HardcoreProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : RegularProtestor(p, imageID, startX, startY, dir, size, depth)
{
	setHealth(20);
}


void HardcoreProtestor::doSomething()
{

}


HardcoreProtestor::~HardcoreProtestor()
{

}
